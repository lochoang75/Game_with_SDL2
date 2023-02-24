#ifndef KIDS_H
#define KIDS_H
#include "SDL_game_object.h"
#include "game_enum.h"
#include "game_object_factory.h"
#include "animation.h"
#include "animation_manage.h"

enum eKidState 
{
    eKID_STAND = 0,
    eKID_RUN_LEFT,
};

class KidAnimationPool: public AnimationPool
{
    public:
        KidAnimationPool();
        ~KidAnimationPool(){};
        void load_animation() override;
    private:
        void load_stand_animation();
        void load_run_animation();
};

KidAnimationPool::KidAnimationPool():AnimationPool()
{
    load_animation();
}

void KidAnimationPool::load_animation()
{
    load_stand_animation();
    load_run_animation();
}

void KidAnimationPool::load_stand_animation()
{
    AnimationFrame sprite_sheet[2] = 
    {
        {"stand_1",0,145,40,70},
        {"stand_2",89,145,40,68}
    };
    AnimationPool::add_animation_for_new_state(sprite_sheet,2);
}

void KidAnimationPool::load_run_animation()
{
    AnimationFrame sprite_sheet[3] = 
    {
        {"run_1",215,72,42,72},
        {"run_2",354,65,46,69},
        {"run_3",0,287,52,69}
    };
    AnimationPool::add_animation_for_new_state(sprite_sheet, 3);
}

class KidObject: public SDLGameObject
{
    public:
        KidObject();
        ~KidObject(){};
        void update() override;
        void draw() override;
        void handle_event();
    private:
        enum eKidState mState;
        const AnimationFrame *frame;
        const AnimationPool *animation;
        int mUpdateCounter = 0;
        int mFrameIdx;
};
KidObject:: KidObject(): SDLGameObject(eKID_OBJECT)
{
    mState = eKID_STAND;
    mFrameIdx = 0;
    animation = AnimationManage::Instance()->get_animation(eKID_OBJECT);
    frame = animation->get_frame(mState, mFrameIdx);
}
void KidObject:: draw()
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

void KidObject::update()
{
    mUpdateCounter++;
    if (mUpdateCounter == 7)
    {
        frame = animation->get_frame(mState, mFrameIdx);
        SDLGameObject::update();
        mUpdateCounter = 0;
    }
}


class KidCreator: public BaseCreator
{
    public:
        GameObject* create_object() const override;
};

GameObject* KidCreator::create_object() const
{
    KidObject *new_object = new KidObject();
    return (GameObject*) new_object;
}
#endif /*KIDS_H*/