#include "animation.h"

StateAnimation::StateAnimation(int total_frame)
{
    mSize = total_frame;
    mCurrent = 0;
    mFrameList = new AnimationFrame[total_frame];
}

StateAnimation::~StateAnimation()
{
    for (int i = 0; i < mSize; i++)
    {
        delete mFrameList;
    }
    mFrameList = NULL;
}


ErrorCode_t StateAnimation::append_frame(AnimationFrame &frame)
{
    if (mCurrent >= mSize)
    {
        LogError("New frame is out of range: %d out of %d", mCurrent + 1, mSize);
        return kINVALID;
    }
    else
    {
        mFrameList[mCurrent] = frame;
        LogDebug("Load frame name %s, x: %d, y: %d, w: %d, h: %d", 
                        mFrameList[mCurrent].get_frame_name().c_str(),
                        mFrameList[mCurrent].get_x(),
                        mFrameList[mCurrent].get_y(),
                        mFrameList[mCurrent].get_y(),
                        mFrameList[mCurrent].get_width(),
                        mFrameList[mCurrent].get_height());
        mCurrent ++;
    }
    return kSUCCESS;
}

const AnimationFrame* StateAnimation::get_frame(int &index) const
{
    if (index >= mCurrent)
    {
        LogError("Your requested index is out of range, we only have %d frame, can't supply %d", mCurrent, index);
        return NULL;
    }
    else
    {
        const AnimationFrame* selected_frame = &mFrameList[index];
        index++;
        if (index == mCurrent)
        {
            index = 0;
        }
        return selected_frame;
    }
}

AnimationPool:: ~AnimationPool()
{
    for (std::vector<StateAnimation*>::iterator object = mStateList.begin(); object < mStateList.end(); object ++)
    {
        (*object)->~StateAnimation();
    }
    mStateList.clear();
}

const AnimationFrame* AnimationPool::get_frame(int enum_state, int &index) const
{
    if (enum_state >= (int)mStateList.size())
    {
        LogError("Unable to get state if index %d out of range %d", enum_state, mStateList.size());
        return NULL;
    }
    StateAnimation* state_animation = mStateList.at(enum_state);
    const AnimationFrame *frame = state_animation->get_frame(index);
    return frame;
}

void AnimationPool:: add_animation_for_new_state(AnimationFrame *frame_array, int size)
{
    StateAnimation *state_animation = new StateAnimation(size);
    if (state_animation == NULL)
    {
        LogError("Can't allocate memory for new state");
        return;
    }
    for(int i = 0; i < size; i++)
    {
        state_animation->append_frame(frame_array[i]);
    }
    mStateList.push_back(state_animation);
    return;
}