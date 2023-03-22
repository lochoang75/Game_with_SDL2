#ifndef GAME_TOUCH_EVENT_DATA_H
#define GAME_TOUCH_EVENT_DATA_H
#include "game_constant.h"
#include "game_event.h"

class GameTouchEventData: public GameEventData
{
    public:
        GameTouchEventData(): GameEventData(eGAME_EVENT_UNSET), mTouchX(0), mTouchY(0){};
        ~GameTouchEventData(){};
        int get_x_position() const {return mTouchX;};
        void set_x_position(int x) {mTouchX = x;};
        int get_y_position() const {return mTouchY;};
        void set_y_position(int y) {mTouchY = y;};
    private:
        int mTouchX;
        int mTouchY;
};

#endif /* GAME_TOUCH_EVENT_DATA_H */