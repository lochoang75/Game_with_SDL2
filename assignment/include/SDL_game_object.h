#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H
#include <SDL2/SDL.h>
#include "game_object.h"
#include "game_enum.h"
#include "texture_manager.h"
#include "game_manage.h"
#include "box2d_facade.h"

class SDLGameObject: public GameObject
{
    public:
        SDLGameObject(): GameObject(), x(0), y(0), mWidth(0), mHeight(0){};
        SDLGameObject(enum eGameObjectType type): GameObject(type), x(0), y(0), mWidth(0), mHeight(0){};
        virtual ~SDLGameObject(){clean_up();};
        virtual void draw() override;
        virtual void update() override;
        virtual void clean_up() override;
        virtual void load(const LoaderParams *pParams) override;
        
        void get_position(int &x, int &y) const;
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum eTextureTypeList get_id() const {return id;};
    protected:

        int x;
        int y;
        int mWidth;
        int mHeight;
        b2Body *mBody;
        enum eTextureTypeList id;
};

#endif /* SDL_GAME_OBJECT_H*/