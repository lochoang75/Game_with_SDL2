#include "texture_manager.h"
TextureManager * TextureManager::mInstance = NULL;

TextureManager::TextureManager()
{
    mTextureList = new GameTexture[eTEXTURE_TOTAL];
    if (mTextureList == NULL)
    {
        LogError("Can allocate memory for texture");
    }
}

TextureManager* TextureManager:: Instance()
{
    if (mInstance == NULL)
    {
        LogInfo("Instance a texture manager");
        mInstance = new TextureManager();
    }

    return mInstance;
}

void TextureManager::load_texture(enum eTextureType id, std::string path, SDL_Renderer *pRenderer)
{
    if (id >= eTEXTURE_TOTAL)
    {
        LogError("Index %d out of range is when request texture, support index up to: %d", id, eTEXTURE_TOTAL);
        return;
    }

    LogDebug("Load texture %s for id %s", path.c_str(), DBG_TextureType(id));
    mTextureList[id].load_from_file(path, pRenderer);
}

void TextureManager::clean_up()
{
    for (int i = 0; i < eTEXTURE_TOTAL; i++)
    {
        mTextureList[i].free();
    }
}

GameTexture* TextureManager:: get_texture(enum eTextureType id) const
{
    GameTexture *game_texture = NULL;
    if (id >= eTEXTURE_TOTAL)
    {
        LogError("Index {} is out of range is when request texture", id);
    }
    else
    {
        game_texture = &mTextureList[id];
    }

    return game_texture;
}