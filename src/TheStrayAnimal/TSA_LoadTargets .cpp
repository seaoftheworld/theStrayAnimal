#include "TSA_LoadTargets.h"

#include "Core/Renderers/Model/StaticShader.h"  // for: StaticShader::attr_stride[StaticShader::id0_pos3f]
                                                // shall be replaced with something better

#define CELL_TRANSLATE_UNIT_X (0.5f)
#define CELL_TRANSLATE_UNIT_Y (0.5f)
#define CELL_TRANSLATE_UNIT_Z (0.5f)
#define CELL_TRANSLATE_DEFAULT_Z      (0)

void TSA_LoadTargets::initOriginSquare() {

    float dummy_pos[] = { -0.5f, 0.5f,  0.0f,
                          0.5f, 0.5f,  0.0f,
                          0.5f, -0.5f, 0.0f,
                         -0.5f, -0.5f, 0.0f };

    float dummy_uv[] = { 0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f,
                        0.0f, 1.0f };

    float dummy_normal[] = { 0.0f, 0.0f, 1.0f,
                             0.0f, 0.0f, 1.0f,
                             0.0f, 0.0f, 1.0f,
                             0.0f, 0.0f, 1.0f };

    float *vertices_attr[] = {
        dummy_pos,
        dummy_uv,
        dummy_normal
    };

    unsigned short test_indices[] = { 0, 1, 2, 0, 3, 2 };

    StaticModel *model = NULL; {
        unsigned int vertices_count_from_pos = ARRAY_SIZE(dummy_pos) / StaticShader::attr_stride[StaticShader::id0_pos3f];
        unsigned int vertices_count_from_uv = ARRAY_SIZE(dummy_uv) / StaticShader::attr_stride[StaticShader::id1_uv2f];
        unsigned int vertices_count_from_normal = ARRAY_SIZE(dummy_normal) / StaticShader::attr_stride[StaticShader::id2_normal3f];

        unsigned int vertices_count = \
            (vertices_count_from_pos == vertices_count_from_uv && \
                vertices_count_from_pos == vertices_count_from_normal) ? (vertices_count_from_pos) : (0);
        unsigned int indices_count = (vertices_count) ? (ARRAY_SIZE(test_indices)) : (0);

        printf("  vertices counts is: %d\n", vertices_count);
        printf("  indices counts are %d\n", indices_count);

        model = loader.loadStaticModel(
            &vertices_attr, vertices_count, test_indices, indices_count
        );

        if (!model) {
            printf("  Failed to generate model for multi_vbo_entity\n");
        }
        else {
            printf("  3D model for origin_square generated,");
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
        std::string texture_file = "data/tex/road.png";

        loader.loadStaticTextures(&texture_file, 1, &texture);
        if (!texture) {
            printf("  Failed to generate texture for multi_vbo_entity\n");
        }
        else {
            printf("  Texture for origin_square generated,");
            printf("    tex-id: %d\n\n", texture->getId());
        }
    }

    if (texture && model) {
        const unsigned short NUM_TRANSFORM = 3;

        origin_square.setTextureModel(texture, model); {
            float trans_values[NUM_TRANSFORM][Entity::transform::max] = {
                { -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  1.0f },
                { -0.5f,  1.5f, 0.0f,  0.0f, 0.0f, 0.0f,  1.0f },
                {  1.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  1.0f }
            };

            for (int i = 0; i < NUM_TRANSFORM; i++) {
                Transform trans(&trans_values[i]);
                origin_square.addTransform(trans);
            }
        }

        // for (unsigned int i = 0; i < 10; i++) {
        //     float trans_values[Entity::transform::max] = {
        //         (float)i * 1.0f + 0.5f, (float)i * 1.0f + 0.1f, (float)i * 1.0f + 0.1f,
        //         0.0f, 0.0f, 0.0f,
        //         (float)i * 0.3f + 0.3f
        //     };
        //     Transform transform(&trans_values);
        //     multi_vbo_entity.addTransform(transform);
        // }
    }
}

void TSA_LoadTargets::initPaw() {

    unsigned int expectedWidth = 32, 
                 expectedHeight = 32,
                 expected_trans_x = 0,
                 expected_trans_y = 0;
    float        expected_rotz = 0; 
    {
        // form the model matrix
        paw.translate_x = expected_trans_x;
        paw.translate_y = expected_trans_y;
        paw.rot_z = expected_rotz;

        // form the attr data for position vbo
        paw.height = expectedHeight;
        paw.width = expectedWidth;
    }

    float rect_vert_2_6_float[2 * 6]; {
        for (unsigned int i = 0; i < (2 * 6); i += 2) {
            rect_vert_2_6_float[i + 0] = (float)(expectedWidth / 2.0f);
            rect_vert_2_6_float[i + 1] = (float)(expectedHeight / 2.0f);
        }

        unsigned int negtiveIdx[] = {
            0, 
            (1 * 2 + 0), (1 * 2 + 1), 
                         (2 * 2 + 1),
                         (3 * 2 + 1),
            (5 * 2 + 0), 
        };
        for (unsigned int i = 0; i < sizeof(negtiveIdx) / sizeof(unsigned int); i++) {
            rect_vert_2_6_float[ negtiveIdx[i] ] = \
                0.0f - rect_vert_2_6_float[ negtiveIdx[i] ];
        }
    }

    SingleAttributeModel *buffer = loader.allocSingleAttributeModel(rect_vert_2_6_float,\
        PICTURE_RENDERER_POS_VBO_VERTICES_STRIDE, \
        PICTURE_RENDERER_POS_VBO_VERTICES_NUM);

    if (buffer) {
        paw.vboId = buffer->getVboID();
    }

    {
    }
}

void TSA_LoadTargets::initGround(AreaData *area_data) {

    if (!area_data) {
        return;
    }

    Transform transform[MAX_CELL_NUM];
    unsigned short num_transform = 0;

    // printf("aaaaaa: area_data->num_cells: %d\n", area_data->num_cells);
    for (int i = 0, offset = 0; i < area_data->num_cells; i++) {
        
        if (area_data->cell[i] == GridCell::ground_only || area_data->cell[i] == GridCell::crate_on_ground) {
            transform[offset].values[Transform::x] = IDX_TO_COORD_X(i) * CELL_TRANSLATE_UNIT_X;
            transform[offset].values[Transform::y] = IDX_TO_COORD_Y(i) * CELL_TRANSLATE_UNIT_Y;
            transform[offset].values[Transform::z] = CELL_TRANSLATE_DEFAULT_Z;
            transform[offset].values[Transform::rot_x] = 0.0f;
            transform[offset].values[Transform::rot_y] = 0.0f;
            transform[offset].values[Transform::rot_z] = 0.0f;
            transform[offset].values[Transform::scale] = 0.25f; offset++;
        }
        else {
            continue;
        }
        num_transform = offset;
    }

    // printf("bbbbbb: ground num_transform: %d\n", num_transform);
    Transform *p_crate_transforms[MAX_CELL_NUM]; {
        for (int i = 0; i < num_transform; i++) {
            p_crate_transforms[i] = &(transform[i]);
            // printf("%2d: x, Y: %f, %f\n", i, \
                p_crate_transforms[i]->values[Transform::x], p_crate_transforms[i]->values[Transform::y]);
        }
        // printf("\n\n");
    };

    ground_obj.loadModel("data/models/ground/Crate1.obj", loader, p_crate_transforms, num_transform);

    // printf("4 lights inited and crate model loaded, press anything to continue ...\n\n"); {
    //     int dbg;
    //     scanf("%d", &dbg);
    // }
}

