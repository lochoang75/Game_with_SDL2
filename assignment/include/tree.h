#ifndef TREE_H
#define TREE_H

#include "game_enum.h"
#include "SDL_game_object.h"
#include "game_object_factory.h"

class TreeObject: public SDLGameObject
{
    public:
        TreeObject(): SDLGameObject(TREE_OBJECT){};
        ~TreeObject(){};
};

class TreeCreator: public BaseCreator
{
    public:
        TreeCreator(): BaseCreator(){};
        ~TreeCreator(){};
        GameObject* create_object() override;
};

GameObject* TreeCreator:: create_object()
{
    TreeObject *new_object = new TreeObject();
    return (GameObject*)new_object;
}
#endif /* TREE_H */