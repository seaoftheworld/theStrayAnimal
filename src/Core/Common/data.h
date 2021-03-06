#pragma once

#include <algorithm> 
#include <vector>

// StaticModel's data shall be compatible with StaticShader
// shall be moved into cpp ???
// #include "../Shader/StaticShader.h"

#define ARRAY_SIZE(array_name) (sizeof(array_name) / sizeof(array_name[0]))
#define MAX_TEXTURE_NUM_ONCE (16)

// enum class StaticModelBufferId {
//     // pos = 0, uv, normal, indices, max
//     pos = 0, uv, indices, max
// };
// #define BID(ID) ( (unsigned int)StaticModelBufferId::ID )

/*
namespace StaticModel__ {
    
    enum BufferId {
        // pos_buff = 0, uv_buff, normal_buff, indices_buff, static_model_buff_num
        pos_buff = 0, uv_buff, indices_buff, buff_num
    };

    const unsigned int attrStrideInFloat[buff_num - 1] = {
        3, // pos_stride = 3, 
        2, // uv_stride = 2, indices_buff, static_model_buff_num
    };
}
// */

class StaticTexture {
public:
    StaticTexture(int texture_id) {
        id = texture_id;
    }

    int getId() {
        return id;
    }

    // void setReflect(float input) {
    //     reflectivity = input;
    // }
    // void setShineDamper(float input) {
    //     shineDamper = input;
    // }

    // float getReflect() {
    //     return reflectivity;
    // }
    // float getShineDamper() {
    //     return shineDamper;
    // }

private:
    int id;
    // float reflectivity = 10.0f;
    // float shineDamper = 10.0f;
};

class Texture {
    float reflectivity = 1;
    float shineDamper = 10.0f;
    unsigned int id;
public:
    Texture(unsigned int tid) : id(tid) {}
    unsigned int getID() {return id;}

    float getReflect() {
        return reflectivity;
    }
    void setReflect(float reflectivity) {
        this->reflectivity = reflectivity;
    }
    float getShineDamper() {
        return shineDamper;
    }
    void setShineDamper(float shineDamper) {
        this->shineDamper = shineDamper;
    }
};

class VaoModel {
    unsigned int vertexCount = 0;
    unsigned int vaoID = 0;
public:
    VaoModel(unsigned int vao, unsigned int count) {
        vertexCount = count;
        vaoID = vao;
    }
    unsigned int getVaoID() {
        return vaoID;
    }
    unsigned int getVertexCount() {
        return vertexCount;
    }
};

class BaseModel {
public:
    typedef enum model_type_t {
        multi_vbos, single_vbo
    } model_type;

    virtual model_type getModelType() = 0;
};

// class SingleVboModel : BaseModel {
// };

class StaticModel_SingleVbo : public BaseModel {

public:
    // single_vbo type (Struct-of-arrays)
    virtual model_type getModelType() override {
        return single_vbo;
    }

    static const unsigned int valid_attr_num = 3;

    static const unsigned int valid_attr_idx[valid_attr_num];
    static const unsigned int valid_attr_stride[valid_attr_num];
    static const unsigned int valid_attr_offset[valid_attr_num];
    static const unsigned int single_vbo_stride_in_float;

    StaticModel_SingleVbo(int input_vbo_id, int input_ibo_id, unsigned int input_num_indices) {

        vbo_id = input_vbo_id;
        ibo_id = input_ibo_id;
        num_indices = input_num_indices;
    }

    unsigned int getNumIndices() {
        return num_indices;
    }

    int getVboId(void) {
        return vbo_id;
    }

    int getIboId(void) {
        return ibo_id;
    }

    // void getVboIboIds(int *vbo, int *ibo) {
    //     if (vbo) {
    //         *vbo = vbo_id;
    //     }
    //     if (ibo) {
    //         *ibo = ibo_id;
    //     }
    // }

private:
    // static const model_type type = single_vbo;
    unsigned int num_indices;
    int vbo_id, ibo_id;
};

// TODO: made it into a class derived from BaseModel
// StaticModel's data shall be compatible with StaticShader
class StaticModel : public BaseModel {

public:
    virtual model_type getModelType() override {
        return multi_vbos;
    }

