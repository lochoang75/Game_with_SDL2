#ifndef KIDS_H
#define KIDS_H
#include "SDL_game_object.h"
#include "game_enum.h"
#include "game_object_factory.h"
#include "animation.h"
#include "animation_manage.h"
#include "game_speech.h"

enum eKidAnimationState 
{
    eKID_STAND = 0,
    eKID_MOVE_RIGHT,
    eKID_MOVE_LEFT,
    eKID_WATER_TREE
};

enum eKidActionState
{
    eKID_ACTION_INTRODUCE = 0,
    eKID_ACTION_PLAN_TREE,
    eKID_ACTION_ASK_QUESTION_1,
    eKID_ACTION_ASK_QUESTION_2,
    eKID_ACTION_ASK_QUESTION_3,
    eKID_ACTION_TRASH_TALK,
    eKID_ACTION_WRONG_ANSWER,
    eKID_ACTION_CORRECT_ANSWER,
    eKID_ACTION_TOTAL
};

class KidAnimationPool: public AnimationPool
{
    public:
        KidAnimationPool();
        ~KidAnimationPool(){};
        void load_animation() override;
    private:
        void load_stand_animation();
        void load_right_move_animation();
        void load_left_move_animation();
        void load_water_tree_animation();
};

class KidObject: public SDLGameObject
{
    public:
        KidObject();
        ~KidObject(){};
        void update() override;
        void draw() override;
        void handle_event();
        void set_tree_position(int tree_x_position);
    private:
        void init_character_speech();
        enum eKidAnimationState mAnimationState;
        enum eKidActionState mActionState;
        const AnimationFrame *mFrame;
        const AnimationPool *mAnimation;
        GameCharacterSpeechSet mSpeechSet[eKID_ACTION_TOTAL];
        int mUpdateCounter = 0;
        int mFrameIdx;
};


class KidCreator: public BaseCreator
{
    public:
        GameObject* create_object() const override;
};

#endif /*KIDS_H*/