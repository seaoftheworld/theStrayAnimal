#pragma once

// #include "Core/Renderers/Model/ModelRendererSpecular.h"
#include "Core/Renderers/Model/MultiLightsRenderer.h"
#include "Core/Renderers/Model/NoLightingRenderer.h"
#include "Core/Renderers/Gui/GuiRenderer.h"

// #include "Core/Renderers/Terrain/TerrainRenderer.h"
#include "Core/Renderers/Skybox/SkyboxRenderer.h"
#include "Core/Renderers/Water/WaterRenderer.h"

#define PROFILING (0)
#include "Core/profile.h"

class TSA_WrappingRenderer {  // need a base-wrapping-renderer ???
    // std::vector<Light *> lights;
    std::vector<Light> lights;

public:
    // TSA_WrappingRenderer(Loader &loader) : picRenderer(loader) {
    TSA_WrappingRenderer() {
        // lights.clear();
    }
    ~TSA_WrappingRenderer() {
        lights.clear();
    }

    // void addLights(Light *light) {
    //     lights.push_back(light);
    // }
    void addLights(Light &light) {
        lights.push_back(light);
    }

public:
    // BasicEntityRenderer   modelRenderer;
    // SpecularEntityRenderer   modelRenderer;
    MultiLightsRenderer mlRenderer;
    NoLightingRenderer  nlRenderer;

    // TerrainRenderer terrainRenderer;
    // GuiRenderer         guiRenderer;
    SkyboxRenderer   skyboxRenderer;
    WaterRenderer     waterRenderer;

    // PictureRenderer     picRenderer;

    void specificSettingsOff();
    void specificSettingsOn();

    void processScene(
        std::vector<TexturedModel> &player_goals_models, std::vector<Light> &lights,
        std::vector<TexturedModel> &the_rest_models) {
        prepare();

        mlRenderer.run(player_goals_models, lights);
        nlRenderer.run(the_rest_models);

        skyboxRenderer.run();
    }

    /*
    void processScene(float clipPlane[][4]) {
        prepare();
            // modelRenderer.run();
            // modelRenderer.run(*lights[0]);

            // glEnable(GL_CLIP_DISTANCE0);
            modelRenderer.run(lights, clipPlane);
            // glDisable(GL_CLIP_DISTANCE0);

            // Light test_light; {
            //     // float position[Light::Position::max_pos] = {0.0f, 1.0f, 2.0f};
            //     // float position[Light::Position::max_pos] = {20.0f, 0.0f, 20.0f};
            //     float position[Light::Position::max_pos] = {10.0f, 10.0f, 20.0f};
            //     // float color[Light::Color::max_color] = {1.6f, 1.2f, 1.6f};
            //     float color[Light::Color::max_color] = { 1.6f, 1.6f, 1.6f };
            //     float dummy_attenuation[Light::Attenuation::max_att] = {0.0f, 0.0f, 0.0f};
            //     test_light.setValues(&position, &color, &dummy_attenuation);
            // }
            // terrainRenderer.run(test_light);

            // terrainRenderer.run(lights, clipPlane);
            skyboxRenderer.run();
    }
    // */

    // void processGui() {
    //     guiRenderer.run();
    // }

    void processWater(WaterFrameBuffers *fbos, unsigned int dudv, unsigned int normal) {
        waterRenderer.run(fbos, dudv, normal);
    }

private:
    void prepare() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
};
