#include "LoadTargets_04.h"

// #include "Core/Renderers/Model/StaticShader.h"  // for: StaticShader::attr_stride[StaticShader::id0_pos3f]
                                                   // shall be replaced with something better
#define NUM_CRATE (4)

void LoadTargets_04::initCrate() {

    // Modify the 4 init-transforms of the crate-entity
    // in the following lines:
    float crate_transform_values[NUM_CRATE][Entity::transform::max] = {
        { 0.0f,  2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.15f},
        {-2.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.15f},
        { 0.0f, -2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.15f},
        { 2.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.15f}
    };

    Transform crate_transforms[NUM_CRATE]; {
        for (unsigned int i = 0; i < NUM_CRATE; i++) {
            crate_transforms[i].values[Transform::x] = crate_transform_values[i][Transform::x];
            crate_transforms[i].values[Transform::y] = crate_transform_values[i][Transform::y];
            crate_transforms[i].values[Transform::z] = crate_transform_values[i][Transform::z];
            crate_transforms[i].values[Transform::rot_x] = crate_transform_values[i][Transform::rot_x];
            crate_transforms[i].values[Transform::rot_y] = crate_transform_values[i][Transform::rot_y];
            crate_transforms[i].values[Transform::rot_z] = crate_transform_values[i][Transform::rot_z];
            crate_transforms[i].values[Transform::scale] = crate_transform_values[i][Transform::scale];
        }
    }

    Transform *p_crate_transforms[NUM_CRATE]; {
        for (unsigned int i = 0; i < NUM_CRATE; i++) {
            p_crate_transforms[i] = &crate_transforms[i];
        }
    };

    crate.loadModel("data/models/crate/Crate1.obj", loader, p_crate_transforms, NUM_CRATE);

    // Doesnt work before shader is bound/opened/started .... !!!
    // multiLightsShader.loadLights(&light_pos[0], &light_color[0], 4);
}

void LoadTargets_04::initSkybox() {
    std::string cloudySky[] = {
        "data/tex/sky/right.png", 
        "data/tex/sky/left.png", 
        "data/tex/sky/back.png", 
        "data/tex/sky/front.png",
        "data/tex/sky/top.png", 
        "data/tex/sky/bottom.png"
    };
    skybox.init(&loader, &cloudySky, 50);
}

void LoadTargets_04::initWaterTiles() {
    {
        std::string texture_file = "data/tex/water/waterDUDV.png";
        Texture *texture = loader.getTexture(texture_file);

        if (!texture) {
            printf("  Failed to generate texture for water_dudv\n");
        }
        else {
            water_dudvTexture = texture->getID();
            printf("  Texture for water_dudv generated,");
            printf("    id: %d\n\n", water_dudvTexture);
        }
    }
    {
        std::string texture_file = "data/tex/water/matchingNormalMap.png";
        Texture *texture = loader.getTexture(texture_file);

        if (!texture) {
            printf("  Failed to generate texture for water_normal\n");
        }
        else {
            water_normalTexture = texture->getID();
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
    float offset[] = {0.0f, 0.0f};
    float xyz_translate[][3] = {
        { 2.5f + offset[0],  2.5f + offset[1], 0.0f},
        {-2.5f + offset[0],  2.5f + offset[1], 0.0f},
        {-2.5f + offset[0], -2.5f + offset[1], 0.0f},
        { 2.5f + offset[0], -2.5f + offset[1], 0.0f}
    };

    // waterTile[0].init( &xyz_translate[0] );
    // waterTile[1].init( &xyz_translate[1] );
    // waterTile[2].init( &xyz_translate[2] );
    // waterTile[3].init( &xyz_translate[3] );
    for (int i = 0; i < sizeof(xyz_translate) / sizeof(xyz_translate[0]); i++) {
        WaterTile tile(&xyz_translate[i]);
        // tile.init(&xyz_translate[i]);
        waterTiles.push_back(tile);
    }

    printf("water tile init done, input any number to continue ...\n\n"); {
        // int dbg;
        // scanf("%d", &dbg);
    }
}

void LoadTargets_04::initGui() {

    float gui_rect_vertices[GUI_RECT_VERTICES_STRIDE * GUI_RECT_VERTICES_NUM] = {
        -1.0f, 1.0,  -1.0f, -1.0f,
         1.0f, 1.0f,  1.0f, -1.0f
    };
    GuiType00::rect = loader.allocSingleAttributeModel(gui_rect_vertices, GUI_RECT_VERTICES_STRIDE, GUI_RECT_VERTICES_NUM);

    {
        // Texture *guiTexture = NULL; {
        //     std::string guiTexturePath = "data/tex/marker.png";
        //     loader.getTexture(&guiTexturePath, 1, &guiTexture);
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
        // float gui_pos[] = { -0.7f, 0.7f };
        // float gui_scale[] = { 0.125f, 0.25f };
        float gui_pos[] = { -0.7f, 0.0f };
        float gui_scale[] = { 0.25f, 0.5f };

        const string texFile = "data/tex/water/matchingNormalMap.png";
        GuiType00 tmpGui; 
        Texture* tex = loader.getTexture(texFile);
        if (tex) {
            tmpGui.init(tex->getID(), &gui_pos, &gui_scale);
            guis.push_back(tmpGui);
            printf("GUI Tex loaded.\n");
        }
        else{
            printf("!!! GUI Tex failed: %s !!!\n", texFile.c_str());
        }
    }

    {
        float gui_pos[] = { 0.7f, 0.7f };
        float gui_scale[] = { 0.25f, 0.25f };
            // gui[1].init(waterTile[1].getFbo()->getTexture(), &gui_pos, &gui_scale);
    }

    {
        float gui_pos[] = { -0.7f, -0.7f };
        float gui_scale[] = { 0.25f, 0.25f };
            // gui[2].init(waterTile[2].getFbo()->getTexture(), &gui_pos, &gui_scale);
    }

    {
        float gui_pos[] = { 0.7f, -0.7f };
        float gui_scale[] = { 0.25f, 0.25f };
            // gui[3].init(waterTile[3].getFbo()->getTexture(), &gui_pos, &gui_scale);
    }

    printf("gui init done, input any num to continue ...\n\n"); {
        // int dbg;
        // scanf("%d", &dbg);
    }
}
