#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game_manage.h"
#include "game_enum.h"
#include "texture_manager.h"
#include "box2d_facade.h"
#define MAX_FRUIT (10)
#define NUM_TREES (3)

int main()
{
    Game::Instance()->init("Fruit Picking");
    Game::Instance()->load_media();
    Game::Instance()->load_animation();
    Game::Instance()->create_object();
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
                case SDL_FINGERMOTION:
                    Game::Instance()->handle_event(eGAME_EVENT_MOUSE_MOVE);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_FINGERDOWN:
                    Game::Instance()->handle_event(eGAME_EVENT_MOUSE_DONW);
                    break;
                case SDL_MOUSEBUTTONUP:
                case SDL_FINGERUP:
                    Game::Instance()->handle_event(eGAME_EVENT_MOUSE_RELEASE);
                    break;
            }

        }

        Game::Instance()->update();
        Game::Instance()->render();
        Box2DPhysicalFacade::get_world()->Step(1.0f / 30.0f, 6.0f, 2.0f);
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(32.0f - elapsed));
    }

    return 0;
}