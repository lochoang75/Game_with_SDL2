#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game_manage.h"
#include "game_enum.h"
#include "texture_manager.h"
#define MAX_FRUIT (10)
#define NUM_TREES (3)
void load_all_texture(SDL_Renderer *pRenderer)
{
    TextureManager::get_instance()->load_texture(eTEXTURE_APPLE, "resources/apple.png", pRenderer);
    TextureManager::get_instance()->load_texture(eTEXTURE_TREE_FORM_1, "resources/tree_1.png", pRenderer);
    TextureManager::get_instance()->load_texture(eTEXTURE_TREE_FORM_2, "resources/tree_2.png", pRenderer);
    TextureManager::get_instance()->load_texture(eTEXTURE_TREE_FORM_3, "resources/tree_3.png", pRenderer);
    TextureManager::get_instance()->load_texture(eTEXTURE_BACKGROUND, "resources/background.png", pRenderer);
}

int main(int argc, char *argv[])
{
    Game::get_instance()->init("Fruit Picking", 0, 0, SDL_WINDOW_SHOWN);
    load_all_texture(Game::get_instance()->get_renderer());

    return 0;
}