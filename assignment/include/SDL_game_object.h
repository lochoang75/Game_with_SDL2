#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H
#include <SDL2/SDL.h>
#include "game_object.h"
#include "game_enum.h"
#include "vector_2d.h"
#include "texture_manager.h"
#include "game_manage.h"

class SDLGameObject: public GameObject
{
    public:
        SDLGameObject(): GameObject(), mPosition(0,0), mVelocity(0,0), mAcceleration(0,0){};
        SDLGameObject(enum eGameObjectType type): GameObject(type), mPosition(0,0), mVelocity(0,0), mAcceleration(0,0) {};
        virtual ~SDLGameObject(){clean_up();};
        virtual void draw() override;
        virtual void update() override;
        virtual void clean_up() override;
        void load(const LoaderParams *pParams) override;

        Vector2D *get_position() {return &mPosition;};
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum eTextureTypeList get_id() const {return id;};
    protected:
        int mWidth;
        int mHeight;
        enum eTextureTypeList id;
        Vector2D mPosition;

        Vector2D mVelocity;
        Vector2D mAcceleration;
};

#endif /* SDL_GAME_OBJECT_H*/