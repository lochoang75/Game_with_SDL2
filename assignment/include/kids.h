#ifndef KIDS_H
#define KIDS_H
#include "SDL_game_object.h"
#include "game_object_factory.h"
#include "animation.h"
#include "animation_manage.h"
#include "game_speech.h"

enum eKidAnimationState 
{
    eKID_STAND = 0,
    eKID_MOVE_RIGHT,
    eKID_MOVE_LEFT,
    eKID_WATER_TREE,
    eKID_TURN_LEFT,
    eKID_TURN_RIGHT
};

enum eKidActionState
{
    eKID_ACTION_INTRODUCE = 0,
    eKID_ACTION_GOTO_TREE,
    eKID_ACTION_PLANT_TREE,
    eKID_ACTION_ASK_QUESTION_1,
    eKID_ACTION_ASK_QUESTION_2,
    eKID_ACTION_WAIT,
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
        void load_left_turn_animation();
        void load_right_turn_animation();
};

class KidObject: public SDLGameObject
{
    public:
        KidObject();
        ~KidObject(){};
        void update() override;
        void draw() override;

        void handle_event(int event);
        eKidActionState get_state() const;
    protected:
        virtual ErrorCode_t create_object_fixture() override;
        virtual ErrorCode_t create_object_body() override;
    private:
        void init_character_speech();
        void set_new_state(enum eKidActionState new_state);
        void set_animation_state(enum eKidAnimationState new_state);
        enum eKidAnimationState mAnimationState;
        enum eKidActionState mActionState;
        enum eKidActionState mPreState;
        const AnimationFrame *mFrame;
        GameCharacterSpeech *mSpeech;
        const AnimationPool *mAnimation;
        GameCharacterSpeechSet mSpeechSet[eKID_ACTION_TOTAL];
        int mUpdateCounter;
        int mFrameIdx;
        int mPendingEvent;
};


class KidCreator: public BaseCreator
{
    public:
        GameObject* create_object() const override;
};

#endif /*KIDS_H*/