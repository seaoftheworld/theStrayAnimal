#pragma once

#include "Core/Shader/Base/BaseShader.h"
#include "Core/Common/light.h"


#ifdef Z370_PC
    #define SPECULAR_VSH_PATH "data/shaders/Z370_PC/models/specular.vsh"
    #define SPECULAR_FSH_PATH "data/shaders/Z370_PC/models/specular.fsh"
#elif defined T14sGen1_PC
    #define SPECULAR_VSH_PATH "data/shaders/T14sGen1_PC/model/specular_lighting_vsh.c"
    #define SPECULAR_FSH_PATH "data/shaders/T14sGen1_PC/model/specular_lighting_fsh.c"
#else 
    #define SPECULAR_VSH_PATH "data/shaders/T14sGen1_PC/model/specular_lighting_vsh.c"
    #define SPECULAR_FSH_PATH "data/shaders/T14sGen1_PC/model/specular_lighting_fsh.c"
#endif

class SpecularShader : public BaseShader {

    int texture_sampler_loc = -1,
        lightPosition_loc = -1, 
        lightColor_loc = -1,

        shineDamper_loc = -1,
        reflect_loc = -1;

public:
    SpecularShader() : BaseShader(SPECULAR_VSH_PATH, SPECULAR_FSH_PATH) {
        printf("  SpecularShader constructor().\n");
        call_subclass_init_funcs();
    }
    ~SpecularShader() {
        printf("  SpecularShader destructor().\n");
    }

    void bindAllAttributeLocations() override;
    void getAllUniformLocations() override;

    void bindTextureSamplerToSlot() {
        uniform1i(texture_sampler_loc, 0);
    }

    void loadLight(Light &light) {
        uniform3fv(lightPosition_loc, 1, light.getPosition3fv());
        uniform3fv(lightColor_loc, 1, light.getColor3fv());
    }

    void loadReflectivity(float input) {
        uniform1f(reflect_loc, input);
    }

    void loadShineDamper(float input) {
        uniform1f(shineDamper_loc, input);
    }
};
