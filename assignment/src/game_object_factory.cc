#include "game_object_factory.h"

GameObjectFactory * GameObjectFactory::mInstance = NULL;

GameObjectFactory:: GameObjectFactory()
{
    for (int i = 0; i < eTOTAL_OBJECT; i++)
    {
        creator_list[i] = NULL;
    }
} 

void GameObjectFactory:: creator_register(enum eGameObjectType type, BaseCreator *pCreator)
{
    if (type >= eTOTAL_OBJECT)
    {
        LogError("Failed to set object to type %d, index out of range", type);
        return;
    }

    if (creator_list[type] != NULL)
    {
        LogError("You are set new creator for type %s it may cause memory leak here", DBG_ObjectType(type));
        creator_list[type] = pCreator;
    }
    else
    {
        LogDebug("Creator <%p> has registered to create object %s", pCreator, DBG_ObjectType(type));
        creator_list[type] = pCreator;
    }
}

GameObject* GameObjectFactory::create_object(enum eGameObjectType type) const
{
    GameObject *created_object = NULL;
    if (type >= eTOTAL_OBJECT)
    {
        LogWarning("Failed to create object with type %d, it's not supported", type);
        return NULL;
    }
    else
    {
        created_object = creator_list[type]->create_object();
    }
    return created_object;
}

