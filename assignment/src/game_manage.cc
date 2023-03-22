#include "game_manage.h"

#include <SDL2/SDL.h>

#include "game_constant.h"
#include "game_macros.h"
#include "game_object_factory.h"
#include "fruit.h"
#include "tree.h"
#include "bird.h"
#include "kids.h"
#include "background.h"
#include "basket.h"
#include "game_bubble.h"
#include "animation_manage.h"
#include "road_sign.h"
#include "game_contact_listener.h"
#include "game_font_manage.h"
#include "game_event.h"
#include "game_touch_event_data.h"
#include "game_touch_event_impl.h"

#include "box2d.h"
#include "vec2.h"

Game *Game::mInstance = NULL;

Game *Game::Instance()
{
    if (mInstance == NULL)
    {
        mInstance = new Game();
    }
    return mInstance;
}

Game::Game()
{
    mWindow = NULL;
    mRenderer = NULL;
    mTimerID = 0;
}

ErrorCode_t Game::init(const char *title)
{
    ErrorCode_t ret = sdl_component_init(title, 0, 0, SDL_WINDOW_SHOWN);
    if (ret != kSUCCESS)
    {
        return ret;
    }

    physics_init();
    creator_register();
    event_init();
    mContactListener.InitContactHandler();
    timer_init();
    return ret;
}

void Game::physics_init()
{
    b2BodyDef ground_body_def;
    ground_body_def.type = b2_staticBody;
    ground_body_def.position.Set(0.0f, 0.0f);
    ground_body_def.angle = 0;
    mGroundBody = Box2DPhysicalFacade::create_body(ground_body_def);
    float x_ground = Box2DPhysicalFacade::compute_distance_to_meter(SCREEN_WIDTH);
    float y_ground = Box2DPhysicalFacade::compute_distance_to_meter(GROUND_POSITION - 100);
    b2Vec2 ground_start(-x_ground / 2, y_ground / 2);
    b2Vec2 ground_end(x_ground / 2, y_ground / 2);
    b2EdgeShape ground_shape;
    ground_shape.SetTwoSided(ground_start, ground_end);
    b2FixtureDef ground_fixture_def;
    ground_fixture_def.shape = &ground_shape;
    ground_fixture_def.density = 1.0f;
    ground_fixture_def.filter.categoryBits = kGROUND;
    Box2DPhysicalFacade::create_fixture(mGroundBody, ground_fixture_def);
    Box2DPhysicalFacade::get_world()->SetContactListener(&mContactListener);
}

void Game::event_init()
{
    GameEventInput *touch_event = new GameTouchEventInput();
    if (touch_event == NULL)
    {
        LogError("Unable to allocate memory for touch_event");
        return;
    }

    touch_event->input_init();
    touch_event->event_register();
    touch_event->start_event_poll();
}

Uint32 periodict_timer_callback(Uint32 interval, void* name);

void Game::timer_init()
{
    mTimerID = SDL_AddTimer(2000, periodict_timer_callback, (void*)Game::Instance());
}

ErrorCode_t Game::sdl_component_init(const char *title, int xpos, int ypos, int flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    mWindow = SDL_CreateWindow(title, xpos, ypos, SCREEN_HEIGHT, SCREEN_WIDTH, flags);
    if (mWindow == NULL)
    {
        LogError("Unable to create windows, SDL Error: %s", SDL_GetError());
        return kFAILED;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if (mRenderer == NULL)
    {
        LogError("Unable to create renderer, SDL Error: %s", SDL_GetError());
        return kFAILED;
    }

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        LogError("SDL image could not initialize! SDL image error: %s\n", IMG_GetError());
    }

    if (TTF_Init())
    {
        LogError("SDL image could not initialize! SDL image error: %s\n", TTF_GetError());
    }

    return kSUCCESS;
}

void Game::creator_register()
{
    GameObjectFactory::Instance()->creator_register(eFRUIT_OBJECT, new FruitCreator());
    GameObjectFactory::Instance()->creator_register(eTREE_OBJECT, new TreeCreator());
    GameObjectFactory::Instance()->creator_register(eBACKGROUND_OBJECT, new BackgroundCreator());
    GameObjectFactory::Instance()->creator_register(eBASKET_OBJECT, new BasketCreator());
    GameObjectFactory::Instance()->creator_register(eBIRD_OBJECT, new BirdCreator());
    GameObjectFactory::Instance()->creator_register(eKID_OBJECT, new KidCreator());
    GameObjectFactory::Instance()->creator_register(eSIGN_OBJECT, new SignCreator());
    GameObjectFactory::Instance()->creator_register(eWATER_BUBBLE_OBJECT, new GameBubbleCreator());
}

