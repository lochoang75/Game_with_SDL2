#ifndef APPLICATION_MANAGE_H
#define APPLICATION_MANAGE_H
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "game_constant.h"
#include "game_object.h"
#include "game_contact_listener.h"
#include "box2d.h"

class Game
{
    public:
        static Game* Instance();
        SDL_Renderer* get_renderer();
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
        void creator_register();
        ErrorCode_t sdl_component_init(const char *title, int xpos, int ypos, int flags);
        void physics_init();
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        static Game *mInstance;
        b2Body *mGroundBody;
        GameContactListener mContactListener;
        std::vector<GameObject*> mGameObjectVector;

        ErrorCode_t _create_background_object();
        ErrorCode_t _create_tree_object(GameObject *&tree);
        ErrorCode_t _create_bird_object();
        ErrorCode_t _create_fruit_object(GameObject *tree);
        ErrorCode_t _create_kid_object();
};

#endif /* APPLICATION_MANAGE_H */