void TSA_LoadTargets::initPlayer(unsigned int player_pos_idx, float rot) {
    Transform transf; {
        transf.values[Transform::x] = IDX_TO_COORD_X(player_pos_idx) * CELL_TRANSLATE_UNIT_X;
        transf.values[Transform::y] = IDX_TO_COORD_Y(player_pos_idx) * CELL_TRANSLATE_UNIT_Y;
        transf.values[Transform::z] = 1.0f * CELL_TRANSLATE_UNIT_Z - 0.3f;
        transf.values[Transform::rot_x] = 0.0f;
        transf.values[Transform::rot_y] = 0.0f;
        transf.values[Transform::rot_z] = rot;
        transf.values[Transform::scale] = 0.5f;
    }
    Transform *p_transforms = &transf;

    player_obj.loadModel("data/models/player/rb73/rb73_yForward_zUp.obj", loader, &p_transforms, 1);
}

void TSA_LoadTargets::updatePlayer(unsigned int player_pos_idx, float rot) {
    for (auto itr = player_obj.entities.begin(); itr != player_obj.entities.end(); itr++) {
        (*itr).setTransformValue(0, Transform::x, IDX_TO_COORD_X(player_pos_idx) * CELL_TRANSLATE_UNIT_X);
        (*itr).setTransformValue(0, Transform::y, IDX_TO_COORD_Y(player_pos_idx) * CELL_TRANSLATE_UNIT_Y);
        (*itr).setTransformValue(0, Transform::rot_z, rot);
    }
}

