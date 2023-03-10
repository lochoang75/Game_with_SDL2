#ifndef ROAD_SIGN_H
#define ROAD_SIGN_H
#include "game_object_factory.h"
#include "SDL_game_object.h"
#include "log_wrapper.h"

class RoadSign: public SDLGameObject
{
public:
    RoadSign(/* args */);
    ~RoadSign();
    int get_x_position() const {return x;};
    int get_y_position() const {return y;};

protected:
    // ErrorCode_t create_object_body() override;
    ErrorCode_t create_object_fixture() override;

private:
    /* data */
};

RoadSign::RoadSign(/* args */): SDLGameObject(eSIGN_OBJECT)
{
}

RoadSign::~RoadSign()
{
}

ErrorCode_t RoadSign:: create_object_fixture()
{
    LogDebug("Get fixture definition for object %s", DBG_ObjectType(mType));
    b2FixtureDef fixture_def;
    b2PolygonShape shape;
    float w_plat = Box2DPhysicalFacade::compute_distance_to_meter(mWidth);
    float h_plat = Box2DPhysicalFacade::compute_distance_to_meter(mHeight); 
    shape.SetAsBox(w_plat/2, h_plat/2);
    fixture_def.shape = &shape;
    fixture_def.density = 5.0;
    fixture_def.friction = 0.3;
    fixture_def.restitution = 0.2;
    fixture_def.filter.categoryBits = kSIGN;
    // fixture_def.filter.maskBits = kBIRD;
    Box2DPhysicalFacade::create_fixture(mBody, fixture_def);
    return kSUCCESS;
}

class SignCreator:public BaseCreator
{
    GameObject *create_object() const override;
};

GameObject* SignCreator::create_object() const
{
    RoadSign* sign_obj = new RoadSign();
    return (GameObject*)sign_obj;
}

#endif /*ROAD_SIGN_H*/