#include "game_manage.h"

#include <SDL2/SDL.h>

#include "game_constant.h"
#include "game_enum.h"
#include "game_object_factory.h"
#include "fruit.h"
#include "tree.h"
#include "bird.h"
#include "kids.h"
#include "background.h"
#include "basket.h"
#include "animation_manage.h"
#include "game_contact_listener.h"
#include "box2d.h"

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
    mContactListener.InitContactHandler();
    return ret;
}

b2EdgeShape ground_shape;

void Game::physics_init()
{
    b2BodyDef ground_body_def;
    ground_body_def.type = b2_staticBody;
    ground_body_def.position.Set(0.0f, 0.0f);
    ground_body_def.angle = 0;
    mGroundBody = Box2DPhysicalFacade::create_body(ground_body_def);
    float x_ground = Box2DPhysicalFacade::compute_distance_to_meter(SCREEN_WIDTH);
    float y_ground = Box2DPhysicalFacade::compute_distance_to_meter(GROUND_POSITION - 100);
    b2Vec2 ground_start(-x_ground/2, y_ground/2);
    b2Vec2 ground_end(x_ground/2, y_ground/2);
    ground_shape.SetTwoSided(ground_start, ground_end);
    b2FixtureDef ground_fixture_def;
    ground_fixture_def.shape = &ground_shape;
    ground_fixture_def.density = 1.0f;
    ground_fixture_def.filter.categoryBits = kGROUND;
    Box2DPhysicalFacade::create_fixture(mGroundBody, ground_fixture_def);
    Box2DPhysicalFacade::get_world()->SetContactListener(&mContactListener);
}

ErrorCode_t Game::sdl_component_init(const char *title, int xpos, int ypos, int flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    mWindow = SDL_CreateWindow(title, xpos, ypos, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
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
}

ErrorCode_t Game::load_media()
{
    TextureManager::Instance()->load_texture(eTEXTURE_APPLE, "resources/apple.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_TREE_FORM_1, "resources/tree_1.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_TREE_FORM_2, "resources/tree_2.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_TREE_FORM_3, "resources/tree_3.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_BACKGROUND, "resources/background.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_BASKET, "resources/basket.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_BIRDS, "resources/birds.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_KIDS, "resources/kids.png", mRenderer);
    return kSUCCESS;
}

ErrorCode_t Game::load_animation()
{
    AnimationManage::Instance()->animation_register(eBIRD_OBJECT, new BirdAnimationPool());
    AnimationManage::Instance()->animation_register(eKID_OBJECT, new KidAnimationPool());
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
        LoaderParams params = LoaderParams(10, GROUND_POSITION - 300, 300, 300, eTEXTURE_TREE_FORM_1);
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
    for (int i = 0; i < 10; i++)
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
            static_cast<TreeObject*>(tree)->get_tree_anchor_point(fruit_x, fruit_y);
            LoaderParams params = LoaderParams(fruit_x - 10, fruit_y - 10, 32, 32, eTEXTURE_APPLE);
            fruit_object->load(&params);
            mGameObjectVector.push_back(fruit_object);
            static_cast<TreeObject*>(tree)->joint_new_object((FruitObject*) fruit_object);
            LogDebug("Create fruit %d success", i);
        }
    }
    return kSUCCESS;
}

    // GameObject *basket_object = GameObjectFactory::Instance()->create_object(eBASKET_OBJECT);
    // if (basket_object == NULL)
    // {
    //     LogError("Unable to allocate memory for basket object");
    //     return kNO_MEM;
    // }
    // else
    // {
    //     LoaderParams params = LoaderParams(400, GROUND_POSITION - 75, 80, 75, eTEXTURE_BASKET);
    //     params.add_physical_density(1.0f);
    //     params.add_physical_friction(0.3f);
    //     params.add_physical_restitution(0.3f);
    //     basket_object->load(&params);
    //     params.add_physical_object_type(ePHYSIC_DYNAMIC);
    //     mGameObjectVector.push_back(basket_object);
    //     LogDebug("Create basket success");
    // }

