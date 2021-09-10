#pragma once
#include "Core/Shader/Base/BaseShader.h"

#ifdef Z370_PC
    #define VSH_PATH "data/shaders/Z370_PC/models/image_mod.vsh"
    #define FSH_PATH "data/shaders/Z370_PC/models/image_mod.fsh"
#elif defined T14sGen1_PC
    #define VSH_PATH "data/shaders/T14sGen1_PC/model/no_lighting_vsh.c"
    #define FSH_PATH "data/shaders/T14sGen1_PC/model/no_lighting_fsh.c"
#else 
    #define VSH_PATH "data/shaders/T14sGen1_PC/model/no_lighting_vsh.c"
    #define FSH_PATH "data/shaders/T14sGen1_PC/model/no_lighting_fsh.c"
#endif


class NoLightingShader : public BaseShader {
    int texture_sampler_loc = -1;

public:
    // For all-in-one (Struct-of-arrays) vbo
    enum attrNum {
        id0_pos3f = 0, id1_uv2f, id2_normal3f, 
        max_attrNum
    };

    static const unsigned int attr_idx[max_attrNum];
    static const unsigned int attr_stride[max_attrNum];
    static const unsigned int attr_offset[max_attrNum];
    static const unsigned int all_in_one_stride;

    NoLightingShader() : BaseShader(VSH_PATH, FSH_PATH) {
        printf("  NoLightingShader constructor called.\n");

        // Derived class' 
        //     bindAllAttributeLocations() and 
        //     getAllUniformLocations()
        // will be called in this step
        call_subclass_init_funcs();
    }
    ~NoLightingShader() {
    }

    void bindAllAttributeLocations() override;
    void getAllUniformLocations() override;

    void sampleTextureUnit(unsigned int i) {
        uniform1i(texture_sampler_loc, i);
    }
};