void TSA_LoadTargets::initCrate(CratesData *crates_data) {
    if (!crates_data) {
        return;
    }

    Transform transform[MAX_NUM_CRATES];
    unsigned short num_transform = 0;

    for (int i = 0; i < crates_data->num; i++) {
            transform[i].values[Transform::x] = IDX_TO_COORD_X(crates_data->crate[i].xy_pos_idx) * CELL_TRANSLATE_UNIT_X;
            transform[i].values[Transform::y] = IDX_TO_COORD_Y(crates_data->crate[i].xy_pos_idx) * CELL_TRANSLATE_UNIT_Y;
            transform[i].values[Transform::z] = crates_data->crate[i].z * CELL_TRANSLATE_UNIT_Z;
            transform[i].values[Transform::rot_x] = 0.0f;
            transform[i].values[Transform::rot_y] = 0.0f;
            transform[i].values[Transform::rot_z] = 0.0f;
            transform[i].values[Transform::scale] = 0.25f; num_transform++;
    }

    printf("crate num_transform: %d\n", num_transform);
    Transform *p_transforms[MAX_NUM_CRATES]; {
        for (int i = 0; i < num_transform; i++) {
            p_transforms[i] = &(transform[i]);
            // printf("%2d: x, Y: %f, %f\n", i, \
                p_transforms[i]->values[Transform::x], p_transforms[i]->values[Transform::y]);
        }
        // printf("\n\n");
    };

    crate_obj.loadModel("data/models/crate/Crate1.obj", loader, p_transforms, num_transform);
}

void TSA_LoadTargets::updateCrate(CratesData *crates_data, unsigned short i) {
    if (!crates_data || i >= crates_data->num) {
        return;
    }
    // crate_data.transform[i].values[Transform::x] = IDX_TO_COORD_X(crates_data->crate[i].xy_pos_idx) * CELL_TRANSLATE_UNIT_X;
    // crate_data.transform[i].values[Transform::y] = IDX_TO_COORD_Y(crates_data->crate[i].xy_pos_idx) * CELL_TRANSLATE_UNIT_Y;
    // crate_data.transform[i].values[Transform::z] = crates_data->crate[i].z * CELL_TRANSLATE_UNIT_Z;

    for (auto itr = crate_obj.entities.begin(); itr != crate_obj.entities.end(); itr++) {
        (*itr).setTransformValue(i, Transform::x, IDX_TO_COORD_X(crates_data->crate[i].xy_pos_idx) * CELL_TRANSLATE_UNIT_X);
        (*itr).setTransformValue(i, Transform::y, IDX_TO_COORD_Y(crates_data->crate[i].xy_pos_idx) * CELL_TRANSLATE_UNIT_Y);
        (*itr).setTransformValue(i, Transform::z, crates_data->crate[i].z * CELL_TRANSLATE_UNIT_Z);
    }
}

void TSA_LoadTargets::initGoals(GoalsData *goals) {
    if (!goals) {
        return;
    }

    Transform transform[MAX_NUM_GOALS];
    unsigned int num_transforms = 0;
    for (int i = 0; i < goals->num && i < MAX_NUM_GOALS; i++) {
        // transform[i].values[Transform::x] = IDX_TO_COORD_X(goals->goal[i].xy_pos_idx) * CELL_TRANSLATE_UNIT_X;
        // transform[i].values[Transform::y] = IDX_TO_COORD_Y(goals->goal[i].xy_pos_idx) * CELL_TRANSLATE_UNIT_Y;
        transform[i].values[Transform::x] = (goals->goal[i].x) * CELL_TRANSLATE_UNIT_X;
        transform[i].values[Transform::y] = (goals->goal[i].y) * CELL_TRANSLATE_UNIT_Y;
        transform[i].values[Transform::z] = 1 * CELL_TRANSLATE_UNIT_Z;
        transform[i].values[Transform::rot_x] = 0.0f;
        transform[i].values[Transform::rot_y] = 0.0f;
        transform[i].values[Transform::rot_z] = 0.0f;
        transform[i].values[Transform::scale] = 0.125f;
        num_transforms++;
    }

    printf("num of goals inited: %d\n", num_transforms);
    Transform *p_transforms[MAX_NUM_GOALS]; {
        for (int i = 0; i < num_transforms; i++) {
            p_transforms[i] = &(transform[i]);
            // printf("%2d: x, Y: %f, %f\n", i, \
                p_transforms[i]->values[Transform::x], p_transforms[i]->values[Transform::y]);
        }
        // printf("\n\n");
    };

    goal_obj.loadModel("data/models/target/Crate1.obj", loader, p_transforms, num_transforms);
}
void TSA_LoadTargets::deleteGoal(GoalsData *goals, unsigned short i) {
    if (!goals || i >= goals->num) {
        return;
    }

    for (auto itr = goal_obj.entities.begin(); itr != goal_obj.entities.end(); itr++) {
        // (*itr).deleteTransform(i);
        (*itr).setTransformValue(i, Transform::z, 5 * CELL_TRANSLATE_UNIT_Z);
    }
}

