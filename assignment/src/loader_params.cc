#include "loader_params.h"

LoaderParams:: LoaderParams(int x, int y, int width, int height, enum eTextureType id)
{
    x_pos = x;
    y_pos = y;
    mWidth = width;
    mHeight = height;
    mId = id;
    mHaveFixture = true;
}

