#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "loader_params.h"
#include "game_enum.h"

class GameObject
{
    public:
        GameObject(){};
        GameObject(enum eGameObjectType type): mType(type){};
        virtual ~GameObject() = 0;
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void clean_up() = 0;
        virtual void load(const LoaderParams* params) = 0;
        enum eGameObjectType get_object_type() {return mType;};
    protected:
        enum eGameObjectType mType;
};
#endif /* GAME_OBJECT_H */