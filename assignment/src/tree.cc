#include "tree.h"

void TreeObject::load(const LoaderParams *pParams)
{
    mWidth = pParams->get_width();
    mHeight = pParams->get_height();
    x = pParams->get_x();
    y = pParams->get_y();
    id = pParams->get_type();
    ErrorCode_t ret = container_init_anchor_point();
    if (ret != kSUCCESS)
    {
        LogError("Unable to initial anchor point for tree");
        return;
    }

    ret = create_object_body();
    if (ret != kSUCCESS)
    {
        LogError("Unable to create body");
        return;
    }

    ret = create_object_fixture();
    if (ret != kSUCCESS)
    {
        LogError("Unable to create fixtures");
        return;
    }
    
    LogDebug("Loaded sucessful");

}

ErrorCode_t TreeObject:: create_object_fixture() 
{
    for (int i = 0; i < mTotalAnchor; i++)
    {
        b2EdgeShape edge;
        int anchor_x = mAnchorArray[i].x;
        int anchor_y = mAnchorArray[i].y;
        float x_pos, y_pos; 
        Box2DPhysicalFacade::compute_cartesian_origin(anchor_x, anchor_y, kAnchorSize, kAnchorSize, x_pos, y_pos);
        b2Vec2 edge_position_start(x_pos - 0.1, y_pos);
        b2Vec2 edge_position_end(x_pos + 0.1, y_pos);
        edge.SetTwoSided(edge_position_start, edge_position_end);
        b2FixtureDef fixture_def;
        fixture_def.shape = &edge;
        fixture_def.filter.categoryBits = kTREE;
        fixture_def.filter.maskBits = kFRUIT;
        Box2DPhysicalFacade::create_fixture(mBody, fixture_def);
    }

    b2PolygonShape shape;
    float w_plat = Box2DPhysicalFacade::compute_distance_to_meter(mWidth - 200);
    float h_plat = Box2DPhysicalFacade::compute_distance_to_meter(mHeight); 
    shape.SetAsBox(w_plat/2, h_plat/2);
    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;
    fixture_def.filter.categoryBits = kTREE;
    fixture_def.filter.maskBits = kKID;
    Box2DPhysicalFacade::create_fixture(mBody, fixture_def);

    return kSUCCESS;
}

ErrorCode_t TreeObject:: container_init_anchor_point()
{
    mAnchorArray = new b2Vec2[mTotalAnchor];
    mJointArray = new b2Joint*[mTotalAnchor];
    if (mAnchorArray == NULL)
    {
        LogError("Unable to allocate memory for anchor point");
        return kNO_MEM;
    }

    if (mJointArray == NULL)
    {
        LogError("Unable to allocate memory for joint array");
        delete mAnchorArray;
        mAnchorArray = NULL;
        return kNO_MEM;
    }

    int anchor_x_location = 40;
    int anchor_y_location = 10;
    srand(time(NULL));
    for (int i = 0; i < mTotalAnchor; i++)
    {
        if (this->x + anchor_x_location >= this->x + mWidth - 40)
        {
            anchor_x_location = 40;
            anchor_y_location += (rand() % 10 + 20);
        }
        else
        {
            anchor_y_location += (rand() % 5 + 20);
        }
        mAnchorArray[i].Set(x + anchor_x_location, y + anchor_y_location);
        mJointArray[i] = NULL;
        anchor_x_location += (rand() % 40 + 30);
    }
    return kSUCCESS;
}

b2Body* TreeObject::container_get_body()
{
    return mBody;
}

b2DistanceJointDef TreeObject::container_get_joint_config(b2Body *host, b2Body *target, b2Vec2 host_anchor, b2Vec2 target_anchor) const
{
    b2DistanceJointDef joint_def;
    joint_def.Initialize(host, target, host_anchor, target_anchor);
    joint_def.collideConnected = true;
    joint_def.maxLength = 0.0f;
    return joint_def;
}

ErrorCode_t TreeObject:: get_tree_anchor_point(int &x, int &y) const
{
    for (int i = 0; i < mTotalAnchor; i++)
    {
        if (mJointArray[i] == NULL)
        {
            x = mAnchorArray[i].x;
            y = mAnchorArray[i].y;
            return kSUCCESS;
        }
    }

    return kFAILED;
}

GameObject* TreeCreator:: create_object() const
{
    TreeObject *new_object = new TreeObject();
    return (GameObject*)new_object;
}