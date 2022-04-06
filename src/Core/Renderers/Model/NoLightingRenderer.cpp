#include "NoLightingRenderer.h"

void NoLightingRenderer::allocShadersData() {
    if (noLightingShader) {
        return;
    }

    // SpecularShader *shader = new SpecularShader;
    NoLightingShader *shader = new NoLightingShader;

    if (!shader) {
        // shader is not allocated
        noLightingShader = NULL;
        return;
    }

    if (shader->getStatus() != BaseShader::link_prog_passed || shader->getProgId() <= 0) {
        // shader failed to compile
        shader->cleanUp();
        shader = NULL;

        noLightingShader = NULL;
        return;
    }

    // load projection matrix for only once here
    shader->start();
    shader->loadProjMatrix(getProjMatrix());
    shader->bindTextureSamplerToSlot();
    shader->stop();

    noLightingShader = shader;
}

void NoLightingRenderer::freeShadersData() {

    if (noLightingShader) {
        noLightingShader->stop();
        noLightingShader->cleanUp();

        delete noLightingShader;
        noLightingShader = NULL;
    }

    entities.clear();
}

bool NoLightingRenderer::ready() {
    return (noLightingShader) ? (true) : (false);
}
