#ifndef BASKET_H
#define BASKET_H
#include "game_enum.h"
#include "SDL_game_object.h"
#include "game_object_factory.h"

class BasketObject: public SDLGameObject
{
    public:
        BasketObject(): SDLGameObject(eBASKET_OBJECT){};
        ~BasketObject(){};
};

class BasketCreator: public BaseCreator
{
    public:
        BasketCreator(): BaseCreator(){};
        ~BasketCreator(){};
        GameObject* create_object() const override;
};

GameObject* BasketCreator:: create_object() const
{
    BasketObject *new_object = new BasketObject();
    return (GameObject*) new_object;
}
#endif /*BASKET_H*/