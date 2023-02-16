#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include "SDL2/SDL.h"
#include "texture_wrapper.h"
#include "iostream"
#include "macrologger.h"
#include "game_enum.h"


class TextureManager
{
    public:
        static TextureManager* get_instance();
        GameTexture *get_texture(enum eTextureList id) const;
        void load_texture(enum eTextureList id, std::string path, SDL_Renderer *pRenderer);

    private:
        TextureManager(); 
        ~TextureManager();
        static TextureManager *mInstance;
        GameTexture *mTextureList;
};

TextureManager::TextureManager()
{
    mTextureList = new GameTexture[TOTAL_TEXTURE];
    if (mTextureList == NULL)
    {
        LOG_ERROR("Can allocate memory for texture");
    }
}

TextureManager* TextureManager:: get_instance()
{
    if (mInstance == NULL)
    {
        LOG_INFO("Instance a texture manager");
        mInstance = new TextureManager();
    }
    else
    {
        LOG_INFO("Reuse texture manager");
    }
    return mInstance;
}

void TextureManager::load_texture(enum eTextureList id, std::string path, SDL_Renderer *pRenderer)
{
    if (id >= TOTAL_TEXTURE)
    {
        LOG_ERROR("Index %d out of range is when request texture, support index up to: %d", id, TOTAL_TEXTURE - 1);
        return;
    }

    mTextureList[id].load_from_file(path, id, pRenderer);
}

GameTexture* TextureManager:: get_texture(enum eTextureList id)
{
    GameTexture *game_texture = NULL;
    if (id >= TOTAL_TEXTURE)
    {
        LOG_ERROR("Index %d is out of range is when request texture", id);
    }
    else
    {
        game_texture = &mTextureList[id];
    }

    return game_texture;
}
#endif /*TEXTURE_MANAGER_H*/