void TSA_LoadTargets::initWaterTextures() {
    std::string texture_file;
    {
        texture_file = "data/tex/water/waterDUDV.png";
        StaticTexture* texture = NULL;

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
        texture_file = "data/tex/water/matchingNormalMap.png";
        StaticTexture* texture = NULL;

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
}

void TSA_LoadTargets::initWaterTiles() {
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

    float offset[] = { 0.0f, 0.0f };
    float translate_on_xyz[NUM_WATER_TILES][3] = {
        { 2.5f + offset[0],  2.5f + offset[1], 0.0f},
        {-2.5f + offset[0],  2.5f + offset[1], 0.0f},
        {-2.5f + offset[0], -2.5f + offset[1], 0.0f},
        { 2.5f + offset[0], -2.5f + offset[1], 0.0f}
    };

    for (int i = 0; i < NUM_WATER_TILES; i++) {
        water_tiles[i].init(&(translate_on_xyz[i]));
    }

    // printf("water tiles init done, press anything to continue ...\n\n"); {
    //     int dbg;
    //     scanf("%d", &dbg);
    // }
}

void TSA_LoadTargets::initSkybox() {

    // To make thin-matrix's skybox textures seamless (z foward in his coord):
    //    left:  rotate-right 90
    //    right: rotate-left 90
    //    front: rotate-left/right: 180, use as back
    //    back:  use as front
    //    down:  rotate-left/right: 180
    //
    // To make test-skybox textures correct ???:
    //    left:  rotate-right 90
    //    right: rotate-left 90
    //    back, down: rotate-left/right: 180
    //    front, up: intact
    std::string lessCloudySky[] = {
        "data/tex/sky/less_cloudy/marked/sRight__.png",  // GL_TEXTURE_CUBE_MAP_POSITIVE_X 
        "data/tex/sky/less_cloudy/marked/sLeft__.png",   // GL_TEXTURE_CUBE_MAP_NEGATIVE_X
        "data/tex/sky/less_cloudy/marked/sBack__.png",   // +y  // used back as front to make thin_matrix's texture seamless
        "data/tex/sky/less_cloudy/marked/sFront__.png",  // -y
        "data/tex/sky/less_cloudy/marked/sUp__.png",     // +z
        "data/tex/sky/less_cloudy/marked/sDown__.png"    // -z

        // "data/tex/sky/test_sky/right.png",  // GL_TEXTURE_CUBE_MAP_POSITIVE_X 
        // "data/tex/sky/test_sky/left.png",   // GL_TEXTURE_CUBE_MAP_NEGATIVE_X
        // "data/tex/sky/test_sky/front.png",  // +y
        // "data/tex/sky/test_sky/back.png",   // -y
        // "data/tex/sky/test_sky/up.png",     // +z
        // "data/tex/sky/test_sky/down.png"    // -z
    };
    skybox.init(&loader, &lessCloudySky, 50);

    // printf("skybox init done, press anything to continue ...\n\n"); {
    //     int dbg;
    //     scanf("%d", &dbg);
    // }
}

/*
void LoadTargets_04::initGui() {

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
        float gui_scale[] = { 0.125f, 0.25f };
        gui[0].init(waterTile[0].getFbo()->getTexture(), &gui_pos, &gui_scale);
    }

    {
        float gui_pos[] = { 0.7f, 0.7f };
        float gui_scale[] = { 0.25f, 0.25f };
        gui[1].init(waterTile[1].getFbo()->getTexture(), &gui_pos, &gui_scale);
    }

    {
        float gui_pos[] = { -0.7f, -0.7f };
        float gui_scale[] = { 0.25f, 0.25f };
        gui[2].init(waterTile[2].getFbo()->getTexture(), &gui_pos, &gui_scale);
    }

    {
        float gui_pos[] = { 0.7f, -0.7f };
        float gui_scale[] = { 0.25f, 0.25f };
        gui[3].init(waterTile[3].getFbo()->getTexture(), &gui_pos, &gui_scale);
    }

    printf("gui init done, press anything to continue ...\n\n"); {
        int dbg;
        scanf("%d", &dbg);
    }
}
//*/
