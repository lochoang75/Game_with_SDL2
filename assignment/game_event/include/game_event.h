#ifndef GAME_EVENT_H
#define GAME_EVENT_H
#include "game_constant.h"

enum eGameEventEnum
{
    eGAME_EVENT_UNSET = 0,
    eGAME_EVENT_MOUSE_DONW = 0x0001 << 1,
    eGAME_EVENT_MOUSE_RELEASE = 0x0001 << 2,
    eGAME_EVENT_MOUSE_MOVE = 0x0001 << 3,
    eGAME_EVENT_CONTACT_TARGET = 0x0001 << 4,
    eGAME_EVENT_BIRD_FLY = 0x0001 << 5,
    eGAME_EVENT_ALL_BIRD_OUT = 0x0001 << 6,
    eGAME_EVENT_TOUCH_DOWN = 0x0001 << 7,
    eGAME_EVENT_TOUCH_RELEASE = 0x0001 << 8,
    eGAME_EVENT_TOUCH_MOTION = 0x0001 << 9
};

class GameEventInput
{
    public:
        GameEventInput(): mIsPolling(false), mIsAllocated(false){};
        virtual ~GameEventInput(){};
        virtual ErrorCode_t input_init() = 0;
        virtual ErrorCode_t event_register() = 0;
        virtual ErrorCode_t start_event_poll() = 0;
        virtual void stop_event_poll() = 0;
    protected:
        bool mIsPolling;
        bool mIsAllocated;
};

class GameEventData
{
    public:
        GameEventData(enum eGameEventEnum eventType): mEventType(eventType){}; 
        virtual ~GameEventData(){};
        enum eGameEventEnum get_event_type() const {return mEventType;};
        void set_event_type(enum eGameEventEnum type) {mEventType = type;};
    protected:
        enum eGameEventEnum mEventType;
};

#endif /* GAME_EVENT_H */