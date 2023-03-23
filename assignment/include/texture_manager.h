#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <SDL2/SDL.h>
#include <iostream>

#include "log_wrapper.h"
#include "texture_wrapper.h"

enum eTextureType
{
    eTEXTURE_BACKGROUND = 0,
    eTEXTURE_TREE_FORM_1 = 1,
    eTEXTURE_TREE_FORM_2 = 2,
    eTEXTURE_TREE_FORM_3 = 3,
    eTEXTURE_APPLE = 4,
    eTEXTURE_BASKET = 5,
    eTEXTURE_BIRDS = 6,
    eTEXTURE_KIDS = 7,
    eTEXTURE_BUBBLE = 8,
    eTEXTURE_SIGN = 9,
    eTEXTURE_WATER_BUBBLE = 10,
    eTEXTURE_TOTAL
};

class TextureManager
{
    public:
        static TextureManager* Instance();
        GameTexture *get_texture(enum eTextureType id) const;
        void load_texture(enum eTextureType id, std::string path, SDL_Renderer *pRenderer);
        void clean_up();
    private:
        TextureManager(); 
        ~TextureManager();
        static TextureManager *mInstance;
        GameTexture *mTextureList;
};

#endif /*TEXTURE_MANAGER_H*/