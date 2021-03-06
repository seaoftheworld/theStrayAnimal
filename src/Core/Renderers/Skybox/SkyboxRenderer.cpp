#include "SkyboxRenderer.h"

const float skybox_init_data_array[SKYBOX_CUBE_MODEL_VERT_STRIDE * SKYBOX_CUBE_MODEL_VERT_NUM] = {

    // Right
     1,  1,  1,
     1,  1, -1,
     1, -1, -1,

     1,  1,  1,     
     1, -1, -1,
     1, -1,  1,

    // Left
    -1,  1, -1,
    -1, -1, -1,
    -1, -1,  1,

    -1, -1,  1,
    -1,  1,  1,
    -1,  1, -1,

    // Front
    -1,  1, -1,  // 1 +--+ 2
    -1,  1,  1,  //   | /
     1,  1,  1,  // 0 |/

     1,  1,  1,  //      + 3
     1,  1, -1,  //     /|
    -1,  1, -1,  // 5  /_| 4

    // Back
    -1, -1, -1,
    -1, -1,  1,
     1, -1, -1,
     1, -1, -1,
    -1, -1,  1,
     1, -1,  1,

    // Top
    -1, -1,  1,
     1, -1,  1,
     1,  1,  1,
     1,  1,  1,
    -1,  1,  1,
    -1, -1,  1,

    // Bottom
    -1,  1, -1,
    -1, -1, -1,
     1,  1, -1,
     1,  1, -1,
     1, -1, -1,
    -1, -1, -1,
};

void Skybox::init(Loader *loader, std::string imgPaths[][6], unsigned int cube_edge_length) {
    if (!loader || !imgPaths) {
        return;
    }

    float vertices_data[SKYBOX_CUBE_MODEL_VERT_STRIDE * SKYBOX_CUBE_MODEL_VERT_NUM];
    for (unsigned int i = 0; i < SKYBOX_CUBE_MODEL_VERT_STRIDE * SKYBOX_CUBE_MODEL_VERT_NUM; i++) {
        vertices_data[i] = cube_edge_length / 2 * skybox_init_data_array[i];
    }

    cube = loader->allocSingleAttributeModel(vertices_data, SKYBOX_CUBE_MODEL_VERT_STRIDE, SKYBOX_CUBE_MODEL_VERT_NUM);
    if (cube) {
        printf("skybox cube vbo: %d\n", cube->getVboID());
        printf("skybox cube vcount: %d\n", cube->getVerticesCount());
    }

    cubeTexture = loader->loadStaticTextureCube(imgPaths);
    printf("cubeTexture: %p\n", cubeTexture);
}

void SkyboxRenderer::allocShadersData() {

    if (skyboxShader) {
        return;
    }

    SkyboxShader *shader = new SkyboxShader;

    if (!shader) {
        // shader is not allocated
        skyboxShader = NULL;
        return;
    }

    if (shader->getStatus() != BaseShader::link_prog_passed || shader->getProgId() <= 0) {
        // shader failed to compile
        shader->cleanUp();
        shader = NULL;

        skyboxShader = NULL;
        return;
    }

    // load projection matrix for the only once
    shader->start();
        shader->loadProjMatrix(getProjMatrix());
    shader->stop();

    skyboxShader = shader;
}

void SkyboxRenderer::freeShadersData() {
    if (skyboxShader) {
        skyboxShader->stop();
        skyboxShader->cleanUp();

        delete skyboxShader;
        skyboxShader = NULL;
    }
}

bool SkyboxRenderer::ready() {
    return (skyboxShader) ? (true) : (false);
}

// void SkyboxRenderer::render(Skybox *skybox) {
//     // shader->start();
//     // if (!terrain || !shader) {
//     //     return;
//     // }

//     // Setting this to be 0 could make drawing unable to crash the program,
//     // when NULL-texture/model pointers are input by mistake.
//     unsigned int vertices_count = 0;
//     if (!skybox) {
//         return;
//     }

//     if (skybox->getCubeTexture()) {
//         // bind a texture buffer object
//         int texture_id = skybox->getCubeTexture()->getId();
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
//     }

//     if (skybox->getCubeModel()) {
//         vertices_count = skybox->getCubeModel()->getVertexCount();

//         glBindBuffer(GL_ARRAY_BUFFER, skybox->getCubeModel()->getVboID());
        
//         glEnableVertexAttribArray(0);
        
//         glVertexAttribPointer(
//             0, 
//             3, GL_FLOAT, 
//             GL_FALSE, 
//             3 << 2,  // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
//             0);
//     }

//     {
//         glDrawArrays(GL_TRIANGLES, 0, vertices_count);
//         // glDrawArrays(GL_TRIANGLES, 0, 3 * 3);
//     }
// }
