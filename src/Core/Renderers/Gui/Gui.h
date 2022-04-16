#include "Core/Common/data.h"

// typedef float(*pA2f)[2];
// typedef pA2f fpA2f();

#define GUI_RECT_VERTICES_STRIDE (2)
#define GUI_RECT_VERTICES_NUM    (4)

class GuiType00 {
private:
    unsigned int textureID;
    float position[2];
    float scale[2];

public:
    // The model for a gui (and all guis)
    static SingleAttributeModel *rect;

public:
    void init(unsigned int input_tex_id, float input_pos[][2], float input_scale[][2]) {
        textureID = input_tex_id;

        if (input_pos) {
            position[0] = (*input_pos)[0];
            position[1] = (*input_pos)[1];
        }

        if (input_scale) {
            scale[0] = (*input_scale)[0];
            scale[1] = (*input_scale)[1];
        }
    }
    unsigned int getTextureID() {
        return textureID;
    }

    float (*getPosition())[2] {
        return &position;
    }
    float (*getScale())[2] {
        return &scale;
    }

    // pA2f sadf() {
    //     return &scale;
    // }
};

// These are supposed tobe used by the PictureRenderer(alloc vbo-buffer for uv) 
// or the user (alloc vbo-buffers for vert-positions)
// to call the loader with correct parameters
#define PICTURE_RENDERER_POS_VBO_VERTICES_STRIDE (2)
#define PICTURE_RENDERER_POS_VBO_VERTICES_NUM    (6)
#define PICTURE_RENDERER_UV_VBO_VERTICES_STRIDE  (2)
#define PICTURE_RENDERER_UV_VBO_VERTICES_NUM     (6)
#define PICTURE_RENDERER_DRAW_VERTICES_NUM    (6)

// This class is supposed tobe used as an interface 
// between PictureRenderer and this renderer's app
struct Picture {

    unsigned int width = 0, height = 0;

    int translate_x = 0, 
        translate_y = 0;
    float rot_z = 0;

    unsigned int vboId = 0, 
                 textureId = 0;
};
