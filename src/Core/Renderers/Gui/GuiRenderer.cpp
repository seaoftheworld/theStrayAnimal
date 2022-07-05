#include "GuiRenderer.h"

void GuiRenderer::allocShadersData() {}

void GuiRenderer::allocShadersDataMod(bool forFBO) {

    if (guiShader) {
        return;
    }

    // Compile and Link the gui-shader
    GuiType00Shader *shader = new GuiType00Shader(forFBO);
    
    if (!shader) {
        // shader is not allocated
        guiShader = NULL;
        return;
    }

    if (shader->getStatus() != BaseShader::link_prog_passed || shader->getProgId() <= 0) {
        // shader failed to compile
        printf("guiShader status: %d\n", shader->getStatus());
        shader->cleanUp();
        shader = NULL;

        guiShader = NULL;
        return;
    }

    // printf("guiShader ok\n");
    // load projection matrix for the only once
    shader->start();
        // // guiShader doesn't support projection/view_matrix now
        // shader->loadProjMatrix(getProjMatrix());
    shader->stop();

    guiShader = shader;
}

void GuiRenderer::freeShadersData() {

    // The specific shader's class-object is deleted here in derived-class
    if (guiShader) {
        guiShader->stop();
        guiShader->cleanUp();

        delete guiShader;
        guiShader = NULL;
    }
}

bool GuiRenderer::ready() {
    return (guiShader) ? (true) : (false);
}

/*
PictureShader *PictureRenderer::picShader = NULL;
unsigned short PictureRenderer::uv_vboId = 0;

void PictureRenderer::allocUvBuffer(Loader& loader) {
    const float uv_buffer[] = {
        0.0f, 0.0f,  // left  top        -   
        0.0f, 1.0f,  // left  bottom     |\ 
        1.0f, 1.0f,  // right bottom     |_\

        1.0f, 1.0f,  // right  bottom  __
        1.0f, 0.0f,  // right  top     \ |
        0.0f, 0.0f,  // left   top      \|
    };

    SingleAttributeModel *uvBuffer =
        loader.allocSingleAttributeModel((float*)uv_buffer, \
            PICTURE_RENDERER_UV_VBO_VERTICES_STRIDE, \
            PICTURE_RENDERER_UV_VBO_VERTICES_NUM);

    if (uvBuffer) {
        uv_vboId = uvBuffer->getVboID();
    }
}

void PictureRenderer::allocShadersData() {

    PictureShader *tempShader = NULL;
    if (picShader) {
        return;
    }

    tempShader = new PictureShader;    
    if (!tempShader) {
        // shader is not allocated
        picShader = NULL;
        return;
    }

    if (tempShader->getStatus() != BaseShader::link_prog_passed || 
        tempShader->getProgId() <= 0) {
        // shader failed to compile
        printf("PictureShader error status: %d\n", tempShader->getStatus());
        tempShader->cleanUp();
        tempShader = NULL;

        picShader = NULL;
        return;
    }

    // load projection matrix for the only once
    tempShader->start(); {
        float fixed_2d_ProjViewMatrix[16] = {};
        tempShader->loadProjMatrix( fixed_2d_ProjViewMatrix );
    }
    tempShader->stop();

    picShader = tempShader;
}

void PictureRenderer::freeShadersData() {

    // The specific shader's class-object is deleted here in derived-class
    if (picShader) {
        picShader->stop();
        picShader->cleanUp();

        delete picShader;
        picShader = NULL;
    }

    pictures.clear();
}

bool PictureRenderer::ready() {
    return (picShader && uv_vboId) ? (true) : (false);
}
// */

void ContrastRenderer::allocShadersData() {

    if (contrastShader) {
        return;
    }

    // Compile and Link the constrast-shader
    ContrastShader *shader = new ContrastShader();
    
    if (!shader) {
        // shader is not allocated
        contrastShader = NULL;
        return;
    }

    if (shader->getStatus() != BaseShader::link_prog_passed || shader->getProgId() <= 0) {
        // shader failed to compile
        printf("contrastShader status: %d\n", shader->getStatus());
        shader->cleanUp();
        shader = NULL;

        contrastShader = NULL;
        return;
    }

    // printf("contrastShader ok\n");
    // load projection matrix for the only once
    shader->start();
        // // contrastShader doesn't support projection/view_matrix now
        // shader->loadProjMatrix(getProjMatrix());
    shader->stop();

    contrastShader = shader;
}

void ContrastRenderer::freeShadersData() {

    // The specific shader's class-object is deleted here in derived-class
    if (contrastShader) {
        contrastShader->stop();
        contrastShader->cleanUp();

        delete contrastShader;
        contrastShader = NULL;
    }
}

bool ContrastRenderer::ready() {
    return (contrastShader) ? (true) : (false);
}
