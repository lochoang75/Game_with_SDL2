#ifndef GAME_SPEECH_H
#define GAME_SPEECH_H
#include <vector>
#include <wchar.h>

#include "SDL2/SDL.h"
#include "game_constant.h"

class GameAnswer
{
    public:
        GameAnswer(){};
        GameAnswer(const GameAnswer &asnwer);
        GameAnswer(const wchar_t *text, int answer_num, int R, int G, int B, int A);
        const GameAnswer operator=(const GameAnswer&);
        const wchar_t *answerText;
        uint8_t answerNumber;
        uint8_t textR;
        uint8_t textG;
        uint8_t textB;
        uint8_t textA;
};


class GameCharacterSpeech
{
    public:
        GameCharacterSpeech();
        GameCharacterSpeech(const wchar_t *simpleSpeech);
        GameCharacterSpeech(const wchar_t *otherSpeech, bool isQuestion);
        GameCharacterSpeech(const wchar_t *question, int answerValue);
        ~GameCharacterSpeech();
        ErrorCode_t append_answer(int answerValue);
        int get_answer(const GameAnswer** &answerArray);
        void clear_all_answers() {mAnswerArray.clear();}
        void set_speech_color(SDL_Color &color) {mTextColor = color;};
        void set_speech_text(const wchar_t *speech);
        SDL_Color get_speech_color() const {return mTextColor;};
        const wchar_t* get_speech() const {return mSpeech;};
        bool is_question() const {return isQuestion;};
    private:
        std::vector<int> mAnswerArray;
        const wchar_t *mSpeech;
        bool isQuestion;
        SDL_Color mTextColor;
};

class GameCharacterSpeechSet
{
    public:
        GameCharacterSpeechSet();
        ~GameCharacterSpeechSet(){};
        void append_new_speech(GameCharacterSpeech *singleSpeech);
        void append_new_speech(GameCharacterSpeech *speechList, int len);
        void set_index(int index);
        void set_repeat(bool repeat);
        GameCharacterSpeech *get_next_speech();

    private:
        std::vector<GameCharacterSpeech*> mSpeechSet;
        bool mReapeat;
        uint8_t mCount;
        uint8_t mCurrentIdx;
};

#endif /*GAME_SPEECH_BUBBLE_H*/