ErrorCode_t Game::_create_bird_object()
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
            LoaderParams params = LoaderParams(600 + i * 100, 150 + i * 50, 32, 32, eTEXTURE_BIRDS);
            bird_object->load(&params);
            mGameObjectVector.push_back(bird_object);
            LogDebug("Create bird success");
        }
    }

    return kSUCCESS;
}

    // GameObject *kid_object = GameObjectFactory::Instance()->create_object(eKID_OBJECT);
    // if (kid_object == NULL)
    // {
    //     LogError("Unable to allocate memory for kid object");
    // } 
    // else
    // {
    //     LoaderParams params = LoaderParams(0, 0, 32, 32, eTEXTURE_KIDS);
    //     params.add_physical_object_type(ePHYSIC_DYNAMIC);
    //     kid_object->load(&params);
    //     mGameObjectVector.push_back(kid_object);
    //     LogDebug("Create kid success");
    // }

ErrorCode_t Game::create_object()
{
    GameObject *tree_object = NULL;
    _create_background_object();
    _create_tree_object(tree_object);
    _create_fruit_object(tree_object);
    _create_bird_object();
    return kSUCCESS;
}

void Game::update()
{ 
    for (std::vector<GameObject*>::iterator object = mGameObjectVector.begin(); object != mGameObjectVector.end(); object ++)
    {
        SDLGameObject *sdl_object = (SDLGameObject*)*object;
        sdl_object->update();
    }

}

void Game::handle_event(enum eGameEventEnum event)
{

    if (event == eGAME_EVENT_MOUSE_DONW)
    {
        int mouse_x, mouse_y;
        int i = 0;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        for (std::vector<GameObject*>::iterator object = mGameObjectVector.begin(); object != mGameObjectVector.end(); object ++)
        {
            SDLGameObject *sdl_object = (SDLGameObject*)*object;
            if (sdl_object->get_object_type() == eFRUIT_OBJECT)
            {
                int obj_x, obj_y;
                sdl_object->get_position(obj_x, obj_y);
                if (mouse_x >= obj_x && mouse_x <= (obj_x + sdl_object->get_width()))
                {
                    if (mouse_y >= obj_y && mouse_y <= (obj_y + sdl_object->get_height()))
                    {
                        FruitObject* fruit = (FruitObject*) *object;
                        fruit->handle_event(event);
                        break;
                    }
                }
            }
            i++;
        }
    } 
    else
    {
        for (std::vector<GameObject*>::iterator object = mGameObjectVector.begin(); object != mGameObjectVector.end(); object ++)
        {
            SDLGameObject *sdl_object = (SDLGameObject*)*object;
            if (sdl_object->get_object_type() == eFRUIT_OBJECT)
            {
                FruitObject* fruit = (FruitObject*) sdl_object;
                fruit->handle_event(event);
            }
        }

    }
}

void Game:: clean_up()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game:: render()
{
    SDL_RenderClear(mRenderer);
    for (std::vector<GameObject*>::iterator object = mGameObjectVector.begin(); object != mGameObjectVector.end(); object++)
    {
        SDLGameObject* sdl_object = (SDLGameObject*) *object;
        sdl_object->draw();
    }
    SDL_RenderDrawLine(mRenderer, ((SCALED_WIDTH / 2.0f) + ground_shape.m_vertex1.x) * MET2PIX, ((SCALED_HEIGHT / 2.0f) + ground_shape.m_vertex1.y) * MET2PIX, ((SCALED_WIDTH / 2.0f) + ground_shape.m_vertex2.x) * MET2PIX, ((SCALED_HEIGHT / 2.0f) + ground_shape.m_vertex2.y) * MET2PIX);

    SDL_RenderPresent(mRenderer);
}

SDL_Renderer* Game::get_renderer()
{
    return mRenderer;
}



