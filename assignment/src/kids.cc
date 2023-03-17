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
    load_left_turn_animation();
    load_right_turn_animation();
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
        {"water_1", 217, 0, 78, 94},
        {"water_2", 296, 174, 41, 85},
    };

    AnimationPool::add_animation_for_new_state(sprite_sheet, 2, false);
}

void KidAnimationPool::load_left_turn_animation()
{
    AnimationFrame sprite_sheet[1] = 
    {
        {"left_1",296,87,39,86},
    };
    AnimationPool::add_animation_for_new_state(sprite_sheet, 1, true);

}

void KidAnimationPool::load_right_turn_animation()
{
    AnimationFrame sprite_sheet[1] = 
    {
        {"right_1",0,289,39,85},
    };
    AnimationPool::add_animation_for_new_state(sprite_sheet, 1, true);
}

static void init_introduce_speech(GameCharacterSpeechSet &speech_set)
{
    GameCharacterSpeech *speech_array = new GameCharacterSpeech[2];
    if (speech_array == NULL)
    {
        LogError("Unable to allocate memory for speech phrase");
        return;
    }

    speech_array[0].set_speech_text(L"Chào bạn");
    speech_array[1].set_speech_text(L"Bạn có thấy cây táo to bên cạnh không, nó là của mình.");
    speech_set.append_new_speech(speech_array, 2);
}

static void init_water_tree_speech(GameCharacterSpeechSet &speech_set)
{
    GameCharacterSpeech *speech_array = new GameCharacterSpeech();
    if (speech_array == NULL)
    {
        LogError("Unable to allocate memory for speech phrase");
        return;
    }
    speech_array[0].set_speech_text(L"Mình sẽ tưới cho cây một chút nước, bạn chờ mình chút nhé !");
    speech_set.append_new_speech(speech_array, 1);
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
    speech_array[1].set_speech_text(L"Trên cây có thật là nhiều táo ...");
    speech_array[2].set_speech_text(L"Một hai ba...");
    speech_set.append_new_speech(speech_array, 3);
}

static void init_question_speech(GameCharacterSpeechSet &speechSet, enum eKidActionState question_number)
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

    if (question == NULL)
    {
        LogError("Invalid argument or can't allocate memory for %d", question_number);
        return;
    }

    question->append_answer(3);
    question->append_answer(5);
    question->append_answer(6);
    question->append_answer(7);
    question->append_answer(8);
    question->append_answer(9);
    question->append_answer(10);
    speechSet.append_new_speech(question);
}

static void init_answer_speech(GameCharacterSpeechSet &speechSet, bool isCorrent)
{
    GameCharacterSpeech *speech = NULL;
    if (isCorrent == false)
    {
        speech = new GameCharacterSpeech(L"Bạn trả lời không đùng rồi, mình cùng thử lại nhé !", false);
    } else {
        speech = new GameCharacterSpeech(L"Bạn thật xuất sắc, câu trả lời chính xác", false);
    }
    speechSet.append_new_speech(speech);
}

