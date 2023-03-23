#ifndef GAME_PHYSIC_OBJECT_H
#define GAME_PHYSIC_OBJECT_H
#include "game_constant.h"
#include "box2d.h"

class GamePhysicObject
{
    public:
        GamePhysicObject(): mBody(NULL), mMass(0.0f){};
        virtual ~GamePhysicObject(){};
    protected:
        virtual ErrorCode_t create_object_body() = 0;
        virtual ErrorCode_t create_object_fixture() = 0;
        void physics_clean_up() {Box2DPhysicalFacade::destroy_body(mBody);};
        b2Body *mBody;
        float mMass;
};
#endif /*GAME_PHYSIC_OBJECT_H*/