#ifndef BIRD_H
#define BIRD_H
#include "game_enum.h"
#include "SDL_game_object.h"
#include "game_object_factory.h"
#include "animation_manage.h"
#include "animation.h"

enum eBirdState {
    eBIRD_STAND = 0,
    eBIRD_TAKE_OFF,
    eBIRD_FLYING,
    eBIRD_CATCH_THE_FRUIT,
    eBIRD_ESCAPE
};

class BirdAnimationPool: public AnimationPool
{
    public:
        BirdAnimationPool();
        ~BirdAnimationPool();
        void load_animation() override;
    private:
        void load_bird_stand_animation();
        void load_bird_fly_animation();
        void load_bird_take_off_animation();
};

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
    load_bird_stand_animation();
    load_bird_take_off_animation();
    load_bird_fly_animation();
}

void BirdAnimationPool:: load_bird_fly_animation()
{
    AnimationFrame fly_frame[3] = {
        {"fly_1",245,0,46,42},
        {"fly_2",146,103,60,28},
        {"fly_3",292,170,46,40}
    };
    AnimationPool::add_animation_for_new_state(fly_frame, 3);
    return;
}

void BirdAnimationPool:: load_bird_stand_animation()
{
    AnimationFrame stand_frame[2] = {
        {"stand_1", 114, 22, 22, 21},
        {"stand_1", 114, 22, 22, 21}
    };
    AnimationPool::add_animation_for_new_state(stand_frame, 2);
}

void BirdAnimationPool:: load_bird_take_off_animation()
{
    AnimationFrame take_off_frame[2] = {
        {"take_off_1", 0, 61, 23, 23},
        {"take_off_2", 24, 61, 26, 21}
    };
    AnimationPool::add_animation_for_new_state(take_off_frame, 2);
}

class BirdObject: public SDLGameObject
{
    public:
        BirdObject();
        ~BirdObject(){};
        void update() override;
        void draw() override;
        void load(const LoaderParams *pParams) override;
        void handle_event(enum eGameEventEnum event);
        enum eBirdState get_bird_state() const {return mState;};
        ErrorCode_t create_object_body() override;
        ErrorCode_t create_object_fixture() override;
    private:
        enum eBirdState mState;
        const AnimationFrame *frame;
        const AnimationPool *animation;
        int mFrameIdx;
        int mUpdateCounter;
};

BirdObject::BirdObject(): SDLGameObject(eBIRD_OBJECT)
{
    mState = eBIRD_FLYING;
    mFrameIdx = 0;
    mUpdateCounter = 0;
    animation = AnimationManage::Instance()->get_animation(eBIRD_OBJECT);
    frame = animation->get_frame(mState, mFrameIdx);
}

ErrorCode_t BirdObject::create_object_body()
{
    LogDebug("Get body definition for object %s", DBG_ObjectType(mType));
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

ErrorCode_t BirdObject:: create_object_fixture()
{
    LogDebug("Get fixture definition for object %s", DBG_ObjectType(mType));
    b2FixtureDef fixture_def;
    b2PolygonShape shape;
    float w_plat = Box2DPhysicalFacade::compute_distance_to_meter(mWidth);
    float h_plat = Box2DPhysicalFacade::compute_distance_to_meter(mHeight); 
    shape.SetAsBox(w_plat/2, h_plat/2);
    fixture_def.shape = &shape;
    fixture_def.density = 1.0;
    fixture_def.friction = 0.3;
    fixture_def.restitution = 0.2;
    Box2DPhysicalFacade::create_fixture(mBody, fixture_def);
    return kSUCCESS;
}

void BirdObject::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
    Box2DPhysicalFacade::set_gravity_scale(mBody, 0.0f);
    Box2DPhysicalFacade::set_velocity(mBody, -1.0f, 0.0f);
}

void BirdObject::update()
{   
    switch (mState)
    {
        case eBIRD_STAND:
            break;
        case eBIRD_TAKE_OFF:
            break;
        case eBIRD_FLYING:
            break;
        case eBIRD_CATCH_THE_FRUIT:
            break;
        case eBIRD_ESCAPE:
            break;
    }

    frame = animation->get_frame(mState, mFrameIdx);
    SDLGameObject::update();
    mUpdateCounter = 0;
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

class BirdCreator: public BaseCreator
{
    public:
        GameObject* create_object() const override;
};

GameObject* BirdCreator::create_object() const
{
    BirdObject *new_object = new BirdObject();
    return (GameObject*) new_object;
}
#endif /*BIRD_H*/