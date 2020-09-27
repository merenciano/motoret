#include "use-pbr-material.h"

namespace motoret
{
    UsePbrMaterial::UsePbrMaterial()
    {

    }

    UsePbrMaterial::~UsePbrMaterial()
    {

    }

    UsePbrMaterial& UsePbrMaterial::set_data(const PbrSceneData &data)
    {
        data_ = data;
        return *this;
    }
}

#ifdef MOTORET_OPENGL
    #include "render/commands/opengl/opengl-use-pbr-material.cpp"
#endif