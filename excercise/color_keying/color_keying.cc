#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class LTexture
{
    public:
        LTexture();
        ~LTexture();
        bool load_from_file(std::string path);
        void free();
        void render(int x, int y);
        int get_width();
        int get_height();
    private:
        SDL_Texture *mTexture;
        int mWidth;
        int mHeight;
};

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

LTexture gFooTexture;
LTexture gBackgroundTexture;

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::load_from_file(std::string path)
{
    free();

    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture:: free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture:: render(int x, int y)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture:: get_width()
{
    return mWidth;
}

int LTexture:: get_height()
{
    return mHeight;
}

bool init()
{
    bool success = true;
    gWindow = SDL_CreateWindow("Color keying", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Unable to create windows, SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL)
        {
            printf ("Could not create renderder, SDL_Error %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    if (!gFooTexture.load_from_file("resource/foo.png"))
    {
        printf("Failed to load Foo' texture image\n");
        success = false;
    }

    if (!gBackgroundTexture.load_from_file("resource/background.png"))
    {
        printf("Failed to load background texture image\n");
        success = false;
    }

    return success;
}

void close()
{
    gFooTexture.free();
    gBackgroundTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    bool quit = false;
    SDL_Event e;
    init();
    loadMedia();
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

        gBackgroundTexture.render(0,0);
        gFooTexture.render(240, 190);
        SDL_RenderPresent(gRenderer);
    }
}