#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <SDL2/SDL.h>
#include <iostream>

#include "log_wrapper.h"
#include "texture_wrapper.h"
#include "game_enum.h"


class TextureManager
{
    public:
        static TextureManager* Instance();
        GameTexture *get_texture(enum eTextureType id) const;
        void load_texture(enum eTextureType id, std::string path, SDL_Renderer *pRenderer);

    private:
        TextureManager(); 
        ~TextureManager();
        static TextureManager *mInstance;
        GameTexture *mTextureList;
};

#endif /*TEXTURE_MANAGER_H*/