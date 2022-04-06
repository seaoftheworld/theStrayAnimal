#include "MultiLightsRenderer.h"

void MultiLightsRenderer::allocShadersData() {
    if (mlShader) {
        return;
    }

    MultiLightsShader *shader = new MultiLightsShader;
    if (!shader) {
        // shader is not allocated
        mlShader = NULL;
        return;
    }

    if (shader->getStatus() != BaseShader::link_prog_passed || shader->getProgId() <= 0) {
        // shader failed to compile
        shader->cleanUp();
        shader = NULL;

        mlShader = NULL;
        return;
    }


    // load projection matrix for the only once
    shader->start();
    shader->loadProjMatrix(getProjMatrix());
    shader->bindTextureSamplerToSlot();
    shader->stop();

    mlShader = shader;
}

void MultiLightsRenderer::freeShadersData() {

    if (mlShader) {
        mlShader->stop();
        mlShader->cleanUp();

        delete mlShader;
        mlShader = NULL;
    }

    entities.clear();
    // lights.clear();
}

bool MultiLightsRenderer::ready() {
    return (mlShader) ? (true) : (false);
}

void NormalMappedModelRenderer::allocShadersData() {
    if (nmShader) {
        return;
    }

    NormalMappedShader *shader = new NormalMappedShader;
    if (!shader) {
        // shader is not allocated
        nmShader = NULL;
        return;
    }

    if (shader->getStatus() != BaseShader::link_prog_passed || shader->getProgId() <= 0) {
        // shader failed to compile
        shader->cleanUp();
        shader = NULL;

        nmShader = NULL;
        return;
    }

    // load projection matrix for the only once
    shader->start();
        shader->loadProjMatrix(getProjMatrix());
        shader->bindTextureSamplerToSlot();
    shader->stop();

    nmShader = shader;
}

void NormalMappedModelRenderer::freeShadersData() {
    if (nmShader) {
        nmShader->stop();
        nmShader->cleanUp();

        delete nmShader;
        nmShader = NULL;
    }
}

bool NormalMappedModelRenderer::ready() {
    return (nmShader) ? (true) : (false);
}
