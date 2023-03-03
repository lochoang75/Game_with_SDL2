#ifndef GAME_CONTACT_LISTENER_H
#define GAME_CONTACT_LISTENER_H
#include <map>

#include "box2d.h"
#include "game_object.h"
#include "game_constant.h"
#include "log_wrapper.h"

typedef void (*ContactHandler)(GameObject *, GameObject*);


class GameContactListener: public b2ContactListener
{
    public:
        void BeginContact(b2Contact *contact);
        void EndContact(b2Contact *contact);
        void InitContactHandler();
    private:
        void HandlerRegister(eGameObjectType firstObj, eGameObjectType seccondObj, ContactHandler handler);
        std::map<std::pair<eGameObjectType, eGameObjectType>, ContactHandler> mContactMap;
};

#endif /*GAME_CONTACT_LISTENER_H*/