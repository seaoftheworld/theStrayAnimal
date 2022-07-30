// #include "Common/Loaderdata.h"
#include "Core/Renderer.h"
#include "GuiShader.h"
#include "Gui.h"

#include "Core/Loader.h"
#include "Core/Common/gl_math.h"

#include "Core/Renderers/Water/WaterTile.h"  // to use 'WaterTileFBO' class for H/VBlurRenderer

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

/*
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
// */

// class PictureRenderer {
// }

class ContrastRenderer : public BaseRenderer {

private:
    ContrastShader *contrastShader = NULL;

public:
    void allocShadersData() override;
    void freeShadersData() override;
    bool ready() override;

    /*
    // void run_gui(std::vector<GuiType00> &guis) {
    void run_dbg_with_gui(int rectVboID, int txID) {
        if (rectVboID <= 0 || txID <= 0)
            return;

        // guiShader->start();
        contrastShader->start();
        glDisable(GL_DEPTH_TEST);
        {
            {
                glActiveTexture(GL_TEXTURE0);
                // glBindTexture(GL_TEXTURE_2D, guis[0].getTextureID());
                glBindTexture(GL_TEXTURE_2D, txID);
            }

            {
                unsigned int stride_in_float = 2;
                glBindBuffer(GL_ARRAY_BUFFER, rectVboID);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(
                    0, 
                    stride_in_float, GL_FLOAT,
                    GL_FALSE, 
                    stride_in_float << 2,  // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
                    0);
            }

            {
                gl_math::mat4 transform_matrix = gl_math::mat4(1.0f); {
                    // gl_math::create_transform_matrix(guis[0].getPosition(), guis[0].getScale(), &transform_matrix);

                    // guiShader->loadTransformMatrix(&transform_matrix[0][0]);
                    contrastShader->loadTransformMatrix(&transform_matrix[0][0]);
                }

                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }
        }
        glEnable(GL_DEPTH_TEST);
        contrastShader->stop();
    }
    // */

    // render data from 'txID' to the rectangle bound in PostProcessing class
    void run(int txID) {

        contrastShader->start(); 
        {
            // unsigned int vertices_count = GuiType00::rect->getVerticesCount();
            unsigned int vertices_count = 4;

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (GLuint)txID);

            //*
            gl_math::mat4 transform_matrix = gl_math::mat4(1.0f); {
                // float rect_pos[] = { 0.5f, 0.0f };
                // float rect_scale[] = { 0.4f, 0.8f };

                float rect_pos[] = { 0.5f, -0.5f };
                float rect_scale[] = { 0.4f, 0.4f };

                gl_math::create_transform_matrix(&rect_pos, &rect_scale, &transform_matrix);
                contrastShader->loadTransformMatrix(&transform_matrix[0][0]);
            }
            // */
            glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices_count);
        }
        contrastShader->stop();
    }

public:
    ContrastRenderer() {
        printf("  __ contrast-renderer constructor().\n");
        freeShadersData();
        allocShadersData();
    }
    ~ContrastRenderer() {
        printf("  __ contrast-renderer destructor().\n");
        freeShadersData();
    }
};

class HBlurRenderer : public BaseRenderer {

private:
    BlurShader* hblurShader = NULL;

public:
    void allocShadersData() override;
    void freeShadersData() override;
    bool ready() override;

    void setHorResolution(float val) {
        hblurShader->start();
        hblurShader->loadHorResolution(val);
        hblurShader->stop();
    }

    // render data from 'txID' to the fbo first, 
    // then to the rectangle bound in PostProcessing class
    void run(WaterTileFBO &fbo, int txID) {

        hblurShader->start();
        {
            // unsigned int vertices_count = GuiType00::rect->getVerticesCount();
            unsigned int vertices_count = 4;

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (GLuint)txID);

            fbo.bind();
            gl_math::mat4 transform_matrix = gl_math::mat4(1.0f); {
                // float rect_pos[] = { 0.5f, -0.5f };
                // float rect_scale[] = { 0.4f, 0.4f };

                // float rect_pos[] = { 0.5f, 0.0f };
                // float rect_scale[] = { 0.4f, 0.8f };

                float rect_pos[] = { 0.0f, 0.0f };
                float rect_scale[] = { 1.0f, 1.0f };

                gl_math::create_transform_matrix(&rect_pos, &rect_scale, &transform_matrix);
                hblurShader->loadTransformMatrix(&transform_matrix[0][0]);
            }
            glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices_count);
            fbo.unbind();
        }
        hblurShader->stop();
    }

public:
    HBlurRenderer() {
        printf("  __ HBlur-renderer constructor().\n");
        freeShadersData();
        allocShadersData();
    }
    ~HBlurRenderer() {
        printf("  __ HBlur-renderer destructor().\n");
        freeShadersData();
    }
};

class VBlurRenderer : public BaseRenderer {

private:
    BlurShader* vblurShader = NULL;

public:
    void allocShadersData() override;
    void freeShadersData() override;
    bool ready() override;

    void setVerResolution(float val) {
        vblurShader->start();
        vblurShader->loadVerResolution(val);
        vblurShader->stop();
    }

    // render data from 'txID' to the fbo first
    // then to the rectangle bound in PostProcessing class
    void run(WaterTileFBO& fbo, int txID) {

        vblurShader->start();
        {
            // unsigned int vertices_count = GuiType00::rect->getVerticesCount();
            unsigned int vertices_count = 4;

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (GLuint)txID);

            fbo.bind();
            gl_math::mat4 transform_matrix = gl_math::mat4(1.0f); {
                // float rect_pos[] = { 0.5f, -0.5f };
                // float rect_scale[] = { 0.4f, 0.4f };

                // float rect_pos[] = { 0.5f, 0.0f };
                // float rect_scale[] = { 0.4f, 0.8f };

                float rect_pos[] = { 0.0f, 0.0f };
                float rect_scale[] = { 1.0f, 1.0f };

                gl_math::create_transform_matrix(&rect_pos, &rect_scale, &transform_matrix);
                vblurShader->loadTransformMatrix(&transform_matrix[0][0]);
            }
            glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices_count);
            fbo.unbind();
        }
        vblurShader->stop();
    }

public:
    VBlurRenderer() {
        printf("  __ VBlur-renderer constructor().\n");
        freeShadersData();
        allocShadersData();
    }
    ~VBlurRenderer() {
        printf("  __ VBlur-renderer destructor().\n");
        freeShadersData();
    }
};
