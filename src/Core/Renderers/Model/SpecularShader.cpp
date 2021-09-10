#include "SpecularShader.h"

#define ATTR_IDX0_POS    (0)
#define ATTR_IDX1_UV     (1)
#define ATTR_IDX2_NORMAL (2)

// #define ATTR_IDX0_POS_STRD    (3)
// #define ATTR_IDX1_UV_STRD     (2)
// #define ATTR_IDX2_NORMAL_STRD (3)

// static inline unsigned int calculateAllInOneStride() {
//     unsigned int sum = 0;
//     for (unsigned int i = 0; i < SpecularShader::max_attrNum; i++) {
//         sum += SpecularShader::attr_stride[i];
//     }

//     return sum;
// }

// const unsigned int SpecularShader::attr_idx[max_attrNum] = {
//     ATTR_IDX0_POS,
//     ATTR_IDX1_UV, 
//     ATTR_IDX2_NORMAL
// };

// const unsigned int SpecularShader::attr_stride[max_attrNum] = {
//     ATTR_IDX0_POS_STRD,
//     ATTR_IDX1_UV_STRD, 
//     ATTR_IDX2_NORMAL_STRD
// };

// const unsigned int SpecularShader::attr_offset[max_attrNum] = {
//     0, 
//     attr_stride[0],
//     attr_stride[0] + attr_stride[1]
// };

// const unsigned int SpecularShader::all_in_one_stride = calculateAllInOneStride();


// This is optional, attr idx could be set explicitly within shader
// in latter versions of gl
void SpecularShader::bindAllAttributeLocations() {
    printf("    SpecularShader::bindAllAttributeLocations() override called.\n");

    // This binding takes effect when the program is linked the next time—it
    // does not change the bindings used by the currently linked program.
    bindAttributeLocation(ATTR_IDX0_POS,    "vertexPosition");
    bindAttributeLocation(ATTR_IDX1_UV,     "vertexUV");
    bindAttributeLocation(ATTR_IDX2_NORMAL, "vertexNormal");

    // print out attributes idx for dbg
    //... ...
}

void SpecularShader::getAllUniformLocations() {
    printf("    SpecularShader::getAllUniformLocations() override called.\n");

    setTransformMatLoc(getUniformLocation("transformMatrix"));
    setViewMatLoc(getUniformLocation("viewMatrix"));
    setProjMatLoc(getUniformLocation("projMatrix"));
    texture_sampler_loc = getUniformLocation("texture_sampler");

    lightPosition_loc = getUniformLocation("lightPosition");
    lightColor_loc = getUniformLocation("lightColor");

    objShineDamper_loc = getUniformLocation("shineDamper");
    objReflect_loc = getUniformLocation("reflectivity");

    printf("    unif_loc: transMat-%d, viewMat-%d, projMat-%d, sampler-%d\n", 
        getTransformMatLoc(), \
        getViewMatLoc(), \
        getProjMatLoc(), \
        texture_sampler_loc);

    printf("              light_pos-%d, light-color-%d\n", lightPosition_loc, lightColor_loc);
    printf("              reflect-%d, shineDamper-%d \n\n", objReflect_loc, objShineDamper_loc);
}
