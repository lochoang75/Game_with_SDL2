#ifndef APPLICATION_MANAGE_H
#define APPLICATION_MANAGE_H
#include <SDL2/SDL.h>
#include <iostream>
#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480 

class ApplicationManageBase
{
    public:
        ApplicationManageBase();
        virtual ~ApplicationManageBase();

        bool init(const char *window_title, uint32_t flags=SDL_RENDERER_ACCELERATED);
        virtual void close();

        virtual int start_event_loop() = 0;
        virtual bool load_media() =  0;
        virtual bool init_resource_loading() = 0;
    protected:
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
};

ApplicationManageBase::ApplicationManageBase()
{
    mWindow = NULL;
    mRenderer = NULL;
}

ApplicationManageBase::~ApplicationManageBase()
{
    close();
}

bool ApplicationManageBase:: init(const char *window_title, uint32_t flags)
{
    bool success = true;
    SDL_Window *window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Unable to create window, SDL_Error %s\n",SDL_GetError());
        success = false;
    }
    else
    {
        mWindow = window;
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, flags);
        if (renderer == NULL)
        {
            printf("Unable to create renderer, SDL_Error %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            mRenderer = renderer;
            success = init_resource_loading();
        }
    }
    
    return success;
}

void ApplicationManageBase::close()
{
    SDL_DestroyRenderer(mRenderer);
    mRenderer = NULL;

    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
}

#endif /* APPLICATION_MANAGE_H */