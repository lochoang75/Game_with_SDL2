#include "loader_params.h"

LoaderParams:: LoaderParams(int x, int y, int width, int height, enum eTextureTypeList id)
{
    x_pos = x;
    y_pos = y;
    mWidth = width;
    mHeight = height;
    mId = id;
}