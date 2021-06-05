// Lucas Merenciano Martinez <lucasmermar@gmail.com>

#ifndef __LEEP_RENDER_COMMANDS_USE_MATERIAL_H__
#define __LEEP_RENDER_COMMANDS_USE_MATERIAL_H__

#include "core/common-defs.h"
#include "render/material-types.h"
#include "render/display-list-command.h"
#include "render/texture.h"
 
namespace leep
{
    class UseMaterial: public DLComm
    {
    public:
        UseMaterial();
        UseMaterial(const UseMaterial&) = delete;
        UseMaterial(UseMaterial&&) = delete;
        ~UseMaterial();

        UseMaterial& set_type(MaterialType type);
        UseMaterial& set_float(float *data, int32_t count);
        UseMaterial& set_tex(Texture *textures, int32_t count, int32_t cube_start = -1);

        virtual void executeCommand() const override;

    private:
        size_t fcount_;
        size_t icount_;
        float *fdata_;
        int32_t *idata_;
        int32_t cube_start_;
        MaterialType type_;
    };
}

#endif // __LEEP_RENDER_COMMANDS_USE_MATERIAL_H__