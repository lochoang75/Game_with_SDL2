#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H
#include <SDL2/SDL.h>
#include <iostream>
#include <stdbool.h>

class BaseTexture
{
    public:
        BaseTexture(): mTexture(NULL), mWidth(100), mHeight(100) {};
        BaseTexture(SDL_Renderer *renderer): mRenderer(renderer), mWidth(100), mHeight(100) {};
        virtual ~BaseTexture();
        virtual bool load_from_file(std:: string path) = 0;
        virtual void free();
        int get_width();
        int get_height();
        void set_renderer(SDL_Renderer *renderer);
        SDL_Renderer* get_renderer();

    protected:
        SDL_Texture *mTexture;
        SDL_Renderer *mRenderer;
        int mWidth;
        int mHeight;
};

BaseTexture::~BaseTexture()
{
    free();
}

void BaseTexture:: set_renderer(SDL_Renderer *renderer)
{
    mRenderer = renderer;
}

SDL_Renderer* BaseTexture:: get_renderer()
{
    return mRenderer;
}

void BaseTexture:: free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mHeight = 0;
        mWidth = 0;
    }
}

int BaseTexture:: get_width()
{
    return mWidth;
}

int BaseTexture:: get_height()
{
    return mHeight;
}

#endif /*TEXTURE_WRAPPER_H*/