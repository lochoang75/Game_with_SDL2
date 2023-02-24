#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H
#include <SDL2/SDL.h>
#include "game_object.h"
#include "game_enum.h"
#include "texture_manager.h"
#include "game_manage.h"
#include "box2d.h"
#include "game_object_phys.h"

class SDLGameObject: public GameObject, public GameObjectPhysicsInterface
{
    public:
        SDLGameObject(): GameObject(), x(0), y(0), mWidth(0), mHeight(0), mBody(NULL){};
        SDLGameObject(enum eGameObjectType type): GameObject(type), x(0), y(0), mWidth(0), mHeight(0), mBody(NULL){};
        virtual ~SDLGameObject(){clean_up();};
        virtual void draw() override;
        virtual void update() override;
        virtual void clean_up() override;
        virtual void load(const LoaderParams *pParams) override;
        void physic_paramter_load(enum ePhysicalShape shape, float density, float friction, float restitution) override;


        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum eTextureTypeList get_id() const {return id;};
    protected:
        void create_body() override;
        int get_x() const override;
        int get_y() const override;
        float get_angle() const override;

        int mWidth;
        int mHeight;
        int x;
        int y;
        b2Body *mBody;
        enum eTextureTypeList id;
};

#endif /* SDL_GAME_OBJECT_H*/