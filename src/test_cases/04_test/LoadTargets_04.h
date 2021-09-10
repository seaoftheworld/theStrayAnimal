#pragma once

#include "Core/AssimpLib.h"
#include "Core/Loader.h"


// #include "Core/Renderers/Terrain/Terrain.h"
// #include "Core/Renderers/Skybox/SkyboxRenderer.h"  // TODO: shall seperate skybox-data with skybox-renderer
// #include "Core/Renderers/Gui/Gui.h"                //       like it is for the other renderers
// #include "Core/Renderers/Water/WaterTile.h"

#include "WrappingRenderer_04.h"  // to include data types for terrain, skybox, gui, and water

// #include "test_cases/02_multi_lighting_entity_renderer/LightsPositionsUpdate.h"

class LoadTargets_04 {
    Loader loader;

    AssimpLib crate;
    Skybox  skybox;

    // GuiType00 gui_00;
    GuiType00 gui[4];

    // WaterFrameBuffers waterFbos;
    unsigned int water_dudvTexture = 0;
    unsigned int water_normalTexture = 0;
    WaterTile waterTile[4];

    void initData() {

        // for (auto rock_entity = rock.entities.begin(); rock_entity != rock.entities.end(); rock_entity++) {
        //     rock_entity->cleanUp();
        // }
        // rock.cleanUp();

        for (auto crate_entity = crate.entities.begin(); crate_entity != crate.entities.end(); crate_entity++) {
            crate_entity->cleanUp();
        }
        crate.cleanUp();

        loader.cleanUp();
    }
    void cleanUp() {
        initData();
        // waterFbos.cleanUp();  // this shall not be called in constructor
    }

    void initCrate();

    void initSkybox();

    void initWaterTiles();
    void initWaterTextures();
    void initGui();

public:
    static float misa_offset_x;
    static float misa_offset_y;

    LoadTargets_04() {
        initData();

        // init entities
        initCrate();
        printf("\n\n crate init done, press anything to continue ...\n\n"); {
            int dbg;
            scanf("%d", &dbg);
        }

        // init skybox
        initSkybox();
        printf("skybox init done, press anything to continue ...\n\n"); {
            int dbg;
            scanf("%d", &dbg);
        }

        // init water
        initWaterTextures();
        initWaterTiles();

        // init gui
        // initGui();
    }
    virtual ~LoadTargets_04() {
        cleanUp();
    }

    GuiType00 *getGui() {
        return gui;
    }

    AssimpLib* getCrate() {
        return &crate;
    }

    Skybox *getSkybox() {
        return &skybox;
    }

    // WaterFrameBuffers *getWaterFbos() {
    //     return &waterFbos;
    // }
    WaterTile *getWaterTiles() {
        return waterTile;
    }
    unsigned int getWaterDudvTexture() {
        return water_dudvTexture;
    }
    unsigned int getWaterNormalTexture() {
        return water_normalTexture;
    }
};
