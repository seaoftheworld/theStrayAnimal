// #pragma once

#include "TheStrayAnimal.h"  // use the 'area_data' from this header to init the 'grounds' data here

#include "Core/AssimpLib.h"
#include "Core/Loader.h"

// #include "Core/Renderers/Terrain/Terrain.h"
// #include "Core/Renderers/Skybox/SkyboxRenderer.h"  // TODO: shall seperate skybox-data with skybox-renderer
// #include "Core/Renderers/Gui/Gui.h"                //       like it is for the other renderers
// #include "Core/Renderers/Water/WaterTile.h"

#include "TSA_WrappingRenderer.h"  // to include data types for terrain, skybox, gui, and water
#include "LevelData.h"


class TSA_LoadTargets {

    static const unsigned char NUM_WATER_TILES = 4;
    WaterTile water_tiles[NUM_WATER_TILES];
    unsigned int water_normalTexture = 0;
    unsigned int water_dudvTexture = 0;

    // Entity origin_square;
    // AssimpLib misa;
    // AssimpLib rock;
    // AssimpLib crate;  // used for the ground now
    
    // Loader &loader;
    Loader loader;
    
    size_t crate_start_idx = 0, crate_end_idx = 0;
    size_t player_start_idx = 0, player_end_idx = 0;
    size_t goals_start_idx = 0, goals_end_idx = 0;
    AssimpLib ground_crates_models;
    AssimpLib player_goals_models;

    // AssimpLib ground_obj;
    // AssimpLib crate_obj;
    // AssimpLib goal_obj;
    // AssimpLib player_obj;


    // Terrain terrain;
    // GuiType00 gui_00;
    // GuiType00 gui[4];
    Skybox  skybox;

    // WaterFrameBuffers waterFbos;
    // unsigned int water_dudvTexture = 0;
    // unsigned int water_normalTexture = 0;
    // WaterTile waterTile[4];

    Picture paw;

    void clearData() {
        // origin_square.cleanUp();
        /*
        for (auto entity = ground_obj.entities.begin(); entity != ground_obj.entities.end(); entity++) {
            entity->cleanUp();
        }
        for (auto entity = crate_obj.entities.begin(); entity != crate_obj.entities.end(); entity++) {
            entity->cleanUp();
        }
        for (auto entity = goal_obj.entities.begin(); entity != goal_obj.entities.end(); entity++) {
            entity->cleanUp();
        }
        for (auto entity = player_obj.entities.begin(); entity != player_obj.entities.end(); entity++) {
            entity->cleanUp();
        }
        ground_obj.cleanUp();
        crate_obj.cleanUp();
        goal_obj.cleanUp();
        player_obj.cleanUp();
        // */

        // loader.cleanUp();
    }

    // void cleanUp() {
    //     // waterFbos.cleanUp();  // this shall not be called in constructor
    //     clearData();
    // }

public:
    // void initSingleVboEntity();
    // void initMultiVboEntity();
    // void initMisa();
    // void initRock();
    // void initOriginSquare();
    void initGround(AreaData *area_data);

    void updateCrate(CratesData *crates_data, unsigned short i);       // update the 1 of the transform values
    void initCrate(CratesData *crates_data);                           // init transforms of the crate-entity

    void updatePlayer(unsigned int player_pos_idx, float rot);
    void initPlayer(unsigned int player_pos_idx, float rot);

    void deleteGoal(GoalsData *goals, unsigned short i);
    void initGoals(GoalsData *goals);

    void initWaterTextures();
    void initWaterTiles();

    // void initTerrain();
    void initSkybox();
    // void initWaterTiles();
    // void initWaterTextures();
    // void initGui();

    void initPaw();

public:
    void setData(TheStrayAnimal &tsa) {

        clearData();
        // initOriginSquare();

        initGround(tsa.getAreaData());
        initCrate(tsa.getCratesData());
        initGoals(tsa.getGoalsData());
        initPlayer(tsa.getPlayerPosition(), 0.0f);

        // printf("\n\n models/entities init done, press anything to continue ...\n\n"); {
        //     int dbg;
        //     scanf("%d", &dbg);
        // }

        // init terrain
        // initTerrain();

        // init skybox
        initSkybox();

        // init water
        initWaterTextures();
        initWaterTiles();

        // init gui
        // initGui();
    }

public:
    // static float misa_offset_x;
    // static float misa_offset_y;

    // TSA_LoadTargets(Loader &r_ldr) : loader(r_ldr) {
    TSA_LoadTargets() {
        clearData();
    }
    virtual ~TSA_LoadTargets() {
        clearData();
        loader.cleanUp();
    }

public:
    // Entity *getOriginSquare() {
    //     return &origin_square;
    // }

    /*
    AssimpLib *getPlayer() {
        return &player_obj;
    }
    AssimpLib *getGoal() {
        return &goal_obj;
    }
    // */
    std::vector<TexturedModel>& getPlayerGoals() {
        return player_goals_models.texturedModels;
    }

    /*
    AssimpLib *getGround() {
        return &ground_obj;
    }
    AssimpLib *getCrate() {
        return &crate_obj;
    }
    // */
    std::vector<TexturedModel>& getGroudCrates() {
        return ground_crates_models.texturedModels;
    }

    Skybox *getSkybox() {
        return &skybox;
    }

    void getWaterTextures(unsigned int &dudv, unsigned int &normal) {
        normal = water_normalTexture;
        dudv = water_dudvTexture;
    }
    unsigned char getWaterTilesNum() {
        return NUM_WATER_TILES;
    }
    WaterTile *getWaterTiles() {
        return water_tiles;
    }
    // Terrain* getTerrain() {
    //     return &terrain;
    // }
    // GuiType00* getGui00() {
    //     return &gui_00;
    // }
    // GuiType00* getGui01() {
    //     return &gui_01;
    // }
    // GuiType00 *getGui() {
    //     return gui;
    // }

    Picture *getPaw() {
        return &paw;
    }

    // AssimpLib* getCrate() {
    //     return &crate;
    // }

    // // WaterFrameBuffers *getWaterFbos() {
    // //     return &waterFbos;
    // // }
    // WaterTile *getWaterTiles() {
    //     return waterTile;
    // }
    // unsigned int getWaterDudvTexture() {
    //     return water_dudvTexture;
    // }
    // unsigned int getWaterNormalTexture() {
    //     return water_normalTexture;
    // }
};

// info read from level data (for the ground) ==fill==> object of this data-struct
// struct GroundTransformData {
//     Transform transform[MAX_CELL_NUM];
//     unsigned short num_transform = 0;
// };

// struct CrateTransformData {
//     Transform transform[MAX_NUM_CRATES];
//     unsigned short num_transform = 0;
// };

// GroundTransformData ground_data;
// CrateTransformData crate_data;  // useless, could be replaced by a temporery variant
