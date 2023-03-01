#ifndef FRUIT_H
#define FRUIT_H
#include "game_enum.h"
#include "SDL_game_object.h"
#include "game_object_factory.h"

enum eFruitState {
    eFRUIT_ON_THE_TREE = 0,
    eFRUIT_SELECTED = 1,
    eFRUIT_RELEASED = 2,
    eFRUIT_FALLING = 3,
    eFRUIT_ON_THE_GROUND = 4
};

class FruitObject: public SDLGameObject
{
    public:
        FruitObject(): SDLGameObject(eFRUIT_OBJECT), mFruitState(eFRUIT_ON_THE_TREE){};
        ~FruitObject(){};
        void update() override;
        void handle_event(enum eGameEventEnum);
        void load(const LoaderParams *pParams) override;
    private:
    
        enum eFruitState mFruitState;
        b2Body *mAppleStalk;
        b2DistanceJoint *mJoint;
};


void FruitObject::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
	b2BodyDef bd;
	bd.type = b2_staticBody;
    mAppleStalk = Box2DPhysicalFacade::create_body(&bd);
    float x_pos;
    float y_pos;
    Box2DPhysicalFacade::compute_cartesian_origin(x, y, mWidth, mHeight, x_pos, y_pos);
    float object_radius = Box2DPhysicalFacade::compute_distance_to_meter(mHeight) /2;
    b2Vec2 stalk_start(x_pos - object_radius, y_pos - object_radius);
    b2Vec2 stalk_end(x_pos + object_radius, y_pos - object_radius);
    b2EdgeShape shape;
	shape.SetTwoSided(stalk_start, stalk_end);
	mAppleStalk->CreateFixture(&shape, 0.0f);
    LogDebug("Apple is at x: %d, y: %d, create stalk at %0.4f, %0.4f", x, y, x_pos, y_pos);

    mBody->SetAngularDamping(8.0f);
    b2Vec2 apple_anchor(x_pos, y_pos - object_radius);
    b2Vec2 stalk_anchor(x_pos, y_pos - object_radius);
    mJoint = (b2DistanceJoint*)Box2DPhysicalFacade::joint_object_with_distance(mAppleStalk, mBody, apple_anchor, stalk_start);
}

void FruitObject:: update()
{
    switch(mFruitState)
    {
        case eFRUIT_SELECTED:
            /* Move follow the mouse*/
            break;
        case eFRUIT_ON_THE_TREE:
            break;
        case eFRUIT_RELEASED:
            mFruitState = eFRUIT_FALLING;
            Box2DPhysicalFacade::destroy_joint(mJoint);
            mJoint = NULL;
            Box2DPhysicalFacade::destroy_body(mAppleStalk);
            mAppleStalk = NULL;
            // Box2DPhysicalFacade::set_gravity_scale(mBody, 1.0f);
            /*Through*/
        case eFRUIT_FALLING:
            /* TODO need to know if object is in the ground*/
            break;
        case eFRUIT_ON_THE_GROUND:
            break;
        default:
            break;
    }
}

void FruitObject::handle_event(enum eGameEventEnum event)
{
    int mouse_x, mouse_y;
    switch(event)
    {
        case eGAME_EVENT_MOUSE_DONW:
            mFruitState = eFRUIT_SELECTED;
            break;
        case eGAME_EVENT_MOUSE_MOVE:
            if (mFruitState != eFRUIT_SELECTED)
            {
                break;
            }
            SDL_GetMouseState(&mouse_x, &mouse_y);
            break;
        case eGAME_EVENT_MOUSE_RELEASE:
            if (mFruitState == eFRUIT_SELECTED)
            {
                mFruitState = eFRUIT_RELEASED;
            }
            break;
        default:
            LogDebug("Unhandle event %d", event);
            break;
    }
}

class FruitCreator: public BaseCreator
{
    public:
        FruitCreator(): BaseCreator(){};
        ~FruitCreator(){};
        GameObject* create_object() const override;
};

GameObject* FruitCreator:: create_object() const
{
    FruitObject *new_object = new FruitObject();
    return (GameObject*) new_object;
}
#endif /*FRUIT_H*/