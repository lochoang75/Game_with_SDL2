#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game_manage.h"
#include "texture_manager.h"
#include "game_event.h"
#include "game_touch_event_data.h"
#include "box2d_facade.h"
#define MAX_FRUIT (10)
#define NUM_TREES (3)

static void print_app_version()
{
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    SDL_Log("We compiled against SDL version %u.%u.%u ...\n",
            compiled.major, compiled.minor, compiled.patch);
    SDL_Log("But we are linking against SDL version %u.%u.%u.\n",
            linked.major, linked.minor, linked.patch);
}

int main()
{
    Game::Instance()->init("Fruit Picking");
    Game::Instance()->load_media();
    Game::Instance()->load_animation();
    Game::Instance()->load_font();
    Game::Instance()->create_object();
    SDL_Event e;
    bool quit = false;
    int x_pos, y_pos;

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
                // case SDL_MOUSEMOTION:
                // case SDL_FINGERMOTION:
                //     Game::Instance()->handle_event(eGAME_EVENT_MOUSE_MOVE);
                //     break;
                case SDL_FINGERDOWN:
                case SDL_MOUSEBUTTONDOWN:
                    // LogDebug("Position x: %d, y: %d", e.button.x, e.button.y);
                    // Game::Instance()->handle_event(eGAME_EVENT_MOUSE_DONW);
                    break;
                case SDL_MOUSEBUTTONUP:
                    // Game::Instance()->handle_event(eGAME_EVENT_MOUSE_RELEASE);
                    break;
                case SDL_USEREVENT:
                    if (e.user.code == eGAME_EVENT_TOUCH_DOWN)
                    {
                        LogDebug("Event mouse down from user event");
                        x_pos = static_cast<GameTouchEventData*>(e.user.data1)->get_x_position();
                        y_pos = static_cast<GameTouchEventData*>(e.user.data1)->get_y_position();
                        Game::Instance()->set_touch_position(x_pos, y_pos);
                        Game::Instance()->handle_event(eGAME_EVENT_TOUCH_DOWN);
                    }
                    break;

                default:
                    // LogDebug("Event with type: %d, user_code: %d", e.type, e.user.code);
                    break;
            }

        }

        Game::Instance()->update();
        Game::Instance()->render();
        Box2DPhysicalFacade::get_world()->Step(1.0f / 12.0f, 6.0f, 2.0f);
        // Uint64 end = SDL_GetPerformanceCounter();
        // float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        // SDL_Delay(floor(32.0f - elapsed));
    }

    Game::Instance()->clean_up();

    return 0;
}