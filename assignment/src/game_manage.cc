#include "game_manage.h"

#include <SDL2/SDL.h>

#include "game_constant.h"
#include "game_enum.h"
#include "game_object_factory.h"
#include "fruit.h"
#include "tree.h"
#include "background.h"
#include "basket.h"

Game *Game::mInstance = NULL;


Game *Game::get_instance()
{
    if (mInstance == NULL)
    {
        mInstance = new Game();
    }
    return mInstance;
}

ErrorCode_t Game::init( const char *title, int xpos, int ypos, int flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    mWindow = SDL_CreateWindow(title, xpos, ypos, SCREEN_WIDTH, SCREEEN_HEIGHT, flags);
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

    GameObjectFactory::Instance()->creator_register(eFRUIT_OBJECT, new FruitCreator());
    GameObjectFactory::Instance()->creator_register(eTREE_OBJECT, new TreeCreator());
    GameObjectFactory::Instance()->creator_register(eBACKGROUND_OBJECT, new BackgroundCreator());
    GameObjectFactory::Instance()->creator_register(eBASKET_OBJECT, new BasketCreator());
    return kSUCCESS;
}

ErrorCode_t Game::load_media()
{
    TextureManager::Instance()->load_texture(eTEXTURE_APPLE, "resources/apple.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_TREE_FORM_1, "resources/tree_1.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_TREE_FORM_2, "resources/tree_2.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_TREE_FORM_3, "resources/tree_3.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_BACKGROUND, "resources/background.png", mRenderer);
    TextureManager::Instance()->load_texture(eTEXTURE_BASKET, "resources/basket.png", mRenderer);
    return kSUCCESS;
}

ErrorCode_t Game::create_static_object()
{
    GameObject *background = GameObjectFactory::Instance()->create_object(eBACKGROUND_OBJECT);
    if (background == NULL)
    {
        LogError("Unable to allocate memory for background object");
        return kNO_MEM;
    }
    else
    {
        LoaderParams params = LoaderParams(0, 0, 640, 480, eTEXTURE_BACKGROUND);
        background->load(&params);
        mGameObjectVector.push_back(background);
    }

    GameObject *tree_object = GameObjectFactory::Instance()->create_object(eTREE_OBJECT);
    if (tree_object == NULL)
    {
        LogError("Unable to allocate memory for tree object");
        return kNO_MEM;
    }
    else
    {
        LoaderParams params = LoaderParams(10, GROUND_POSITION - 300, 300, 300, eTEXTURE_TREE_FORM_1);
        tree_object->load(&params);
        mGameObjectVector.push_back(tree_object);
    }
    return kSUCCESS;
}

ErrorCode_t Game::create_dynamic_object()
{
    /*TODO: Change to load from json or st, that create map dynamic, instead of hardcode*/
    const int x_offset = 30;
    const int tree_base_position_x = 10 + x_offset;
    const int y_offset = 20;
    const int tree_base_position_y = GROUND_POSITION - 300 + y_offset;
    int x_fruit_offset = 0;
    int y_fruit_offset = 0;
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
            x_fruit_offset += rand() % 32 + 32;
            if (x_fruit_offset >= 200)
            {
                y_fruit_offset = y_fruit_offset + 35;
                x_fruit_offset = 0;
            }
            else
            {
                y_fruit_offset += 10;
            }
            
            int new_fruit_x_pos = tree_base_position_x + x_fruit_offset;
            int new_fruit_y_pos = tree_base_position_y + y_fruit_offset;
            LoaderParams params = LoaderParams(new_fruit_x_pos, new_fruit_y_pos, 32, 32, eTEXTURE_APPLE);
            fruit_object->load(&params);
            mGameObjectVector.push_back(fruit_object);
        }
    }

    GameObject *basket_object = GameObjectFactory::Instance()->create_object(eBASKET_OBJECT);
    if (basket_object == NULL)
    {
        LogError("Unable to allocate memory for basket object");
        return kNO_MEM;
    }
    else
    {
        LoaderParams params = LoaderParams(400, GROUND_POSITION - 75, 80, 75, eTEXTURE_BASKET);
        basket_object->load(&params);
        mGameObjectVector.push_back(basket_object);
    }
    
    return kSUCCESS;
}

ErrorCode_t Game::create_object()
{
    ErrorCode_t error = create_static_object();
    if (error == kSUCCESS)
    {
        error = create_dynamic_object();
    }

    return error;
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
                Vector2D *position = sdl_object->get_position();
                if (mouse_x >= position->getX() && mouse_x <= (position->getX() + sdl_object->get_width()))
                {
                    if (mouse_y >= position->getY() && mouse_y <= (position->getY() + sdl_object->get_height()))
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
    SDL_RenderPresent(mRenderer);
}

SDL_Renderer* Game::get_renderer()
{
    return mRenderer;
}