    // multi_vbos type (Array-of-structs)
    static const unsigned short vboNum = 3;                 // pos, uv, normal
    static const unsigned short allBuffNum = (vboNum + 1);  // 2 vbos + 1 ibo
    
    static const unsigned int vbo_atrr_idx[vboNum];
    static const unsigned int vbo_stride[vboNum];

    StaticModel(int input_values[][allBuffNum], unsigned int input_num_indices) {
        std::fill_n(buffers, allBuffNum, -1);
        setBuffers(input_values);
        num_indices = input_num_indices;
    }

    void getBuffers(int output_buffer[][allBuffNum]) {
        if (output_buffer) {
            for (int i = 0; i < allBuffNum; i++) {
                (*output_buffer)[i]  = buffers[i];
            }
        }
    }

    unsigned int getNumIndices() {
        return num_indices;
    }

private:
    // multi_vbos type (Array-of-structs)
    // static const model_type type = multi_vbos;

    int buffers[allBuffNum];
    unsigned int num_indices;

    void setBuffers(int input_values[][allBuffNum]) {
        if (input_values) {
            for (int i = 0; i < allBuffNum; i++) {
                buffers[i] = (*input_values)[i];
            }
        }
    }
};

// The following data-structure is used for generating a 'simple' 3d-model (a few triangles), 
// like the model for skybox-cube, GUI-rectangle, water-tile rectangle ... 
//
// This structure contains info for only 1 vbo of data for attribute-0 in the corresponding glsl-shader,
// which usually indicates vertices' positions, a vertex's uv information for texture 
// can be generated according to its position.
//
// Models for skybox, gui or water-tile generated from this class
// doesn't have normal information in this structure either,
// though it could be calculated according to pos in shader.
//
// It does not include Texture-id info, texture-id has to be bind seperately before drawing.
//
// To draw this model, 
//     1. bind the vbo-id first by calling                            getVboID(), then enable the corresponding glsl-shader's attri-0 (or other index),
//     2. set the attribute-data's stride correctly by calling        getVerticesStride(), 
//        bind the texture seperately (optionally),
//     3. then draw by calling glDrawArray(Tri/Tri_strip/Line/..., 0, getVerticesCount())
//
// For skybox model, gui, and water-tile model:
//     'water-tile' allocated in: LoadTargets_03::initWaterTile()
//
// stride in float: 3 for skybox model, 2 for gui model, 2 for water-tile model
// vertices count:  ? for skybox,                                     ==> glDrawArray(triangle, 0, ?), 
//                  4 for gui,                                        ==> glDrawArray(triangle_strip, 0, 4), 
//                  2 (triangles) * 3 vert/triangle = 6 for watertile ==> glDrawArray(triangle, 0, 6), 
//
// TODO: stride-in-float shall be supported, rather than taking 3 or 2 according to different cases
//       vao to replace vbo ...
//
class SingleAttributeModel {

private:
    unsigned int dataStride = 0;  // Up to the glsl-shader, 2-floats for water-tile model, 
                                  //                        3-floats for skybox's cube model
    int vboID         = -1, 
        verticesCount = -1;

public:
    // Bind the vbo-id, enable glsh-shader's attribute-0 to use the bound vbo-data
    //  (vertices-position data for skybox, gui and water-tile shaders in attri-0), 
    // and set the stride-by-float correctly for the bound data
    // before drawing with glDrawArray()
    int getVboID() {
        return vboID;
    }

    unsigned int getVerticesStride() {
        return dataStride;
    }

    // Optional: bind gl-texture id before drawing

    // Draw by calling glDrawArray(TRI/TRI_STRIP, 0, singleAttrModel->getVerticesCount() )
    int getVerticesCount() {
        return verticesCount;
    }

public:
    void setData(unsigned int input_vertices_stride, int input_vertices_count, int input_vbo) {
        dataStride = input_vertices_stride;
        verticesCount = input_vertices_count;
        vboID = input_vbo;
    }
};

struct Transform {
    enum transform {
        x = 0, y, z, rot_x, rot_y, rot_z, scale, max
    };

    float values[transform::max];

    Transform() {
        for (int i = x; i < max; i++) {
            values[i] = 0.0f;
        }
    }
    Transform(float input_values[][transform::max]) {
        if (!input_values)
            return;

        for (int i = 0; i < transform::max; i++) {
            values[i] = (*input_values)[i];
        }
    }