ErrorCode_t Game::load_media()
{
    TextureManager::Instance()->load_texture(eTEXTURE_APPLE, IMG_RESOURCES_PATH("apple.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_TREE_FORM_1, IMG_RESOURCES_PATH("tree_1.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_TREE_FORM_2, IMG_RESOURCES_PATH("tree_2.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_TREE_FORM_3, IMG_RESOURCES_PATH("tree_3.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_BACKGROUND, IMG_RESOURCES_PATH("background.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_BASKET, IMG_RESOURCES_PATH("basket.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_BIRDS, IMG_RESOURCES_PATH("birds.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_KIDS, IMG_RESOURCES_PATH("farmers.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_BUBBLE, IMG_RESOURCES_PATH("chat_box.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_SIGN, IMG_RESOURCES_PATH("sign.png"), mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_WATER_BUBBLE, IMG_RESOURCES_PATH("water_bubble.png"), mRenderer);
    return kSUCCESS;
}

ErrorCode_t Game::load_animation()
{
    AnimationManage::Instance()->animation_register(eBIRD_OBJECT, new BirdAnimationPool());
    AnimationManage::Instance()->animation_register(eKID_OBJECT, new KidAnimationPool());
    AnimationManage::Instance()->animation_register(eWATER_BUBBLE_OBJECT, new AnswerBubbleAnimationPool());
    return kSUCCESS;
}

ErrorCode_t Game::load_font()
{
    // GameFontManage::load_new_font(eDEFAULT_FONT, "fonts/Arial.ttf", 18);
    GameFontManage::load_new_font(eDEFAULT_FONT, FONT_RESOURCES_PATH("dlxfont.ttf"), 18);
    return kSUCCESS;
}

ErrorCode_t Game::_create_background_object()
{
    GameObject *background = GameObjectFactory::Instance()->create_object(eBACKGROUND_OBJECT);
    if (background == NULL)
    {
        LogError("Unable to allocate memory for background object");
        return kNO_MEM;
    }
    else
    {
        LoaderParams params = LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, eTEXTURE_BACKGROUND);
        params.add_physical_fixture(false);
        background->load(&params);
        mGameObjectVector.push_back(background);
        LogDebug("Create background sucess ");
    }
    return kSUCCESS;
}

ErrorCode_t Game::_create_tree_object(GameObject *&tree)
{
    tree = GameObjectFactory::Instance()->create_object(eTREE_OBJECT);
    if (tree == NULL)
    {
        LogError("Unable to allocate memory for tree object");
        return kNO_MEM;
    }
    else
    {
        LoaderParams params = LoaderParams(20, GROUND_POSITION - 300, 300, 300, eTEXTURE_TREE_FORM_1);
        tree->load(&params);
        mGameObjectVector.push_back(tree);
        LogDebug("Create tree success");
    }
    return kSUCCESS;
}

ErrorCode_t Game::_create_fruit_object(GameObject *tree)
{
    /*TODO: Change to load from json or st, that create map dynamic, instead of hardcode*/
    srand(time(NULL));
    for (int i = 0; i < 5; i++)
    {
        GameObject *fruit_object = GameObjectFactory::Instance()->create_object(eFRUIT_OBJECT);
        if (fruit_object == NULL)
        {
            LogError("Unable to allocate memory for fruit object");
            return kNO_MEM;
        }
        else
        {
            int fruit_x = 0;
            int fruit_y = 0;
            static_cast<TreeObject *>(tree)->get_tree_anchor_point(fruit_x, fruit_y);
            LoaderParams params = LoaderParams(fruit_x - 10, fruit_y - 10, 25, 24, eTEXTURE_APPLE);
            fruit_object->load(&params);
            mGameObjectVector.push_back(fruit_object);
            static_cast<TreeObject *>(tree)->joint_new_object((FruitObject *)fruit_object);
            LogDebug("Create fruit %d success", i);
        }
    }
    return kSUCCESS;
}

ErrorCode_t Game::_create_bird_object(GameObject *roadSign)
{
    for (int i = 0; i < 3; i++)
    {
        GameObject *bird_object = GameObjectFactory::Instance()->create_object(eBIRD_OBJECT);
        if (bird_object == NULL)
        {
            LogError("Unable to allocate memory for bird object");
        }
        else
        {
            int sign_x = static_cast<RoadSign *>(roadSign)->get_x_position();
            int sign_y = static_cast<RoadSign *>(roadSign)->get_y_position();
            LoaderParams params = LoaderParams(sign_x + i * 20, sign_y, 32, 32, eTEXTURE_BIRDS);
            bird_object->load(&params);
            mGameObjectVector.push_back(bird_object);
            LogDebug("Create bird success");
        }
    }

    return kSUCCESS;
}

ErrorCode_t Game::_create_kid_object()
{
    GameObject *kid_object = GameObjectFactory::Instance()->create_object(eKID_OBJECT);
    if (kid_object == NULL)
    {
        LogError("Unable to allocate memory for kid object");
        return kNO_MEM;
    }
    else
    {
        LoaderParams params = LoaderParams(700, GROUND_POSITION - 80, 46, 90, eTEXTURE_KIDS);
        kid_object->load(&params);
        mGameObjectVector.push_back(kid_object);
        LogDebug("Create kid success");
    }
    return kSUCCESS;
}

ErrorCode_t Game::_create_road_sign(GameObject *&signObject)
{
    signObject = GameObjectFactory::Instance()->create_object(eSIGN_OBJECT);
    if (signObject == NULL)
    {
        LogError("Unable to allocate memory for sign object");
        return kNO_MEM;
    }
    else
    {
        LoaderParams params = LoaderParams(SCREEN_WIDTH - 77, GROUND_POSITION - 94, 77, 94, eTEXTURE_SIGN);
        signObject->load(&params);
        mGameObjectVector.push_back(signObject);
        LogDebug("Create sign success");
    }
    return kSUCCESS;
}

ErrorCode_t Game::_create_chat_box(GameObject *&chatBox)
{
    chatBox = GameQuestionBubble::Instance();
    if (chatBox == NULL)
    {
        LogError("Unable to allocate memory for chat box object");
        return kNO_MEM;
    }
    else
    {
        LoaderParams params = LoaderParams(0, GROUND_POSITION, SCREEN_WIDTH, SCREEN_HEIGHT - GROUND_POSITION, eTEXTURE_BUBBLE);
        chatBox->load(&params);
        mGameObjectVector.push_back(chatBox);
        LogDebug("Create chat box successful");
    }
    return kSUCCESS;
}

ErrorCode_t Game::_create_answer_bubble(GameObject *pParent)
{
    for (int i = 0; i < 5; i++)
    {
        GameObject *new_bubble = GameObjectFactory::Instance()->create_object(eWATER_BUBBLE_OBJECT);
        if (new_bubble == NULL)
        {
            LogError("Unable to allocate memory for water bubble object");
            return kNO_MEM;
        }
        else
        {
            LoaderParams params = LoaderParams(0, 0, 0, 0, eTEXTURE_WATER_BUBBLE);
            new_bubble->load(&params);
            static_cast<GameQuestionBubble *>(pParent)->add_answer_bubble((GameAnswerBubble *)new_bubble);
            mGameObjectVector.push_back(new_bubble);
        }
    }

    LogDebug("Create water bubble successful");
    return kSUCCESS;
}

ErrorCode_t Game::create_object()
{
    GameObject *tree_object = NULL;
    GameObject *sign_object = NULL;
    GameObject *chat_box = NULL;
    _create_background_object();
    _create_road_sign(sign_object);
    _create_tree_object(tree_object);
    _create_fruit_object(tree_object);
    _create_kid_object();
    _create_bird_object(sign_object);
    _create_chat_box(chat_box);
    _create_answer_bubble(chat_box);
    return kSUCCESS;
}

int Game::get_number_fruit_on_the_tree()
{
    uint8_t fruit_on_the_tree = 0;
    for (std::vector<GameObject *>::iterator object = mGameObjectVector.begin(); object != mGameObjectVector.end(); object++)
    {
        if ((*object)->get_object_type() == eFRUIT_OBJECT)
        {
            if (static_cast<FruitObject*>(*object)->get_state() == eFRUIT_ON_THE_TREE)
            {
                fruit_on_the_tree ++;
            }
        }
    }
    return fruit_on_the_tree;
}

void Game::update()
{
    // LogDebug("###### Updating #######");
    for (std::vector<GameObject *>::iterator object = mGameObjectVector.begin(); object != mGameObjectVector.end(); object++)
    {
        (*object)->update();
    }
}

void Game::set_touch_position(int &x, int &y)
{
    touch_x = x;
    touch_y = y;
}

double degreesToRadians(double degrees)
{
    return degrees * M_PI / 180;
}

void Game::handle_event(enum eGameEventEnum event)
{
    LogDebug("Mouse position befoer rotate x: %d, y: %d", touch_x, touch_y);
    vec2d position = {touch_x, touch_y - SCREEN_HEIGHT};
    position.rotate(-90);
    touch_x = position.x + SCREEN_HEIGHT;
    touch_y = position.y + SCREEN_HEIGHT;
    LogDebug("Mouse position after rotate x: %d, y: %d", touch_x, touch_y);
    for (std::vector<GameObject *>::iterator object = mGameObjectVector.begin(); object != mGameObjectVector.end(); object++)
    {
        int obj_x, obj_y, obj_w, obj_h;
        (*object)->get_position(obj_x, obj_y);
        (*object)->get_size(obj_w, obj_h);
        if (touch_x < (obj_x - 10) || touch_x > (obj_x + obj_w + 10))
        {
            /*horizontal postion out of object*/
            continue;
        }

        if (touch_y < (obj_y - 10) || touch_y > (obj_y + obj_h + 10))
        {
            /*vertical postion out of object*/
            continue;
        }

        LogDebug("Mouse down event on object %s pos: x: %d, y: %d, w: %d, h: %d", DBG_ObjectType((*object)->get_object_type()), obj_x, obj_y, obj_w, obj_h);
        (*object)->handle_event(eGAME_EVENT_MOUSE_DONW);
    }
    // else
    // {
    //     for (std::vector<GameObject *>::iterator object = mGameObjectVector.begin(); object != mGameObjectVector.end(); object++)
    //     {
    //         SDLGameObject *sdl_object = (SDLGameObject *)*object;
    //         if (sdl_object->get_object_type() == eFRUIT_OBJECT)
    //         {
    //             FruitObject *fruit = (FruitObject *)sdl_object;
    //             fruit->handle_event(event)e
    //         }
    //     }
    // }
}

void Game::clean_up()
{
    SDL_RemoveTimer(mTimerID);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::render()
{
    // LogDebug("###### Rendering #######");
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(mRenderer);
    for (std::vector<GameObject *>::iterator object = mGameObjectVector.begin(); object != mGameObjectVector.end(); object++)
    {
        // LogDebug("Render of object %s", DBG_ObjectType((*object)->get_object_type()));
        (*object)->draw();
    }

    SDL_RenderPresent(mRenderer);
    // LogDebug("###### Render Completed #######");
}

SDL_Renderer *Game::get_renderer()
{
    return mRenderer;
}

Uint32 periodict_timer_callback(Uint32 interval, void* name)
{
    bool kick_the_bird = false;
    int bird_escape = 0;
    int fruits_on_the_tree = 0;
    KidObject* kid = NULL;
    eBirdState preState = eBIRD_ESCAPE;
    for (std::vector<GameObject *>::iterator object = static_cast<Game*>(name)->mGameObjectVector.begin(); 
        object != static_cast<Game*>(name)->mGameObjectVector.end(); object++)
    {
        if ((*object)->get_object_type() == eKID_OBJECT)
        {
            kid = (KidObject*)(*object);
            eKidActionState state = kid->get_state();
            if (state == eKID_ACTION_WAIT)
            {
                kick_the_bird = true;
            } else
            {
                (*object)->handle_event(eGAME_EVENT_MOUSE_DONW);
            }
        }

        if ((*object)->get_object_type() == eBIRD_OBJECT)
        {
            eBirdState state = static_cast<BirdObject*>(*object)->get_bird_state();
            if (state == eBIRD_STAND)
            {
                if (preState != eBIRD_ESCAPE)
                {
                    break;
                }
                if (kick_the_bird)
                {
                    LogDebug("Bird will fly after this");
                    static_cast<BirdObject*>(*object)->handle_event(eGAME_EVENT_BIRD_FLY);
                    break;
                }
            } else if (state == eBIRD_ESCAPE)
            {
                bird_escape++;
            } else
            {
                preState = state;
            }
        }
    }

    if (bird_escape == 3)
    {
        kid->handle_event(eGAME_EVENT_ALL_BIRD_OUT);
    }

    return interval;
}
