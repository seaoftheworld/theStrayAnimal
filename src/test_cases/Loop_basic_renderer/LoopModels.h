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
    AssimpLib fruits;
    AssimpLib theRestModels;
    Texture* rb73_nmap = NULL;

    vector<GuiType00> guis;
    WaterTileFBO fbo;  // gui is supposed to display texture-obj from this fbo

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
    LoopModels() {
        cleanUp();

        // initSingleVboEntity();
        // initMultiVboEntity();
        initAllModels();

        /*
        vector<double> vec_double;
        vector<float> vec_float;
        vector<int> vec_int;
        vector<char> vec_char;
        
        vector<double>::size_type vec_double_max = vec_double.max_size();
        size_t vec_double_max_size = vec_double.max_size();

        printf("max size of vectors: \n%zu, \n%zu, \n%zu, \n%zu\n", 
            vec_double.max_size(), 
            vec_float.max_size(), 
            vec_int.max_size(), 
            vec_char.max_size()
        );
        */

        printf("\n\n models/entities init done, input any number to continue ...\n\n"); {
            int dbg;
            scanf("%d", &dbg);
        }
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
    WaterTileFBO& getWaterTileFBO() {
        return fbo;
    }
};
