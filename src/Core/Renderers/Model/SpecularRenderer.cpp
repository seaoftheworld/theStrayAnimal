#include "SpecularRenderer.h"

void SpecularRenderer::allocShadersData() {
    if (specularShader) {
        return;
    }

    // StaticShader *shader = new StaticShader;
    SpecularShader *shader = new SpecularShader;

    if (!shader) {
        // shader is not allocated
        specularShader = NULL;
        return;
    }

    if (shader->getStatus() != BaseShader::link_prog_passed || shader->getProgId() <= 0) {
        // shader failed to compile
        shader->cleanUp();
        shader = NULL;

        specularShader = NULL;
        return;
    }


    // load projection matrix for the only once
    shader->start();
    shader->loadProjMatrix(getProjMatrix());
    shader->bindTextureSamplerToSlot();
    shader->stop();

    specularShader = shader;
}

void SpecularRenderer::freeShadersData() {

    if (specularShader) {
        specularShader->stop();
        specularShader->cleanUp();

        delete specularShader;
        specularShader = NULL;
    }

    entities.clear();
}

bool SpecularRenderer::ready() {
    return (specularShader) ? (true) : (false);
}
