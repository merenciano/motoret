// Lucas Merenciano Martinez <lucasmermar@gmail.com>

#ifndef __LEEP_RENDER_MATERIAL_TYPES_H__
#define __LEEP_RENDER_MATERIAL_TYPES_H__ 1

#include "glm/mat4x4.hpp"

namespace leep
{
    // Not enum class because its values are used as array indexes for the renderer materials
    enum MaterialType
    {
        MT_PBR = 0,
        MT_PLAIN_COLOR = 1,
        MT_SKYBOX = 2,

        MT_MAX,
        MT_NONE
    };

    struct PbrData
    {
	private:
		// The model matrix is setted with set_model method of the material
		float model_[16];
	public:
        float tiling_x_;
        float tiling_y_;
		float roughness_;
		float metallic_;
		float reflectance_;
		float padding[3];
    };

    struct PlainColorData
    {
        glm::mat4 model_;
        float r_;
        float g_;
        float b_;
        float a_;
    };
}
#endif // __LEEP_RENDER_MATERIAL_TYPES_H__