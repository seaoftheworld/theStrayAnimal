#include "LoadTargets_03.h"
float LoadTargets_03::misa_offset_x = 4.0f;
float LoadTargets_03::misa_offset_y = 4.0f;

/*
void LoadTargets_03::initSingleVboEntity() {

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
        else {
            printf("  3D model for single_vbo_entity generated,");
            printf("    vbo/ibo-ids: %d, %d\n\n", m->getVboId(), m->getIboId());
        }

    }

    StaticTexture *texture = NULL; {
        std::string texture_file = "data/tex/road.png";

        loader.loadStaticTextures(&texture_file, 1, &texture);
        if (!texture) {
            printf("  Failed to generate texture for single_vbo_entity\n");
            // return false;
        }
        else {
            printf("  Texture for single_vbo_entity generated,");
            printf("    tex-id: %d\n\n", texture->getId());
        }
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

/*
void LoadTargets_03::initMultiVboEntity() {

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
        // unsigned int vertices_count_from_pos    = ARRAY_SIZE(test_pos) / NoLightingShader::attr_stride[NoLightingShader::id0_pos3f];
        // unsigned int vertices_count_from_uv     = ARRAY_SIZE(test_uv) / NoLightingShader::attr_stride[NoLightingShader::id1_uv2f];
        // unsigned int vertices_count_from_normal = ARRAY_SIZE(dummy_normal) / NoLightingShader::attr_stride[NoLightingShader::id2_normal3f];
        unsigned int vertices_count_from_pos = ARRAY_SIZE(test_pos) / 3;
        unsigned int vertices_count_from_uv = ARRAY_SIZE(test_uv) / 2;
        unsigned int vertices_count_from_normal = ARRAY_SIZE(dummy_normal) / 3;

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
        else {
            printf("  3D model for multi_vbo_entity generated,");
            printf("    vbos/ibo-ids:  ");
            
            int ids[StaticModel::allBuffNum];
            model->getBuffers(&ids);

            for (int i = 0; i < StaticModel::allBuffNum; i++) {
                printf("%d", ids[i]);
            }
            printf("\n\n");
        }
    }

    StaticTexture *texture = NULL; {
        std::string texture_file = "data/tex/font.png";

        loader.loadStaticTextures(&texture_file, 1, &texture);
        if (!texture) {
            printf("  Failed to generate texture for multi_vbo_entity\n");
            // return false;
        }
        else {
            printf("  Texture for multi_vbo_entity generated,");
            printf("    tex-id: %d\n\n", texture->getId());
        }
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

void LoadTargets_03::initRock() {

    float values[Transform::max] = {
                10.0f, 10.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                10.0f
    };
    Transform transform(&values);
    Transform *transforms = &transform;

    // TODO: improve meshes' hierachy
    models.loadModel("data/models/terrain_bottom/rocks.obj", loader, &transforms, 1);
}

void LoadTargets_03::initMisa() {

    float values[Transform::max] = {
                misa_offset_x, misa_offset_y, 0.0f + 0.5f,
                0.0f, 0.0f, 0.0f,
                1.0f
    };
    Transform transform(&values);
    Transform *transforms = &transform;

    // TODO: improve meshes' hierachy
    models.loadModel("data/models/misa/misa_yForward_zUp.obj", loader, &transforms, 1);
}

// Number of transforms for the crate is defined according to LightsPosition's initial positions
void LoadTargets_03::initCrate() {

    // Modify the 4 init-transforms of the crate-entity
    // in the following lines:
    float crate_transform_values[NUM_LIGHTS][Transform::max];

    for (unsigned int i = 0; i < NUM_LIGHTS; i++) {

        const float crate_scale = 0.12f;

        crate_transform_values[i][Transform::x] = LightsPositionsUpdate::initPosition[i][Light::Position::x];
        crate_transform_values[i][Transform::y] = LightsPositionsUpdate::initPosition[i][Light::Position::y];
        crate_transform_values[i][Transform::z] = LightsPositionsUpdate::initPosition[i][Light::Position::z];

        crate_transform_values[i][Transform::rot_x] = 0.0f;
        crate_transform_values[i][Transform::rot_y] = 0.0f;
        crate_transform_values[i][Transform::rot_z] = 0.0f;

        crate_transform_values[i][Transform::scale] = crate_scale;
    }

    Transform crate_transforms[NUM_LIGHTS]; {
        for (unsigned int i = 0; i < NUM_LIGHTS; i++) {
            crate_transforms[i].values[Transform::x] = crate_transform_values[i][Transform::x];
            crate_transforms[i].values[Transform::y] = crate_transform_values[i][Transform::y];
            crate_transforms[i].values[Transform::z] = crate_transform_values[i][Transform::z];
            crate_transforms[i].values[Transform::rot_x] = crate_transform_values[i][Transform::rot_x];
            crate_transforms[i].values[Transform::rot_y] = crate_transform_values[i][Transform::rot_y];
            crate_transforms[i].values[Transform::rot_z] = crate_transform_values[i][Transform::rot_z];
            crate_transforms[i].values[Transform::scale] = crate_transform_values[i][Transform::scale];
        }
    }

    Transform *p_crate_transforms[NUM_LIGHTS]; {
        for (unsigned int i = 0; i < NUM_LIGHTS; i++) {
            p_crate_transforms[i] = &crate_transforms[i];
        }
    };

    crate_start_idx = models.texturedModels.size();
    models.loadModel("data/models/crate/Crate1.obj", loader, p_crate_transforms, NUM_LIGHTS);
    crate_end_idx = models.texturedModels.size();

    // Doesnt work before shader is bound/opened/started ... !!!
    // multiLightsShader.loadLights(&light_pos[0], &light_color[0], 4);

    // printf("4 lights inited and crate model loaded, press anything to continue ...\n\n"); {
    //     int dbg;
    //     scanf("%d", &dbg);
    // }
}

void LoadTargets_03::initTerrain() {
    // InstrumentationTimer timer("init terrain data");
    TerrainTexturePack texturePack; {

        TerrainTexture terrainTexture00; {
            std::string terrainTexturePath = "data/tex/terrain/grassy2.png";
            StaticTexture *terrainTexture = NULL;

            loader.loadStaticTextures(&terrainTexturePath, 1, &terrainTexture);
            terrainTexture00.init(terrainTexture->getId());
        }

        TerrainTexture terrainTexture01; {
            std::string terrainTexturePath = "data/tex/terrain/mud.png";
            StaticTexture* terrainTexture = NULL;

            loader.loadStaticTextures(&terrainTexturePath, 1, &terrainTexture);
            terrainTexture01.init(terrainTexture->getId());
        }

        TerrainTexture terrainTexture02; {
            std::string terrainTexturePath = "data/tex/terrain/grassFlowers.png";
            StaticTexture* terrainTexture = NULL;

            loader.loadStaticTextures(&terrainTexturePath, 1, &terrainTexture);
            terrainTexture02.init(terrainTexture->getId());
        }

        TerrainTexture terrainTexture03; {
            std::string terrainTexturePath = "data/tex/terrain/path.png";
            StaticTexture* terrainTexture = NULL;

            loader.loadStaticTextures(&terrainTexturePath, 1, &terrainTexture);
            terrainTexture03.init(terrainTexture->getId());
        }

        texturePack.init(terrainTexture00, terrainTexture01, terrainTexture02, terrainTexture03);

        // printf("\n\n terrain model init done, press anything to continue ...\n\n"); {
        //     int dbg;
        //     scanf("%d", &dbg);
        // }
    }

    TerrainTexture blendmap; {
        std::string terrainTexturePath = "data/tex/terrain/blendmap.png";
        StaticTexture *terrainTexture = NULL;

        loader.loadStaticTextures(&terrainTexturePath, 1, &terrainTexture);
        blendmap.init(terrainTexture->getId());
    }

    terrain.init(&loader, 0, 0, texturePack, blendmap, "data/tex/terrain/height_map/heightmap.png"); {
        printf("grass tex id: %d.\n", terrain.getTexturePack()->getTerrainTexture00()->getTextureID());
        printf("  mud tex id: %d.\n", terrain.getTexturePack()->getTerrainTexture01()->getTextureID());
        printf("flowertex id: %d.\n", terrain.getTexturePack()->getTerrainTexture02()->getTextureID());
        printf(" path tex id: %d.\n", terrain.getTexturePack()->getTerrainTexture03()->getTextureID());
        printf("blend tex id: %d.\n\n\n", terrain.getBlendMap()->getTextureID());
    }
}

void LoadTargets_03::initSkybox() {
    std::string cloudySky[] = {
        "data/tex/sky/right.png", 
        "data/tex/sky/left.png", 
        "data/tex/sky/back.png", 
        "data/tex/sky/front.png",
        "data/tex/sky/top.png", 
        "data/tex/sky/bottom.png"
    };
    skybox.init(&loader, &cloudySky, 50);

    printf("skybox init done, press anything to continue ...\n\n"); {
        // int dbg;
        // scanf("%d", &dbg);
    }
}

void LoadTargets_03::initGui() {

    float gui_rect_vertices[GUI_RECT_VERTICES_STRIDE * GUI_RECT_VERTICES_NUM] = {
        -1.0f, 1.0,  -1.0f, -1.0f, 
         1.0f, 1.0f,  1.0f, -1.0f
    };
    GuiType00::rect = loader.allocSingleAttributeModel(gui_rect_vertices, GUI_RECT_VERTICES_STRIDE, GUI_RECT_VERTICES_NUM);

    {
        // StaticTexture *guiTexture = NULL; {
        //     std::string guiTexturePath = "data/tex/marker.png";
        //     loader.loadStaticTextures(&guiTexturePath, 1, &guiTexture);
        // }

        // if (guiTexture) {
        //     float gui_pos[] = {-0.75f, 0.75f};
        //     float gui_scale[] = { 0.25f, 0.25f };

        //     gui.init(guiTexture->getId(), &gui_pos, &gui_scale);
        //     printf("gui tex id: %d\n", gui.getTextureID());
        //     // printf("gui addr: 0x%p\n", &gui);
        // }
    }

    {
        float gui_pos[] = { -0.7f, 0.7f };
        float gui_scale[] = { 0.25f, 0.25f };
        gui_00.init(waterFbos.getReflectionTexture(), &gui_pos, &gui_scale);
    }

    {
        float gui_pos[] = { 0.7f, 0.7f };
        float gui_scale[] = { 0.25f, 0.25f };
        gui_01.init(waterFbos.getRefractionTexture(), &gui_pos, &gui_scale);
    }

    printf("gui init done, press anything to continue ...\n\n"); {
        // int dbg;
        // scanf("%d", &dbg);
    }
}

void LoadTargets_03::initWaterTiles() {
    {
        string texture_file = "data/tex/water/waterDUDV.png";
        StaticTexture *texture = NULL;

        loader.loadStaticTextures(&texture_file, 1, &texture);
        if (!texture) {
            printf("  Failed to generate texture for water_dudv\n");
        }
        else {
            water_dudvTexture = texture->getId();

            printf("  Texture for water_dudv generated,");
            printf("    id: %d\n\n", water_dudvTexture);
        }
    }
    {
        string texture_file = "data/tex/water/matchingNormalMap.png";
        StaticTexture *texture = NULL;

        loader.loadStaticTextures(&texture_file, 1, &texture);
        if (!texture) {
            printf("  Failed to generate texture for water_normal\n");
        }
        else {
            water_normalTexture = texture->getId();

            printf("  Texture for water_normal generated,");
            printf("    id: %d\n\n", water_normalTexture);
        }
    }

    // The normalized values from -1 ~ 1 belows corresponds to 
    // vertex-shader's calculation for UV coordinates:
    //    uv = vec2(x/2 + 0.5, y/2 + 0.5)

    // For glDrawArray(trangle_strip) mode
    // float water_tile_vertices[WATER_TILE_VERTICES_STRIDE * WATER_TILE_VERTICES_NUM] = {
    //     -1.0f, 1.0, -1.0f, -1.0f, 
    //      1.0f, 1.0f, 1.0f, -1.0f
    // };
    // WaterTile::rect = loader.loadRawModel(water_tile_vertices, WATER_TILE_VERTICES_STRIDE, WATER_TILE_VERTICES_NUM);

    // TODO: shall be done in water renderer ??? since this is ubiquatous for all water and corresponds to shader
    // Data to be used by glDrawArray(triangle_mode)
    float water_tile_vertices[WATER_TILE_VERTICE_STRIDE * WATER_TILE_TRIANGLES_NUM * 3] = {
        -1, -1,  -1, 1,  1, -1,   // left-bottom triangle (        half rectangle) of a water-tile (square width 2), facing the XY panel
         1, -1,  -1, 1,  1, 1     // right-top triangle   (another half rectangle) facing the XY panel
    };
    WaterTile::rect = loader.allocSingleAttributeModel(water_tile_vertices, WATER_TILE_VERTICE_STRIDE, WATER_TILE_TRIANGLES_NUM * 3);

    // float xyz_offsets[] = {-1.0f, -1.0f, 0.0f};
    // float xyz_offsets[] = {-1.0f, -1.0f, 0.0f};
    float offset[] = {10.0f, 10.0f};
    float xyz_translate[][3] = {
        { 2.5f + offset[0],  2.5f + offset[1], -1.5f},
        {-2.5f + offset[0],  2.5f + offset[1], -1.5f},
        {-2.5f + offset[0], -2.5f + offset[1], -1.5f},
        { 2.5f + offset[0], -2.5f + offset[1], -1.5f}
    };

    for (int i = 0; i < sizeof(xyz_translate) / sizeof(xyz_translate[0]); i++) {
        WaterTile tile(&xyz_translate[i]);
        waterTiles.push_back(tile);
    }

    printf("water tile init done, input any number to continue ...\n\n"); {
        // int dbg;
        // scanf("%d", &dbg);
    }
}
