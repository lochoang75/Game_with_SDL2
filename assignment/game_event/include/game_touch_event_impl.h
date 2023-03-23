#ifndef GAME_TOUCH_EVENT_IMPL_H
#define GAME_TOUCH_EVENT_IMPL_H
#include <SDL2/SDL.h>
#include "game_event.h"
#include "game_touch_event_data.h"

#include <thread>

#include "game_constant.h"

class GameTouchEventInput: public GameEventInput
{
    public:
        GameTouchEventInput(): GameEventInput(), mEventType(eGAME_EVENT_UNSET), mEventFd(-1){};
        ~GameTouchEventInput();
        ErrorCode_t input_init() override;
        void input_deinit() override;
        ErrorCode_t event_register() override;
        ErrorCode_t start_event_poll() override;
        void stop_event_poll() override;
    private:
        void _start_event_poll(Uint32);
        Uint32 mEventType;
        std::thread mPollingThread;
        int mEventFd;
};
#endif