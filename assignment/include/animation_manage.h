#ifndef ANIMATION_MANAGE_H
#define ANIMATION_MANAGE_H
#include "animation.h"
#include "game_constant.h"
#include "log_wrapper.h"
#include "game_object.h"

class AnimationManage 
{
    public:
        static AnimationManage* Instance();
        ErrorCode_t animation_register(eGameObjectType object_type, AnimationPool *pool);
        const AnimationPool* get_animation(eGameObjectType object_type);
        void clean_up();

    private:
        AnimationManage();
        ~AnimationManage(){};
        AnimationPool *mAnimationList[eTOTAL_OBJECT];
        static AnimationManage* mInstance;
};

#endif /*ANIMATION_MANAGE_H*/