#ifndef APPLICATION_MANAGE_H
#define APPLICATION_MANAGE_H
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "game_constant.h"
#include "game_object.h"
#include "box2d.h"

class Game
{
    public:
        static Game* Instance();
        SDL_Renderer* get_renderer();
        b2World *get_world();
        ErrorCode_t init(const char *title);

        ErrorCode_t load_media();
        ErrorCode_t load_animation();
        ErrorCode_t create_object();
        void update();
        void clean_up();
        void render();
        void handle_event(enum eGameEventEnum);
        void close();
    
    private:
        Game();
        ~Game(){};
        ErrorCode_t create_static_object();
        ErrorCode_t create_dynamic_object();
        void creator_register();
        ErrorCode_t sdl_component_init(const char *title, int xpos, int ypos, int flags);
        void physics_init();
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        static Game *mInstance;
        b2World *mWorld;
        b2Body *mGroundBody;
        std::vector<GameObject*> mGameObjectVector;
};

#endif /* APPLICATION_MANAGE_H */