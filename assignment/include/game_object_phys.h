#ifndef GAME_OBJECT_PHYS_H
#define GAME_OBJECT_PHYS_H
#include "box2d.h"

enum eGameObjectPhysic {
    ePHYSIC_STATIC = 0,
    ePHYSIC_DYNAMIC
};

enum ePhysicalShape {
    eCHAIN_SHAPE = 0,
    eCIRCEL_SHAPE,
    eEDGE_SHAPE,
    ePOLYGON_SHAPE
};

class GameObjectPhysicsInterface
{
    public:
        virtual void physic_paramter_load(enum ePhysicalShape shape, float *density, float friction, float restitution) = 0;
        virtual void set_velocity(float x_vel, float y_vel);

    protected:
        virtual void create_body() = 0;
        virtual int get_x() const = 0;
        virtual int get_y() const = 0;
        virtual float get_angle() const = 0;
};
#endif /*GAME_OBJECT_PHYS_H*/