// #pragma once

#include "Core/Shader/Base/BaseShader.h"


#ifdef Z370_PC
    // #define GUI_VSH_PATH "data/shaders/Gui/Gui.vsh"
    // #define GUI_FSH_PATH "data/shaders/Gui/Gui.fsh"
    #define GUI_VSH_PATH "data/shaders/Z370_PC/models/specular.vsh"
    #define GUI_FSH_PATH "data/shaders/Z370_PC/models/specular.fsh"
#elif defined T14sGen1_PC
    #define GUI_VSH_PATH "data/shaders/T14sGen1_PC/gui/gui_vsh.c"
    #define GUI_FSH_PATH "data/shaders/T14sGen1_PC/gui/gui_fsh.c"
#else 
    #define GUI_VSH_PATH "data/shaders/T14sGen1_PC/gui/gui_vsh.c"
    #define GUI_FOR_FBO_VSH_PATH "data/shaders/T14sGen1_PC/gui/gui_for_fbo_vsh.c"
    #define GUI_FSH_PATH "data/shaders/T14sGen1_PC/gui/gui_fsh.c"
#endif

class GuiType00Shader : public BaseShader {

public:
    // enum attrNum {
    //     id0_pos2f = 0, max_attrNum
    // };

    // static const unsigned int attr_idx[max_attrNum];
    // static const unsigned int attr_stride[max_attrNum];
    // static const unsigned int attr_offset[max_attrNum];
    // static const unsigned int all_in_one_stride;

    GuiType00Shader(bool forFBO) : BaseShader((forFBO) ? (GUI_FOR_FBO_VSH_PATH) : (GUI_VSH_PATH), GUI_FSH_PATH) {
        printf("  subclass constructor called.\n");
        call_subclass_init_funcs();

        // enable specific settings
        // specificSettingsOn();
    }
    ~GuiType00Shader() {
    }

    void bindAllAttributeLocations() override;
    void getAllUniformLocations() override;

    // void sampleTextureUnit(unsigned int i) {
    //     uniform1i();
    // }
};

#define CONTRAST_VSH_PATH "data/shaders/T14sGen1_PC/postProcessing/contrast_vsh.c"
#define CONTRAST_FSH_PATH "data/shaders/T14sGen1_PC/postProcessing/contrast_fsh.c"

class ContrastShader : public BaseShader {

public:
    ContrastShader() : BaseShader(CONTRAST_VSH_PATH, CONTRAST_FSH_PATH) {
        printf("  subclass constructor called.\n");
        call_subclass_init_funcs();

        // enable specific settings
        // specificSettingsOn();
    }
    ~ContrastShader() {
    }

    void bindAllAttributeLocations() override;
    void getAllUniformLocations() override;
};

#define HBLUR_VSH_PATH "data/shaders/T14sGen1_PC/postProcessing/blur_hor_vsh.c"
#define VBLUR_VSH_PATH "data/shaders/T14sGen1_PC/postProcessing/blur_ver_vsh.c"
#define VBLUR_FSH_PATH "data/shaders/T14sGen1_PC/postProcessing/blur_fsh.c"

class BlurShader : public BaseShader {
    int horResolution_loc = -1,
        verResolution_loc = -1;

public:
    enum class ShaderType {
        horizonal_blur = 0,
        vertical_blur
    };

    BlurShader(ShaderType type) : \
    BaseShader((type == ShaderType::horizonal_blur) ? (HBLUR_VSH_PATH) : (VBLUR_VSH_PATH), VBLUR_FSH_PATH) {
        printf("  subclass constructor called.\n");
        call_subclass_init_funcs();

        // enable specific settings
        // specificSettingsOn();
    }
    ~BlurShader() {
    }

    void loadHorResolution(float input) {
        uniform1f(horResolution_loc, input);
    }

    void loadVerResolution(float input) {
        uniform1f(verResolution_loc, input);
    }

    void bindAllAttributeLocations() override;
    void getAllUniformLocations() override;
};

// class PictureShader : public BaseShader {
// public:
//     PictureShader() : BaseShader("afadfs", "adsfadsf") {
//     }
//     ~PictureShader() {
//     }
//     void bindAllAttributeLocations() override {};
//     void getAllUniformLocations() override {};
// };
