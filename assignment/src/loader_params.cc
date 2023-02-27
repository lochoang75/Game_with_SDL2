#include "loader_params.h"

LoaderParams:: LoaderParams(int x, int y, int width, int height, enum eTextureTypeList id)
{
    x_pos = x;
    y_pos = y;
    mWidth = width;
    mHeight = height;
    mId = id;
    mPhysType = ePHYSIC_STATIC;
    mFriction = 0.0f;
    mDensity = 0.0f;
    mRestitution = 0.0f;
    mShape = ePOLYGON_SHAPE;
}

