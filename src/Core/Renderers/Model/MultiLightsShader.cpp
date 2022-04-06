#include "MultiLightsShader.h"

// #define ATTR_IDX0_POS    (0)
// #define ATTR_IDX1_UV     (1)
// #define ATTR_IDX2_NORMAL (2)

// #define ATTR_IDX0_POS_STRD    (3)
// #define ATTR_IDX1_UV_STRD     (2)
// #define ATTR_IDX2_NORMAL_STRD (3)

// static inline unsigned int calculateAllInOneStride() {
//     unsigned int sum = 0;
//     for (unsigned int i = 0; i < MultiLightsShader::max_attrNum; i++) {
//         sum += MultiLightsShader::attr_stride[i];
//     }

//     return sum;
// }

// const unsigned int MultiLightsShader::attr_idx[max_attrNum] = {
//     ATTR_IDX0_POS,
//     ATTR_IDX1_UV, 
//     ATTR_IDX2_NORMAL
// };

// const unsigned int MultiLightsShader::attr_stride[max_attrNum] = {
//     ATTR_IDX0_POS_STRD,
//     ATTR_IDX1_UV_STRD, 
//     ATTR_IDX2_NORMAL_STRD
// };

// const unsigned int MultiLightsShader::attr_offset[max_attrNum] = {
//     0, 
//     attr_stride[0],
//     attr_stride[0] + attr_stride[1]
// };

// const unsigned int MultiLightsShader::all_in_one_stride = calculateAllInOneStride();

void MultiLightsShader::bindAllAttributeLocations() {
    // printf("    override for setting attr-idx called.\n");
    // This binding takes effect when the program is linked the next time—it
    // does not change the bindings used by the currently linked program.
    bindAttributeLocation(0, "vertexPosition");
    bindAttributeLocation(1, "vertexUV");
    bindAttributeLocation(2, "vertexNormal");
}

void MultiLightsShader::getAllUniformLocations() {
    // printf("    override for getting uniform-loc called.\n");
    setTransformMatLoc(getUniformLocation("transformMatrix"));
    setViewMatLoc(getUniformLocation("viewMatrix"));
    setProjMatLoc(getUniformLocation("projMatrix"));
    texture_sampler_loc = getUniformLocation("texture_sampler");

    printf("    multi-lights shader uniforms: %d, %d, %d\n"
        "  transMat-%d, viewMat-%d, projMat-%d, sampler-%d\n", \
        getTransformMatLoc(), \
        getViewMatLoc(), \
        getProjMatLoc(), \
        texture_sampler_loc);

    {
        std::string prefix0 = "lightPosition[";
        std::string prefix1 = "lightColor[";
        std::string prefix2 = "lightAttenuation[";
        
        for (int i = 0; i < SHADER_MAX_LIGHTS; i++) {

            std::string result = prefix0 + std::to_string(i) + "]";
            lightPosition_loc[i] = getUniformLocation(result.c_str());

            result = prefix1 + std::to_string(i) + "]";
            lightColor_loc[i] = getUniformLocation(result.c_str());

            result = prefix2 + std::to_string(i) + "]";
            lightAttenuation_loc[i] = getUniformLocation(result.c_str());

            printf("  for light_pos[%d]:         %d\n", i,    lightPosition_loc[i]);
            printf("  for light_color[%d]:       %d\n", i,       lightColor_loc[i]);
            printf("  for light_attenuation[%d]: %d\n", i, lightAttenuation_loc[i]);
        }
        printf("\n");
    }

    shineDamper_loc = getUniformLocation("shineDamper");
    reflect_loc = getUniformLocation("reflectivity");
    printf("  shineDamper/reflect: %d-%d\n", shineDamper_loc, reflect_loc);
}

void NormalMappedShader::bindAllAttributeLocations() {
    printf("    override for setting attr-idx called.\n");

    // This binding takes effect when the program is linked the next time—it
    // does not change the bindings used by the currently linked program.
    bindAttributeLocation(0, "vertexPosition");
    bindAttributeLocation(1, "vertexUV");
    bindAttributeLocation(2, "vertexNormal");
    bindAttributeLocation(3, "tangent");
}

void NormalMappedShader::getAllUniformLocations() {
    printf("    override for getting uniform-loc called.\n");

    setTransformMatLoc(getUniformLocation("transformMatrix"));
    setViewMatLoc(getUniformLocation("viewMatrix"));
    setProjMatLoc(getUniformLocation("projMatrix"));

    printf("    unif_loc for mvp loc: %d, %d, %d\n\n", 
        getTransformMatLoc(), getViewMatLoc(), getProjMatLoc());

    std::string prefix0 = "lightPosition[";
    std::string prefix1 = "lightColor[";
    std::string prefix2 = "lightAttenuation[";
    
    for (int i = 0; i < SHADER_MAX_LIGHTS; i++) {

        std::string result = prefix0 + std::to_string(i) + "]";
        // std::string result = prefix0 + std::to_string(i);
        // printf("light pos: %s\n", result.c_str());
        lightPosition_loc[i] = getUniformLocation(result.c_str());

        result = prefix1 + std::to_string(i) + "]";
        // result = prefix1 + std::to_string(i);
        // printf("light color: %s\n", result.c_str());
        lightColor_loc[i] = getUniformLocation(result.c_str());

        result = prefix2 + std::to_string(i) + "]";
        // printf("light att: %s\n", result.c_str());
        lightAttenuation_loc[i] = getUniformLocation(result.c_str());

        printf("    unif_loc-%d for light_pos:         %d\n", i,    lightPosition_loc[i]);
        printf("    unif_loc-%d for light_color:       %d\n", i,       lightColor_loc[i]);
        printf("    unif_loc-%d for light_attenuation: %d\n", i, lightAttenuation_loc[i]);
    }
    printf("\n\n");

    texture_sampler_loc = getUniformLocation("texture_sampler");
    normal_map_sampler_loc = getUniformLocation("normal_map_sampler");
    printf("    texture/normal_map sampler loc: %d, %d\n\n", texture_sampler_loc, normal_map_sampler_loc);

    shineDamper_loc = getUniformLocation("shineDamper");
    reflect_loc = getUniformLocation("reflectivity");
    printf("    unif_loc for reflec/shineDamper: %d, %d\n\n", reflect_loc, shineDamper_loc);
}
