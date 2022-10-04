#include "LoopModels.h"

void LoopModels::initAllModels() {

    // apple
    {
        float values00[Transform::max] = {
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            .1f
        };
        float values01[Transform::max] = {
            MODEL_MODEL_DIST, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            .1f
        };

        Transform transform0(&values00);
        Transform transform1(&values01); {
            Transform* transforms[2] = { &transform0, &transform1 };

            // TODO: improve meshes' hierachy
            // misa.loadModel("data/models/misa/misa_yForward_zUp.obj", \
                loader, transforms, sizeof(transforms)/sizeof(transforms[0]));

            // The normals for misa-model may be incorrect, unlike rb73 model,
            // even if 'smooth' interpolation-qulifier is used,
            // misa is not displayed perspectively correct,
            // still has got hard edges like when 'flat' is used.
            // misa.loadModel("data/models/player/rb73/rb73_yForward_zUp.obj", \
                loader, transforms, sizeof(transforms)/sizeof(transforms[0]), true);

            // fruits.loadModel("data/models/target/orange/orange.obj", \

            fruits.loadModel("data/models/target/apple/apple.obj", \
                loader, transforms, sizeof(transforms) / sizeof(transforms[0]));
        }
    }
    /*
    {
        float values02[Transform::max] = {
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            .12f
        };
        Transform transform2(&values02); {
            Transform* transforms[] = { &transform2 };

            fruits_up_scaled.loadModel("data/models/target/apple/apple.obj", \
                loader, transforms, sizeof(transforms) / sizeof(transforms[0]));
        }
    }
    // */

    // banana
    {
        float values00[Transform::max] = {
            2.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            .1f
        };
        Transform transform0(&values00); {
            Transform* transforms[] = { &transform0 };

            fruits.loadModel("data/models/target/banana/banana.obj", \
                loader, transforms, sizeof(transforms) / sizeof(transforms[0]));
        }
    }

    // orange
    {
        float values00[Transform::max] = {
            4.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            .1f
        };

        Transform transform0(&values00); {
            Transform* transforms[] = { &transform0 };

            // fruits.loadModel("data/models/target/apple/apple.obj", \

            fruits.loadModel("data/models/target/orange/orange.obj", \
                loader, transforms, sizeof(transforms) / sizeof(transforms[0]));
        }
    }

    // barrel
    {
        float values02[Transform::max] = {
            0.0f, 2.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            .2f
        };

        Transform transform02(&values02);
        Transform* array_transforms[] = { &transform02 }; {
            theRestModels.loadModel("data/models/others/barrel/barrel.obj", loader, array_transforms, 1, true);
        }
    }

    // rb73
    {
        float values02[Transform::max] = {
            0.0f, 4.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            1.0f
        };

        Transform transform02(&values02); 
        Transform *array_transforms[] = { &transform02 }; {
            // rb73.loadModel("data/models/player/rb73/rb73_yForward_zUp.obj", loader, array_transforms, 1);
            theRestModels.loadModel("data/models/player/rb73/rb73_yForward_zUp.obj", loader, array_transforms, 1, true);
        }
    }
        /*
        for (TexturedModel ir_mesh : rb73.normalMappedModels) {
            // ir_mesh.setNormalMap(rb73_nmap);
            // printf("n-map after set: %p\n", ir_mesh.getNormalMap());
            ir_mesh.normalMap = rb73_nmap;
        }
        for (TexturedModel ir_mesh : rb73.normalMappedModels) {
            printf("n-map info: %p\n", ir_mesh.normalMap);
        }
        printf("\n\n");
        // */

    /*
    printf("n-mapped models loaded: \n");
    for (auto ir_mesh : rb73.normalMappedModels) {
        printf("n-map info2: %p\n", ir_mesh.getNormalMap());
    }
    for (TexturedModel ir_mesh : rb73.normalMappedModels) {
        printf("n-map info2: %p-", ir_mesh.getNormalMap());
        printf("%c, ", (ir_mesh.getNormalMap() == NULL) ? ('n') : ('y'));
    }
    printf("\n");

    for (TexturedModel ir_mesh : rb73.normalMappedModels) {
        printf("n-map info3: %p\n", ir_mesh.getNormalMap());
    }
    for (TexturedModel ir_mesh : rb73.normalMappedModels) {
        printf("n-map info3: %p-", ir_mesh.getNormalMap());
        printf("%c, ", (ir_mesh.getNormalMap() == NULL) ? ('n') : ('y'));
    }
    printf("\n");

    printf("\n\n");
    // */

    {
        // Set normal-texutures for norma-mapped models

        //*
        // printf("aaa");
        // Texture* rb73_nmap = loader.getTexture("data/models/player/rb73/mtl/robot_Normal_OpenGL.png");
        // rb73_nmap = loader.getTexture("data/models/others/barrel/barrelNormal.png");
        rb73_nmap = loader.getTexture("data/models/player/rb73/mtl/robot_Normal_OpenGL.png");
        printf("n-map loaded: %p\n", rb73_nmap);

        // printf("bbb");
        for (size_t i = 0; i < theRestModels.normalMappedModels.size(); i++) {
            (theRestModels.normalMappedModels)[i].setNormalMap(rb73_nmap);
        }

        for (TexturedModel ir_mesh : theRestModels.normalMappedModels) {
            printf("texture info a: %p\n", ir_mesh.getNormalMap());
        }

        for (size_t i = 0; i < theRestModels.normalMappedModels.size(); i++) {
            printf("texture info b: %p\n", (theRestModels.normalMappedModels)[i].getNormalMap());
        }
        printf("\n\n");
        // */
    }

    // Gui
    {
        float gui_rect_vertices[GUI_RECT_VERTICES_STRIDE * GUI_RECT_VERTICES_NUM] = {
            -1.0f, 1.0,  -1.0f, -1.0f,
             1.0f, 1.0f,  1.0f, -1.0f
        };
        GuiType00::rect = loader.allocSingleAttributeModel(gui_rect_vertices, GUI_RECT_VERTICES_STRIDE, GUI_RECT_VERTICES_NUM);
        printf("GUI Rect model loaded.\n");

        {
            // float gui_pos[] = { -0.7f, 0.7f };
            // float gui_scale[] = { 0.125f, 0.25f };

            // float gui_pos[] = { -0.5f, -0.5f };
            // float gui_scale[] = { 0.4f, 0.4f };

            float gui_pos[] = { -0.5f, 0.0f };
            float gui_scale[] = { 0.4f, 0.8f };

            // const string texFile = "data/tex/water/matchingNormalMap.png";
            // Texture* tex = loader.getTexture(texFile);
            // if (tex) 
            {
                GuiType00 tmpGui;
                tmpGui.init(outputFbo.getTexture(), &gui_pos, &gui_scale);
                guis.push_back(tmpGui);
                printf("GUI initalized with tx, pos/scale.\n\n");
            }
            // else{ printf("!!! GUI Tex failed: %s !!!\n", texFile.c_str());}
        }
    }

    // rect for post-processing
    {
        // float gui_rect_vertices[GUI_RECT_VERTICES_STRIDE * GUI_RECT_VERTICES_NUM] = {
        float gui_rect_vertices[2 * 4] = {
            -1.0f, 1.0,  -1.0f, -1.0f,
             1.0f, 1.0f,  1.0f, -1.0f
        };

        // SingleAttributeModel *rect = loader.allocSingleAttributeModel(gui_rect_vertices, GUI_RECT_VERTICES_STRIDE, GUI_RECT_VERTICES_NUM);
        SingleAttributeModel* rect = loader.allocSingleAttributeModel(gui_rect_vertices, 2, 4);
        if (rect) {
            postProcessingRectID = rect->getVboID();
            printf("Rect model for post-processing loaded, vboID: %d.\n", postProcessingRectID);
        }
        else {
            printf("Rect model for post-processing loading failed!\n");
        }
    }
}

