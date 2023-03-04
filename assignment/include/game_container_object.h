#ifndef GAME_CONTAINER_OBJECT_H
#define GAME_CONTAINER_OBJECT_H
#include "box2d.h"
#include "game_constant.h"
extern const int kAnchorSize;

class GameContainerObject;

class ContainedObject
{
    public:
        ContainedObject(): mContainer(NULL), mAnchorIndex(-1){};
        virtual ~ContainedObject(){};
    protected:
        friend class GameContainerObject;

        virtual b2Body* get_body() = 0;
        virtual b2Vec2 get_anchor_point() const = 0;
        void set_container(GameContainerObject *container);
        void set_anchorindex(int index);
        void unjoint_from_current_container();
    private:
        GameContainerObject *mContainer;
        int mAnchorIndex;
};

class GameContainerObject
{
    public:
        GameContainerObject(int total_anchor): mAnchorArray(NULL), mJointArray(NULL), mTotalAnchor(total_anchor){};
        int joint_new_object(ContainedObject *);
        void unjoint_object(int anchor_index);

    protected:
        virtual ErrorCode_t container_init_anchor_point() = 0;
        virtual b2Body *container_get_body() = 0;
        b2Vec2 *mAnchorArray;
        b2Joint **mJointArray;
        int mTotalAnchor;
    private:
        b2Vec2 container_get_anchor_point(int index);
};
#endif /*GAME_CONTAINER_OBJECT_H*/