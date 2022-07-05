#pragma once

#include "Core/Renderers/Model/MultiLightsRenderer.h"
#include "Core/Renderers/Model/NoLightingRenderer.h"
#include "Core/Renderers/Gui/GuiRenderer.h"

#include "Core/Renderers/Water/WaterRenderer.h"  // For the loopModes.cpp file to include WaterFBO class

// #include "LoopModels.h"  // for the vboID of post-processing rectangle
// class LoopModels;

const unsigned short NUM_LIGHTS = 5;
// Light light[NUM_LIGHTS];

class loopWrappingRenderer {
    std::vector<Light> lights;

public:
    NoLightingRenderer       nolightingRenderer;
    // MultiLightsEntityRenderer mlRenderer;
    NormalMappedModelRenderer nmRenderer;
    GuiRenderer              guiRenderer;

    loopWrappingRenderer() : guiRenderer(true) {
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

    // void specificSettingsOff() {}
    void specificSettingsOn() {
        // glClearColor(0.7f, 0.7f, 0.8f, 1.0f);
        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        // glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Usually enabled by default in driver
        glEnable(GL_MULTISAMPLE);

        // glEnable(GL_CULL_FACE);  // requried the model to be enclosed, otherwise
        // glCullFace(GL_BACK);     // will not be correctly displayed ???
        // glCullFace(GL_FRONT);
    }

    // supposed to be rendered into default fbo
    void process(vector<TexturedModel>& normalMappedModels, vector<GuiType00>&guis) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // mlRenderer.run(normalMappedModels, lights);
        nmRenderer.run(normalMappedModels, lights);

        guiRenderer.run(guis);
    }

    // supposed to be rendered into non-default fbo
    void processNoLighting(vector<TexturedModel> &models) {
        glClearColor(0.4f, 0.4f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // mlRenderer.run(texturedModels, lights);
        nolightingRenderer.run(models);
    }
};

class PostProcessing {
private:
    ContrastRenderer contrastRenderer;

    void start(unsigned int vboID) {
        // unsigned int stride_in_float = GuiType00::rect->getVerticesStride();
        unsigned int stride_in_float = 2;
        // unsigned int vertices_count = GuiType00::rect->getVerticesCount();
        // unsigned int vertices_count = 4;

        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,
            stride_in_float, GL_FLOAT,
            GL_FALSE,
            stride_in_float << 2,  // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
            0);
        glDisable(GL_DEPTH_TEST);
    }

    void stop() {
        glEnable(GL_DEPTH_TEST);
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

public:

    bool shaderOK() {
        if (contrastRenderer.ready())
            return true;
        else
            return false;
    }

    void run(int recVboID, int txID) {
        if (recVboID <= 0 || txID <= 0) {
            return;
        }

        start(recVboID);
        {
            contrastRenderer.run(0, txID);
        }
        stop();
    }
};
