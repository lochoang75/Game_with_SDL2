#include "game_touch_event_impl.h"

#include <thread>

#include "log_wrapper.h"
#include "linux/input.h"
#include "fcntl.h"
#define TOUCH_EVENT_POOL_SIZE (100)
#define TOUCH_HOR_MIN 8 /*If EVDEV_XXX_MIN > EVDEV_XXX_MAX the XXX axis is automatically inverted*/
#define TOUCH_HOR_MAX 710
#define TOUCH_VER_MIN 9
#define TOUCH_VER_MAX 1269

const char *TOUCH_DEVICE = "/dev/input/event0";
GameTouchEventData l_event_pool[TOUCH_EVENT_POOL_SIZE];
static uint8_t l_current_event = 0;
static GameTouchEventData *touch_event_data = &l_event_pool[l_current_event];

GameTouchEventInput::~GameTouchEventInput()
{
}

ErrorCode_t GameTouchEventInput::input_init()
{
    mEventFd = open(TOUCH_DEVICE, O_RDWR | O_NOCTTY);
    if (mEventFd == -1)
    {
        perror("Unable to open evdev interface:");
        return kFAILED;
    }

    fcntl(mEventFd, F_SETFL, O_NONBLOCK);
    return kSUCCESS;
}

ErrorCode_t GameTouchEventInput::event_register()
{
    mEventType = SDL_RegisterEvents(1);
    if (mEventType == ((Uint32)0 - 1))
    {
        LogError("Unable to register for touch event");
        return kFAILED;
    }
    else
    {
        LogInfo("Event registered %d", mEventType);
    }
    return kSUCCESS;
}

ErrorCode_t GameTouchEventInput::start_event_poll()
{
    if (mIsPolling)
    {
        LogWarning("Event is polling, duplicate control");
        return kDUPLICATED;
    }

    if (mIsAllocated)
    {
        LogInfo("Reused allocated thread");
    }
    else
    {
        mPollingThread = std::thread(&GameTouchEventInput::_start_event_poll, this, mEventType);
        mIsAllocated = true;
    }

    LogDebug("Start polling for event");
    mIsPolling = true;
    return kSUCCESS;
}

void GameTouchEventInput::stop_event_poll()
{
    mIsPolling = false;
}

static int _touch_position_remap(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static void _offset_event_data_pointer()
{
    l_current_event ++;
    if (l_current_event == TOUCH_EVENT_POOL_SIZE)
    {
        l_current_event = 0;
    }
    touch_event_data = &l_event_pool[l_current_event];
}

static int _touch_event_handle(struct input_event &inputEvent, Uint32 evType)
{
    int value = 0;
    if (inputEvent.type == EV_ABS)
    {
        if (inputEvent.code == ABS_MT_POSITION_X)
        {
            // value = inputEvent.value;
            value = _touch_position_remap(inputEvent.value, TOUCH_HOR_MIN, TOUCH_HOR_MAX, 0, SCREEN_HEIGHT); 
            touch_event_data->set_x_position(value);
        }
        else if (inputEvent.code == ABS_MT_POSITION_Y)
        {
            // value = inputEvent.value;
            value = _touch_position_remap(inputEvent.value, TOUCH_VER_MIN, TOUCH_VER_MAX, 0, SCREEN_WIDTH); 
            touch_event_data->set_y_position(value);
        }
    }
    if (inputEvent.type == EV_SYN && inputEvent.code == SYN_MT_REPORT)
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
        event.type = evType;
        event.user.code = eGAME_EVENT_TOUCH_DOWN;
        event.user.data1 = touch_event_data;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
        _offset_event_data_pointer();
    }

    return 0;
}

void GameTouchEventInput::_start_event_poll(Uint32 eventType)
{
    struct input_event in;

    while (true)
    {
        // TODO: poll for event
        if (!mIsPolling)
        {
            usleep(EVENT_IDLE_MS * 1000);
            continue;
        }

        int ret = read(mEventFd, &in, sizeof(struct input_event));
        if (ret > 0)
        {
            _touch_event_handle(in, mEventType);
        }
    }
}
