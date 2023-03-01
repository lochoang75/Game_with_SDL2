#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H
#include "game_enum.h"

class LoaderParams
{
    public:
        LoaderParams(){};
        LoaderParams(int x, int y, int width, int height, enum eTextureTypeList id);
        void add_physical_shape(enum ePhysicalShape shape) {mShape = shape;};
        void add_physical_object_type(enum eGameObjectPhysic phys_type) {mPhysType = phys_type;};
        void add_physical_density(float density) {mDensity = density;};
        void add_physical_friction(float friction) {mFriction = friction;};
        void add_physical_restitution(float restitution) {mRestitution = restitution;};
        int get_x() const {return x_pos;};
        int get_y() const {return y_pos;};
        int get_width() const {return mWidth;};
        int get_height() const {return mHeight;};
        enum ePhysicalShape get_physical_shape() const {return mShape;};
        enum eGameObjectPhysic get_physical_object_type() const {return mPhysType;};
        float get_physical_density() const {return mDensity;};
        float get_physical_friction() const {return mFriction;};
        float get_physical_restitution() const {return mRestitution;};
        enum eTextureTypeList get_type() const {return mId;};
    private:
        int x_pos;
        int y_pos;
        int mWidth;
        int mHeight;
        enum eTextureTypeList mId;
        enum eGameObjectPhysic mPhysType;
        enum ePhysicalShape mShape;
        float mDensity;
        float mFriction;
        float mRestitution;
};

#endif /*LOADER_PARAMS_H*/