#include "Core/Renderers/Model/MultiLightsShader.h"
#include "Core/Renderer.h"

class NormalMappedModelRenderer : public BaseRenderer {
    NormalMappedShader *nmShader = NULL;

public:
    NormalMappedModelRenderer() {
        printf("  __ normal-mapped renderer constructor().\n");
        freeShadersData();
        allocShadersData();
    }
    virtual ~NormalMappedModelRenderer() {
        printf("  __ normal-mapped renderer destructor().\n");
        freeShadersData();
    }

    void allocShadersData() override;
    void freeShadersData() override;
    bool ready() override;

    void run(std::vector<TexturedModel> &normalMappedModels, std::vector<Light> &lights) {
        if (!nmShader) {
            return;
        }

        nmShader->start();
            nmShader->loadViewMatrix( getViewMatrix() );
            nmShader->loadReflectivity(20.0f);
            nmShader->loadShineDamper(20.0f);
            nmShader->loadLights(lights);

            for (TexturedModel ir_textured_model : normalMappedModels) {
                // Setting this to be 0 could make drawing unable to crash the program,
                // when NULL-texture/model pointers are input by mistake.
                unsigned int indices_count = 0;

                Texture *pTexture = ir_textured_model.getTexture();
                Texture *pNMap = ir_textured_model.getNormalMap();
                // printf("nmap: %p\n", pNMap);
                VaoModel *pModel = ir_textured_model.getModel();


                if (pTexture) {
                    // bind a texture buffer object
                    // glActiveTexture(GL_TEXTURE0);
                    // glBindTexture(GL_TEXTURE_2D, pTexture->getID());
                    // glActiveTexture(GL_TEXTURE1);
                    // glBindTexture(GL_TEXTURE_2D, pNMap->getID());

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, pTexture->getID());

                    // glActiveTexture(GL_TEXTURE1);
                    // glBindTexture(GL_TEXTURE_2D, pNMap->getID());
                    // glBindTexture(GL_TEXTURE_2D, pTexture->getID());
                }

                if (pNMap) {
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, pNMap->getID());
                }

                if (pModel) {
                    indices_count = pModel->getVertexCount();
                    glBindVertexArray(pModel->getVaoID());
                    glEnableVertexAttribArray(0);
                    glEnableVertexAttribArray(1);
                    glEnableVertexAttribArray(2);
                    glEnableVertexAttribArray(3);
                }

                // set the uniforms for shaders before every time's draw
                {
                    unsigned int transforms_num = ir_textured_model.tranformsNum();

                    for (unsigned int i = 0; i < transforms_num; i++) {
                        // Proj-Matrix should have been loaded before 
                        // the rendering loop is entered.
                        gl_math::mat4 model_matrix; {
                            gl_math::model_matrix_SRT_Normal(ir_textured_model.getTransformValues(i), &model_matrix);
                        }
                        nmShader->loadTransformMatrix(&model_matrix[0][0]);

                        // Draw the triangles
                        glDrawElements(
                            GL_TRIANGLES, indices_count,  // num of indices
                            GL_UNSIGNED_INT,  // type
                            0                 // element array buffer(indices buffer) offset
                        );
                    }
                }

                if (pModel) {
                    glDisableVertexAttribArray(0);
                    glDisableVertexAttribArray(1);
                    glDisableVertexAttribArray(2);
                    glDisableVertexAttribArray(3);
                    // Models which has been renderer could be ruined without this line
                    // if the other renderers are using vbo without using vao
                    glBindVertexArray(0);
                }
            }
    }
};

class MultiLightsRenderer : public BaseRenderer {
private:
    MultiLightsShader *mlShader = NULL;
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

    // void addLight(Light *light) {
    //     lights.push_back(light);
    // }

public:
    MultiLightsRenderer() {
        printf("  __ ml-renderer constructor()\n");
        freeShadersData();
        allocShadersData();
    }
    ~MultiLightsRenderer() {
        printf("  __ ml-renderer destructor()\n");
        freeShadersData();
    }

    void allocShadersData() override;
    void freeShadersData() override;
    bool ready() override;

