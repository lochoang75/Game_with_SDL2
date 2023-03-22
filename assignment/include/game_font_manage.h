#ifndef GAME_FONT_MANAGE_H
#define GAME_FONT_MANAGE_H
#include <SDL2/SDL_ttf.h>

enum eGameFont
{
    eDEFAULT_FONT = 0,
    eDELUXE_FONT,
    eTOTAL_FONTS
};

class GameFontManage
{
    public:
        static void load_new_font(enum eGameFont font_enum, const char* font_path, int font_size);
        static TTF_Font* get_font(enum eGameFont font_enum);

    private:
        GameFontManage(){};
        ~GameFontManage(){};
        static GameFontManage *mFontManage;
        static TTF_Font *mFontList[eTOTAL_FONTS]; 
        static bool isInstance;
};
#endif /* GAME_FONT_MANAGE_H*/