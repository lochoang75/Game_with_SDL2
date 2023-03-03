#ifndef TREE_H
#define TREE_H

#include "game_enum.h"
#include "SDL_game_object.h"
#include "game_object_factory.h"
#include "game_container_object.h"

class TreeObject: public SDLGameObject, public GameContainerObject
{
    public:
        TreeObject():SDLGameObject(eTREE_OBJECT), GameContainerObject(10){};
        ~TreeObject(){};
        ErrorCode_t get_tree_anchor_point(int &x, int &y) const;
    protected:
        ErrorCode_t container_init_anchor_point() override;
        b2Body* container_get_body() override;
        void load(const LoaderParams *pParams) override;
        ErrorCode_t create_object_fixture() override;
};

class TreeCreator: public BaseCreator
{
    public:
        TreeCreator(): BaseCreator(){};
        ~TreeCreator(){};
        GameObject* create_object() const override;
};

#endif /* TREE_H */