    void run(std::vector<TexturedModel> &texturedModels, std::vector<Light> &lights) {
        if (!mlShader) {
            return;
        }

        mlShader->start();
            mlShader->loadViewMatrix( getViewMatrix() );
            mlShader->loadReflectivity(20.0f);
            mlShader->loadShineDamper(20.0f);
            mlShader->loadLights(lights);  // mod

            for (TexturedModel ir_textured_model : texturedModels) {
                // Setting this to be 0 could make drawing unable to crash the program,
                // when NULL-texture/model pointers are input by mistake.
                unsigned int indices_count = 0;

                Texture *pTexture = ir_textured_model.getTexture();
                VaoModel *pModel = ir_textured_model.getModel();

                if (pTexture) {
                    // bind a texture buffer object
                    unsigned int tid = pTexture->getID();
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, tid);
                }

                if (pModel) {
                    indices_count = pModel->getVertexCount();
                    glBindVertexArray(pModel->getVaoID());
                    glEnableVertexAttribArray(0);
                    glEnableVertexAttribArray(1);
                    glEnableVertexAttribArray(2);
                }

                // set the uniforms for shaders before every time's draw
                {
                    unsigned int transforms_num = ir_textured_model.tranformsNum();

                    for (unsigned int i = 0; i < transforms_num; i++) {
                        // Proj-Matrix should have been loaded before 
                        // the rendering loop is entered.
                        gl_math::mat4 model_matrix; {
                            gl_math::model_matrix_SRT_Normal(ir_textured_model.getTransformValues(i), &model_matrix);
                        }
                        mlShader->loadTransformMatrix(&model_matrix[0][0]);

                        // Draw the triangles
                        glDrawElements(
                            GL_TRIANGLES, indices_count,  // num of indices
                            GL_UNSIGNED_INT,  // type
                            0                 // element array buffer(indices buffer) offset
                        );
                    }
                }
            }
            // Models which has been renderer could be ruined without this line
            // if the other renderers are using vbo without using vao
            glBindVertexArray(0);
    }
    
    // to be scraped
    void run(const std::vector<Light *> &lights, float clipPlane[][4]) {

        if (!mlShader) {
            return;
        }

        mlShader->start();
        mlShader->loadViewMatrix( getViewMatrix() );
        
        // mlShader->loadReflectivity(20.0f);
        // mlShader->loadShineDamper(20.0f);
        // mlShader->loadLight(light);        
        //     unsigned int misa_start_idx = 0;
        //     entityRendererWraper(misa_start_idx, misa_entities_num);

        // mlShader->loadReflectivity(10.0f);
        // mlShader->loadShineDamper(10.0f);
        //     unsigned int the_rest_entities_start_idx = misa_entities_num;
        //     entityRendererWraper(the_rest_entities_start_idx, total_entities_num - misa_entities_num);

        mlShader->loadReflectivity(20.0f);
        mlShader->loadShineDamper(20.0f);
        // mlShader->loadLights(lights);

        if (clipPlane) {
            // mlShader->loadClipPlane(&(*clipPlane)[0]);
        }
            render();



        // PROFILE_FUNCTION();
        // prepare();
        // {
        //     PROFILE_SCOPE("entity");
        //     // mlShader->start();
        //     // mlShader->loadViewMatrix( getViewMatrix() );
            
        //     //     mlShader->loadLight(light);
                
        //     //     mlShader->loadReflectivity(20.0f);
        //     //     mlShader->loadShineDamper(20.0f);
        //     //     unsigned int misa_start_idx = 0;
        //     //     entityRendererWraper(misa_start_idx, misa_entities_num);

        //     //     mlShader->loadReflectivity(10.0f);
        //     //     mlShader->loadShineDamper(10.0f);
        //     //     unsigned int the_rest_entities_start_idx = misa_entities_num;
        //     //     entityRendererWraper(the_rest_entities_start_idx, total_entities_num - misa_entities_num);
        // }

        // {
        //     // PROFILE_SCOPE("terrain");
        //     // terrainShader->start();
        //     // terrainShader->loadViewMatrix( getViewMatrix() );

        //     //     terrainShader->loadLight(light);

        //     //     terrainShader->loadReflectivity(20.0f);
        //     //     terrainShader->loadShineDamper(20.0f);
        //     //     terrainRendererWraper();
        // }

        // {
        //     PROFILE_SCOPE("skybox");
        //     // if (sky) {
        //         // skyboxShader->start();
        //         // skyboxShader->loadSkyboxViewMatrix( getViewMatrix() );
        //         //     skyboxRenderer.render(sky);
        //     // }
        // }

        // {
        //     PROFILE_SCOPE("gui overlay");
        //     // guiRenderer.render();
        // }
    }

    void render() {
        for (int i = 0; i < entities.size(); i++) {
            auto entity = entities.begin() + i;
            render((*entity));
        }
    }

    void render(Entity *entity) {

        if (!entity || !mlShader) {
            return;
        }

        // Setting this to be 0 could make drawing unable to crash the program,
        // when NULL-texture/model pointers are input by mistake.
        unsigned int indices_count = 0;

        StaticTexture *static_texture = entity->getTexture();
        BaseModel *static_model = entity->getModel();

        if (static_texture) {
            // bind a texture buffer object
            int texture_id = static_texture->getId();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_id);
        }

        if (static_model) {

            switch (static_model->getModelType()) {    

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
                            for (unsigned int i = 0; i < StaticModel_SingleVbo::valid_attr_num; i++) {
                                
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

                    for (unsigned int i = 0; i < StaticModel::vboNum; i++) {
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
                    mlShader->loadTransformMatrix(&model_matrix[0][0]);
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

    /*
    void render(TexturedModel* texturedModel) {

        if (!entity || !mlShader) {
            return;
        }

        // Setting this to be 0 could make drawing unable to crash the program,
        // when NULL-texture/model pointers are input by mistake.
        unsigned int indices_count = 0;

        StaticTexture* static_texture = entity->getTexture();
        BaseModel* static_model = entity->getModel();

        if (static_texture) {
            // bind a texture buffer object
            int texture_id = static_texture->getId();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_id);
        }

        if (static_model) {

            switch (static_model->getModelType()) {

            case BaseModel::single_vbo:
            {
                indices_count = ((StaticModel_SingleVbo*)static_model)->getNumIndices();

                // TODO: use to C++ static/dynamic cast instead
                int vbo_id = ((StaticModel_SingleVbo*)static_model)->getVboId();
                int ibo_id = ((StaticModel_SingleVbo*)static_model)->getIboId();

                // bind the all-in-one vbo
                {
                    // enable a corresponding-attribute in v-shader (pos, uv, or normal), then
                    // set how to interprete all-in-one vbo data for each attribute's data.
                    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
                    for (unsigned int i = 0; i < StaticModel_SingleVbo::valid_attr_num; i++) {

                        glEnableVertexAttribArray(StaticModel_SingleVbo::valid_attr_idx[i]);

                        glVertexAttribPointer(
                            StaticModel_SingleVbo::valid_attr_idx[i],
                            StaticModel_SingleVbo::valid_attr_stride[i], GL_FLOAT,
                            GL_FALSE,
                            StaticModel_SingleVbo::single_vbo_stride_in_float << 2,   // N-floats * 4 ==> stride in bytes (N = 3, 2, ...)
                            (const void*)StaticModel_SingleVbo::valid_attr_offset[i] // offset is measured in Bytes
                        );
                    }
                }

                // bind the ibo
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
            }
            break;

            case BaseModel::multi_vbos:
            {
                indices_count = ((StaticModel*)static_model)->getNumIndices();

                int vbos_ibo_ids[StaticModel::allBuffNum];
                ((StaticModel*)static_model)->getBuffers(&vbos_ibo_ids);
                // printf("vbo-num: %d, all buffnum: %d", StaticModel::vboNum, StaticModel::allBuffNum);
                // printf("ids: %d, %d, %d  ", vbos_ibo_ids[0], vbos_ibo_ids[1], vbos_ibo_ids[2]);
                // printf("attr-idx: %d, %d ", StaticModel::vbo_atrr_idx[0], StaticModel::vbo_atrr_idx[1]);
                // printf("stride: %d, %d\n", StaticModel::vbo_stride[0], StaticModel::vbo_stride[1]);

            // bind vbo, enable its corresponding-attribute in v-shader (pos, uv, or normal), then
            // set how to interpretate vbo data into the attribute.

                for (unsigned int i = 0; i < StaticModel::vboNum; i++) {
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
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos_ibo_ids[StaticModel::vboNum]);
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
                    {
                        // gl_math::model_matrix_SRT_Normal(entity->getInfo(i), &model_matrix);
                        gl_math::model_matrix_SRT_Normal(entity->getTransformValues(i), &model_matrix);
                    }
                    mlShader->loadTransformMatrix(&model_matrix[0][0]);
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
    // */
};
