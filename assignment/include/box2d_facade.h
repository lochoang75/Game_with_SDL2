#ifndef GAME_OBJECT_PHYS_H
#define GAME_OBJECT_PHYS_H
#include "box2d.h"
#include "loader_params.h"

class Box2DPhysicalFacade
{
    public:
        static void compute_cartesian_origin(int xP, int yP, int obWidth, int obHeight, float &xM, float &yM);
        static void compute_pixel_postion(float xM, float yM, int width, int height, int &xP, int &yP);
        static float compute_distance_to_meter(int pixelDistance);
        static b2World* get_world(){return mWorld;};
    
        static b2Body* create_body(const LoaderParams *pParams);
        static b2Body* create_body(b2BodyDef *body_def);
        static void set_velocity(b2Body *body, float x_vel, float y_vel);
        static void set_gravity_scale(b2Body *body, float scale);
        static void get_current_position(b2Body *body, float &x, float &y);
        static double get_angle(b2Body *body);
        static b2Joint *joint_object_with_distance(b2Body *body, b2Body *target, b2Vec2 position, b2Vec2 distance);

        static void destroy_body(b2Body *body);
        static void destroy_joint(b2Joint *joint);

    private:
        Box2DPhysicalFacade(){};
        ~Box2DPhysicalFacade(){};
        static void physic_paramter_load(b2Body *body, const LoaderParams *pParams);
        static b2World *mWorld;

};
#endif /*GAME_OBJECT_PHYS_H*/