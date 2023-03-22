#include "game_bubble.h"
#include "texture_manager.h"
#include "game_manage.h"
#include "game_font_manage.h"
#include "animation.h"
#include "animation_manage.h"
#include "vec2.h"

void AnswerBubbleAnimationPool::load_animation()
{
    load_bubble_normal_animation();
    load_bubble_explose_animation();
}

void AnswerBubbleAnimationPool::load_bubble_normal_animation()
{
    AnimationFrame sprite_sheet[1] =
        {
            {"normal_1", 53, 40, 50, 49},
            // {"normal_2", 122, 25, 31, 33},
            // {"normal_3", 209, 25, 33, 33},
            // {"normal_4", 296, 24, 35, 34}
        };

    AnimationPool::add_animation_for_new_state(sprite_sheet, 1, true);
}

void AnswerBubbleAnimationPool::load_bubble_explose_animation()
{
    AnimationFrame sprite_sheet[6] =
        {
            {"explose_1", 588, 34, 72, 61},
            {"explose_2", 38, 147, 71, 65},
            {"explose_3", 175, 145, 77, 70},
            {"explose_4", 310, 145, 79, 70},
            {"explose_5", 447, 144, 79, 70},
            {"explose_6", 589, 144, 73, 65}
        };

    AnimationPool::add_animation_for_new_state(sprite_sheet, 6, false);
}

GameBubble::GameBubble(enum eGameObjectType type) : GameObject(type)
{
    mBackgroundX = 0;
    mBackgroundY = 0;
    mTextOffsetX = 0;
    mTextOffsetY = 0;
    mTextTexture = NULL;
    mText = NULL;
    set_render_text(L" ");
    mTextColor = {0, 0, 0, 255};
}

void GameBubble::set_text_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    mTextColor = {red, green, blue, alpha};
}

void GameBubble::set_text_color(SDL_Color color)
{
    mTextColor = color;
}

void GameBubble::draw()
{
    draw_background();
    draw_text();
}

void GameBubble::load(const LoaderParams *pParams)
{
    mBackgroundX = pParams->get_x();
    mBackgroundY = pParams->get_y();
    mWidth = pParams->get_width();
    mHeight = pParams->get_height();
    id = pParams->get_type();
    load_animation();
}

void GameBubble::draw_text()
{
    SDL_Rect src_rect, dst_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    int x = mBackgroundX + mTextOffsetX;
    int y = mBackgroundY + mTextOffsetY;
    SDL_Renderer *p_renderer = Game::Instance()->get_renderer();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    TTF_Font *rendered_font = GameFontManage::get_font(eDEFAULT_FONT);
    SDL_Surface *text_surface = TTF_RenderUNICODE_Blended(rendered_font, mText, mTextColor);
    src_rect.w = text_surface->w;
    src_rect.h = text_surface->h;
    SDL_Point center = {0 ,SCREEN_HEIGHT};
    vec2d position = {x, y - SCREEN_HEIGHT};
    position.rotate(90);
    y = -position.y - SCREEN_HEIGHT + 2 * x;
    x = position.x - SCREEN_HEIGHT;  
    dst_rect.x = x;
    dst_rect.y = y;
    dst_rect.w = text_surface->w;
    dst_rect.h = text_surface->h; 
    if (mTextTexture != NULL)
    {
        SDL_DestroyTexture(mTextTexture);
    }
    mTextTexture = SDL_CreateTextureFromSurface(p_renderer, text_surface);
    SDL_FreeSurface(text_surface);

    SDL_RenderCopyEx(p_renderer, mTextTexture, &src_rect, &dst_rect, 90, &center, flip);
    // LogDebug("Draw bubble text complete %s", DBG_ObjectType(mType));
}

void GameBubble::draw_background()
{
    SDL_Rect src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = mWidth;
    src_rect.h = mHeight;
    SDL_Renderer *p_renderer = Game::Instance()->get_renderer();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    GameTexture *texture = TextureManager::Instance()->get_texture(id);
    if (texture == NULL)
    {
        LogError("Error occur when get texture for id %s", DBG_TextureType(id));
    }
    else
    {
        // LogDebug("Draw object %d at x: %0.4f, y: %0.4f, w: %d, height: %d", id, pos_x, pos_y, mWidth, mHeight);
        texture->draw(mBackgroundX, mBackgroundY, &src_rect, 0, p_renderer, flip);
    }
    // LogDebug("Draw background complete");
    return;
}

void GameBubble::clean_up()
{
    if (mText != NULL)
    {
        free(mText);
    }
}

void GameBubble::set_render_text(const wchar_t *text_to_show)
{
    free(mText);
    mText = (uint16_t *)calloc(wcslen(text_to_show), sizeof(wchar_t));
    if (mText == NULL)
    {
        LogError("Can't allocate memory for text");
        return;
    }
    for (size_t i = 0; i < (wcslen(text_to_show)); i++)
    {
        mText[i] = (uint16_t)text_to_show[i];
    }
}

