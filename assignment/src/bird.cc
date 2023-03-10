#include "bird.h"

#include "fruit.h"

BirdAnimationPool::BirdAnimationPool():AnimationPool()
{
    load_animation();
}

BirdAnimationPool::~BirdAnimationPool()
{
    for (std::vector<StateAnimation*>::iterator object = mStateList.begin(); object != mStateList.end(); object++)
    {
        delete (*object);
    }

    mStateList.clear();
}

void BirdAnimationPool:: load_animation()
{
    for (uint8_t i = eBIRD_STAND; i < eBIRD_LAST_STATE; i++)
    {
        switch (static_cast<eBirdState>(i))
        {
        case eBIRD_STAND:
            load_bird_stand_animation();
            break;
        case eBIRD_FLYING:
            load_bird_fly_animation();
            break;
        case eBIRD_TAKE_OFF:
            load_bird_take_off_animation();
            break;
        case eBIRD_CATCH_THE_FRUIT:
            load_bird_catch_the_fruit_animation();
            break;
        case eBIRD_ESCAPE:
            load_bird_escape_animation();
            break;
        default:
            break;
        }
    }
}

void BirdAnimationPool:: load_bird_fly_animation()
{
    AnimationFrame fly_frame[3] = {
        {"fly_1", 0, 0, 46, 42},
        {"fly_2", 0, 113, 60, 28},
        {"fly_3", 0, 43, 46,40}
    };
    AnimationPool::add_animation_for_new_state(fly_frame, 3, true);
    return;
}

void BirdAnimationPool:: load_bird_stand_animation()
{
    AnimationFrame stand_frame[4] = {
        {"stand_1", 94, 0, 33, 29},
        {"stand_2", 94, 30, 33, 29},
        {"stand_3", 94, 60, 33, 29},
        {"stand_4", 94, 176, 33, 29}
    };
    AnimationPool::add_animation_for_new_state(stand_frame, 4, true);
}

void BirdAnimationPool:: load_bird_take_off_animation()
{
    AnimationFrame take_off_frame[3] = {
        {"take_off_1", 260, 252, 46, 42},
        {"take_off_2", 47, 41, 46, 40},
        {"take_off_3", 47, 0, 46, 40}
    };
    AnimationPool::add_animation_for_new_state(take_off_frame, 3, false);
}

void BirdAnimationPool:: load_bird_catch_the_fruit_animation()
{
    AnimationFrame catch_the_fruit_frame[1] = {
        {"catch_fruit_1", 175, 0, 37, 42}
    };
    AnimationPool::add_animation_for_new_state(catch_the_fruit_frame, 1, false);
}

void BirdAnimationPool:: load_bird_escape_animation()
{
    AnimationFrame escape_frame[3] = {
        {"escaping_1", 155, 227, 46, 40},
        {"escaping_2", 0, 116, 60, 28},
        {"escaping_3", 245, 129, 46, 42}
    };
    AnimationPool::add_animation_for_new_state(escape_frame, 3, true);
}


BirdObject::BirdObject(): SDLGameObject(eBIRD_OBJECT), GameContainerObject(1)
{
    mBirdState = eBIRD_STAND;
    mFrameIdx = 0;
    mUpdateCounter = 0;
    mTargetFruit = NULL;
    fruit_catched = false;
    animation = AnimationManage::Instance()->get_animation(eBIRD_OBJECT);
    frame = animation->get_frame(mBirdState, mFrameIdx);
}

ErrorCode_t BirdObject::create_object_body()
{
    LogDebug("Get body definition for object %s", DBG_ObjectType(mType));
    b2BodyDef body_def;
    float body_x, body_y;
    Box2DPhysicalFacade::compute_cartesian_origin(x, y, mWidth, mHeight, body_x, body_y);

    body_def.type = b2_dynamicBody;
    body_def.position.Set(body_x, body_y);
    body_def.fixedRotation = true;
    body_def.userData.pointer = reinterpret_cast<uintptr_t> (this);
    mBody = Box2DPhysicalFacade::create_body(body_def);
    if (mBody == NULL)
    {
        return kNO_MEM;
    }
    return kSUCCESS;
}

ErrorCode_t BirdObject:: create_object_fixture()
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
    fixture_def.filter.categoryBits = kBIRD;
    Box2DPhysicalFacade::create_fixture(mBody, fixture_def);

    for (int i = 0; i < mTotalAnchor; i++)
    {
        LogDebug("Get fixture definition for object %s", DBG_ObjectType(mType));
        b2EdgeShape claws_shape;
        b2Vec2 pixel_anchor = mAnchorArray[i];
        float pos_x, pos_y;
        Box2DPhysicalFacade::compute_cartesian_origin(pixel_anchor.x, pixel_anchor.y, kAnchorSize, kAnchorSize, pos_x, pos_y);
        claws_shape.SetTwoSided(b2Vec2(pos_x, pos_y - 0.1), b2Vec2(pos_x, pos_y + 0.1));

        b2FixtureDef claws_def;
        claws_def.shape = &claws_shape;
        claws_def.filter.categoryBits = kBIRD;
        claws_def.filter.maskBits = kFRUIT;
        claws_def.density = 1.0;
        claws_def.friction = 0.3;
        Box2DPhysicalFacade::create_fixture(mBody, claws_def);
    }

    return kSUCCESS;
}

