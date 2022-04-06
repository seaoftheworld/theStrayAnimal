#include "NoLightingShader.h"

// " This binding takes effect when the program is linked the next time — 
//   it does not change the bindings used by the currently linked program."
void NoLightingShader::bindAllAttributeLocations() {
    // printf("    NoLightingShader::bindAllAttributeLocations() override called.\n");
    bindAttributeLocation(0, "vertexPosition");
    bindAttributeLocation(1, "vertexUV");
    // bindAttributeLocation(ATTR_IDX2_NORMAL, "vertexNormal");
}

void NoLightingShader::getAllUniformLocations() {
    // printf("    NoLightingShader::getAllUniformLocations() override called.\n");    

    setTransformMatLoc(getUniformLocation("transformMatrix"));
    setViewMatLoc(getUniformLocation("viewMatrix"));
    setProjMatLoc(getUniformLocation("projMatrix"));
    texture_sampler_loc = getUniformLocation("texture_sampler");

    printf("    NoLightingShader unifs:\n  \
        transMat-%d, viewMat-%d, projMat-%d, sampler-%d\n", \
        getTransformMatLoc(), \
        getViewMatLoc(), \
        getProjMatLoc(), \
        texture_sampler_loc);
}
