#include "loader_params.h"

LoaderParams:: LoaderParams(int x, int y, int width, int height, enum eTextureTypeList id)
{
    x_pos = x;
    y_pos = y;
    mWidth = width;
    mHeight = height;
    mId = id;
    mPhysType = ePHYSIC_STATIC;
    mFriction = 0.3f;
    mDensity = 1.0f;
    mRestitution = 0.5f;
    mShape = ePOLYGON_SHAPE;
}

