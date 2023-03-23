#include "game_font_manage.h"
#include "log_wrapper.h"

TTF_Font* GameFontManage::mFontList[eTOTAL_FONTS] = {NULL};

void GameFontManage::load_new_font(enum eGameFont font_enum, const char *font_path, int font_size)
{
    if (font_enum > eTOTAL_FONTS)
    {
        LogError("font %d is not supported, it's out of range", font_enum);
        return;
    }

    if (mFontList[font_enum] != NULL)
    {
        LogWarning("You are about to override font that already load");
    }

    mFontList[font_enum] = TTF_OpenFont(font_path, font_size);
    if (mFontList[font_enum] == NULL)
    {
        LogWarning("Loaded error, can't load font %s", TTF_GetError());
    }
    LogInfo("Loaded font %s for font %s", font_path, DBG_FontType(font_enum));
    return;
}

TTF_Font* GameFontManage:: get_font(enum eGameFont font_enum)
{
    if (font_enum > eTOTAL_FONTS)
    {
        LogError("Font %d is out of range use default font", font_enum);
        return mFontList[eDEFAULT_FONT];
    }
    
    if (mFontList[font_enum] == NULL)
    {
        LogError("Font is not loaded, use default font");
        return mFontList[eDEFAULT_FONT];
    }

    return mFontList[font_enum];
}

void GameFontManage::clean_up()
{
    for (int i = 0; i < eTOTAL_FONTS; i++)
    {
        if (mFontList[i] != NULL)
        {
            TTF_CloseFont(mFontList[i]);
            mFontList[i] = NULL;
        }
    }
    TTF_Quit();
}