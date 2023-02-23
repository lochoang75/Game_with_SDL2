#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <vector>
#include "game_constant.h"
#include "log_wrapper.h"

class AnimationFrame
{
    public:
        AnimationFrame(): mFrameName(""), x(0), y(0), mWidth(0), mHeight(0){};
        AnimationFrame(const char *name, int x, int y, int width, int height):
                        mFrameName(name), x(x), y(y), mWidth(width), mHeight(height){};
        AnimationFrame(AnimationFrame *other): mFrameName(other->mFrameName), x(other->x), 
                                                y(other->y), mWidth(other->mWidth), mHeight(other->mHeight){};
        AnimationFrame operator = (AnimationFrame const & r_obj)
        {
            mFrameName = r_obj.mFrameName;
            x = r_obj.x;
            y = r_obj.y;
            mWidth = r_obj.mWidth;
            mHeight = r_obj.mHeight;
            
            return this;
        }
        virtual ~AnimationFrame(){};
        std::string get_frame_name() const {return mFrameName;};
        int get_x() const {return x;};
        int get_y() const {return y;};
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
    private:
        std::string mFrameName;
        int x;
        int y;
        int mWidth;
        int mHeight;
};

class StateAnimation
{
    public:
        StateAnimation() = delete;
        StateAnimation(int total_frame);
        ~StateAnimation();
        ErrorCode_t append_frame(AnimationFrame &frame);
        const AnimationFrame* get_frame(int &index) const;
    private:
        int mSize;
        int mCurrent;
        AnimationFrame *mFrameList;
};

class AnimationPool
{
    public:
        AnimationPool(){};
        virtual ~AnimationPool();
        virtual const AnimationFrame* get_frame(int enum_state, int &index) const;
        virtual void load_animation() = 0;
    protected:
        void add_animation_for_new_state(AnimationFrame *frame_array, int size);
        std::vector<StateAnimation*> mStateList;
};

#endif /* ANIMATION_H */