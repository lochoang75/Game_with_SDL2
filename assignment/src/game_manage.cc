#include "game_manage.h"

#include <SDL2/SDL.h>

#include "game_constant.h"
#include "game_enum.h"
#include "game_object_factory.h"
#include "fruit.h"
#include "tree.h"

Game *Game::mInstance = NULL;


Game *Game::get_instance()
{
    if (mInstance == NULL)
    {
        mInstance = new Game();
    }
    return mInstance;
}

bool Game::init( const char *title, int xpos, int ypos, int flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    mWindow = SDL_CreateWindow(title, xpos, ypos, SCREEN_WIDTH, SCREEEN_HEIGHT, flags);
    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    GameObjectFactory::Instance()->creator_register(FRUIT_OBJECT, new FruitCreator());
    GameObjectFactory::Instance()->creator_register(TREE_OBJECT, new TreeCreator());
    return 0;
}

void Game::update()
{

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
    SDL_RenderPresent(mRenderer);
}

SDL_Renderer* Game::get_renderer()
{
    return mRenderer;
}



