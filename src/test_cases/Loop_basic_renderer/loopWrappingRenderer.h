#include "Core/Renderers/Model/MultiLightsRenderer.h"
#include "Core/Renderers/Model/NoLightingRenderer.h"

const unsigned short NUM_LIGHTS = 5;
// Light light[NUM_LIGHTS];

class loopWrappingRenderer {
    std::vector<Light> lights;

public:
    loopWrappingRenderer() {
        float pos[NUM_LIGHTS][Light::Position::max_pos] = {
            { 20.0f,   0.0f, 25.0f},  // x+
            {  0.0f,  20.0f, 25.0f},  // y+
            {-20.0f,   0.0f, 25.0f},  // x-
            {  0.0f, -20.0f, 25.0f},  // y-
            {  0.0f, -20.0f, 1.0f}    // y-
        };
        float color[NUM_LIGHTS][Light::Color::max_color] = {
            { 1.0f, 1.0f, 0.6f },   // yellow
            { 0.9f, 1.0f, 0.9f },   // green
            { 1.0f, 1.0f, 1.0f },
            { 0.6f, 0.6f, 1.0f },   // blue
            { 1.0f, 1.0f, 1.0f }    // white
        };
        float attenuation[Light::Attenuation::max_att] = { 2.0f, 0.02f, 0.0f };

        for (int i = 0; i < NUM_LIGHTS; i++) {
            Light light;
            light.setValues(&pos[i], &color[i], &attenuation);
            lights.push_back(light);
        }
    }
    virtual ~loopWrappingRenderer() {
        lights.clear();
    }

    NoLightingRenderer       nlRenderer;
    // MultiLightsEntityRenderer mlRenderer;
    NormalMappedModelRenderer nmRenderer;

    // void specificSettingsOff() {}
    void specificSettingsOn() {
        // glClearColor(0.7f, 0.7f, 0.8f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        // glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_MULTISAMPLE); // Usually enabled by default in driver

        // glEnable(GL_CULL_FACE);  // requried the model to be enclosed, otherwise
        // glCullFace(GL_BACK);     // will not be correctly displayed ???
        // glCullFace(GL_FRONT);
    }

    void process(std::vector<TexturedModel>& texturedModels, std::vector<TexturedModel>& normalMappedModels) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // mlRenderer.run(texturedModels, lights);
        nlRenderer.run(texturedModels);
        // mlRenderer.run(normalMappedModels, lights);
        nmRenderer.run(normalMappedModels, lights);
    }
};
