#ifndef GAME_OBJECT_FACTORY
#define GAME_OBJECT_FACTORY
#include <iostream>
#include <spdlog/spdlog.h>

#include "game_enum.h"
#include "game_object.h"

class BaseCreator
{
    public:
        BaseCreator() {};
        virtual ~BaseCreator(){};
        virtual GameObject *create_object() = 0;
};

class GameObjectFactory
{
    public:
        static GameObjectFactory* Instance() 
        {
            if (mInstance == NULL)
            {
                mInstance = new GameObjectFactory();
            }
            return mInstance;
        }
        void creator_register(enum eGameObjectType type, BaseCreator *pCreator);
        GameObject* create_object(enum eGameObjectType type) const;
    
    private:
        GameObjectFactory(); 
        ~GameObjectFactory(){};
        static GameObjectFactory *mInstance;
        BaseCreator* creator_list[TOTAL_OBJECT];
};


#endif /* GAME_OBJECT_FACTORY */