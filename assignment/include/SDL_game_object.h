#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H
#include "game_object.h"
#include "game_enum.h"

class SDLGameObject: GameObject
{
    public:
        SDLGameObject(): GameObject(){};
        virtual ~SDLGameObject();
        virtual void draw();
        virtual void update();
        virtual void clean_up();

        int get_x() const {return x;};
        int get_y() const {return y;};
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum eTextureList get_id() const {return id;};
    protected:
        int x;
        int y;
        int mWidth;
        int mHeight;
        enum eTextureList id;
};
#endif /* SDL_GAME_OBJECT_H*/