void GameBubble::set_render_text(GameCharacterSpeech *speech)
{
    set_render_text(speech->get_speech());
    set_text_color(speech->get_speech_color());
}

void GameBubble::get_position(int &x_pos, int &y_pos) const
{
    x_pos = mBackgroundX;
    y_pos = mBackgroundY;
}

void GameBubble::get_size(int &width, int &height) const
{
    width = mWidth;
    height = mHeight;
}
GameAnswerBubble::GameAnswerBubble() : GameBubble(eWATER_BUBBLE_OBJECT)
{
    mCurrentFrame = NULL;
    mAnimation = NULL;
    mFrameIdx = 0;
    mState = eWATER_BUBBLE_HIDE;
    mTextOffsetX = 20;
    mTextOffsetY = 10;
    mFrameCounter = 0;
    mAnswerFlag = false;
    mAnswer = GameAnswer();
}

GameAnswerBubble::GameAnswerBubble(const GameAnswer &answer) : GameBubble(eWATER_BUBBLE_OBJECT), mAnswer(answer)
{
    mTextOffsetX = 8;
    mTextOffsetY = 2;
    mCurrentFrame = NULL;
    mFrameIdx = 0;
    mFrameCounter = 0;
    mAnswerFlag = false;
    mState = eWATER_BUBBLE_HIDE;
}

void GameAnswerBubble::load_animation()
{
    mAnimation = AnimationManage::Instance()->get_animation(eWATER_BUBBLE_OBJECT);
}

void GameAnswerBubble::set_position(int x, int y)
{
    this->mBackgroundX = x;
    this->mBackgroundY = y;
    LogDebug("Answer x at: %d, y at: %d", x, y);
}

void GameAnswerBubble:: animation_variable_reset()
{
    mFrameCounter = 0;
    mFrameIdx = 0;
}

void GameAnswerBubble::update()
{
    switch (mState)
    {
    case eWATER_BUBBLE_HIDE:
    case eWATER_BUBBLE_READY_TO_SHOW:
        mCurrentFrame = NULL;
        animation_variable_reset();
        break;

    case eWATER_BUBBLE_SHOW_NORMAL:
        mCurrentFrame = mAnimation->get_frame(mState, mFrameIdx);
        break;

    case eWATER_BUBBLE_SHOW_EXPLOSE:
        mCurrentFrame = mAnimation->get_frame(mState, mFrameIdx);
        if (mAnimation->is_completed(mState, mFrameIdx))
        {
            LogDebug("User is answer value: %u", mAnswer.answerNumber);
            mAnswerFlag = true;
            mState = eWATER_BUBBLE_HIDE;
        }
        break;

    default:
        /*ignore handle other state*/
        break;
    }
}

void GameAnswerBubble::handle_event(int event)
{
    enum eAnswerBubbleAnimationState preState = mState;
    switch (event)
    {
    case eBUBBLE_EVENT_CLICK_ON:
        if (mState == eWATER_BUBBLE_SHOW_NORMAL)
        {
            mState = eWATER_BUBBLE_SHOW_EXPLOSE;
        }
        break;

    case eBUBBLE_EVENT_SHOW:
        if (mState == eWATER_BUBBLE_READY_TO_SHOW)
        {
            mState = eWATER_BUBBLE_SHOW_NORMAL;
        }
        break;

    case eBUBBLE_EVENT_HIDE:
        if (mState == eWATER_BUBBLE_SHOW_NORMAL)
        {
            mState = eWATER_BUBBLE_READY_TO_SHOW;
        }
        break;

    case eBUBBLE_EVENT_ENABLE:
        mState = eWATER_BUBBLE_READY_TO_SHOW;

    default:
        /* Unhandle other, just ignore*/
        break;
    }

    if (preState != mState)
    {
        animation_variable_reset();
    }
}

void GameAnswerBubble::draw()
{
    if (mCurrentFrame == NULL)
    {
        // LogDebug("Frame is null not draw %s", DBG_ObjectType(mType));
        return;
    }
    // LogDebug("Frame will be drawing at %p",mCurrentFrame);

    draw_background();
    draw_text();
}

void GameAnswerBubble::draw_background()
{
    SDL_Rect src_rect;
    src_rect.x = mCurrentFrame->get_x();
    src_rect.y = mCurrentFrame->get_y();
    src_rect.w = mCurrentFrame->get_width();
    src_rect.h = mCurrentFrame->get_height();
    mWidth = mCurrentFrame->get_width();
    mHeight = mCurrentFrame->get_height();
    SDL_Renderer *p_renderer = Game::Instance()->get_renderer();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    GameTexture *texture = TextureManager::Instance()->get_texture(id);
    if (texture == NULL)
    {
        LogError("Error occur when get texture for id %d", id);
    }
    else
    {
        texture->draw(mBackgroundX, mBackgroundY, &src_rect, 0, p_renderer, flip);
    }
    // LogDebug("Draw background complete for Answer bubble");
    return;
}

