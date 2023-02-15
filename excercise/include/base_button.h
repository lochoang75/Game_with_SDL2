#ifndef BASE_BUTTON_H
#define BASE_BUTTON_H
#include <SDL2/SDL.h>

class BaseButton
{
    public:
        BaseButton();
        virtual ~BaseButton();
        void set_position(int x, int y);
        int get_current_sprite();
        virtual void handle_event(SDL_Event *event) = 0;
        const SDL_Point *get_position();
    protected:
        SDL_Point mPosition;
        int mCurrentSprite;
};

BaseButton::BaseButton()
{
    mPosition.x = 0;
    mPosition.y = 0;
    mCurrentSprite = 0;
}

BaseButton::~BaseButton()
{

}

void BaseButton::set_position(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

const SDL_Point* BaseButton:: get_position()
{
    return &mPosition;
}

int BaseButton::get_current_sprite()
{
    return mCurrentSprite;
}

#endif /*BASE_BUTTON_H*/