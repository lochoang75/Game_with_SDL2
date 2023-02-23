#include "animation_manage.h"
AnimationManage* AnimationManage::mInstance = NULL;

AnimationManage* AnimationManage::Instance()
{
    if (mInstance == NULL)
    {
        LogInfo("Instance animation manager");
        mInstance = new AnimationManage();
    }

    return mInstance;
}

ErrorCode_t AnimationManage:: animation_register(eGameObjectType object_type, AnimationPool *pool)
{
    mAnimationList[object_type] = pool;
    return kSUCCESS;
}

const AnimationPool* AnimationManage:: get_animation(eGameObjectType object_type)
{
    return mAnimationList[object_type]; 
}
