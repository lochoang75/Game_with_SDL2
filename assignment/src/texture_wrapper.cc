#include "texture_wrapper.h"

GameTexture::~GameTexture()
{
    free();
}

void GameTexture::free()
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
    SDL_RenderCopyEx(pRenderer, mTexture, &srcRect, &destRect, 0, NULL, flip);
}

void GameTexture::draw(int x, int y, SDL_Rect *src_rect, double angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect desRect;
    desRect.w = src_rect->w;
    desRect.h = src_rect->h;
    desRect.x = x;
    desRect.y = y;
    SDL_RenderCopyEx(pRenderer, mTexture, src_rect, &desRect, angle, NULL, flip);
}

int GameTexture:: get_width()
{
    return mWidth;
}

int GameTexture:: get_height()
{
    return mHeight;
}

bool GameTexture:: load_from_file(std::string path, SDL_Renderer *pRenderer)
{
    free();

    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        LogError("SDL image error on load image %s, IMG error: %s", path.c_str(), IMG_GetError());
    }
    else
    {        
        mTexture = SDL_CreateTextureFromSurface(pRenderer, loaded_surface);
        if (mTexture == NULL)
        {
            LogError("SDL texture create failed, SDL error %s", SDL_GetError());
        }

        SDL_FreeSurface(loaded_surface);
    }

    return mTexture == NULL;
}
