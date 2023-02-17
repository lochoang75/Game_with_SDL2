#include "texture_manager.h"
TextureManager * TextureManager::mInstance = NULL;

TextureManager::TextureManager()
{
    mTextureList = new GameTexture[TOTAL_TEXTURE];
    if (mTextureList == NULL)
    {
        spdlog::error("Can allocate memory for texture");
    }
}

TextureManager* TextureManager:: get_instance()
{
    if (mInstance == NULL)
    {
        spdlog::info("Instance a texture manager");
        mInstance = new TextureManager();
    }
    else
    {
        spdlog::info("Reuse texture manager");
    }
    return mInstance;
}

void TextureManager::load_texture(enum eTextureTypeList id, std::string path, SDL_Renderer *pRenderer)
{
    if (id >= TOTAL_TEXTURE)
    {
        spdlog::error("Index %d out of range is when request texture, support index up to: %d", id, TOTAL_TEXTURE - 1);
        return;
    }

    mTextureList[id].load_from_file(path, id, pRenderer);
}

GameTexture* TextureManager:: get_texture(enum eTextureTypeList id) const
{
    GameTexture *game_texture = NULL;
    if (id >= TOTAL_TEXTURE)
    {
        spdlog::error("Index %d is out of range is when request texture", id);
    }
    else
    {
        game_texture = &mTextureList[id];
    }

    return game_texture;
}