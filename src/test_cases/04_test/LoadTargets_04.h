#pragma once

#include "Core/AssimpLib.h"
#include "Core/Loader.h"


// #include "Core/Renderers/Terrain/Terrain.h"
// #include "Core/Renderers/Skybox/SkyboxRenderer.h"  // TODO: shall seperate skybox-data with skybox-renderer
// #include "Core/Renderers/Gui/Gui.h"                //       like it is for the other renderers
// #include "Core/Renderers/Water/WaterTile.h"

#include "WrappingRenderer_04.h"  // to include data types for terrain, skybox, gui, and water

class LoadTargets_04 {
    Loader loader;

    AssimpLib crate;
    Skybox  skybox;

    // WaterFrameBuffers waterFbos;
    unsigned int water_dudvTexture = 0;
    unsigned int water_normalTexture = 0;
    std::vector<WaterTile> waterTiles;
    // WaterTile waterTile[4];

    // GuiType00 gui_00;
    GuiType00 gui[4];

    void initData() {

        // for (auto rock_entity = rock.entities.begin(); rock_entity != rock.entities.end(); rock_entity++) {
        //     rock_entity->cleanUp();
        // }
        // rock.cleanUp();

        // for (auto crate_entity = crate.entities.begin(); crate_entity != crate.entities.end(); crate_entity++) {
        //     crate_entity->cleanUp();
        // }
        loader.cleanUp();
        crate.cleanUp();
    }
    void cleanUp() {
        initData();
        // waterFbos.cleanUp();  // this shall not be called in constructor
    }

    void initSkybox();
    void initCrate();

    void initWaterTiles();
    void initGui();

public:
    static float misa_offset_x;
    static float misa_offset_y;

    LoadTargets_04() {
        initData();

        // init entities
        initCrate();
        printf("\n\n crate init done, press anything to continue ...\n\n"); {
            // int dbg;
            // scanf("%d", &dbg);
        }

        // init skybox
        initSkybox();
        printf("skybox init done, press anything to continue ...\n\n"); {
            // int dbg;
            // scanf("%d", &dbg);
        }

        // init water
        initWaterTiles();

        // Init GUI
        initGui();
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
    // WaterTile *getWaterTiles() {
    //     return waterTile;
    // }
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
