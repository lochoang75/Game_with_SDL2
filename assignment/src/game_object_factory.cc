#include "game_object_factory.h"

GameObjectFactory:: GameObjectFactory()
{
    for (int i = 0; i < TOTAL_OBJECT; i++)
    {
        creator_list[i] = NULL;
    }
} 

void GameObjectFactory:: creator_register(enum eGameObjectType type, BaseCreator *pCreator)
{
    if (type >= TOTAL_OBJECT)
    {
        spdlog::error("Failed to set object to type %d, index out of range", type);
        return;
    }

    if (creator_list[type] != NULL)
    {
        creator_list[type] = pCreator;
    }
    else
    {
        spdlog::warn("You are set new creator for type %d it may cause memory leak here", type);
        creator_list[type] = pCreator;
    }
}

GameObject* GameObjectFactory::create_object(enum eGameObjectType type) const
{
    GameObject *created_object = NULL;
    if (type >= TOTAL_OBJECT)
    {
        spdlog::error("Failed to create object with type %d, it's not supported",type);
        return NULL;
    }
    else
    {
        created_object = creator_list[type]->create_object();
    }
    return created_object;
}

