#pragma once

#include "Core/Common/data.h"
#include "Core/Common/gl_header.h"

#include "WindowSystem/WindowSystem.h"

#define WATER_TILE_VERTICE_STRIDE (2)  // to be used for the SingleAttributeModel-object of water
#define WATER_TILE_TRIANGLES_NUM  (2)  // to be used for the SingleAttributeModel-object of water

// #define WATER_TILE_FBO_WIDTH  (200)
// #define WATER_TILE_FBO_HEIGHT (200)
#define WATER_TILE_FBO_WIDTH  (400)
#define WATER_TILE_FBO_HEIGHT (300)

// a simpler fbo than WaterFrameBuffers
class WaterTileFBO {
    int fboID = -1, 
        txColorBuffID = -1,  // texture based colorBuff, depthBuff for fb, 
        txDepthBuffID = -1,  //   https://www.khronos.org/opengl/wiki/Texture
        rbColorBuffID = -1,  // renderBuffer based colorBuff, depthBuff for fb
        rbDepthBuffID = -1;  //   https://www.khronos.org/opengl/wiki/Renderbuffer_Object
public:
    unsigned int m_width = 0, m_height = 0;

    void resoveToFbo(const WaterTileFBO &output_fbo) {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, output_fbo.getFboID());
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fboID);

        // glBlitFramebuffer(0, 0, WATER_TILE_FBO_WIDTH, WATER_TILE_FBO_HEIGHT, \
            0, 0, WATER_TILE_FBO_WIDTH, WATER_TILE_FBO_HEIGHT, \
            GL_COLOR_BUFFER_BIT, GL_NEAREST);

        glBlitFramebuffer(0, 0, m_width, m_height, \
            0, 0, output_fbo.m_width, output_fbo.m_height, \
            GL_COLOR_BUFFER_BIT, GL_NEAREST);

        // unbind();
    }

    // WaterTileFBO(unsigned int width, unsigned int height, bool multi_sampled) {
    WaterTileFBO(bool multi_sampled = false) {

        glGenFramebuffers(1, (GLuint *)&fboID);
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);

        //Indicates render to color-attachment0 when bound
        glDrawBuffer(GL_COLOR_ATTACHMENT0); 
        if (multi_sampled) {
            // generate and attach rbo color-buffer for this fbo
            {
                glGenRenderbuffers(1, (GLuint *)&rbColorBuffID);
                glBindRenderbuffer(GL_RENDERBUFFER, rbColorBuffID);

                // glRenderbufferStorageMultisample(\
                    GL_RENDERBUFFER, 4, GL_RGBA8, \
                    width, height);

                glRenderbufferStorageMultisample(\
                    GL_RENDERBUFFER, 4, GL_RGBA8, \
                    WATER_TILE_FBO_WIDTH, WATER_TILE_FBO_HEIGHT);

                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbColorBuffID);
            }

            // generate and attach rbo depth-buffer for this fbo
            {
                glGenRenderbuffers(1, (GLuint *)&rbDepthBuffID);
                glBindRenderbuffer(GL_RENDERBUFFER, rbDepthBuffID);

                // glRenderbufferStorageMultisample(\
                //     GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT24, \
                //     width, height);
                glRenderbufferStorageMultisample(\
                    GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT24, \
                    WATER_TILE_FBO_WIDTH, WATER_TILE_FBO_HEIGHT);

                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbDepthBuffID);
            }
        }
        else {
            // generate and attach texture-obj color-buffer for this fbo
            {
                glGenTextures(1, (GLuint *)&txColorBuffID);
                glBindTexture(GL_TEXTURE_2D, txColorBuffID); {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WATER_TILE_FBO_WIDTH, WATER_TILE_FBO_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

                    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
                    // glTexImage2D(\
                        GL_TEXTURE_2D, 0, GL_RGB, WATER_TILE_FBO_WIDTH, WATER_TILE_FBO_HEIGHT, \
                        0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                }
                glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, txColorBuffID, 0);
            }

            {
                // generate and attach texture-obj depth-buffer for this fbo
                glGenTextures(1, (GLuint*)&txDepthBuffID);
                glBindTexture(GL_TEXTURE_2D, txDepthBuffID); {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, WATER_TILE_FBO_WIDTH, WATER_TILE_FBO_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

                    // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
                    // glTexImage2D(\
                        GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, WATER_TILE_FBO_WIDTH, WATER_TILE_FBO_HEIGHT, \
                        0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                }
                glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, txDepthBuffID, 0);
            }
        }

        // m_width = width; m_height = height;
        m_width = WATER_TILE_FBO_WIDTH;
        m_height = WATER_TILE_FBO_HEIGHT;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // generate fbo for blur
    //*
    WaterTileFBO(unsigned int width, unsigned int height) {
        glGenFramebuffers(1, (GLuint *)&fboID);
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);
        {
            //Indicates render to color-attachment0 when bound
            glDrawBuffer(GL_COLOR_ATTACHMENT0);
            // generate and attach texture-obj color-buffer for this fbo
            {
                glGenTextures(1, (GLuint *)&txColorBuffID);
                glBindTexture(GL_TEXTURE_2D, txColorBuffID); {

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                }
                glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, txColorBuffID, 0);
            }

            {
                // generate and attach texture-obj depth-buffer for this fbo
                glGenTextures(1, (GLuint*)&txDepthBuffID);
                glBindTexture(GL_TEXTURE_2D, txDepthBuffID); {

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                }
                glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, txDepthBuffID, 0);
            }
        }

        m_width = width;
        m_height = height;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    // */

    ~WaterTileFBO() {
        if (txColorBuffID > 0) {
            glDeleteTextures(1, (GLuint *)&txColorBuffID);
        }
        if (txDepthBuffID > 0) {
            glDeleteTextures(1, (GLuint*)&txDepthBuffID);
        }

        if (rbColorBuffID > 0) {
            glDeleteRenderbuffers(1, (GLuint *)&rbColorBuffID);
        }
        if (rbDepthBuffID > 0) {
            glDeleteRenderbuffers(1, (GLuint *)&rbDepthBuffID);
        }

        glDeleteFramebuffers(1, (GLuint *)&fboID);
    }

public:
    int getTexture() {
        return txColorBuffID;
    }

public:
    void bind() {
        // glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);
        glViewport(0, 0, m_width, m_height);
    }
    static void unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    }
    unsigned int getFboID() const {
        return fboID;
    }
};

class WaterTile {
private:
    // x,y values passed into the water-shader are fixed normalized-values from -1 to 1
    // for the 4 vertices of a rectangular (uv calculation based on this accordingly),
    // z value in glsl-shader is set to be fixed '0'
    //
    // The transform of a water-tile is from the model-matrix (model of MVP)
    // generated by the values below:
    float transform[3] = {0.0f, 0.0f, 0.0f};
    // WaterTileFBO fbo;

    // TODO: rename to be translate and support size either
public:
    static const float SIZE;

    // The model for a water-tile (and all water-tiles). This requires the a loader-object 
    // to allocate a model correctly, then assign value for this pointer,
    // as in LoadTargets_03::initWaterTile()
    static SingleAttributeModel *rect;

public:
    WaterTile(float input_data[][3]) {
        setData(input_data);
    }
    WaterTile() {}

    void setData(float input_data[][3]) {
        transform[0] = input_data[0][0];
        transform[1] = input_data[0][1];
        transform[2] = input_data[0][2];
    }
    float (*getTransform())[3] {
        return &transform;
    }

    float getHeight() {
        return transform[2];
    }

    // WaterTileFBO &getFbo() {
    //     return fbo;
    // }
};
