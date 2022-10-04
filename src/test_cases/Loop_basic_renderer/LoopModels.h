#include "Core/AssimpLib.h"
#include "Core/Loader.h"

#include "loopWrappingRenderer.h"  // to include data for gui-tile or water-tile ...

#include <vector>

#define CAM_MODEL_INIT_DIST (40.0f)
#define MODEL_MODEL_DIST (40.5f)

class LoopModels {
    Loader loader;

    // Entity single_vbo_entity;
    // Entity multi_vbo_entity;
    Texture* rb73_nmap = NULL;
    AssimpLib theRestModels;
    AssimpLib fruits;

    vector<GuiType00> guis;

    WaterTileFBO multiSampledFbo;
    WaterTileFBO       outputFbo;  // the gui-rectangle(left) is supposed to display the color-buffer of this fbo

    WaterTileFBO brightnessFbo, \
        blurFbo1_h, blurFbo1_v, \
        blurFbo2_h, blurFbo2_v, \
        blurFbo3_h, blurFbo3_v;

    int postProcessingRectID = -1;

    // void initSingleVboEntity();
    // void initMultiVboEntity();
    void initAllModels();

    void cleanUp() {
        // single_vbo_entity.cleanUp();
        // multi_vbo_entity.cleanUp();

        // for (auto ir_mesh : fruits.texturedModels) {
        //     ir_mesh.cleanUp();
        // }
        fruits.cleanUp();
        theRestModels.cleanUp();

        loader.cleanUp();
    }

public:

    LoopModels() : \
        multiSampledFbo(true), \
        outputFbo(false), \
        brightnessFbo(WATER_TILE_FBO_WIDTH / 4, WATER_TILE_FBO_HEIGHT / 4), \
        blurFbo1_h(WATER_TILE_FBO_WIDTH / 2.0, WATER_TILE_FBO_HEIGHT / 2.0), \
        blurFbo1_v(WATER_TILE_FBO_WIDTH / 2.0, WATER_TILE_FBO_HEIGHT / 2.0), \
        blurFbo2_h(WATER_TILE_FBO_WIDTH / 2.5, WATER_TILE_FBO_HEIGHT / 2.5), \
        blurFbo2_v(WATER_TILE_FBO_WIDTH / 2.5, WATER_TILE_FBO_HEIGHT / 2.5), \
        blurFbo3_h(WATER_TILE_FBO_WIDTH / 3, WATER_TILE_FBO_HEIGHT / 3), \
        blurFbo3_v(WATER_TILE_FBO_WIDTH / 3, WATER_TILE_FBO_HEIGHT / 3) {
        cleanUp();

        // initSingleVboEntity();
        // initMultiVboEntity();
        initAllModels(); {
            // vector<double> vec_double;
            // vector<float> vec_float;
            // vector<char> vec_char;
            // vector<int> vec_int;

            // // vector<double>::size_type vec_double_max = vec_double.max_size();
            // // size_t vec_double_max_size = vec_double.max_size();

            // printf("max size of vectors for double, float, int, char: \n%zu, \n%zu, \n%zu, \n%zu\n", 
            //     vec_double.max_size(), 
            //     vec_float.max_size(), 
            //     vec_int.max_size(), 
            //     vec_char.max_size()
            // );
        }

        // printf("\n\n models/entities init done, input any number to continue ...\n\n"); {
        //     int dbg;
        //     scanf("%d", &dbg);
        // }
    }
    virtual ~LoopModels() {
        cleanUp();
    }

    AssimpLib *getFruits() {
        return &fruits;
    }
    AssimpLib *getTheRestModels() {
        return &theRestModels;
    }

    vector<GuiType00>& getGuis() {
        return guis;
    }

    WaterTileFBO& getMultiSampledFBO() {
        return multiSampledFbo;
    }
    WaterTileFBO& getOutputFBO() {
        return outputFbo;
    }

    WaterTileFBO& getBrightnessFBO() {
        return brightnessFbo;
    }
    WaterTileFBO& getBlurFBO1_h() {
        return blurFbo1_h;
    }
    WaterTileFBO& getBlurFBO1_v() {
        return blurFbo1_v;
    }
    WaterTileFBO& getBlurFBO2_h() {
        return blurFbo2_h;
    }
    WaterTileFBO& getBlurFBO2_v() {
        return blurFbo2_v;
    }
    WaterTileFBO& getBlurFBO3_h() {
        return blurFbo3_h;
    }
    WaterTileFBO& getBlurFBO3_v() {
        return blurFbo3_v;
    }

    int getPostProcessingRectID() {
        return postProcessingRectID;
    }
};
