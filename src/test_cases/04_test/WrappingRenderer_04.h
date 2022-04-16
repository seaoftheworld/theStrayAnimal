#pragma once

// #include "Core/Renderers/Model/NoLightingRenderer.h"
// #include "Core/Renderers/Model/SpecularRenderer.h"
#include "Core/Renderers/Model/MultiLightsRenderer.h"

// #include "Core/Renderers/Terrain/TerrainRenderer.h"
#include "Core/Renderers/Gui/GuiRenderer.h"
#include "Core/Renderers/Skybox/SkyboxRenderer.h"
#include "Core/Renderers/Water/WaterRenderer.h"

#define PROFILING (0)
#include "Core/profile.h"

class WrappingRenderer_04 {  // need a base-wrapping-renderer ???
public:
    /*
    std::vector<Light *> lights;
    WrappingRenderer_04() {
        lights.clear();
    }
    ~WrappingRenderer_04() {
        lights.clear();
    }

    void addLights(Light *light) {
        lights.push_back(light);
    }
    // */

public:
    // NoLightingRenderer   nlRenderer;
    //   SpecularRenderer   spRenderer;
    MultiLightsRenderer mlRenderer;

    // TerrainRenderer terrainRenderer;
    GuiRenderer         guiRenderer;
    SkyboxRenderer   skyboxRenderer;
    WaterRenderer     waterRenderer;

    void specificSettingsOff();
    void specificSettingsOn();

    void processScene(std::vector<TexturedModel> &models, std::vector<Light> &lights) {
        prepare();
        mlRenderer.run(models, lights);
        skyboxRenderer.run();
    }

    void processScene(Light &light, float clipPlane[][4]) {
        prepare();
            // entityRenderer.run();
            // entityRenderer.run(*lights[0]);

            // glEnable(GL_CLIP_DISTANCE0);
            // mlRenderer.run(lights, clipPlane);
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

    void processWater(std::vector<WaterTile> &tiles, unsigned int dudv, unsigned int normal) {
        waterRenderer.run(tiles, dudv, normal);
    }

    void processWater(WaterFrameBuffers *fbos, unsigned int dudv, unsigned int normal) {
        waterRenderer.run(fbos, dudv, normal);
    }

    void processGui() {
        guiRenderer.run();
    }

private:
    void prepare() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
};