    // void setValue(unsigned int target_idx, float input_data) {
    //     if (target_idx < transform::max) {
    //         values[target_idx] = input_data;
    //     }
    // }

    // void setValues(unsigned int start_idx, unsigned int num, float *input_data) {
    //     if (start_idx < transform::max) {

    //         for (unsigned int i = 0; (i < num) && (i < transform::max); i++) {
    //             if (input_data) {
    //                 values[start_idx + i] = *input_data; input_data++;
    //             }
    //         }
    //     }
    // }

    // void setValues(float input_data[][transform::max]) {
    //     if (input_data) {
    //         for (int i = 0; i < transform::max; i++) {
    //             values[i] = (*input_values)[i];
    //         }
    //     }
    // }
};

class Entity {
    std::vector<Transform> transforms;  // TODO: shall be public ???

    StaticTexture *texture;
    BaseModel *model;

public:
    enum transform {
        x = 0, y, z, rot_x, rot_y, rot_z, scale, max
    };

    Entity() {
        texture = NULL;
        model = NULL;
        
        // info.clear();
        transforms.clear();
    }

public:
    void setTextureModel(StaticTexture *t, BaseModel *m) {
        // if (!t || !m) {
        //     return;
        // }

        texture = t; 
        model = m;

        // info.clear();
        transforms.clear();
    }

    // void addInfo(EntityInfo &input_info) {
    //     // if (input_info != NULL) {
    //         info.push_back(input_info);
    //     // }
    // }

    void addTransform(Transform &transform) {
        transforms.push_back(transform);
    }

    void deleteTransform(unsigned int i) {
        // transforms.erase(); ???
    }

    void cleanUp() {
        transforms.clear();
    }

    // size_t getInfoSize() {
    //     return info.size();
    // }
    size_t tranformsNum() {
        return transforms.size();
    }

    // const float (*getInfo(unsigned int i))[transform::max] {

    //     size_t size = info.size();
    //     if (size == 0)
    //         return NULL;

    //     if (i >= size) {
    //         i = size - 1;
    //     }

    //     return info[i].getData();
    // }
    const float (*getTransformValues(unsigned int i))[transform::max] {

        size_t size = transforms.size();
        if (size == 0)
            return NULL;

        if (i >= size) {
            i = size - 1;
        }

        // return info[i].getData();
        return &(transforms[i].values);
    }

    StaticTexture *getTexture() {
        return texture;
    }

    BaseModel *getModel() {
        return model;
    }

public:
    void increasePosition(unsigned int i, float dx, float dy, float dz) {
        // (*(info[i].getData()))[x] += dx;
        // (*(info[i].getData()))[y] += dy;
        // (*(info[i].getData()))[z] += dz;

        (transforms[i].values)[x] += dx;
        (transforms[i].values)[y] += dy;
        (transforms[i].values)[z] += dz;
    }

    void increaseRotation(unsigned int i, float dx, float dy, float dz) {
        // (*(info[i].getData()))[rot_x] += dx;
        // (*(info[i].getData()))[rot_y] += dy;
        // (*(info[i].getData()))[rot_z] += dz;

        (transforms[i].values)[rot_x] += dx;
        (transforms[i].values)[rot_y] += dy;
        (transforms[i].values)[rot_z] += dz;
    }

    // void setRotZ(unsigned int i, float rotz) {
    //     // (*(info[i].getData()))[rot_z] = rotz;
    //     (transforms[i].values)[rot_z] = rotz;
    // }

        void setTransformValue(unsigned int transform_idx, unsigned int value_idx, float input_value) {
            if (transform_idx < transforms.size() && value_idx < transform::max) {
                transforms[transform_idx].values[value_idx] = input_value;
            }
        }

        // void increaseTransformValue(unsigned int transform_idx, unsigned int value_idx, float delta) {
        //     if (transform_idx < transforms.size() && value_idx < transform::max) {
        //         transforms[transform_idx].values[value_idx] += delta;
        //     }
        // }

        // void setTransformValues(unsigned int start_idx, unsigned int num, float *input_data) {
        //     if (start_idx < transform::max) {

        //         for (unsigned int i = 0; (i < num) && (i < transform::max); i++) {
        //             if (input_data) {
        //                 values[start_idx + i] = *input_data; input_data++;
        //             }
        //         }
        //     }
        // }

