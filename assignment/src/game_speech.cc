#include "game_speech.h"
#include "texture_manager.h"
#include "game_font_manage.h"
#define SUPPORTED_NUMBER (11)

GameAnswer:: GameAnswer(const GameAnswer &answer)
{
    answerText = answer.answerText;
    answerNumText = answer.answerNumText;
    answerNumber = answer.answerNumber;
    textR = answer.textR;
    textG = answer.textG;
    textB = answer.textB;
    textA = answer.textA;
}

GameAnswer::GameAnswer(const wchar_t *text, const wchar_t *numText, uint8_t answer_num, uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    answerText = text;
    answerNumText = numText;
    answerNumber = answer_num;
    textR = R;
    textG = G;
    textB = B;
    textA = A;
}

void GameAnswer::operator=(const GameAnswer &other)
{
    answerText = other.answerText;
    answerNumText = other.answerNumText;
    answerNumber = other.answerNumber;
    textR = other.textR;
    textG = other.textG;
    textB = other.textB;
    textA = other.textA;
}

GameCharacterSpeech:: GameCharacterSpeech(const wchar_t *question, int answerValue)
{
    mAnswerArray.push_back(answerValue);
    isQuestion = true;
    mSpeech = question;
    mTextColor = { 0, 0, 0, 255};
    isRendered = false;
}

GameCharacterSpeech:: GameCharacterSpeech(): mSpeech(NULL), isQuestion(false)
{
    mTextColor = { 0, 0, 0, 255};
    isRendered = false;
}

GameCharacterSpeech::GameCharacterSpeech(const wchar_t *simpleSpeech): mSpeech(simpleSpeech), isQuestion(false)
{
    mTextColor = { 0, 0, 0, 255};
    isRendered = false;
}


GameCharacterSpeech::GameCharacterSpeech(const wchar_t *otherSpeech, bool isQuestion): mSpeech(otherSpeech), isQuestion(isQuestion)
{
    mTextColor = { 0, 0, 0, 255};
    isRendered = false;
}


GameCharacterSpeech:: ~GameCharacterSpeech()
{
    clear_all_answers();
}

void GameCharacterSpeech:: set_speech_text(const wchar_t *speech)
{
    mSpeech = speech;
}

void GameCharacterSpeech::set_rendered_flag(bool flag)
{
    isRendered = flag;
}

ErrorCode_t GameCharacterSpeech:: append_answer(int answerValue)
{
    if (isQuestion)
    {
        mAnswerArray.push_back(answerValue);
        return kSUCCESS;
    }

    return kFAILED;
}

static GameAnswer lanswer_array[SUPPORTED_NUMBER] = 
{
    {L"không", L"0", 0, 125, 125, 125, 125},
    {L"một", L"1", 1, 125, 125, 125, 125},
    {L"hai", L"2", 2, 125, 125, 125, 125},
    {L"ba", L"3", 3, 125, 125, 125, 125},
    {L"bốn", L"4", 4, 125, 125, 125, 125},
    {L"năm", L"5", 5, 125, 125, 125, 125},
    {L"sáu", L"6", 6, 125, 125, 125, 125},
    {L"bảy", L"7", 7, 125, 125, 125, 125},
    {L"tám", L"8", 8, 125, 125, 125, 125},
    {L"chín", L"9", 9, 125, 125, 125, 125},
    {L"mười", L"10", 10,  125, 125, 125, 125}
};

static const GameAnswer* get_answer_by_index(int id)
{
    if (id > SUPPORTED_NUMBER)
    {
        LogDebug("Number %d is not supported yet, created it", id);
        return &lanswer_array[0];
    }

    return &lanswer_array[id];
}

int GameCharacterSpeech:: get_answer(const GameAnswer** &answerArray)
{
    std::vector<int>::iterator it;
    answerArray = new const GameAnswer* [mAnswerArray.size()];
    int i = 0;
    for (it = mAnswerArray.begin(); it != mAnswerArray.end(); it ++)
    {
        answerArray[i] = get_answer_by_index((*it));
        i++;
    }

    return i;
}

GameCharacterSpeechSet::GameCharacterSpeechSet()
{
    mReapeat = false;
    mCount = 0;
    mCurrentIdx = 0;
    mCompleted = false;
}

void GameCharacterSpeechSet:: append_new_speech(GameCharacterSpeech* new_speech)
{
    mSpeechSet.push_back(new_speech);
    mCount++;
}

void GameCharacterSpeechSet:: append_new_speech(GameCharacterSpeech *newSpeechList, int len)
{
    for (int i = 0; i < len; i++)
    {
        append_new_speech(&newSpeechList[i]);
    }
}

bool GameCharacterSpeechSet::is_completed()
{
    // if (mCurrentIdx == mCount)
    // {
    //     if(mSpeechSet[mCurrentIdx - 1]->is_rendered())
    //     {
    //         mCompleted = true;
    //     }
    // }
    return mCompleted;
}

GameCharacterSpeech* GameCharacterSpeechSet::get_next_speech()
{
    if (mCurrentIdx == mCount)
    {
        if (mReapeat)
        {
            mCurrentIdx = 0;
        } 
        else
        {
            mCompleted = true;
            return NULL;
        }
    }
    GameCharacterSpeech *new_speech = mSpeechSet[mCurrentIdx];
    mCurrentIdx++;

    return new_speech;
}

void GameCharacterSpeechSet:: set_index(int index)
{
    if (index < mCount)
    {
        LogError("Index reseting to %d", index);
        mCurrentIdx = index;
        mCompleted = false;
    }
    else
    {
        LogError("Indexing error, cannot set frame to invalid number");
    }
}

void GameCharacterSpeechSet:: set_repeat(bool repeat)
{
    mReapeat = repeat;
}
