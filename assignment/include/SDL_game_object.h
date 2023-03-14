#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H
#include <SDL2/SDL.h>
#include "game_object.h"
#include "game_enum.h"
#include "texture_manager.h"
#include "game_manage.h"
#include "box2d_facade.h"
#include "game_physic_object.h"

class SDLGameObject: public GameObject, public GamePhysicObject
{
    public:
        SDLGameObject(): GameObject(), GamePhysicObject(), x(0), y(0), mWidth(0), mHeight(0){};
        SDLGameObject(enum eGameObjectType type): GameObject(type), GamePhysicObject(), x(0), y(0), mWidth(0), mHeight(0){};
        virtual ~SDLGameObject(){clean_up();};
        virtual void draw() override;
        virtual void update() override;
        virtual void clean_up() override;
        virtual void load(const LoaderParams *pParams) override;
        virtual void handle_event(int event) override {(void)event;};

        virtual void get_position(int &x, int &y) const override;
        virtual void get_size(int &width, int &height) const override;
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum eTextureType get_id() const {return id;};
    protected:

        virtual ErrorCode_t create_object_body() override;
        virtual ErrorCode_t create_object_fixture() override;

        int x;
        int y;
        int mWidth;
        int mHeight;
        enum eTextureType id;
};

#endif /* SDL_GAME_OBJECT_H*/