        void setTransformValues(unsigned int transform_idx, float *input_data, unsigned int *input_offset, unsigned int input_offset_num) {

            if (!input_offset || !input_data) {
                return;
            }

            for (unsigned int i = 0; i < input_offset_num && i < transform::max; i++) {
                if (input_offset[i] >= transform::max) {
                    continue;
                }

                if (input_data) {
                    transforms[transform_idx].values[ input_offset[i] ] = input_data[i];
                }
            }
        }
};

class TexturedModel {
    std::vector<Transform> transforms;

    Texture *normalMap = NULL;
    Texture *texture = NULL;
    VaoModel *model = NULL;

public:
    // Texture *normalMap;
    void setTextureModel(Texture *tex, VaoModel *mod) {
        if (tex) {
            texture = tex;
        }
        if (mod) {
            model = mod;
        }
    }

    void setNormalMap(Texture *nm) {
        normalMap = nm;
    }

    Texture *getTexture() {
        return texture;
    }

    VaoModel *getModel() {
        return model;
    }

    Texture *getNormalMap() {
        return normalMap;
    }

public:
    // enum transform {
    //     x = 0, y, z, rot_x, rot_y, rot_z, scale, max
    // };

    void addTransform(Transform &transform) {
        transforms.push_back(transform);
    }

    void deleteTransform(unsigned int i) {
        // transforms.erase(); ???
    }

    size_t tranformsNum() {
        return transforms.size();
    }

    void setTransformValues(unsigned int transform_idx, float *input_data, unsigned int *input_offset, unsigned int input_offset_num) {

        if (!input_offset || !input_data) {
            return;
        }

        for (unsigned int i = 0; i < input_offset_num && i < Transform::max; i++) {
            if (input_offset[i] >= Transform::max) {
                continue;
            }

            if (input_data) {
                transforms[transform_idx].values[ input_offset[i] ] = input_data[i];
            }
        }
    }

    void setTransformValue(unsigned int transform_idx, unsigned int value_idx, float input_value) {
        if (transform_idx < transforms.size() && value_idx < Transform::max) {
            transforms[transform_idx].values[value_idx] = input_value;
        }
    }

    const float (*getTransformValues(unsigned int i))[Transform::max] {

        size_t size = transforms.size();
        if (size == 0)
            return NULL;

        if (i >= size) {
            i = size - 1;
        }

        // return info[i].getData();
        return &(transforms[i].values);
    }

    void increaseRotation(unsigned int i, float dx, float dy, float dz) {
        (transforms[i].values)[Transform::rot_x] += dx;
        (transforms[i].values)[Transform::rot_y] += dy;
        (transforms[i].values)[Transform::rot_z] += dz;
    }

    void cleanUp() {
        transforms.clear();
    }

    // void setRotZ(unsigned int i, float rotz) {
    //     // (*(info[i].getData()))[rot_z] = rotz;
    //     (transforms[i].values)[rot_z] = rotz;
    // }
    // void increaseTransformValue(unsigned int transform_idx, unsigned int value_idx, float delta) {
    //     if (transform_idx < transforms.size() && value_idx < transform::max) {
    //         transforms[transform_idx].values[value_idx] += delta;
    //     }
    // }
    // void setTransformValues(unsigned int start_idx, unsigned int num, float *input_data) {
    //     if (start_idx < transform::max) {

    //         for (unsigned int i = 0; (i < num) && (i < transform::max); i++) {
    //             if (input_data) {
    //                 values[start_idx + i] = *input_data; input_data++;
    //             }
    //         }
    //     }
    // }
};

// class EntityInfo {
// public:
//     enum transform {
//         x = 0, y, z, rot_x, rot_y, rot_z, scale, max
//     };

//     EntityInfo(float input_info[][transform::max]) {
//         if (!input_info)
//             return;

//         for (unsigned int i = transform::x; i < transform::max; i++) {
//             pos_rot_scale[i] = (*input_info)[i];
//         }
//     }

//     float(*getData())[transform::max] {
//         return &pos_rot_scale;
//     }

// private:
//     float pos_rot_scale[transform::max];
// };


// class Entity;  // forward declare doesn't work for enum ???