void BirdObject::load(const LoaderParams *pParams)
{
    container_init_anchor_point();
    SDLGameObject::load(pParams);
}

void BirdObject:: set_bird_state(eBirdState new_state)
{
    mBirdState = new_state;
    mFrameIdx = 0;
}

void BirdObject::update()
{   
    bool animation_change  = true;
    uint8_t counter_limit = 10;
    b2Vec2 object_velocity = mBody->GetLinearVelocity();
    switch (mBirdState)
    {
        case eBIRD_STAND:
            if ((rand() % 100) > 70)
            {
                animation_change = false;
            }
            break;
        case eBIRD_TAKE_OFF:
            break;
        case eBIRD_FLYING:
            counter_limit = 3;
            object_velocity = mBody->GetLinearVelocity();
            if (object_velocity.y > 0)
            {
                mBody->ApplyForce(b2Vec2(-1.0, -(mMass * 10.0f) - 3), mBody->GetPosition(), true);
            }
            break;
        case eBIRD_CATCH_THE_FRUIT:
            LogDebug("Bird will catch the fruit after that");
            if (fruit_catched)
            {
                set_bird_state(eBIRD_ESCAPE);
            } else
            {
                joint_new_object(mTargetFruit);
                fruit_catched = true;
            }
            break;
        case eBIRD_ESCAPE:
            if (object_velocity.y > 0)
            {
                mBody->ApplyForce(b2Vec2(2.0, -(mMass * 10.0f) - 20), mBody->GetPosition(), true);
            }
            break;
        default:
            break;
    }

    if (mUpdateCounter == counter_limit)
    {
        if (animation_change)
        {
            frame = animation->get_frame(mBirdState, mFrameIdx);
        }
        mUpdateCounter = 0;
    }
    mUpdateCounter ++;
    SDLGameObject::update();
}

eBirdState BirdObject::handle_event(eGameEventEnum event)
{
    LogDebug("Bird handle event %s", DBG_EventType(event));
    switch (event)
    {
    case eGAME_EVENT_CONTACT_TARGET:
        if (mBirdState == eBIRD_FLYING)
        {
            LogDebug("Bird will take that fruit");
            set_bird_state(eBIRD_CATCH_THE_FRUIT);
        }
        else if (mBirdState == eBIRD_ESCAPE)
        {
            Box2DPhysicalFacade::set_velocity(mBody, 2.0f, -1.0f);
            LogDebug("Bird will ignore that fruit");
        } 
        else
        {
            LogDebug("Bird will ignore that fruit");
        }
        break;
    default:
        LogDebug("Bird get the event %s not handle", DBG_EventType(event));
        break;
    }
    return mBirdState;
}

void BirdObject::draw()
{
    double angle = Box2DPhysicalFacade::get_angle(mBody);
    float pos_x, pos_y;
    Box2DPhysicalFacade::get_current_position(mBody, pos_x, pos_y);
    Box2DPhysicalFacade::compute_pixel_postion(pos_x, pos_y, mWidth, mHeight, x, y);
    SDL_Rect src_rect;
    src_rect.x = frame->get_x();
    src_rect.y = frame->get_y();
    src_rect.w = frame->get_width();
    src_rect.h = frame->get_height();
    SDL_Renderer *p_renderer = Game::Instance()->get_renderer();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    GameTexture *texture = TextureManager::Instance()->get_texture(id);
    if (texture == NULL)
    {
        LogError("Error occur when get texture for id %d", id);
    }
    else
    {
        texture->draw(x, y, &src_rect, angle, p_renderer, flip);
    }
    return;
}

ErrorCode_t BirdObject::container_init_anchor_point()
{
    mAnchorArray = new b2Vec2[mTotalAnchor];
    mJointArray = new b2Joint*[mTotalAnchor];
    for (int i = 0; i < mTotalAnchor; i++)
    {
        mJointArray[i] = NULL;
        mAnchorArray[i] = b2Vec2(x + (mWidth/2), y + mHeight);
    }
    return kSUCCESS;
}

b2Body* BirdObject::container_get_body()
{
    return mBody;
}

void BirdObject::bird_aim_this_fruit(FruitObject *target_fruit)
{
    mTargetFruit = target_fruit;
}

b2Vec2 BirdObject:: container_get_anchor_point(int index)
{
    b2Vec2 anchor_point;
    do {
        b2Vec2 center = mBody->GetPosition();
        float w_plat = Box2DPhysicalFacade::compute_distance_to_meter(mWidth);
        float h_plat = Box2DPhysicalFacade::compute_distance_to_meter(mHeight);
        anchor_point.Set(center.x - w_plat/2, center.y - h_plat/2);
        LogDebug("Bird anchor point at: %0.4f, %0.4f", anchor_point.x, anchor_point.y);
        index--;
    } while (index > 0);
    return anchor_point;
}

b2DistanceJointDef BirdObject:: container_get_joint_config(b2Body *host, b2Body *target, b2Vec2 host_anchor, b2Vec2 target_anchor) const
{
    b2DistanceJointDef joint_def;
    joint_def.Initialize(host, target, host_anchor, target_anchor);
    joint_def.collideConnected = true;
    joint_def.maxLength = 0.8f;
    joint_def.damping = 100.0f;
    return joint_def;
}



GameObject* BirdCreator::create_object() const
{
    BirdObject *new_object = new BirdObject();
    return (GameObject*) new_object;
}