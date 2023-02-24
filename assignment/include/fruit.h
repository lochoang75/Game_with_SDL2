#ifndef FRUIT_H
#define FRUIT_H
#include "game_enum.h"
#include "SDL_game_object.h"
#include "game_object_factory.h"

enum eFruitState {
    eFRUIT_ON_THE_TREE = 0,
    eFRUIT_SELECTED = 1,
    eFRUIT_RELEASED = 2,
    eFRUIT_FALLING = 3,
    eFRUIT_ON_THE_GROUND = 4
};

class FruitObject: public SDLGameObject
{
    public:
        FruitObject(): SDLGameObject(eFRUIT_OBJECT), mFruitState(eFRUIT_ON_THE_TREE){};
        ~FruitObject(){};
        void update() override;
        void handle_event(enum eGameEventEnum);
    private:
        enum eFruitState mFruitState;
};

void FruitObject:: update()
{
    switch(mFruitState)
    {
        case eFRUIT_SELECTED:
            /* Move follow the mouse*/
            break;
        case eFRUIT_ON_THE_TREE:
            break;
        case eFRUIT_RELEASED:
            mFruitState = eFRUIT_FALLING;
            /*Through*/
        case eFRUIT_FALLING:
            SDLGameObject::update();
            break;
        case eFRUIT_ON_THE_GROUND:
            break;
        default:
            break;
    }
}

void FruitObject::handle_event(enum eGameEventEnum event)
{
    int mouse_x, mouse_y;
    switch(event)
    {
        case eGAME_EVENT_MOUSE_DONW:
            mFruitState = eFRUIT_SELECTED;
            break;
        case eGAME_EVENT_MOUSE_MOVE:
            if (mFruitState != eFRUIT_SELECTED)
            {
                break;
            }
            SDL_GetMouseState(&mouse_x, &mouse_y);
            break;
        case eGAME_EVENT_MOUSE_RELEASE:
            if (mFruitState == eFRUIT_SELECTED)
            {
                mFruitState = eFRUIT_RELEASED;
            }
            break;
    }
}

class FruitCreator: public BaseCreator
{
    public:
        FruitCreator(): BaseCreator(){};
        ~FruitCreator(){};
        GameObject* create_object() const override;
};

GameObject* FruitCreator:: create_object() const
{
    FruitObject *new_object = new FruitObject();
    return (GameObject*) new_object;
}
#endif /*FRUIT_H*/