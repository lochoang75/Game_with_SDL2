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
    eBIRD_FLYING
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

void BirdObject::update()
{
    mUpdateCounter++;
    if (mUpdateCounter == 7)
    {
        frame = animation->get_frame(mState, mFrameIdx);
        SDLGameObject::update();
        mUpdateCounter = 0;
    }
}

void BirdObject::draw()
{
    SDL_Renderer *p_renderer = Game::get_instance()->get_renderer();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    GameTexture *texture = TextureManager::Instance()->get_texture(id);
    if (texture == NULL)
    {
        LogError("Error occur when get texture for id %d", id);
    }
    else
    {
        texture->draw(x, y, frame->get_x(), frame->get_y(), 
                        frame->get_width(), frame->get_height(), p_renderer, flip);
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