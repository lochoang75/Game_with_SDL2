#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game_manage.h"
#include "texture_manager.h"
#define MAX_FRUIT (10)
#define NUM_TREES (3)


int main(int argc, char *argv[])
{
    Game::get_instance()->init("Fruit Picking", 0, 0, SDL_WINDOW_SHOWN);
    return 0;
}