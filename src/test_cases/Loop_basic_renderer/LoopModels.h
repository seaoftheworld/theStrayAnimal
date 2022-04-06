#include "Core/AssimpLib.h"
#include "Core/Loader.h"

// #include "Core/Renderers/Terrain/Terrain.h"
// #include "Core/Renderers/Skybox/SkyboxRenderer.h"  // shall seperate skybox-data with skybox-renderer ???
// #include "WrappingRenderer.h"

#include <vector>

#define CAM_MODEL_INIT_DIST (40.0f)
#define MODEL_MODEL_DIST (40.5f)

class LoopModels {
    Loader loader;

    // Entity single_vbo_entity;
    // Entity multi_vbo_entity;
    AssimpLib fruits;
    AssimpLib rb73;
    Texture* rb73_nmap = NULL;

    // void initSingleVboEntity();
    // void initMultiVboEntity();
    void initFruitsRb73();

    void cleanUp() {
        // single_vbo_entity.cleanUp();
        // multi_vbo_entity.cleanUp();

        // for (auto ir_mesh : fruits.texturedModels) {
        //     ir_mesh.cleanUp();
        // }
        fruits.cleanUp();
        rb73.cleanUp();

        loader.cleanUp();
    }

public:
    LoopModels() {
        cleanUp();

        // initSingleVboEntity();
        // initMultiVboEntity();
        initFruitsRb73();

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

        printf("\n\n models/entities init done, press anything to continue ...\n\n"); {
            int dbg;
            scanf("%d", &dbg);
        }
    }
    virtual ~LoopModels() {
        cleanUp();
    }

    // Entity *getSingleVboEntity() {
    //     return &single_vbo_entity;
    // }
    // Entity *getMultiVboEntity() {
    //     return &multi_vbo_entity;
    // }
    AssimpLib *getFruits() {
        return &fruits;
    }
    AssimpLib *getRb73() {
        return &rb73;
    }
};
