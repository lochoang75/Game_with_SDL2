#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game_manage.h"
#include "game_enum.h"
#include "texture_manager.h"
#define MAX_FRUIT (10)
#define NUM_TREES (3)

int main(int argc, char *argv[])
{
    Game::get_instance()->init("Fruit Picking", 0, 0, SDL_WINDOW_SHOWN);
    Game::get_instance()->load_media();
    Game::get_instance()->load_animation();
    Game::get_instance()->create_object();
    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        Uint64 start = SDL_GetPerformanceCounter();
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
                continue;
            }

            switch (e.type)
            {
                case SDL_MOUSEMOTION:
                    Game::get_instance()->handle_event(eGAME_EVENT_MOUSE_MOVE);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Game::get_instance()->handle_event(eGAME_EVENT_MOUSE_DONW);
                    break;
                case SDL_MOUSEBUTTONUP:
                    Game::get_instance()->handle_event(eGAME_EVENT_MOUSE_RELEASE);
                    break;
            }

        }

        Game::get_instance()->update();
        Game::get_instance()->render();
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(16.666f - elapsed));
    }

    return 0;
}