#include "LoadTargets_02.h"

/*
void LoadTargets_02::initMisa() {

    float values[TexturedModel::transform::max] = {
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                1.0f
    };
    Transform transform(&values);
    Transform *transforms = &transform;

    // TODO: improve meshes' hierachy
    // misa.loadModel("data/models/misa/misa_yForward_zUp.obj", loader, &transforms, 1);
    misa.loadModel("data/models/player/rb73/rb73_yForward_zUp.obj", loader, &transforms, 1);
}
// */

// void LoadTargets_02::initCrate() {
void LoadTargets_02::initAllModels() {

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
    crate_start_idx = allModels.texturedModels.size();
    allModels.loadModel("data/models/crate/Crate1.obj", loader, p_crate_transforms, NUM_LIGHTS);
    // crate_start_idx = allModels.normalMappedModels.size();
    // allModels.loadModel("data/models/crate/Crate1.obj", loader, p_crate_transforms, NUM_LIGHTS, true);

    {
        float values[Transform::max] = {
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                1.0f
        };
        Transform transform(&values);
        Transform* transforms = &transform;

        // TODO: improve meshes' hierachy
        // misa.loadModel("data/models/misa/misa_yForward_zUp.obj", loader, &transforms, 1);

        //*
        size_t rb73_start_idx = allModels.texturedModels.size();
        allModels.loadModel("data/models/player/rb73/rb73_yForward_zUp.obj", loader, &transforms, 1);
        size_t rb73_end_idx = allModels.texturedModels.size();
        // */

        /*
        size_t rb73_start_idx = allModels.normalMappedModels.size();
        allModels.loadModel("data/models/player/rb73/rb73_yForward_zUp.obj", loader, &transforms, 1, true);
        size_t rb73_end_idx = allModels.normalMappedModels.size();

        Texture* rb73_nmap = loader.getTexture("data/models/player/rb73/mtl/robot_Normal_OpenGL.png");
        // Texture* rb73_nmap = loader.getTexture("data/models/others/barrel/barrelNormal.png");
        std::vector<TexturedModel>::iterator ir_rb73_mesh = allModels.normalMappedModels.begin() + rb73_start_idx;
        for (; ir_rb73_mesh != allModels.normalMappedModels.begin() + rb73_end_idx; ir_rb73_mesh++) {
            ir_rb73_mesh->setNormalMap(rb73_nmap);
        }
        // */
    }
}
