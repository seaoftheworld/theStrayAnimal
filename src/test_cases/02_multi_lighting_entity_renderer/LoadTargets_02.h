#include "LightsPositionsUpdate.h"
#include "Core/AssimpLib.h"
#include "Core/Loader.h"

class LoadTargets_02 {
    // AssimpLib crate;
    // AssimpLib misa;
    size_t crate_start_idx = 0;
    AssimpLib allModels;
    Loader loader;

    void cleanUp() {

        // for (auto misa_entity = misa.entities.begin(); misa_entity != misa.entities.end(); misa_entity++) {
        //     misa_entity->cleanUp();
        // }
        // misa.cleanUp();

        // for (auto crate_entity = crate.entities.begin(); crate_entity != crate.entities.end(); crate_entity++) {
        //     crate_entity->cleanUp();
        // }
        // crate.cleanUp();

        allModels.cleanUp();
        loader.cleanUp();
    }

    void initAllModels();
    // void initCrate();
    // void initMisa();

public:
    LoadTargets_02() {
        cleanUp();

        initAllModels();
        // initCrate();
        // initMisa();
        printf("\nmodels init done, input any Number to continue ...\n"); {
            int dbg;
            // scanf("%d", &dbg);
        }
    }
    virtual ~LoadTargets_02() {
        cleanUp();
    }

    AssimpLib& getModels() {
        return allModels;
    }
    size_t getCrateStartIdx() {
        return crate_start_idx;
    }

    /*
    AssimpLib *getMisa() {
        return &misa;
    }
    AssimpLib *getCrate() {
        return &crate;
    }
    // */
};