// A stack of pictures with transparent color
/*
void LoopModels::initMultiVboEntity() {

    float test_pos[] = { -0.5f, 0.5f,  0.0f, 
                          0.5f, 0.5f,  0.0f, 
                          0.5f, -0.5f, 0.0f, 
                         -0.5f, -0.5f, 0.0f };

    float test_uv[] = { 0.0f, 0.0f, 
                        1.0f, 0.0f, 
                        1.0f, 1.0f, 
                        0.0f, 1.0f };

    float dummy_normal[] = { 0.0f, 0.0f, 1.0f, 
                             0.0f, 0.0f, 1.0f, 
                             0.0f, 0.0f, 1.0f, 
                             0.0f, 0.0f, 1.0f };

    float *test_vertex_attr[] = {
        test_pos, 
        test_uv,
        dummy_normal
    };

    unsigned short test_indices[] = { 0, 1, 2, 0, 3, 2 };

    StaticModel *model = NULL; {
        unsigned int vertices_count_from_pos    = ARRAY_SIZE(test_pos) / NoLightingShader::attr_stride[NoLightingShader::id0_pos3f];
        unsigned int vertices_count_from_uv     = ARRAY_SIZE(test_uv) / NoLightingShader::attr_stride[NoLightingShader::id1_uv2f];
        unsigned int vertices_count_from_normal = ARRAY_SIZE(dummy_normal) / NoLightingShader::attr_stride[NoLightingShader::id2_normal3f];

        unsigned int vertices_count = \
            (vertices_count_from_pos == vertices_count_from_uv && \
             vertices_count_from_pos == vertices_count_from_normal) ? (vertices_count_from_pos) : (0);
        unsigned int indices_count = (vertices_count) ? ( ARRAY_SIZE(test_indices) ) : (0);

        printf("  vertices counts is: %d\n", vertices_count);
        printf("  indices counts are %d\n", indices_count);
        
        model = loader.loadStaticModel(
            &test_vertex_attr, vertices_count, 
            test_indices, indices_count
        );

        if (!model) {
            printf("  Failed to generate model for multi_vbo_entity\n");
        }

        printf("  3D model for multi_vbo_entity generated,");
        printf("    vbos/ibo-ids:  ");
        
        int ids[StaticModel::allBuffNum];
        model->getBuffers(&ids);

        for (int i = 0; i < StaticModel::allBuffNum; i++) {
            printf("%d", ids[i]);
        }
        printf("\n\n");
    }

    StaticTexture *texture = NULL; {
        std::string texture_file = "data/tex/font.png";

        loader.loadStaticTextures(&texture_file, 1, &texture);
        if (!texture) {
            printf("  Failed to generate texture for multi_vbo_entity\n");
            // return false;
        }

        printf("  Texture for multi_vbo_entity generated,");
        printf("    tex-id: %d\n\n", texture->getId());
    }

    if (texture && model) {

        multi_vbo_entity.setTextureModel(texture, model);

        for (unsigned int i = 0; i < 10; i++) {
            float trans_values[Transform::max] = {
                (float)i * 1.0f + 0.5f, (float)i * 1.0f + 0.1f, (float)i * 1.0f + 0.1f,
                0.0f, 0.0f, 0.0f,
                (float)i * 0.3f + 0.3f
            };

            Transform transform(&trans_values);
            multi_vbo_entity.addTransform(transform);
        }
    }
}
// */

