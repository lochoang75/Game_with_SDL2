#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640 

bool init();
bool loadMedia() { return true;};
void close();
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;

void close()
{
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
}

bool init()
{
    bool success = true;
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be create! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}

int main(int argc, char * argv[])
{
    init();
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        // Draw solid rectangle
        SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH /2, SCREEN_HEIGHT /2};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &fillRect);

        // Draw border rectange
        SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2/3, SCREEN_HEIGHT * 2/3};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(gRenderer, &outlineRect);

        // Draw blue horizontal line
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(gRenderer,0 , SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

        // Draw vertical line of yellow dots
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
        for (int i = 0; i < SCREEN_HEIGHT; i+= 4)
        {
            SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
        }

        SDL_RenderPresent(gRenderer);
    }
    close();
}

