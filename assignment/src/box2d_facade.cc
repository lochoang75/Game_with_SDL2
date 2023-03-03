#include "box2d_facade.h"

#include "game_constant.h"
#include "log_wrapper.h"

b2World *Box2DPhysicalFacade::mWorld = new b2World(b2Vec2(0.0f, 10.0f));

b2Body* Box2DPhysicalFacade::create_body(b2BodyDef &body_def)
{
    return mWorld->CreateBody(&body_def);
}

void Box2DPhysicalFacade::create_fixture(b2Body *body, b2FixtureDef &fixture_def)
{
    body->CreateFixture(&fixture_def);
}

void Box2DPhysicalFacade::destroy_body(b2Body *body)
{
    mWorld->DestroyBody(body);
}

void Box2DPhysicalFacade::destroy_joint(b2Joint *joint)
{
    mWorld->DestroyJoint(joint);
}

void Box2DPhysicalFacade:: get_current_position(b2Body *body, float &x, float &y)
{
    b2Vec2 position = body->GetPosition();
    x = position.x;
    y = position.y;
    // LogDebug("Box position is at %0.2f and %0.2f", position.x, position.y);
}

void Box2DPhysicalFacade:: set_velocity(b2Body *body, float x_vel, float y_vel)
{
    b2Vec2 vel(x_vel, y_vel);
    body->SetLinearVelocity(vel);
}

double Box2DPhysicalFacade:: get_angle(b2Body *body)
{
    return body->GetAngle() * RAD2DEG;
}

b2Joint* Box2DPhysicalFacade:: joint_object_with_distance(b2Body *body, b2Body *target, b2Vec2 anchorA, b2Vec2 anchorB)
{
    float hertz = 1.0f;
    float dampingRatio = 0.7f;

    b2DistanceJointDef jd;
    jd.Initialize(target, body, anchorA, anchorB);
    jd.collideConnected = true;
    int length = jd.length;
    b2LinearStiffness(jd.stiffness, jd.damping, hertz, dampingRatio, jd.bodyA, jd.bodyB);
    b2Joint *joint = mWorld->CreateJoint(&jd);
    return joint;
}

void Box2DPhysicalFacade:: set_gravity_scale(b2Body *body, float scale)
{
    body->SetGravityScale(scale);
    body->SetAwake(true);
    return;
}

void Box2DPhysicalFacade:: compute_cartesian_origin(int xP, int yP, int obWidth, int obHeight, float &xM, float &yM)
{
    xM =  (xP + (obWidth/2.0f)) / MET2PIX - (SCALED_WIDTH / 2.0f);
    yM = (yP + (obHeight/2.0f)) / MET2PIX - (SCALED_HEIGHT / 2.0f);
}

void Box2DPhysicalFacade:: compute_pixel_postion(float xM, float yM, int width, int height, int &xP, int &yP)
{

    xP = ((SCALED_WIDTH / 2.0f) + xM) * MET2PIX - width/ 2;
    yP = ((SCALED_HEIGHT / 2.0f) + yM) * MET2PIX - height/ 2;
}

float Box2DPhysicalFacade:: compute_distance_to_meter(int pixelDistance)
{
    return (float)pixelDistance/MET2PIX;
}