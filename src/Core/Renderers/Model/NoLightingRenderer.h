#include "Core/Renderers/Model/NoLightingShader.h"
#include "Core/Renderer.h"

class NoLightingRenderer : public BaseRenderer {
private:
    // SpecularShader *noLightingShader = NULL;
    NoLightingShader *noLightingShader = NULL;
    std::vector<Entity *> entities;

public:
    void addEntity(Entity *input_entity) {
        if (input_entity) {
            entities.push_back(input_entity);
        }
    }

    unsigned int getEntitiesSize() {
        return entities.size();
    }

    void clearEntities() {
        entities.clear();
    }

    std::vector<Entity *> &getEntities() {
        return entities;
    }

public:
    NoLightingRenderer() {
        printf("  __ no-lighting-renderer constructor().\n");
        freeShadersData();
        allocShadersData();
    }
    ~NoLightingRenderer() {
        printf("  __ ~no-lighting-renderer destructor()).\n");
        freeShadersData();
    }

    void allocShadersData() override;
    void freeShadersData() override;
    bool ready() override;
    
    void run(std::vector<TexturedModel>& models) {
        if (!noLightingShader) {
            return;
        }

        noLightingShader->start(); {
            noLightingShader->loadViewMatrix(getViewMatrix());

            for (TexturedModel ir_model : models) {
                // Setting this to be 0 could make drawing unable to crash the program,
                // when NULL-texture/model pointers are input by mistake.
                unsigned int indices_count = 0;

                Texture* tmp_texture = ir_model.getTexture();
                VaoModel* tmp_vao_model = ir_model.getModel();

                // Before each draw-call, the texture-object (the color-buffer created) shall be 
                // set (with it's texture-id) to bound to a 'texture-unit', 
                // for the 'sampler2D' in the frag-shader to fetch color from the same unit 
                // (according to the uv for each vertex).
                //
                // Seems the sampler samples unit-0 by default, if there's multi-textures to sample from,
                // then the samplers has to be set (with it's uniform-locations for the shader) 
                // to sample-from/bound-to correspondent 'texture-units' 
                // when the shader's created.
                if (tmp_texture) {

                    // Seems the frag-shader's sampler fetches from texture-unit-0 by default, so
                    // bind the texture buffer-object (mem-buffer for pixel-colors) to 
                    // unit-0 for the frag-shader's sampler to sample from.
                    //
                    // Could also explicitly set the sampler to fetch from unit-0
                    // with gluniform1i(loc_sampler2D, 0) call,
                    // when creating this shader.
                    //
                    // In terrain shader, with multi textures to sample from, sampler2Ds are indeed
                    // bound to corresondent texture units for sampling
                    // when the shader's created.

                    // Bind this texture-buffer to unit-0, since the shader's 
                    // sampler samples from unit-0 
                    // (default setting, also set explicitly when shader created).
                    unsigned int tid = tmp_texture->getID();
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, tid);
                }

                if (tmp_vao_model) {

                    indices_count = tmp_vao_model->getVertexCount();
                    glBindVertexArray(tmp_vao_model->getVaoID());
                    glEnableVertexAttribArray(0);
                    glEnableVertexAttribArray(1);
                    // glEnableVertexAttribArray(2);

                    {
                        for (unsigned int i = 0; i < ir_model.tranformsNum(); i++) {

                            gl_math::mat4 model_matrix;
                            // if (str_rot) {
                            //     // gl_math::model_matrix_STR_Rot(entity->getInfo(i), &model_matrix);
                            //     gl_math::model_matrix_STR_Rot(entity->getTransformValues(i), &model_matrix);
                            // }
                            // else 
                            {
                                // gl_math::model_matrix_SRT_Normal(entity->getInfo(i), &model_matrix);
                                gl_math::model_matrix_SRT_Normal(ir_model.getTransformValues(i), &model_matrix);
                            }

                            // gl_math::mat4 mvp = gl_math::mat4_multiply(projection_matrix, view_matrix, model_matrix);
                            // shader->loadTransformMatrix(&mvp[0][0]);

                            // Proj-Matrix should have been loaded before 
                            // the rendering loop is entered.
                            noLightingShader->loadTransformMatrix(&model_matrix[0][0]);
                            glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
                        }
                    }
                }
            }
            // Models which has been renderer could be ruined without this line
            // if the other renderers are using vbo without using vao
            glBindVertexArray(0);
        }
    }

    void run() {

        if (!noLightingShader) {
            return;
        }

        noLightingShader->start();
        noLightingShader->loadViewMatrix( getViewMatrix() );
        
        // noLightingShader->loadReflectivity(20.0f);
        // noLightingShader->loadShineDamper(20.0f);
        // noLightingShader->loadLight(light);        
        //     unsigned int misa_start_idx = 0;
        //     entityRendererWraper(misa_start_idx, misa_entities_num);

        // noLightingShader->loadReflectivity(10.0f);
        // noLightingShader->loadShineDamper(10.0f);
        //     unsigned int the_rest_entities_start_idx = misa_entities_num;
        //     entityRendererWraper(the_rest_entities_start_idx, total_entities_num - misa_entities_num);

        // noLightingShader->loadReflectivity(20.0f);
        // noLightingShader->loadShineDamper(20.0f);
        // noLightingShader->loadLight(light);
            render();
    }

    void render() {
        for (int i = 0; i < entities.size(); i++) {
            auto entity = entities.begin() + i;
            render((*entity));
        }
    }

    void render(Entity *entity) {

        if (!entity || !noLightingShader) {
            return;
        }

        // Setting this to be 0 could make drawing unable to crash the program,
        // when NULL-texture/model pointers are input by mistake.
        unsigned int indices_count = 0;

        StaticTexture *static_texture = entity->getTexture();
        BaseModel *static_model = entity->getModel();

        // Before each draw-call, the texture-object (the color-buffer created) shall be 
        // set (with it's texture-id) to bound to a 'texture-unit', 
        // for the 'sampler2D' in the frag-shader to fetch color from the same unit 
        // (according to the uv for each vertex).
        //
        // Seems the sampler samples unit-0 by default, if there's multi-textures to sample from,
        // then the samplers has to be set (with it's uniform-locations for the shader) 
        // to sample-from/bound-to correspondent 'texture-units' 
        // when the shader's created.
        if (static_texture) {

            // Seems the frag-shader's sampler fetches from texture-unit-0 by default, so
            // bind the texture buffer-object (mem-buffer for pixel-colors) to 
            // unit-0 for the frag-shader's sampler to sample from.
            //
            // Could also explicitly set the sampler to fetch from unit-0
            // with gluniform1i(loc_sampler2D, 0) call,
            // when creating this shader.
            //
            // In terrain shader, with multi textures to sample from, sampler2Ds are indeed
            // bound to corresondent texture units for sampling
            // when the shader's created.

            // Bind this texture-buffer to unit-0, since the shader's 
            // sampler samples from unit-0 
            // (default setting, also set explicitly when shader created).
            int texture_id = static_texture->getId();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_id);
        }

        if (static_model) {

            switch (static_model->getModelType()) {    

                // The 2 square pictures displaying road are single_vbo model
                case BaseModel::single_vbo:
                {
                    indices_count = ((StaticModel_SingleVbo *)static_model)->getNumIndices();

                    // TODO: use to C++ static/dynamic cast instead
                    int vbo_id = ((StaticModel_SingleVbo*)static_model)->getVboId();
                    int ibo_id = ((StaticModel_SingleVbo*)static_model)->getIboId();

                    // bind the all-in-one vbo
                    {
                        // enable a corresponding-attribute in v-shader (pos, uv, or normal), then
                        // set how to interprete all-in-one vbo data for each attribute's data.
                            glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

                            // The NoLightingShader doesn't do anything about normal-attribute data,
                            // so it could be ignored.
                            for (unsigned int i = 0; i < StaticModel_SingleVbo::valid_attr_num - 1; i++) {
                                
                                glEnableVertexAttribArray(StaticModel_SingleVbo::valid_attr_idx[i]);

                                glVertexAttribPointer(
                                    StaticModel_SingleVbo::valid_attr_idx[i],
                                    StaticModel_SingleVbo::valid_attr_stride[i], GL_FLOAT,
                                    GL_FALSE,
                                    StaticModel_SingleVbo::single_vbo_stride_in_float << 2,   // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
                                    (const void *)StaticModel_SingleVbo::valid_attr_offset[i] // offset is measured in Bytes
                                );
                            }

                            // printf("\n\n\n\n");
                            // printf(" single vbo info, valid_attr_num: %d\n", StaticModel_SingleVbo::valid_attr_num);
                            // printf(" indices count: %d\n", indices_count);
                            // printf("   idx: %d, %d, %d\n", \
                            //     StaticModel_SingleVbo::valid_attr_idx[0],
                            //     StaticModel_SingleVbo::valid_attr_idx[1],
                            //     StaticModel_SingleVbo::valid_attr_idx[2]
                            // );

                            // printf(" strides: %d, %d, %d\n", \
                            //     StaticModel_SingleVbo::valid_attr_stride[0],
                            //     StaticModel_SingleVbo::valid_attr_stride[1],
                            //     StaticModel_SingleVbo::valid_attr_stride[2]
                            // );

                            // printf(" total stride: %d\n", \
                            //     StaticModel_SingleVbo::single_vbo_stride_in_float
                            // );

                            // printf(" offsets: %d, %d, %d\n", \
                            //     StaticModel_SingleVbo::valid_attr_offset[0],
                            //     StaticModel_SingleVbo::valid_attr_offset[1],
                            //     StaticModel_SingleVbo::valid_attr_offset[2]
                            // );
                            // printf("\n\n\n\n");
                    }

                    // bind the ibo
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
                }
                break;

                // The many pictures with transparency is multi_vbo model
                case BaseModel::multi_vbos:
                {
                    indices_count = ((StaticModel *)static_model)->getNumIndices();

                    int vbos_ibo_ids[StaticModel::allBuffNum];
                    ((StaticModel *)static_model)->getBuffers(&vbos_ibo_ids);
                        // printf("vbo-num: %d, all buffnum: %d", StaticModel::vboNum, StaticModel::allBuffNum);
                        // printf("ids: %d, %d, %d  ", vbos_ibo_ids[0], vbos_ibo_ids[1], vbos_ibo_ids[2]);
                        // printf("attr-idx: %d, %d ", StaticModel::vbo_atrr_idx[0], StaticModel::vbo_atrr_idx[1]);
                        // printf("stride: %d, %d\n", StaticModel::vbo_stride[0], StaticModel::vbo_stride[1]);

                    // bind vbo, enable its corresponding-attribute in v-shader (pos, uv, or normal), then
                    // set how to interpretate vbo data into the attribute.

                    // The NoLightingShader doesn't do anything about normal-attribute data,
                    // so it could be ignored.
                    for (unsigned int i = 0; i < StaticModel::vboNum - 1; i++) {
                    // for (unsigned int i = 0; i < 3 - 3; i++) {
                        glBindBuffer(GL_ARRAY_BUFFER, vbos_ibo_ids[i]);
                        
                        glEnableVertexAttribArray(StaticModel::vbo_atrr_idx[i]);
                        
                        glVertexAttribPointer(
                            StaticModel::vbo_atrr_idx[i], 
                            StaticModel::vbo_stride[i], GL_FLOAT, 
                            GL_FALSE, 
                            StaticModel::vbo_stride[i] << 2,  // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
                            0);
                    }

                    // bind the ibo
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos_ibo_ids[StaticModel::vboNum] );
                }
                break;

                default:
                break;
            }
        }

        // set the uniforms for shaders before every time's draw
        {
            // unsigned int num_entities = entity->getInfoSize();
            unsigned int transforms_num = entity->tranformsNum();

            for (unsigned int i = 0; i < transforms_num; i++) {
                
                {
                    gl_math::mat4 model_matrix;
                    // if (str_rot) {
                    //     // gl_math::model_matrix_STR_Rot(entity->getInfo(i), &model_matrix);
                    //     gl_math::model_matrix_STR_Rot(entity->getTransformValues(i), &model_matrix);
                    // }
                    // else 
                    {
                        // gl_math::model_matrix_SRT_Normal(entity->getInfo(i), &model_matrix);
                        gl_math::model_matrix_SRT_Normal(entity->getTransformValues(i), &model_matrix);
                    }

                    // gl_math::mat4 mvp = gl_math::mat4_multiply(projection_matrix, view_matrix, model_matrix);
                    // shader->loadTransformMatrix(&mvp[0][0]);

                    // Proj-Matrix should have been loaded before 
                    // the rendering loop is entered.
                    noLightingShader->loadTransformMatrix(&model_matrix[0][0]);
                }

                // Draw the triangles
                // printf("draw: %d\n\n", indices_count);
                glDrawElements(
                    GL_TRIANGLES,      // mode
                    indices_count,     // num of indices
                    GL_UNSIGNED_SHORT, // type
                    0                  // element array buffer(indices buffer) offset
                );
            }
        }
    }
};