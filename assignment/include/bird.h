#ifndef BIRD_H
#define BIRD_H
#include "SDL_game_object.h"
#include "game_object_factory.h"
#include "animation_manage.h"
#include "animation.h"
#include "game_container_object.h"
#include "fruit.h"

enum eBirdState {
    eBIRD_STAND = 0,
    eBIRD_TAKE_OFF,
    eBIRD_FLYING,
    eBIRD_CATCH_THE_FRUIT,
    eBIRD_ESCAPE,
    eBIRD_LAST_STATE
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
        void load_bird_catch_the_fruit_animation();
        void load_bird_escape_animation();
        
};

class BirdObject: public SDLGameObject, public GameContainerObject
{
    public:
        BirdObject();
        ~BirdObject(){};
        void update() override;
        void draw() override;
        void load(const LoaderParams *pParams) override;
        eBirdState handle_event(eGameEventEnum event);
        enum eBirdState get_bird_state() const {return mBirdState;};
        void bird_aim_this_fruit(FruitObject *target);

    protected:
        ErrorCode_t create_object_body() override;
        ErrorCode_t create_object_fixture() override;
        ErrorCode_t container_init_anchor_point() override;
        b2Body* container_get_body() override;
        b2Vec2 container_get_anchor_point(int index) override;
        b2DistanceJointDef container_get_joint_config(b2Body *host, b2Body *target, b2Vec2 host_anchor, b2Vec2 target_anchor) const override;
        void set_bird_state(eBirdState new_state);

    private:
        enum eBirdState mBirdState;
        const AnimationFrame *frame;
        const AnimationPool *animation;
        int mFrameIdx;
        int mUpdateCounter;
        FruitObject *mTargetFruit;
        bool fruit_catched;
};


class BirdCreator: public BaseCreator
{
    public:
        GameObject* create_object() const override;
};

#endif /*BIRD_H*/