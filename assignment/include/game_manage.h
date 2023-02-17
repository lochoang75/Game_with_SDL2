#ifndef APPLICATION_MANAGE_H
#define APPLICATION_MANAGE_H
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "game_object.h"

class Game
{
    public:
        static Game* get_instance();
        SDL_Renderer* get_renderer();
        bool init( const char *title, int xpos, int ypos, int flags);
        void close();

        bool load_media();
        void update();
        void clean_up();
        void render();
    
    private:
        Game(){};
        ~Game(){};
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        static Game *mInstance;
        std::vector<GameObject*> mGameObjectVector;
};

#endif /* APPLICATION_MANAGE_H */