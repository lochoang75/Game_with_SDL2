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
    SDL_Rect srcRect, desRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = desRect.w = width;
    srcRect.h = desRect.h = height;
    SDL_Point center = {0 ,SCREEN_HEIGHT};
    vec2f position(x , y - SCREEN_HEIGHT);
    position.rotate(90);
    desRect.x = position.x - SCREEN_HEIGHT;  
    desRect.y = -position.y - SCREEN_HEIGHT + x;
    SDL_RenderCopyEx(pRenderer, mTexture, &srcRect, &desRect, 90, &center, flip);
}

void GameTexture::draw(int x, int y, SDL_Rect *src_rect, double angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    float scale = SCREEN_WIDTH/SCREEN_HEIGHT;
    SDL_Rect desRect;
    desRect.w = src_rect->w;
    desRect.h = src_rect->h;
    SDL_Point center = {0 ,SCREEN_HEIGHT};
    vec2f position(x, y - SCREEN_HEIGHT);
    position.rotate(90);
    desRect.x = position.x - SCREEN_HEIGHT;  
    desRect.y = -position.y - SCREEN_HEIGHT + 2*x;
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
