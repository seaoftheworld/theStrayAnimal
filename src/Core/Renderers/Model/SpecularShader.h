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

        objShineDamper_loc = -1,
        objReflect_loc = -1;

public:
    // enum attrNum {
    //     id0_pos3f = 0, id1_uv2f, id2_normal3f, max_attrNum
    // };
    // static const unsigned int attr_idx[max_attrNum];
    // static const unsigned int attr_stride[max_attrNum];
    // static const unsigned int attr_offset[max_attrNum];
    // static const unsigned int all_in_one_stride;

    SpecularShader() : BaseShader(SPECULAR_VSH_PATH, SPECULAR_FSH_PATH) {
        
        printf("  SpecularShader constructor called.\n");
        call_subclass_init_funcs();

        // enable specific settings
        // specificSettingsOn();
    }
    ~SpecularShader(){
    }

    void bindAllAttributeLocations() override;
    void getAllUniformLocations() override;

    // void loadAlpha(float p) {
    //     uniform1f(alpha_loc, p);
    // }
    void loadLight(Light &light) {
        uniform3fv(lightPosition_loc, 1, light.getPosition3fv());
        uniform3fv(lightColor_loc, 1, light.getColor3fv());
    }

    void loadReflectivity(float input) {
        uniform1f(objReflect_loc, input);
    }

    void loadShineDamper(float input) {
        uniform1f(objShineDamper_loc, input);
    }

    void sampleTextureUnit(unsigned int i) {
        uniform1i(texture_sampler_loc, i);
    }
};
