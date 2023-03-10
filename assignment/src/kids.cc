#include "kids.h"
#include "game_speech.h"
#include "game_bubble.h"
#include "log_wrapper.h"

KidAnimationPool::KidAnimationPool():AnimationPool()
{
    load_animation();
}

void KidAnimationPool::load_animation()
{
    load_stand_animation();
    load_right_move_animation();
    load_left_move_animation();
    load_water_tree_animation();
}

void KidAnimationPool::load_stand_animation()
{
    AnimationFrame sprite_sheet[1] = 
    {
        {"stand_1",296,174,41,85},
    };
    AnimationPool::add_animation_for_new_state(sprite_sheet,1, false);
}

void KidAnimationPool::load_right_move_animation()
{
    AnimationFrame sprite_sheet[3] = 
    {
        {"right_1",0,289,39,85},
        {"right_2",84,289,42,83},
        {"right_3",177,205,45,80}
    };
    AnimationPool::add_animation_for_new_state(sprite_sheet, 3, true);
}

void KidAnimationPool::load_left_move_animation()
{
    AnimationFrame sprite_sheet[3] = 
    {
        {"left_1",296,87,39,86},
        {"left_2",40,289,43,83},
        {"left_3",248,289,46,80}
    };
    AnimationPool::add_animation_for_new_state(sprite_sheet, 3, true);
}

void KidAnimationPool::load_water_tree_animation()
{
    AnimationFrame sprite_sheet[2] =
    {
        {"water_1", 217, 95, 78, 94},
        {"water_2",0,289,39,85},
    };

    AnimationPool::add_animation_for_new_state(sprite_sheet, 2, true);
}

static void init_introduce_speech(GameCharacterSpeechSet &speech_set)
{
    GameCharacterSpeech *speech_array = new GameCharacterSpeech[3];
    if (speech_array == NULL)
    {
        LogError("Unable to allocate memory for speech phrase");
        return;
    }

    speech_array[0].set_speech_text(L"Chào bạn");
    speech_array[1].set_speech_text(L"Bạn có thấy cây táo to bên cạnh không, nó là của ông mình.");
    speech_array[2].set_speech_text(L"Mình sẽ tưới cho cây một chút nước, bạn chờ mình chút nhé !");
    speech_set.append_new_speech(speech_array, 3);
}

static void init_plan_tree_speech(GameCharacterSpeechSet &speech_set)
{
    GameCharacterSpeech *speech_array = new GameCharacterSpeech[3];
    if (speech_array == NULL)
    {
        LogError("Unable to allocate memory for speech phrase");
        return;
    }
    speech_array[0].set_speech_text(L"Woww");
    speech_array[1].set_speech_text(L"Những trái táo đang dần xuất hiện ... ");
    speech_array[2].set_speech_text(L"Một hai ba...");
    speech_set.append_new_speech(speech_array, 3);
}

static void init_question_speech(GameCharacterSpeechSet &speech_set, enum eKidActionState question_number)
{
    GameCharacterSpeech *question = NULL; 
    if (question_number == eKID_ACTION_ASK_QUESTION_1)
    {
        question = new GameCharacterSpeech(L"Bạn có thể đếm giúp mình trên cây có bao nhiêu quả táo không ?", true);
    } else if (question_number == eKID_ACTION_ASK_QUESTION_2)
    {
        question = new GameCharacterSpeech(L"Mình muốn chia táo cho chim, bạn giúp mình đếm số chim nhé ?", true);
    } else if (question_number == eKID_ACTION_ASK_QUESTION_3)
    {
        question = new GameCharacterSpeech(L"Mình còn lại bao nhiêu quả táo trên cây nhỉ ?", true);
    }

    question->append_answer(3);
    question->append_answer(5);
    question->append_answer(6);
    question->append_answer(7);
    question->append_answer(8);
    question->append_answer(9);
    question->append_answer(10);
    speech_set.append_new_speech(question);
}

static void init_trash_talk_speech(GameCharacterSpeechSet &speech_set)
{
    GameCharacterSpeech *speech_array = new GameCharacterSpeech[10];

    speech_array[0].set_speech_text(L"Mot");
    speech_array[1].set_speech_text(L"Hai");
    speech_array[2].set_speech_text(L"Ba");
    speech_array[3].set_speech_text(L"Bon");
    speech_array[4].set_speech_text(L"Nam");
    speech_array[5].set_speech_text(L"Sau");
    speech_array[6].set_speech_text(L"Bay");
    speech_array[7].set_speech_text(L"Tam");
    speech_array[8].set_speech_text(L"Chin");
    speech_array[9].set_speech_text(L"Muoi");

    speech_set.append_new_speech(speech_array, 10);
}

void KidObject:: init_character_speech()
{
    init_trash_talk_speech(mSpeechSet[eKID_ACTION_TRASH_TALK]);
    init_introduce_speech(mSpeechSet[eKID_ACTION_INTRODUCE]);
    init_plan_tree_speech(mSpeechSet[eKID_ACTION_PLAN_TREE]);
    init_question_speech(mSpeechSet[eKID_ACTION_ASK_QUESTION_1], eKID_ACTION_ASK_QUESTION_1);
    init_question_speech(mSpeechSet[eKID_ACTION_ASK_QUESTION_2], eKID_ACTION_ASK_QUESTION_2);
    init_question_speech(mSpeechSet[eKID_ACTION_ASK_QUESTION_3], eKID_ACTION_ASK_QUESTION_3);
}

KidObject:: KidObject(): SDLGameObject(eKID_OBJECT)
{
    mAnimationState = eKID_STAND;
    mActionState = eKID_ACTION_TRASH_TALK;
    mFrameIdx = 0;
    mAnimation = AnimationManage::Instance()->get_animation(eKID_OBJECT);
    mFrame = mAnimation->get_frame(mAnimationState, mFrameIdx);
    init_character_speech();
}

void KidObject:: draw()
{
    double angle = Box2DPhysicalFacade::get_angle(mBody);
    float pos_x, pos_y;
    Box2DPhysicalFacade::get_current_position(mBody, pos_x, pos_y);
    Box2DPhysicalFacade::compute_pixel_postion(pos_x, pos_y, mWidth, mHeight, x, y);
    SDL_Rect src_rect;
    src_rect.x = mFrame->get_x();
    src_rect.y = mFrame->get_y();
    src_rect.w = mFrame->get_width();
    src_rect.h = mFrame->get_height();
    SDL_Renderer *p_renderer = Game::Instance()->get_renderer();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    GameTexture *texture = TextureManager::Instance()->get_texture(id);
    if (texture == NULL)
    {
        LogError("Error occur when get texture for id %d", id);
    }
    else
    {
        texture->draw(x, y, &src_rect, angle, p_renderer, flip);
    }
    return;
}

void KidObject::update()
{
    mUpdateCounter++;
    if (mUpdateCounter == 7)
    {
        mFrame = mAnimation->get_frame(mAnimationState, mFrameIdx);
        SDLGameObject::update();

        GameCharacterSpeech *next_speech = mSpeechSet[eKID_ACTION_ASK_QUESTION_1].get_next_speech();
        GameQuestionBubble::Instance()->set_render_text(next_speech);
        mUpdateCounter = 0;
    }

}

GameObject* KidCreator::create_object() const
{
    KidObject *new_object = new KidObject();
    return (GameObject*) new_object;
}