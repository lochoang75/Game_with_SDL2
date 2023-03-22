#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "loader_params.h"

enum eGameObjectType
{
    eFRUIT_OBJECT = 0,
    eTREE_OBJECT = 1,
    eBASKET_OBJECT = 2,
    eBACKGROUND_OBJECT = 3,
    eBIRD_OBJECT = 4,
    eKID_OBJECT = 5,
    eBUBBLE_OBJECT = 6,
    eWATER_BUBBLE_OBJECT = 7,
    eSIGN_OBJECT = 8,
    eTOTAL_OBJECT
};

class GameObject
{
    public:
        GameObject(){};
        GameObject(enum eGameObjectType type): mType(type){};
        virtual ~GameObject() {};
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void clean_up() = 0;
        virtual void load(const LoaderParams* params) = 0;
        virtual void handle_event(int event) = 0;
        virtual void get_position(int &x, int &y) const = 0;
        virtual void get_size(int &width, int &height) const = 0;
        enum eGameObjectType get_object_type() {return mType;};
    protected:
        enum eGameObjectType mType;
};
#endif /* GAME_OBJECT_H */