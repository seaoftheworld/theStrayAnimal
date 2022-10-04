// To use OpenGL, Libs depended on are: 
// 1. glfw (included in WindowSystem.h)
// 2. gl3w (included in Renderer.h)
// 3. gl_math

#define __USE_INLINE_METHODS__
#include "WindowSystem/WindowSystem.h"

#include "loopWrappingRenderer.h"
#include "LoopModels.h"

#include <iostream>
#include <stdio.h>

int loop_test_with_basic_entity_renderer() {

    printf("  __ loop_test_with_basic_entity_renderer __ \n");

    WindowSystem &win = WindowSystem::instance();
    if (win.start() < 0) {
        win.stop();
        return -3;
    }

    std::cout << "  OpenGL Window/Context created (on MsWin), Init GL3W for modern OpenGL" << std::endl;
    if (!BaseRenderer::init()) {
        std::cout << "  Renderer::init()/gl3wInit() failed !" << std::endl;
        win.stop();
        return -2;
    }

    // -----------------------------
    loopWrappingRenderer wrappingRenderer;
    PostProcessing postProcessing;
    if (!wrappingRenderer.nolightingRenderer.ready() || 
        !wrappingRenderer.nmRenderer.ready() ||
        !wrappingRenderer.guiRenderer.ready() ||
        !postProcessing.shaderOK()) {
        // !wrappingRenderer.mlRenderer.ready() ||
        // loading/compiling/linking shader-program failed
        win.stop();
        return -1;
    }
    wrappingRenderer.specificSettingsOn();

    LoopModels models; {
        // wrappingRenderer.entityRenderer.addEntity(models.getSingleVboEntity());
        // wrappingRenderer.entityRenderer.addEntity(models.getMultiVboEntity());

        /*
        for (auto misa_entity = models.getMisa()->entities.begin(); misa_entity != models.getMisa()->entities.end(); misa_entity++) {
            wrappingRenderer.mlRenderer.addEntity(&(*misa_entity));
        }
        */
    }

    // Light test_light; {
    //     // float position[Light::Position::max_pos] = {0.0f, 1.0f, 2.0f};
    //     // float position[Light::Position::max_pos] = {20.0f, 0.0f, 20.0f};
    //     float position[Light::Position::max_pos] = { 20.0f, 20.0f, 20.0f };
    //     // float color[Light::Color::max_color] = {1.6f, 1.2f, 1.6f};
    //     float color[Light::Color::max_color] = { 1.6f, 1.6f, 1.6f };
    //     float dummy_attenuation[Light::Attenuation::max_att] = { 0.0f, 0.0f, 0.0f };
    //     test_light.setValues(&position, &color, &dummy_attenuation);
    // }

    Camera cam(gl_math::vec3(-10.0f, 0.0f, 0.0f), (3.14 / 2), 0.0f);
    // Camera cam(gl_math::vec3(-1.6f, 0.0f, 0.0f), (3.14 / 2), 0.0f);

    // cam  position: -10.000000, 0.000000, 0.000000
    // cam direction: 1.000000, 0.000000, 0.000000
    // cam        up: -0.000000, 0.000000, 1.0

    // double prevFrameTime = 0;
    double now = 0, 
           last_wake_up_time = 0, 
           last_update_time = 0, 
           last_render_time = 0,
           last_1s_time = 0;

    unsigned int rendered_times = 0,  // cleared every 1-sec
                 updated_times = 0,   // recording how many times sleep/wakeup/update/render
                 wakeup_times = 0,    // codes are executed in 1-sec
                 sleep_times = 0;
    unsigned int fps = 0;

    // float  update_cycle = (1.0f / (60)),
    //        render_cycle = (1.0f / (120)),
    //        min_cycle = (update_cycle < render_cycle) ? (update_cycle) : (render_cycle);
    float  update_cycle = (1.0f / (60)),
           render_cycle = (1.0f / (60)),
           min_cycle = (update_cycle < render_cycle) ? (update_cycle) : (render_cycle);

    while ( win.isValid() ) {

        static bool first = true;
        if (first) {
            win.setCursorPos(WIN_WIDTH / 2, WIN_HEIGHT / 2);
            now = win.getTime();
            
            last_wake_up_time = now; // assigned value after min_cycle-time has passed
            last_update_time = now;  // assigned value after update-codes executed
            last_render_time = now;  // assigned value after render-codes executed
            last_1s_time = now;
            
            first = false;
        }
        else {
            now = win.getTime();
        }

        // Print info to debug and reset debug infos every 1-second
        static bool stop = false;
        if (now - last_1s_time > 1.0f) {
            {
                printf("  __ 1s: sleep/wakeup: %d--%d, update/render: %d--%d \n\n", 
                    sleep_times, wakeup_times, updated_times, rendered_times);
                // if (updated_times < update_freq) {
                // }
                // if (rendered_times < render_freq) {
                // }

                rendered_times = 0;
                updated_times = 0;
                wakeup_times = 0;
                sleep_times = 0;

                last_1s_time = now;
            }

            {
                // unsigned short et_idx = 0;
                // float rot_z_step = 0.785f;

                // static bool increase = false;
                
                // for (auto itr = assimp_misa.entities.begin(); itr != assimp_misa.entities.end(); itr++) {
                //     float delta_rot_z = ( increase ) ? (rot_z_step) : (-rot_z_step);
                //     (*itr).increaseRotation(et_idx, 0.0f, 0.0f, delta_rot_z);
                // }

                // if ((*assimp_misa.entities[0].getInfo(et_idx))[Transform::rot_z] > 3.14f) {
                //     printf("rot_z max: %f\n", (*assimp_misa.entities[0].getInfo(et_idx))[Transform::rot_z]);
                //     increase = false;
                // }
                // else if ((*assimp_misa.entities[0].getInfo(et_idx))[Transform::rot_z] < -3.14f) {
                //     printf("rot_z min: %f\n", (*assimp_misa.entities[0].getInfo(et_idx))[Transform::rot_z]);
                //     increase = true;
                // }
            }

            {
                printf("  __ 1s: %d fps\n", fps);
                fps = 0;
            }

            if (stop) {
                static unsigned char i = 0;
                i++;
                // if (i > 2) {
                if (i > 0) {
                    stop = false;
                    i = 0;
                }
            }
        }

        // When less than the amount of 'min_cycle' time has passed since the last valid loop,
        // sleep for 'min_cycle' time before the next loop for power-consumption.
        //
        // When one cycle is set to be smaller than the other, say, 
        // rendering-cycle is set to be 1/120 sec, while 
        //    update-cycle is set to be 1/70 sec,
        // the codes/algrithm below will make the longer cycle (update-cycle) 
        // not exactly the same as it is set:
        //     update/render-times is 60/120 in this case on T14sGen1 PC
        //     (although it's set to be 70/120).
        //
        if (now - last_wake_up_time < min_cycle) {
            // sleep for 'min_cycle' time using the OS's api
            sleep_times++;
            continue;
        }
        else {
            wakeup_times++;
            last_wake_up_time = now;
        }

        // Update data (view-mat) according to input, update entity pos, rot, scale...
        if ( now - last_update_time >= update_cycle ) {
        // {
            win.pollEvents();  // not respond when close win with mouse without this

            // Update the cam automatically as programmed, 
            // or according to input
            {
                // static gl_math::vec3 cam_pos(-(CAM_MODEL_INIT_DIST), 2.0f, 0.0f);
                // cam_pos.x += (now - last_update_time) * 3.5f;
                // if (cam_pos.x >= MODEL_MODEL_DIST - CAM_MODEL_INIT_DIST) {
                //     cam_pos.x = -(CAM_MODEL_INIT_DIST);
                //     // printf("Cam_pos resumed.\n");
                // }
                // gl_math::vec3 cam_dir(1.0, 0.0, 0.0);
                // gl_math::vec3 cam_up(0.0, 0.0, 1.0);

                // BaseRenderer::calculateViewMatrix(cam_pos, cam_dir, cam_up);

                cam.input_update(win);
                BaseRenderer::calculateViewMatrix(cam.getPosition(), cam.getDirection(), cam.getUp());
            }

            /*
            // Misa spins
            {
                unsigned short transform_idx = 0;
                float rot_z_step = 0.048f;

                static bool facing_left = true;
                static bool turn_back = false;

                if (!stop) {
                    float delta_rot_z = ( facing_left ) ? (rot_z_step) : (-rot_z_step);
                    delta_rot_z = (turn_back) ? (-delta_rot_z) : (delta_rot_z);
                    
                    for (auto itr = models.getMisa()->entities.begin(); itr != models.getMisa()->entities.end(); itr++) {
                        itr->increaseRotation(transform_idx, 0.0f, 0.0f, delta_rot_z);
                    }

                    Entity *misaEntity = &models.getMisa()->entities[0];
                    float misa_angle = (*(misaEntity->getTransformValues(transform_idx)))[Transform::rot_z];

                    if (!turn_back) {
                        if (facing_left && misa_angle > 3.14f + 3.14f / 4.0f) {
                            printf("rot_z max: %f\n", misa_angle);
                            turn_back = true;
                            // stop = true;
                        }
                        else if (!facing_left && misa_angle < -3.14f - 3.14f / 4.0f) {
                            printf("rot_z min: %f\n", misa_angle);
                            turn_back = true;
                            // stop = true;
                        }
                    }
                    else {
                        if (misa_angle > -rot_z_step && misa_angle < rot_z_step) {
                            turn_back = false;
                            facing_left = (!facing_left);
                            stop = true;
                        }
                    }
                }
            }
            //*/

            last_update_time = now;
            updated_times++;
        }

        // Render entities
        if ( now - last_render_time >= render_cycle ) {
        // {
            // wrappingRenderer.process(test_light);
            // wrappingRenderer.process();

            // for (auto ir_texed_model : models.getMisa()->texturedModels) {
                // texturedModelRenderer(ir_texed_model);
            // }

            // Render the fruits into a fbo (outputFbo) after anti-aliasing, color-buffer 
            // of this fbo will also be used for post-processing and blur effect
            {
                models.getMultiSampledFBO().bind();
                wrappingRenderer.processNoLighting(models.getFruits()->texturedModels);

                // blit from the current multiSampledFbo to the 2nd fbo, then unbind every fbo
                models.getMultiSampledFBO().resoveToFbo(models.getOutputFBO());
                WaterTileFBO::unbind();
            }

            // Render the fruits into a fbo (outputFbo) without anti-aliasing, color-buffer of this fbo 
            // will also be used for post-processing and blur effect
            {
                // models.getOutputFBO().bind();
                // wrappingRenderer.processNoLighting(models.getFruits()->texturedModels);
                // WaterTileFBO::unbind();
            }

            // Render rb73, barrel models with normal-renderer to the background/default fb, 
            // and render the gui's rect (rect on the left), 
            // the gui's texture is set to be from 'outputFbo' for fruits when init models.
            wrappingRenderer.process(\
                models.getTheRestModels()->normalMappedModels,\
                models.getGuis());

            // Render the Post-processing's rect (rect on the right)
            postProcessing.run(\
                models.getPostProcessingRectID(), models.getOutputFBO().getTexture(), \
                models.getBrightnessFBO(),
                models.getBlurFBO1_h(), models.getBlurFBO1_v(), 
                models.getBlurFBO2_h(), models.getBlurFBO2_v(),
                models.getBlurFBO3_h(), models.getBlurFBO3_v());

            win.swapBuffers();
            last_render_time = now;
            rendered_times++;
            fps++;
        }

        // win.swapBuffers();
        // fps++;
    }

    win.stop();
    return 0;
}
