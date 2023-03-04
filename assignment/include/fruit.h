#ifndef FRUIT_H
#define FRUIT_H
#include "game_enum.h"
#include "SDL_game_object.h"
#include "game_object_factory.h"
#include "game_container_object.h"
#include "game_container_object.h"

enum eFruitState {
    eFRUIT_ON_THE_TREE = 0,
    eFRUIT_SELECTED = 1,
    eFRUIT_RELEASED = 2,
    eFRUIT_CATCHED = 3,
    eFRUIT_WITH_BIRD = 4,
    eFRUIT_FALLING = 5,
    eFRUIT_ON_THE_GROUND = 6
};

class FruitObject: public SDLGameObject, public ContainedObject
{
    public:
        FruitObject(): SDLGameObject(eFRUIT_OBJECT), ContainedObject(), mFruitState(eFRUIT_ON_THE_TREE){};
        ~FruitObject(){};
        void update() override;
        void handle_event(enum eGameEventEnum);
        b2Body *get_body() override {return mBody;};
        b2Vec2 get_anchor_point() const override;

    protected:
        ErrorCode_t create_object_body() override;
        ErrorCode_t create_object_fixture() override;
    private:
        enum eFruitState mFruitState;
};

class FruitCreator: public BaseCreator
{
    public:
        FruitCreator(): BaseCreator(){};
        ~FruitCreator(){};
        GameObject* create_object() const override;
};

#endif /*FRUIT_H*/