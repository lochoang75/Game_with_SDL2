#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "loader_params.h"

class GameObject
{
    public:
        GameObject(){};
        virtual ~GameObject();
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void clean_up() = 0;
        virtual void load(const LoaderParams* params) = 0;
};
#endif /* GAME_OBJECT_H */