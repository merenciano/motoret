#include "render/commands/equirectangular-to-cubemap.h"

#include "core/manager.h"
#include "render/renderer.h"
#include "render/internal-resources.h"
#include "render/commands/create-cubemap.h"
#include "render/commands/create-texture.h"
#include "render/commands/draw.h"
#include "render/commands/render-options.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tools/resource-map.h" // TODO remove
namespace leep
{
    void EquirectangularToCubemap::executeCommand() const
    {
        // COMPILE SHADER
        Renderer &r = GM.renderer();
        InternalTexture ieq = r.textures_[in_equi_.handle()];
        *(Texture*)&out_cube_ = GM.resource_map().getTexture("Skybox");
        InternalTexture icu = r.textures_[out_cube_.handle()];

        if (ieq.version_ == 0)
        {
            CreateTexture().set_texture(in_equi_).executeCommand();
        }

        if (icu.version_ == 0)
        {
            CreateCubemap().set_texture(out_cube_).executeCommand();
        }
        
        glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
        glm::mat4 views[] =
        {
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
        };

        GLuint fb;
        glGenFramebuffers(1, &fb);
        glBindFramebuffer(GL_FRAMEBUFFER, fb);
        glViewport(0, 0, icu.width_, icu.height_);
        Material m;
        EquirecToCubeData etcd;
        m.set_albedo(in_equi_);
        m.set_type(MT_EQUIREC_TO_CUBE);
        RenderOptions().enable_depth_test(false).enable_write_depth(false).executeCommand();
        for (int32_t i = 0; i < 6; ++i)
        {
            etcd.vp_ = proj * views[i];
            m.set_data(etcd);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, icu.internal_id_, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            Draw().set_geometry(Renderer::s_cube).set_material(m).executeCommand();
        }
    }
}