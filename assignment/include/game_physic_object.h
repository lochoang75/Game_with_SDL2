#ifndef GAME_PHYSIC_OBJECT_H
#define GAME_PHYSIC_OBJECT_H
#include "game_constant.h"
#include "box2d.h"

class GamePhysicObject
{
    public:
        GamePhysicObject(): mBody(NULL){};
        virtual ~GamePhysicObject(){};
    protected:
        virtual ErrorCode_t create_object_body() = 0;
        virtual ErrorCode_t create_object_fixture() = 0;
        b2Body *mBody;
};
#endif /*GAME_PHYSIC_OBJECT_H*/