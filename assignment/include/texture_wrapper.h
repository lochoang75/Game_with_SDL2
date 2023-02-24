#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdbool.h>

#include "log_wrapper.h"

class GameTexture
{
    public:
        GameTexture(): mTexture(NULL), mWidth(100), mHeight(100) {};
        ~GameTexture();
        bool load_from_file(std:: string path, int id, SDL_Renderer *renderer);
        void free();
        void draw(int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip);
        void draw(int x, int y, int src_x, int src_y, int width, int height, SDL_Renderer*, SDL_RendererFlip);
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

#endif /*TEXTURE_WRAPPER_H*/