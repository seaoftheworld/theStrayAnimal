#pragma once

#include "Core/AssimpLib.h"
#include "Core/Loader.h"


// #include "Core/Renderers/Terrain/Terrain.h"
// #include "Core/Renderers/Skybox/SkyboxRenderer.h"  // TODO: shall seperate skybox-data with skybox-renderer
// #include "Core/Renderers/Gui/Gui.h"                //       like it is for the other renderers
// #include "Core/Renderers/Water/WaterTile.h"

#include "WrappingRenderer.h"  // to include data types for terrain, skybox, gui, and water

#include "test_cases/02_multi_lighting_entity_renderer/LightsPositionsUpdate.h"

class LoadTargets_03 {
    Loader loader;

    size_t crate_start_idx = 0, crate_end_idx = 0;
    AssimpLib models;

    Terrain terrain;
    Skybox  skybox;
    GuiType00 gui_00;
    GuiType00 gui_01;

    vector<WaterTile> waterTiles;
    // WaterTile waterTile[4];
    WaterFrameBuffers waterFbos;
    unsigned int water_dudvTexture = 0;
    unsigned int water_normalTexture = 0;

    void initData() {
        // single_vbo_entity.cleanUp();
        // multi_vbo_entity.cleanUp();

        // for (auto misa_entity = misa.entities.begin(); misa_entity != misa.entities.end(); misa_entity++) {
        //     misa_entity->cleanUp();
        // }
        // for (auto crate_entity = crate.entities.begin(); crate_entity != crate.entities.end(); crate_entity++) {
        //     crate_entity->cleanUp();
        // }
        // for (auto rock_entity = rock.entities.begin(); rock_entity != rock.entities.end(); rock_entity++) {
        //     rock_entity->cleanUp();
        // }

        loader.cleanUp();
        // misa.cleanUp();
        // crate.cleanUp();
        // rock.cleanUp();
        models.cleanUp();
    }
    void cleanUp() {
        initData();
        waterFbos.cleanUp();  // this shall not be called in constructor
    }

    // void initSingleVboEntity();
    // void initMultiVboEntity();
    void initCrate();
    void initMisa();
    void initRock();

    void initTerrain();
    void initSkybox();

    void initWaterTiles();
    void initGui();

public:
    static float misa_offset_x;
    static float misa_offset_y;

    LoadTargets_03() {
        initData();
        // init entities
        // initSingleVboEntity();
        // initMultiVboEntity();

        initCrate();
        initMisa();

        // init terrain
        initTerrain();
        initRock();

        // init skybox
        initSkybox();

        // init water
        initWaterTiles();

        // Init GUI
        // initGui();
    }
    virtual ~LoadTargets_03() {
        cleanUp();
    }

    // Entity *getSingleVboEntity() {
    //     return &single_vbo_entity;
    // }
    // Entity *getMultiVboEntity() {
    //     return &multi_vbo_entity;
    // }

    // AssimpLib *getCrate() {
    //     return &crate;
    // }
    // AssimpLib *getMisa() {
    //     return &misa;
    // }
    // AssimpLib *getRock() {
    //     return &rock;
    // }
    AssimpLib &getModels() {
        return models;
    }
    size_t getCrateStartIdx() { return crate_start_idx; }
    size_t getCrateEndIdx() { return crate_end_idx; }

    Terrain *getTerrain() {
        return &terrain;
    }
    Skybox *getSkybox() {
        return &skybox;
    }

    GuiType00 *getGui00() {
        return &gui_00;
    }
    GuiType00* getGui01() {
        return &gui_01;
    }

    WaterFrameBuffers *getWaterFbos() {
        return &waterFbos;
    }
    std::vector<WaterTile> &getWaterTiles() {
        return waterTiles;
    }
    unsigned int getWaterDudvTexture() {
        return water_dudvTexture;
    }
    unsigned int getWaterNormalTexture() {
        return water_normalTexture;
    }
};
