// #include "Common/Loaderdata.h"
#include "Core/Renderer.h"
#include "GuiShader.h"
#include "Gui.h"

#include "Core/Loader.h"
#include "Core/Common/gl_math.h"

class PictureRenderer : public BaseRenderer {

    std::vector<Picture *> pictures;
    static PictureShader *picShader;

    void allocUvBuffer(Loader &loader);
    static unsigned short uv_vboId;

public:
    void allocShadersData() override;
    void freeShadersData() override;
    bool ready() override;

public:
    PictureRenderer(Loader &loader) {
        printf("  __ PictureRenderer constructor().\n");
        freeShadersData();
        allocShadersData();

        allocUvBuffer(loader);
    }
    ~PictureRenderer() {
        printf("  __ PictureRenderer destructor().\n");
        freeShadersData();
    }

public:
    // the vbo of a picture should have already been allocated
    void addPicture(Picture *pic) {
        if (!pic) {
            return;
        }

        pictures.push_back(pic);
    }

    unsigned int numPictures() {
        return pictures.size();
    }

    void render_single_picture(unsigned int idx) {

        Picture *pic = NULL;
        size_t size = pictures.size();
        if (idx >= size) {
            return;
        }

        auto itr = pictures.begin() + idx;
        pic = *itr;

        picShader->start();
        glDisable(GL_DEPTH_TEST);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            unsigned int vertices_count = 0, stride_in_float = 0;
            if (pic->vboId) {
                // stride_in_float = GuiType00::rect->getVerticesStride();
                // vertices_count = GuiType00::rect->getVerticesCount();

                // bind attr data for verticies position
                glBindBuffer(GL_ARRAY_BUFFER, pic->vboId);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(
                    0, 
                    stride_in_float, GL_FLOAT,
                    GL_FALSE, 
                    stride_in_float << 2,  // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
                    0);

                // bind attr data for verticies uv
                glBindBuffer(GL_ARRAY_BUFFER, uv_vboId);
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(
                    0, 
                    stride_in_float, GL_FLOAT,
                    GL_FALSE, 
                    stride_in_float << 2,  // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
                    0);
            }

            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, pic->textureId);

                gl_math::mat4 transform_matrix = gl_math::mat4(1.0f); {
                    // gl_math::create_transform_matrix((*gui)->getPosition(), (*gui)->getScale(), &transform_matrix);
                    // guiShader->loadTransformMatrix(&transform_matrix[0][0]);
                }

                glDrawArrays(GL_TRIANGLES, 0, vertices_count);
            }

        glEnable(GL_DEPTH_TEST);
    }

    void render(Picture *pic) {

        if (!pic) {
            return;
        }

        picShader->start();
        glDisable(GL_DEPTH_TEST);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            unsigned int vertices_count = 0, stride_in_float = 0;
            if (pic->vboId && pic->textureId) {
                
                vertices_count = PICTURE_RENDERER_DRAW_VERTICES_NUM;

                // bind attr data for verticies position
                stride_in_float = PICTURE_RENDERER_POS_VBO_VERTICES_STRIDE;

                glBindBuffer(GL_ARRAY_BUFFER, pic->vboId);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(
                    0, 
                    stride_in_float, GL_FLOAT,
                    GL_FALSE, 
                    stride_in_float << 2,  // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
                    0);

                // bind attr data for verticies uv
                stride_in_float = PICTURE_RENDERER_UV_VBO_VERTICES_STRIDE;

                glBindBuffer(GL_ARRAY_BUFFER, uv_vboId);
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(
                    0, 
                    stride_in_float, GL_FLOAT,
                    GL_FALSE, 
                    stride_in_float << 2,  // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
                    0);
            }

            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, pic->textureId);

                gl_math::mat4 transform_matrix = gl_math::mat4(1.0f); {
                    // gl_math::create_transform_matrix((*gui)->getPosition(), (*gui)->getScale(), &transform_matrix);
                    // guiShader->loadTransformMatrix(&transform_matrix[0][0]);
                }

                glDrawArrays(GL_TRIANGLES, 0, vertices_count);
            }

        glEnable(GL_DEPTH_TEST);
    }
};

class GuiRenderer : public BaseRenderer {

private:
    GuiType00Shader *guiShader = NULL;

    // Contains Transform and Scale info for each gui tobe displayed
    // std::vector<GuiType00 *> guis;

public:
    void allocShadersDataMod(bool forFBO);
    void allocShadersData() override;
    void freeShadersData() override;
    bool ready() override;

    // void addGui(GuiType00 *gui) {
    //     guis.push_back(gui);
    // }

    void run(std::vector<GuiType00> &guis) {
        guiShader->start();
        glDisable(GL_DEPTH_TEST);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            render(guis);

        glEnable(GL_DEPTH_TEST);
    }
    
    void render(std::vector<GuiType00> &guis) {

        unsigned int vertices_count = 0, stride_in_float = 0;
        if (GuiType00::rect) {
            stride_in_float = GuiType00::rect->getVerticesStride();
            vertices_count = GuiType00::rect->getVerticesCount();

            glBindBuffer(GL_ARRAY_BUFFER, GuiType00::rect->getVboID());
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(
                0, 
                stride_in_float, GL_FLOAT,
                GL_FALSE, 
                stride_in_float << 2,  // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
                0);
        }

        for (size_t i = 0; i < guis.size(); i++) {

            auto gui = guis.begin() + i;

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, gui->getTextureID());

            gl_math::mat4 transform_matrix = gl_math::mat4(1.0f); {
                gl_math::create_transform_matrix(gui->getPosition(), gui->getScale(), &transform_matrix);
                guiShader->loadTransformMatrix(&transform_matrix[0][0]);
            }

            glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices_count);
        }
    }

public:
    GuiRenderer(bool forFBO) {
        printf("  __ gui-renderer constructor().\n");
        freeShadersData();
        allocShadersDataMod(forFBO);
    }
    ~GuiRenderer() {
        printf("  __ gui-renderer destructor().\n");
        freeShadersData();
    }
};
