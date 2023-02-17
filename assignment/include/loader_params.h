#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H
#include "game_enum.h"

class LoaderParams
{
    public:
        LoaderParams(){};
        LoaderParams(int x, int y, int width, int height, enum eTextureTypeList id);
        int get_x() const {return x_pos;};
        int get_y() const {return y_pos;};
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum eTextureTypeList get_type() const {return mId;};
    private:
        int x_pos;
        int y_pos;
        int mWidth;
        int mHeight;
        enum eTextureTypeList mId;
};
#endif /*LOADER_PARAMS_H*/