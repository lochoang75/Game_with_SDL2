#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H
#include "game_enum.h"

class LoaderParams
{
    public:
        LoaderParams(){};
        LoaderParams(int x, int y, int width, int height, enum eTextureList id);
        int get_x() const {return x_pos;};
        int get_y() const {return y_pos;};
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum eTextureList get_type() const {return mId;};
    private:
        int x_pos;
        int y_pos;
        int mWidth;
        int mHeight;
        enum eTextureList mId;
};

LoaderParams:: LoaderParams(int x, int y, int width, int height, enum eTextureList id)
{
    x_pos = x;
    y_pos = y;
    mWidth = width;
    mHeight = height;
    mId = id;
}
#endif /*LOADER_PARAMS_H*/