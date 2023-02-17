#ifndef FRUIT_H
#define FRUIT_H
#include "game_enum.h"
#include "SDL_game_object.h"
#include "game_object_factory.h"

class FruitObject: public SDLGameObject
{
    public:
        FruitObject(): SDLGameObject(FRUIT_OBJECT){};
        ~FruitObject(){};
};

class FruitCreator: public BaseCreator
{
    public:
        FruitCreator(): BaseCreator(){};
        ~FruitCreator(){};
        GameObject* create_object() override;
};

GameObject* FruitCreator:: create_object()
{
    FruitObject *new_object = new FruitObject();
    return (GameObject*) new_object;
}
#endif /*FRUIT_H*/