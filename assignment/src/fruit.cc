#include "fruit.h"

b2Vec2 FruitObject:: get_anchor_point() const
{
    float x_pos, y_pos;
    Box2DPhysicalFacade::compute_cartesian_origin(x, y, mWidth, mHeight, x_pos, y_pos);
    float width = Box2DPhysicalFacade::compute_distance_to_meter(mWidth);
    float height = Box2DPhysicalFacade::compute_distance_to_meter(mHeight);
    b2Vec2 anchor = b2Vec2(x_pos, y_pos);// - b2Vec2((width/2), (height/2));
    LogDebug("Fruit anchor point at x: %0.4f y: %0.4f", anchor.x, anchor.y);
    return anchor;
}


ErrorCode_t FruitObject:: create_object_body() 
{
    b2BodyDef body_def;
    float body_x, body_y;
    Box2DPhysicalFacade::compute_cartesian_origin(x, y, mWidth, mHeight, body_x, body_y);

    body_def.type = b2_dynamicBody;
    body_def.position.Set(body_x, body_y);
    body_def.userData.pointer = reinterpret_cast<uintptr_t> (this);
    mBody = Box2DPhysicalFacade::create_body(body_def);
    if (mBody == NULL)
    {
        return kNO_MEM;
    }
    return kSUCCESS;
}

ErrorCode_t FruitObject:: create_object_fixture() 
{
    b2FixtureDef fixture_def;
    b2PolygonShape shape;
    float w_plat = Box2DPhysicalFacade::compute_distance_to_meter(mWidth);
    float h_plat = Box2DPhysicalFacade::compute_distance_to_meter(mHeight); 
    shape.SetAsBox(w_plat/2, h_plat/2);
    fixture_def.shape = &shape;
    fixture_def.density = 0.2f;
    fixture_def.friction = 0.3f;
    fixture_def.restitution = 0.3f;
    fixture_def.filter.categoryBits = kFRUIT;
    fixture_def.filter.maskBits = kBIRD | kGROUND;
    Box2DPhysicalFacade::create_fixture(mBody, fixture_def);
    return kSUCCESS;
}

// void FruitObject::load(const LoaderParams *pParams)
// {
// }

void FruitObject:: update()
{
    switch(mFruitState)
    {
        case eFRUIT_SELECTED:
            /* Move follow the mouse*/
            break;
        case eFRUIT_ON_THE_TREE:
            break;
        case eFRUIT_CATCHED:
            LogDebug("Fruit has been catched");
            unjoint_from_current_container();
            Box2DPhysicalFacade::set_gravity_scale(mBody, 0.02f);
            Box2DPhysicalFacade::set_velocity(mBody, 1.5f, -1.0f);
            mBody->SetFixedRotation(true);
            mFruitState = eFRUIT_WITH_BIRD;
            break;
        case eFRUIT_RELEASED:
            LogDebug("Fruit will be unjoint from the tree");
            unjoint_from_current_container();
            mFruitState = eFRUIT_FALLING;
            // Box2DPhysicalFacade::set_gravity_scale(mBody, 1.0f);
            /*Through*/
        case eFRUIT_FALLING:
            /* TODO need to know if object is in the ground*/
            break;
        case eFRUIT_WITH_BIRD:
            Box2DPhysicalFacade::set_velocity(mBody, 1.5f, -1.0f);
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
        case eGAME_EVENT_CONTACT_TARGET:
            if (mFruitState == eFRUIT_ON_THE_TREE)
            {
                mFruitState = eFRUIT_CATCHED;
            }
            break;
        default:
            LogDebug("Unhandle event %d", event);
            break;
    }
}



GameObject* FruitCreator:: create_object() const
{
    FruitObject *new_object = new FruitObject();
    return (GameObject*) new_object;
}