// The 2 square pictures
/*
void LoopModels::initSingleVboEntity() {

    float single_vbo_data[] = {
        -0.5f, 0.5f,  -0.0f, 
         0.0f, 0.0f, 
         0.0f, 0.0f, 1.0f, 

         0.5f, 0.5f,  -0.0f, 
         1.0f, 0.0f, 
         0.0f, 0.0f, 1.0f, 

         0.5f, -0.5f, -0.0f, 
         1.0f, 1.0f, 
         0.0f, 0.0f, 1.0f, 

        -0.5f, -0.5f, -0.0f,
         0.0f, 1.0f,
         0.0f, 0.0f, 1.0f
    };

    unsigned short indices[] = { 
        0, 1, 2, 0, 3, 2 
    };

    StaticModel_SingleVbo *m = NULL; {
        unsigned int vertices_count = ARRAY_SIZE(single_vbo_data) / StaticModel_SingleVbo::single_vbo_stride_in_float;
        unsigned int indices_count = ARRAY_SIZE(indices);
        printf("  single-vbo: vertices count is: %d\n", vertices_count);
        printf("               indices count is: %d\n", indices_count);

        m = loader.loadSingleVboModel(single_vbo_data, vertices_count, indices, indices_count);
        if (!m) {
            printf("  Failed to generate model for single_vbo_entity\n");
            // return false;
        }

        printf("  3D model for single_vbo_entity generated,");
        printf("    vbo/ibo-ids: %d, %d\n\n", m->getVboId(), m->getIboId());
    }

    StaticTexture *texture = NULL; {
        std::string texture_file = "data/tex/road.png";

        loader.loadStaticTextures(&texture_file, 1, &texture);
        if (!texture) {
            printf("  Failed to generate texture for single_vbo_entity\n");
            // return false;
        }

        printf("  Texture for single_vbo_entity generated,");
        printf("    tex-id: %d\n\n", texture->getId());
    }

    if (texture && m) {

        single_vbo_entity.setTextureModel(texture, m);

        float trans_big_square_values[Transform::max] = {
            // (float)i * 1.0f + 0.5f, (float)i * 1.0f + 0.1f, (float)i * 1.0f + 0.1f,
            // 0.0f, 0.0f, 0.0f,
            // (float)i * 0.3f + 0.3f

            -5.0f, -5.0f, 1.0f,
            0.0f, 0.0f, 0.0f,
            4.0f
        };
        Transform trans_big_square(&trans_big_square_values);
        single_vbo_entity.addTransform(trans_big_square);

        float trans_small_square_values[Transform::max] = {
            // -1.5f, -1.5f, 2.0f,
            -5.0f, -5.0f, 2.0f,
            0.0f, 0.0f, 0.0f,
            1.0f
        };
        Transform trans_small_square(&trans_small_square_values);
        single_vbo_entity.addTransform(trans_small_square);
    }
}
// */
