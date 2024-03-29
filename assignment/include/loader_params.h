#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H
#include "texture_manager.h"

class LoaderParams
{
    public:
        LoaderParams(){};
        LoaderParams(int x, int y, int width, int height, enum eTextureType id);
        void add_physical_fixture(bool will_create) {mHaveFixture = will_create;};
        int get_x() const {return x_pos;};
        int get_y() const {return y_pos;};
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum eTextureType get_type() const {return mId;};
        bool is_create_fixture() const {return mHaveFixture;};
    private:
        int x_pos;
        int y_pos;
        int mWidth;
        int mHeight;
        enum eTextureType mId;
        bool mHaveFixture;
};

#endif /*LOADER_PARAMS_H*/