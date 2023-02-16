#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdbool.h>

#include "pretty_debug.h"

class GameTexture
{
    public:
        GameTexture(): mTexture(NULL), mWidth(100), mHeight(100) {};
        ~GameTexture();
        bool load_from_file(std:: string path, int id, SDL_Renderer *renderer);
        void free();
        void draw(int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip);
        int get_width();
        int get_height();
        int get_texture_id() const {return mId;};
        void set_texture_id(int id) {mId = id;};
    protected:
        int mId;
        SDL_Texture *mTexture;
        int mWidth;
        int mHeight;
};

GameTexture::~GameTexture()
{
    free();
}

void GameTexture:: free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mHeight = 0;
        mWidth = 0;
    }
}

void GameTexture:: draw(int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect, destRect;
    srcRect.x = srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, mTexture, &srcRect, &destRect, 0, 0, flip);
}

int GameTexture:: get_width()
{
    return mWidth;
}

int GameTexture:: get_height()
{
    return mHeight;
}

bool GameTexture:: load_from_file(std::string path, int id, SDL_Renderer *pRenderer)
{
    free();

    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        LOG_ERROR("SDL image error on load image %s, IMG error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {        
        mTexture = SDL_CreateTextureFromSurface(pRenderer, loaded_surface);
        if (mTexture == NULL)
        {
            LOG_ERROR("SDL texture create failed, SDL error %s\n", SDL_GetError());
        }

        SDL_FreeSurface(loaded_surface);
    }

    return mTexture == NULL;
}

#endif /*TEXTURE_WRAPPER_H*/