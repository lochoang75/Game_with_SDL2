#include "texture_wrapper.h"
#include "game_constant.h"
#include "vec2.h"

void GameTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mHeight = 0;
        mWidth = 0;
    }
}

GameTexture::~GameTexture()
{
    free();
}

void GameTexture:: draw(int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect, destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    SDL_Point center = {SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
    vec2f position(x, y);
    position.rotate(90);
    destRect.x = position.x - SCREEN_WIDTH/4 + SCREEN_WIDTH/30; 
    destRect.y = position.y + SCREEN_HEIGHT/4 + SCREEN_HEIGHT /8 ;
    SDL_RenderCopyEx(pRenderer, mTexture, &srcRect, &destRect, 90, &center, flip);
}

void GameTexture::draw(int x, int y, SDL_Rect *src_rect, double angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect desRect;
    desRect.w = src_rect->w;
    desRect.h = src_rect->h;
    SDL_Point center = {SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
    vec2f position(x, y);
    position.rotate(90);
    desRect.x = position.x - SCREEN_WIDTH/4 + SCREEN_WIDTH/30; 
    desRect.y = position.y + SCREEN_HEIGHT/4 + SCREEN_HEIGHT /8 ;
    // LogDebug("After rotation x: %d, y: %d", desRect.x, desRect.y);
    SDL_RenderCopyEx(pRenderer, mTexture, src_rect, &desRect, 90 + angle, &center, flip);
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
