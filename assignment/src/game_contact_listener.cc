#include "game_contact_listener.h"
#include <map>

#include "game_constant.h"
#include "game_object.h"
#include "bird.h"
#include "fruit.h"
#include "log_wrapper.h"

void GameContactListener::BeginContact(b2Contact *contact)
{
    b2BodyUserData user_data_1 = contact->GetFixtureA()->GetBody()->GetUserData();
    b2BodyUserData user_data_2 = contact->GetFixtureB()->GetBody()->GetUserData();
    GameObject *obj_1, *obj_2;
    if (user_data_1.pointer != 0)
    {
        obj_1 = (GameObject*)user_data_1.pointer;
    }
    else
    {
        LogDebug("Contact object 1 user data is unset");
        return;
    }

    if (user_data_2.pointer != 0)
    {

        obj_2 = (GameObject*)user_data_2.pointer;
    }
    else
    {
        LogDebug("Contact object 2 user data is unset");
        return;
    }

    eGameObjectType object_1_type = obj_1->get_object_type();
    eGameObjectType object_2_type = obj_2->get_object_type();
    LogDebug("Contact between %s and %s has begin", DBG_ObjectType(object_1_type), DBG_ObjectType(object_2_type));

    std::pair<eGameObjectType, eGameObjectType> key_pair;
    if (object_1_type > object_2_type)
    {
        key_pair = std::make_pair(object_1_type, object_2_type);
    }
    else
    {
        GameObject *tmp = obj_1;
        obj_1 = obj_2;
        obj_2 = tmp;
        key_pair = std::make_pair(object_2_type, object_1_type);
    }
    std::map<std::pair<eGameObjectType, eGameObjectType>, ContactHandler>::iterator it;

    it = mContactMap.find(key_pair);
    if (it != mContactMap.end())
    {
        ContactHandler handler = it->second;
        if (handler != NULL)
        {
            handler(obj_1, obj_2);
        }
    }
}

void GameContactListener::EndContact(b2Contact *contact)
{
}

static void handle_contact_fruit_fruit(GameObject *first, GameObject *seccond)
{
    LogDebug("Contact handler for fruit and fruit has been called");
}

static void handle_contact_bird_fruit(GameObject *bird, GameObject *fruit)
{
    LogDebug("Contact handler for bird and fruit has been called");
    eBirdState bird_state = static_cast<BirdObject*>(bird)->handle_event(eGAME_EVENT_CONTACT_TARGET);
    if (bird_state == eBIRD_CATCH_THE_FRUIT)
    {
        static_cast<FruitObject*>(fruit)->handle_event(eGAME_EVENT_CONTACT_TARGET);
        static_cast<BirdObject*>(bird)->bird_aim_this_fruit((FruitObject*)fruit);
    }
}

void GameContactListener::InitContactHandler()
{
    HandlerRegister(eFRUIT_OBJECT, eFRUIT_OBJECT, &handle_contact_fruit_fruit);
    HandlerRegister(eBIRD_OBJECT, eFRUIT_OBJECT, &handle_contact_bird_fruit);
}

void GameContactListener::HandlerRegister(eGameObjectType firstObj, eGameObjectType seccondObj, ContactHandler handler)
{
    mContactMap.insert(std::make_pair(std::make_pair(firstObj, seccondObj), handler));
    LogDebug("Register to handle contact between %s and %s", DBG_ObjectType(firstObj), DBG_ObjectType(seccondObj));
}