void GameAnswerBubble::set_answer(const GameAnswer &answer)
{
    mAnswer = answer;
    set_render_text(mAnswer.answerNumText);
    mAnswerFlag = false;
}

bool GameAnswerBubble::is_user_answer(GameAnswer &answer) const
{
    if (mAnswerFlag)
    {
        answer = mAnswer;
    }
    return mAnswerFlag;
}


GameObject *GameBubbleCreator::create_object() const
{
    GameAnswerBubble *new_object = new GameAnswerBubble();
    return (GameObject *)new_object;
}

GameQuestionBubble *GameQuestionBubble::mInstance = NULL;

GameQuestionBubble::GameQuestionBubble() : GameBubble(eBUBBLE_OBJECT)
{
    mState = eQUESTION_BUBBLE_SHOW_ANSWER;
    mTextOffsetX = 45;
    mTextOffsetY = 15;
    isQuestion = false;
    mIsShow = false;
}

void GameQuestionBubble::update()
{
    switch (mState)
    {
    case eQUESTION_BUBBLE_HIDE:
        set_show_flag(false);
        hide_all_answer_bubble();
        break;

    case eQUESTION_BUBBLE_SHOW:
        hide_all_answer_bubble();
        break;

    case eQUESTION_BUBBLE_SHOW_ANSWER:
        if (isQuestion)
        {
            update_position_for_answer_bubble();
        }
        break;

    default:
        break;
    }
}

void GameQuestionBubble::update_position_for_answer_bubble()
{
    int start_x = mBackgroundX + 40;
    int start_y = mBackgroundY + 40;
    std::vector<GameAnswerBubble *>::iterator it;
    for (it = mAnsBubbleList.begin(); it != mAnsBubbleList.end(); it++)
    {
        (*it)->set_position(start_x, start_y);
        (*it)->handle_event(eBUBBLE_EVENT_SHOW);
        start_x += 80;
    }
}

void GameQuestionBubble::hide_all_answer_bubble()
{
    std::vector<GameAnswerBubble *>::iterator it;
    for (it = mAnsBubbleList.begin(); it != mAnsBubbleList.end(); it++)
    {
        (*it)->handle_event(eBUBBLE_EVENT_HIDE);
    }
}

void GameQuestionBubble::handle_event(int event)
{
    switch (event)
    {
    case eGAME_EVENT_MOUSE_DONW:
        // if (mState == eQUESTION_BUBBLE_SHOW)
        // {
        //     mState = eQUESTION_BUBBLE_SHOW_ANSWER;
        // }
        // else if (mState == eQUESTION_BUBBLE_SHOW_ANSWER)
        // {
        //     mState = eQUESTION_BUBBLE_SHOW;
        // }
        break;

    default:
        /*ignore other event*/
        break;
    }
}

void GameQuestionBubble::add_answer_bubble(GameAnswerBubble *answerBubble)
{
    mAnsBubbleList.push_back(answerBubble);
}

bool GameQuestionBubble::get_user_answer(GameAnswer &answer) const
{
    std::vector<GameAnswerBubble *>::const_iterator it;
    for (it = mAnsBubbleList.begin(); it != mAnsBubbleList.end(); it ++)
    {
        if ((*it)->is_user_answer(answer))
        {
            LogDebug("User is answered");
            return true;
        }
    }
    return false;
}

void GameQuestionBubble::clear_user_answer()
{
    std::vector<GameAnswerBubble *>::iterator it;
    for (it = mAnsBubbleList.begin(); it != mAnsBubbleList.end(); it ++)
    {
        (*it)->clear_answer_flag();
    }
    return;
}


void GameQuestionBubble::set_render_text(GameCharacterSpeech *speech)
{
    GameBubble::set_render_text(speech);

    if (speech->is_question())
    {
        LogDebug("Add answer for question bubble");
        const GameAnswer **answer_array = NULL;
        int size = speech->get_answer(answer_array);
        if (size > (uint8_t)mAnsBubbleList.size())
        {
            LogError("Number of answer is more than number of space !");
            delete answer_array;
            return;
        }
        mState = eQUESTION_BUBBLE_SHOW_ANSWER;
        isQuestion = true;
        for (int i = 0; i < size; i++)
        {
            mAnsBubbleList[i]->set_answer(*answer_array[i]);
            mAnsBubbleList[i]->handle_event(eBUBBLE_EVENT_ENABLE);
        }
    }
    else
    {
        LogDebug("Add text for normal chat");
        isQuestion = false;
        mState = eQUESTION_BUBBLE_SHOW;
    }
}

GameQuestionBubble *GameQuestionBubble::Instance()
{
    if (mInstance == NULL)
    {
        mInstance = new GameQuestionBubble();
    }

    return mInstance;
}
