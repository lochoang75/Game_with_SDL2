#include "animation.h"

StateAnimation::StateAnimation(int total_frame, bool repeat)
{
    mSize = total_frame;
    mRepeat = repeat;
    mCurrentTotal = 0;
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
    if (mCurrentTotal >= mSize)
    {
        LogError("New frame is out of range: %d out of %d", mCurrentTotal + 1, mSize);
        return kINVALID;
    }
    else
    {
        mFrameList[mCurrentTotal] = frame;
        LogDebug("Load frame name %s, x: %d, y: %d, w: %d, h: %d", 
                        mFrameList[mCurrentTotal].get_frame_name().c_str(),
                        mFrameList[mCurrentTotal].get_x(),
                        mFrameList[mCurrentTotal].get_y(),
                        mFrameList[mCurrentTotal].get_y(),
                        mFrameList[mCurrentTotal].get_width(),
                        mFrameList[mCurrentTotal].get_height());
        mCurrentTotal ++;
    }
    return kSUCCESS;
}

const AnimationFrame* StateAnimation::get_frame(int &index) const
{
    if (index >= mCurrentTotal)
    {
        LogError("Your requested index is out of range, we only have %d frame, can't supply %d", mCurrentTotal, index);
        return NULL;
    }
    else
    {
        const AnimationFrame* selected_frame = &mFrameList[index];
        if (index == mCurrentTotal - 1)
        {
            if (mRepeat)
            {
                index = 0;
            }
        } 
        else 
        {
            index++;
        }
        return selected_frame;
    }
}

bool StateAnimation:: is_animate_completed(int &index) const
{
    if (index >= mCurrentTotal)
    {
        LogError("Your requested index is out of range, we only have %d frame, can't supply %d", mCurrentTotal, index);
        return NULL;
    }
    else
    {
        if (index == (mCurrentTotal - 1))
        {
            return true;
        }
        else
        {
            return false;
        }
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

bool AnimationPool:: is_completed(int enum_state, int &index) const
{
    if (enum_state >= (int)mStateList.size())
    {
        LogError("Unable to get state if index %d out of range %d", enum_state, mStateList.size());
        return false;
    }
    else
    {
        StateAnimation* state_animation = mStateList.at(enum_state);
        return state_animation->is_animate_completed(index);
    }
}

void AnimationPool:: add_animation_for_new_state(AnimationFrame *frame_array, int size, bool repeat)
{
    StateAnimation *state_animation = new StateAnimation(size, repeat);
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