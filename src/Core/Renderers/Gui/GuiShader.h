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

class PictureShader : public BaseShader {
public:
    PictureShader() : BaseShader("afadfs", "adsfadsf") {
    }
    ~PictureShader() {
    }
    void bindAllAttributeLocations() override {};
    void getAllUniformLocations() override {};
};
