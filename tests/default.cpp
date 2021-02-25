#include "leep.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void leep::Init()
{
    {
        // Resource creation CPU side (GPU allocation will occur on first use)
        ResourceMap &rm = GM.resource_map();
        const std::string tp = "../assets/tex/";
        rm.addTexture("Skybox", 1024.0f, 1024.0f, TexType::ENVIRONMENT);
        rm.addTexture("IrradianceEnv", 1024.0f, 1024.0f, TexType::ENVIRONMENT);
        rm.addTexture("PrefilterSpec", 128.0f, 128.0f, TexType::PREFILTER_ENVIRONMENT);
        rm.addTexture("LutMap", 512.0f, 512.0f, TexType::LUT);
        /*
        rm.addTexture("Cerberus_A" ,tp + "cerberus_A.png", TexType::SRGB);
        rm.addTexture("Cerberus_N" ,tp + "cerberus_N.png", TexType::RGB);
        rm.addTexture("Cerberus_M" ,tp + "cerberus_M.png", TexType::RGB);
        rm.addTexture("Cerberus_R" ,tp + "cerberus_R.png", TexType::RGB);
        rm.addGeometry("Cerberus"  ,"../assets/obj/cerberus.obj");
        */
    }

    GM.memory().createContainer(EntityType::RENDERABLE);

    PbrData mat_data;
    mat_data.color_ = glm::vec3(0.3f, 0.3f, 0.3f);
    mat_data.use_albedo_map_ = 0.0f;
    mat_data.use_pbr_maps_ = 0.0f;
    mat_data.tiling_x_ = 1.0f;
    mat_data.tiling_y_ = 1.0f;
    mat_data.metallic_ = 0.5f;
    mat_data.roughness_ = 0.4f;
    mat_data.reflectance_ = 0.5f;

    Entity e = Entity::CreateEntity("Pipa", EntityType::RENDERABLE);
    LTransform &tr = e.getComponent<LTransform>();
    tr.transform_ = glm::scale(tr.transform_,
                    glm::vec3(0.33f, 0.33f, 0.33f));
    Drawable &dw = e.getComponent<Drawable>();
    dw.geometry_ = GM.resource_map().getGeometry("Sphere");
    dw.material_.set_type(MaterialType::MT_PBR);
    dw.material_.set_data(mat_data);
    /*dw.material_.set_albedo(GM.resource_map().getTexture("HDREnv"));
    dw.material_.set_metallic(GM.resource_map().getTexture("Cerberus_M"));
    dw.material_.set_roughness(GM.resource_map().getTexture("Cerberus_R"));
    dw.material_.set_normal(GM.resource_map().getTexture("Cerberus_N"));*/

    DisplayList init_dl;
    init_dl.addCommand<RenderOptions>()
        .enable_depth_test(true)
        .enable_write_depth(true)
        .set_cull_face(CullFace::BACK)
        .enable_blend(true)
        .set_blend_func(BlendFunc::ONE, BlendFunc::ZERO);
    init_dl.addCommand<EquirectangularToCubemap>()
        .set_in_path("../assets/tex/env/rooftop-env.hdr")
        .set_out_cube(GM.resource_map().getTexture("Skybox"))
        .set_out_prefilter(GM.resource_map().getTexture("PrefilterSpec"))
        .set_out_lut(GM.resource_map().getTexture("LutMap"));
    init_dl.addCommand<EquirectangularToCubemap>()
        .set_in_path("../assets/tex/env/rooftop-dif.hdr")
        .set_out_cube(GM.resource_map().getTexture("IrradianceEnv"));
    init_dl.submit();

    /*LEEP_INFO("Draw: {0}", sizeof(Draw));
    LEEP_INFO("EquirecToCube: {0}", sizeof(EquirectangularToCubemap));
    LEEP_INFO("RenderOptions: {0}", sizeof(RenderOptions));
    LEEP_INFO("UsePbrMaterial: {0}", sizeof(UsePbrMaterial));
    LEEP_INFO("Material: {0}", sizeof(Material));
    LEEP_INFO("Geometry: {0}", sizeof(Geometry));
    LEEP_INFO("Texture: {0}", sizeof(Texture));
    LEEP_INFO("MaterialData: {0}", sizeof(Material::MaterialData));*/

    printf("%d\n", sizeof(int*));
    printf("%d\n", sizeof(DLComm*));
}

void leep::Logic()
{
    GM.input().updateInput();
    CameraMovement(1.0f, 1.0f).executeSystem();
    UpdateTransform(GM.memory().container(EntityType::RENDERABLE)).executeSystem();
    UpdateSceneGraph().executeSystem();
    //Entity::GetEntity("Pipa").getComponent<LTransform>().rotateYWorld(0.001f);
    // Render commands
    DisplayList dl;
    PbrSceneData pbr_sd;
    pbr_sd.view_projection_ = GM.camera().view_projection();
    pbr_sd.camera_position_ = GM.camera().position();
    pbr_sd.light_direction_intensity_ = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

    Material full_screen_img;
    full_screen_img.set_type(MaterialType::MT_FULL_SCREEN_IMAGE);
    full_screen_img.set_albedo(GM.camera().framebuffer().color());
    
    dl.addCommand<UseFramebuffer>()
        .set_framebuffer(GM.camera().framebuffer());

    dl.addCommand<RenderOptions>()
        .enable_depth_test(true)
        .enable_write_depth(true)
        .set_cull_face(CullFace::BACK)
        .enable_blend(true)
        .set_blend_func(BlendFunc::ONE, BlendFunc::ZERO);

    dl.addCommand<Clear>()
        .set_clear_buffer(true, true, false)
        .set_clear_color(0.2f, 0.2f, 0.2f, 1.0f);

    dl.addCommand<UsePbrMaterial>()
        .set_scene_data(pbr_sd)
        .set_irradiance_map(GM.resource_map().getTexture("IrradianceEnv"))
        .set_prefilter_map(GM.resource_map().getTexture("PrefilterSpec"))
        .set_lut_map(GM.resource_map().getTexture("LutMap"));

    dl.submit();

    Render(GM.memory().container(EntityType::RENDERABLE)).executeSystem();
    
    DisplayList dl2;
    dl2.addCommand<UseSkyboxMaterial>();
    dl2.addCommand<DrawSkybox>()
        .set_cubemap(GM.resource_map().getTexture("Skybox"));
   
    dl2.addCommand<UseFramebuffer>();

    dl2.addCommand<RenderOptions>()
        .enable_depth_test(false);

    dl2.addCommand<Clear>()
        .set_clear_buffer(true, false, false)
        .set_clear_color(1.0f, 0.0f, 0.0f, 1.0f);

    dl2.addCommand<Draw>()
        .set_geometry(GM.resource_map().getGeometry("Quad"))
        .set_material(full_screen_img);
        
    dl2.submit();
    //DeleteReleased().executeSystem();
}
