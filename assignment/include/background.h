#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "SDL_game_object.h"
#include "game_object_factory.h"
class BackgroundObject : public SDLGameObject
{
    public:
        BackgroundObject(): SDLGameObject(eBACKGROUND_OBJECT){};
        ~BackgroundObject(){};
};

class BackgroundCreator: public BaseCreator
{
    public:
        BackgroundCreator(): BaseCreator(){};
        ~BackgroundCreator(){};

        GameObject* create_object() const override;
};

GameObject* BackgroundCreator:: create_object() const
{
    BackgroundObject* new_object = new BackgroundObject();
    return (GameObject*) new_object;
}
#endif /*BACKGROUND_H*/