static void init_trash_talk_speech(GameCharacterSpeechSet &speech_set)
{
    GameCharacterSpeech *speech_array = new GameCharacterSpeech[10];
    if (speech_array == NULL)
    {
        LogError("Unable to allocate memory for speech phrase");
        return;
    }

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

static void init_wait_speech(GameCharacterSpeechSet &speechSet)
{
    GameCharacterSpeech *speech = new GameCharacterSpeech(L"Chim đang bay lại ăn táo của mình ....", false);
    if (speech == NULL)
    {
        LogError("Unable to allocate memory for speech");
        return;
    }
    speechSet.append_new_speech(speech);
}

void KidObject:: init_character_speech()
{
    init_trash_talk_speech(mSpeechSet[eKID_ACTION_TRASH_TALK]);
    init_introduce_speech(mSpeechSet[eKID_ACTION_INTRODUCE]);
    init_water_tree_speech(mSpeechSet[eKID_ACTION_GOTO_TREE]);
    init_plan_tree_speech(mSpeechSet[eKID_ACTION_PLANT_TREE]);
    init_question_speech(mSpeechSet[eKID_ACTION_ASK_QUESTION_1], eKID_ACTION_ASK_QUESTION_1);
    init_question_speech(mSpeechSet[eKID_ACTION_ASK_QUESTION_2], eKID_ACTION_ASK_QUESTION_2);
    init_wait_speech(mSpeechSet[eKID_ACTION_WAIT]);
    init_question_speech(mSpeechSet[eKID_ACTION_ASK_QUESTION_3], eKID_ACTION_ASK_QUESTION_3);
    init_answer_speech(mSpeechSet[eKID_ACTION_WRONG_ANSWER], false);
    init_answer_speech(mSpeechSet[eKID_ACTION_CORRECT_ANSWER], true);
}

void KidObject:: set_new_state(enum eKidActionState newState)
{
    LogDebug("Action state changed from %d to %d", mActionState, newState);
    mPreState = mActionState;
    mActionState = newState;
    mSpeechSet[mActionState].set_index(0);
}

void KidObject:: set_animation_state(enum eKidAnimationState newState)
{
    mFrameIdx = mFrameIdx * (int)(mAnimationState == newState);
    mAnimationState = newState;
}

KidObject:: KidObject(): SDLGameObject(eKID_OBJECT)
{
    set_animation_state(eKID_STAND);
    mActionState = eKID_ACTION_INTRODUCE;
    mFrameIdx = 0;
    mAnimation = AnimationManage::Instance()->get_animation(eKID_OBJECT);
    mFrame = mAnimation->get_frame(mAnimationState, mFrameIdx);
    init_character_speech();
    mSpeech = mSpeechSet[mActionState].get_next_speech();
    mPendingEvent = 0;
}

ErrorCode_t KidObject:: create_object_body()
{
    LogDebug("Get body definition for object %s", DBG_ObjectType(mType));
    b2BodyDef body_def;
    float body_x, body_y;
    Box2DPhysicalFacade::compute_cartesian_origin(x, y, mWidth, mHeight, body_x, body_y);

    body_def.type = b2_dynamicBody;
    body_def.position.Set(body_x, body_y);
    body_def.userData.pointer = reinterpret_cast<uintptr_t> (this);
    mBody = Box2DPhysicalFacade::create_body(body_def);
    if (mBody == NULL)
    {
        return kNO_MEM;
    }

    return kSUCCESS;
}

ErrorCode_t KidObject::create_object_fixture()
{
    LogDebug("Get fixture definition for object %s", DBG_ObjectType(mType));
    b2FixtureDef fixture_def;
    b2PolygonShape shape;
    float w_plat = Box2DPhysicalFacade::compute_distance_to_meter(mWidth);
    float h_plat = Box2DPhysicalFacade::compute_distance_to_meter(mHeight); 
    shape.SetAsBox(w_plat/2, h_plat/2);
    fixture_def.shape = &shape;
    fixture_def.density = 1.0;
    fixture_def.friction = 0.3;
    fixture_def.restitution = 0.2;
    fixture_def.filter.categoryBits = kKID;
    fixture_def.filter.maskBits = kTREE | kGROUND;
    Box2DPhysicalFacade::create_fixture(mBody, fixture_def);
    return kSUCCESS;
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

    if (mSpeech != NULL && !mSpeech->is_rendered())
    {
        LogDebug("set question at address %p", mSpeech);
        GameQuestionBubble::Instance()->set_render_text(mSpeech);
        mSpeech->set_rendered_flag(true);
    }
    return;
}

void KidObject::update()
{
    // LogDebug("Frame get update for state %d frame id %d", mAnimationState, mFrameIdx);
    if (mUpdateCounter >= 3)
    {
        mFrame = mAnimation->get_frame(mAnimationState, mFrameIdx);
        mUpdateCounter = 0;
    }
    mUpdateCounter++;

    GameAnswer user_answer;
    switch (mActionState)
    {
    case eKID_ACTION_INTRODUCE:
        if (mPendingEvent & eGAME_EVENT_MOUSE_DONW)
        {
            mSpeech = mSpeechSet[mActionState].get_next_speech();
            if (mSpeech == NULL)
            {
                set_animation_state(eKID_MOVE_LEFT);
                set_new_state(eKID_ACTION_GOTO_TREE);
            }
        }
        break;
    case eKID_ACTION_GOTO_TREE:
        mSpeech = mSpeechSet[mActionState].get_next_speech();
        if (mPendingEvent & eGAME_EVENT_CONTACT_TARGET)
        {
            set_animation_state(eKID_WATER_TREE);
            Box2DPhysicalFacade::set_velocity(mBody, 0.0f, 0.0f);
            set_new_state(eKID_ACTION_PLANT_TREE);
        } else
        {
            Box2DPhysicalFacade::set_velocity(mBody, -1.0f, 0.0f);
        }
        break;

    case eKID_ACTION_PLANT_TREE:
        if (!mAnimation->is_completed(mAnimationState, mFrameIdx))
        {
            break;
        }
        if (mPendingEvent &eGAME_EVENT_MOUSE_DONW)
        {
            mSpeech = mSpeechSet[mActionState].get_next_speech();
            if (mSpeech == NULL)
            {
                set_new_state(eKID_ACTION_ASK_QUESTION_1);;
                set_animation_state(eKID_STAND);
            }
        }
        break;

    case eKID_ACTION_ASK_QUESTION_1:
        mSpeech = mSpeechSet[mActionState].get_next_speech();
        if (mPreState == eKID_ACTION_WRONG_ANSWER && mSpeech != NULL)
        {
            mSpeech->set_rendered_flag(false);
        }
        if (mSpeech != NULL)
        {
            LogDebug("get question at address %p", mSpeech);
        }

        if (GameQuestionBubble::Instance()->get_user_answer(user_answer))
        {
            LogDebug("User answer is %d", user_answer.answerNumber);
            if (user_answer.answerNumber == 10)
            {
                set_new_state(eKID_ACTION_CORRECT_ANSWER);
            } else
            {
                set_new_state(eKID_ACTION_WRONG_ANSWER);
            }
        }
        /* Perform get answer and compare here*/
        break;
    case eKID_ACTION_ASK_QUESTION_2:
        mSpeech = mSpeechSet[mActionState].get_next_speech();
        if (mPreState == eKID_ACTION_WRONG_ANSWER && mSpeech != NULL)
        {
            mSpeech->set_rendered_flag(false);
        }

        if (GameQuestionBubble::Instance()->get_user_answer(user_answer))
        {
            LogDebug("User answer is %d", user_answer.answerNumber);
            if (user_answer.answerNumber == 3)
            {
                set_new_state(eKID_ACTION_CORRECT_ANSWER);
            } else
            {
                set_new_state(eKID_ACTION_WRONG_ANSWER);
            }
        }
        break;
    case eKID_ACTION_WAIT:
        mSpeech = mSpeechSet[mActionState].get_next_speech();
        if (mPendingEvent & eGAME_EVENT_ALL_BIRD_OUT)
        {
            set_animation_state(eKID_STAND);
            set_new_state(eKID_ACTION_ASK_QUESTION_3);
        }         
        /* Perform get answer and compare here*/
        break;
    case eKID_ACTION_ASK_QUESTION_3:
        mSpeech = mSpeechSet[mActionState].get_next_speech();
        set_animation_state(eKID_STAND);
        if (mPreState == eKID_ACTION_WRONG_ANSWER && mSpeech != NULL)
        {
            mSpeech->set_rendered_flag(false);
        }
        if (GameQuestionBubble::Instance()->get_user_answer(user_answer))
        {
            LogDebug("User answer is %d", user_answer.answerNumber);
            if (user_answer.answerNumber == Game::Instance()->get_number_fruit_on_the_tree())
            {
                set_new_state(eKID_ACTION_CORRECT_ANSWER);
            } else
            {
                set_new_state(eKID_ACTION_WRONG_ANSWER);
            }
        }
        /* Perform get answer and compare here*/
        break;
    case eKID_ACTION_CORRECT_ANSWER:
        GameQuestionBubble::Instance()->clear_user_answer();
        mSpeech = mSpeechSet[mActionState].get_next_speech();
        if (mSpeech != NULL)
        {
            mSpeech->set_rendered_flag(false);
        }
        if (mPendingEvent & eGAME_EVENT_MOUSE_DONW)
        {
            if (mSpeech == NULL)
            {
                if (mPreState == eKID_ACTION_ASK_QUESTION_1)
                {
                    set_new_state(eKID_ACTION_ASK_QUESTION_2);
                }
                else if (mPreState == eKID_ACTION_ASK_QUESTION_2)
                {
                    set_new_state(eKID_ACTION_WAIT);
                } else if (mPreState == eKID_ACTION_ASK_QUESTION_3)
                {
                    set_new_state(eKID_ACTION_TRASH_TALK);
                } 
            } else 
            {
                mSpeech->set_rendered_flag(false);
            }
        }
        break;
    case eKID_ACTION_WRONG_ANSWER:
        GameQuestionBubble::Instance()->clear_user_answer();
        mSpeech = mSpeechSet[mActionState].get_next_speech();
        if (mSpeech != NULL)
        {
            mSpeech->set_rendered_flag(false);
        }
        if (mPendingEvent & eGAME_EVENT_MOUSE_DONW)
        {
            if (mSpeech == NULL)
            {
                set_new_state(mPreState);
            }
            else
            {
                mSpeech->set_rendered_flag(false);
            }
        }
        break;
    default:
        break;
    }

    /* clear all event*/
    mPendingEvent = 0x00;
}



void KidObject::handle_event(int event)
{
    mPendingEvent |= event;
}

eKidActionState KidObject::get_state() const
{
    return mActionState;
}

GameObject* KidCreator::create_object() const
{
    KidObject *new_object = new KidObject();
    return (GameObject*) new_object;
}