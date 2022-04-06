#include "SpecularShader.h"


// This is optional, attr idx could be set explicitly within shader
// in latter versions of glsl
void SpecularShader::bindAllAttributeLocations() {
    // printf("    SpecularShader::bindAllAttributeLocations() override called.\n");
    // This binding takes effect when the program is linked the next time—it
    // does not change the bindings used by the currently linked program.
    bindAttributeLocation(0, "vertexPosition");
    bindAttributeLocation(1, "vertexUV");
    bindAttributeLocation(2, "vertexNormal");
}

void SpecularShader::getAllUniformLocations() {
    // printf("    SpecularShader::getAllUniformLocations() override called.\n");
    setTransformMatLoc(getUniformLocation("transformMatrix"));
    setViewMatLoc(getUniformLocation("viewMatrix"));
    setProjMatLoc(getUniformLocation("projMatrix"));
    texture_sampler_loc = getUniformLocation("texture_sampler");

    lightPosition_loc = getUniformLocation("lightPosition");
    lightColor_loc = getUniformLocation("lightColor");
    shineDamper_loc = getUniformLocation("shineDamper");
    reflect_loc = getUniformLocation("reflectivity");

    printf("    SpecularShader unifs:\n" \
        "  transMat-%d, viewMat-%d, projMat-%d, sampler-%d\n", \
        getTransformMatLoc(), \
        getViewMatLoc(), \
        getProjMatLoc(), \
        texture_sampler_loc);
    printf("  light-pos/color-%d/%d, shineDamp/reflect-%d/%d\n", \
        lightPosition_loc, lightColor_loc, shineDamper_loc, reflect_loc);
}
