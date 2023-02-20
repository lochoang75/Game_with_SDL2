#ifndef APPLICATION_MANAGE_H
#define APPLICATION_MANAGE_H
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "game_constant.h"
#include "game_object.h"

class Game
{
    public:
        static Game* get_instance();
        SDL_Renderer* get_renderer();
        ErrorCode_t init(const char *title, int xpos, int ypos, int flags);

        ErrorCode_t load_media();
        ErrorCode_t create_object();
        void update();
        void clean_up();
        void render();
        void handle_event(enum eGameEventEnum);
        void close();
    
    private:
        Game(){};
        ~Game(){};
        ErrorCode_t create_static_object();
        ErrorCode_t create_dynamic_object();
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        static Game *mInstance;
        std::vector<GameObject*> mGameObjectVector;
};

#endif /* APPLICATION_MANAGE_H */