#include "game_container_object.h"
#include "log_wrapper.h"
#include "box2d_facade.h"

void ContainedObject:: set_container(GameContainerObject *container)
{
    if (mContainer != NULL)
    {
        LogWarning("Object is contained in other object, remove it first contained !");
    }
    else
    {
        mContainer = container;
    }
}

void ContainedObject::set_anchorindex(int index)
{
    if (mAnchorIndex != -1)
    {
        LogWarning("Object is contained in other object, implict remove current container");
        unjoint_from_current_container();
    }
    mAnchorIndex = index;
}

void ContainedObject:: unjoint_from_current_container()
{
    if (mContainer != NULL)
    {
        mContainer->unjoint_object(mAnchorIndex);
        mAnchorIndex = -1;
        mContainer = NULL;
    }
}

int GameContainerObject::joint_new_object(ContainedObject *target)
{
    if (mAnchorArray == NULL || mJointArray == NULL)
    {
        LogError("You need to init anchor array and joint array in order to joint object");
        return -1;
    }

    for (int i = 0; i < mTotalAnchor; i++)
    {
        if (mJointArray[i] == NULL)
        {
            b2Body *target_body = target->get_body();
            target_body->SetAngularDamping(10.0f);
            b2Body *host_body = container_get_body();
            b2Vec2 host_anchor = container_get_anchor_point(i);
            b2Vec2 target_anchor = target->get_anchor_point();
            LogDebug("Found anchor at %d will joint apple to this", i);
            mJointArray[i] = Box2DPhysicalFacade::joint_object_with_distance(host_body, target_body, host_anchor, target_anchor);
            target->set_container(this);
            target->set_anchorindex(i);
            return i;
        }
    }

    return -1;
}

void GameContainerObject::unjoint_object(int anchor_index)
{
    if (mAnchorArray == NULL || mJointArray == NULL)
    {
        LogError("You need to init anchor array and joint array in order to unjoint object");
        return;
    }

    if (anchor_index >= mTotalAnchor)
    {
        LogError("Remove joint index out of range");
        return;
    }

    Box2DPhysicalFacade::destroy_joint(mJointArray[anchor_index]);
    mJointArray[anchor_index] = NULL;
}

b2Vec2 GameContainerObject::container_get_anchor_point(int index)
{
    int anchor_x = mAnchorArray[index].x;
    int anchor_y = mAnchorArray[index].y;
    float x_pos, y_pos;
    Box2DPhysicalFacade::compute_cartesian_origin(anchor_x, anchor_y, 40, 40, x_pos, y_pos);
    b2Vec2 anchor_point(x_pos, y_pos);
    LogDebug("Tree anchor point at x: %0.4f y: %0.4f", x_pos, y_pos);
    return anchor_point;
}
