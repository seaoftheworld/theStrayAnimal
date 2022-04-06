#include "data.h"
// #include "Core/Renderers/Model/StaticShader.h"

// Vbos info for Arrays-of-struct multi-vbo type's model
// -----------------------------------------------------
/*
const unsigned int StaticModel::vbo_atrr_idx[vboNum] = {
    // each vbo's corresponding attr index-num in shader
    NoLightingShader::attr_idx[NoLightingShader::id0_pos3f],
    NoLightingShader::attr_idx[NoLightingShader::id1_uv2f],
    NoLightingShader::attr_idx[NoLightingShader::id2_normal3f]
    // 0
};

const unsigned int StaticModel::vbo_stride[vboNum] = {
    // each vbo's corresponding attr stride (by float) in shader
    NoLightingShader::attr_stride[NoLightingShader::id0_pos3f],
    NoLightingShader::attr_stride[NoLightingShader::id1_uv2f],
    NoLightingShader::attr_stride[NoLightingShader::id2_normal3f]
    // 0
};
// */

const unsigned int StaticModel::vbo_atrr_idx[vboNum] = {
    // each vbo's corresponding attr index-num in shader
    0, 1, 2
};

const unsigned int StaticModel::vbo_stride[vboNum] = {
    // each vbo's corresponding attr stride (by float) in shader
    3, 2, 3
};

// Valid-attributes' info in a single-vbo (Struct-of-arrays type's model)
// --------------------------------------
/*
static unsigned int calculate_single_vbo_stride() {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < StaticModel_SingleVbo::valid_attr_num; i++) {
        sum += StaticModel_SingleVbo::valid_attr_stride[i];
    }
    return sum;
}

const unsigned int StaticModel_SingleVbo::valid_attr_idx[valid_attr_num] = {
    // each valid attribute's index number from the shader
    NoLightingShader::attr_idx[NoLightingShader::id0_pos3f],
    NoLightingShader::attr_idx[NoLightingShader::id1_uv2f],
    NoLightingShader::attr_idx[NoLightingShader::id2_normal3f]
};

const unsigned int StaticModel_SingleVbo::valid_attr_stride[valid_attr_num] = {
    // each valid attribute's stride (in float) from  the shader
    NoLightingShader::attr_stride[NoLightingShader::id0_pos3f],
    NoLightingShader::attr_stride[NoLightingShader::id1_uv2f],
    NoLightingShader::attr_stride[NoLightingShader::id2_normal3f]
};

const unsigned int StaticModel_SingleVbo::valid_attr_offset[valid_attr_num] = {
    // each valid attribute's offset (in float) (used when rendering)
    0,
    NoLightingShader::attr_stride[NoLightingShader::id0_pos3f] * sizeof(float), // offset is measured in Bytes when rendering
    (NoLightingShader::attr_stride[NoLightingShader::id0_pos3f] + NoLightingShader::attr_stride[NoLightingShader::id1_uv2f]) * sizeof(float)
};
// */

static unsigned int calculate_single_vbo_stride() {
    unsigned int sum = 0;
    // for (unsigned int i = 0; i < StaticModel_SingleVbo::valid_attr_num; i++) {
    //     sum += StaticModel_SingleVbo::valid_attr_stride[i];
    // }
    return sum;
}

const unsigned int StaticModel_SingleVbo::valid_attr_idx[valid_attr_num] = {
    // each valid attribute's index number from the shader
    0, 1, 2
};

const unsigned int StaticModel_SingleVbo::valid_attr_stride[valid_attr_num] = {
    // each valid attribute's stride (in float) from  the shader
    3, 2, 3
};

const unsigned int StaticModel_SingleVbo::valid_attr_offset[valid_attr_num] = {
    // each valid attribute's offset (in float) (used when rendering)
    0, 3 * sizeof(float), // offset is measured in Bytes when rendering
    (3 + 2) * sizeof(float)
};

const unsigned int StaticModel_SingleVbo::single_vbo_stride_in_float = calculate_single_vbo_stride();
