#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H
#include "game_enum.h"

class LoaderParams
{
    public:
        LoaderParams(){};
        LoaderParams(int x, int y, int width, int height, enum eTextureTypeList id);
        void set_physic(enum eGameObjectPhysic);
        int get_x() const {return x_pos;};
        int get_y() const {return y_pos;};
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum eTextureTypeList get_type() const {return mId;};
        enum eGameObjectPhysic get_physic() const {return mPhysType;};
    private:
        int x_pos;
        int y_pos;
        int mWidth;
        int mHeight;
        enum eTextureTypeList mId;
        enum eGameObjectPhysic mPhysType;
};

LoaderParams:: LoaderParams(int x, int y, int width, int height, enum eTextureTypeList id)
{
    x_pos = x;
    y_pos = y;
    mWidth = width;
    mHeight = height;
    mId = id;
    mPhysType = ePHYSIC_STATIC;
}

void LoaderParams::set_physic(enum eGameObjectPhysic phys_type)
{
    mPhysType = phys_type;
}
#endif /*LOADER_PARAMS_H*/