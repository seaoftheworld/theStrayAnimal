// To use OpenGL, Libs depended on are: 
// 1. glfw (included in WindowSystem.h)
// 2. gl3w (included in Renderer.h)
// 3. gl_math

#define SET_FPS_LIMIT (1)
// #if SET_FPS_LIMIT
// #else
// #endif

#define __USE_INLINE_METHODS__
#include "WindowSystem/WindowSystem.h"

#include "WrappingRenderer_04.h"
#include "LoadTargets_04.h"

// #define PROFILING (0)
// #include "Core/profile.h"
int test_04() {

    printf("  __ 04 test04 __\n");

    WindowSystem &win = WindowSystem::instance();
    if (win.start() < 0) {
        win.stop();
        return -3;
    }

    if (!BaseRenderer::init()) {
        std::cout << "  BaseRenderer::init()/gl3wInit() failed !" << std::endl;
        win.stop();
        return -2;
    }

    // ---------------------------------
    WrappingRenderer_04 renderers; {
        if (!renderers.mlRenderer.ready() ||
            !renderers.skyboxRenderer.ready() ||
            !renderers.guiRenderer.ready() ||
            !renderers.waterRenderer.ready()) {
            win.stop();
            return -1;
        }

        printf("all shaders init done, input any number to continue ...\n\n"); {
            // int dbg;
            // scanf("%d", &dbg);
        }
    }
    renderers.specificSettingsOn();

    // Instrumentor::Get().BeginSession("init part profiling");
    // Instrumentor::Get().EndSession();
    LoadTargets_04 targets; {
        renderers.skyboxRenderer.setSkybox(targets.getSkybox());

        // renderers.guiRenderer.addGui(&(targets.getGui()[0]));
        // renderers.guiRenderer.addGui(&(targets.getGui()[1]));
        // renderers.guiRenderer.addGui(&(targets.getGui()[2]));
        // renderers.guiRenderer.addGui(&(targets.getGui()[3]));

        // WaterTile *waterTiles = targets.getWaterTiles();
        // renderers.waterRenderer.addWaterTile(&waterTiles[0]);
        // renderers.waterRenderer.addWaterTile(&waterTiles[1]);
        // renderers.waterRenderer.addWaterTile(&waterTiles[2]);
        // renderers.waterRenderer.addWaterTile(&waterTiles[3]);
    }

    // Light light; {
    //     // float position[Light::Position::max_pos] = {0.0f, 1.0f, 2.0f};
    //     float position[Light::Position::max_pos] = {5.0f, 5.0f, 10.0f};

    //     // float color[Light::Color::max_color] = {1.6f, 1.2f, 1.6f};
    //     float color[Light::Color::max_color] = { 1.6f, 1.6f, 1.6f };
    //     float dummy_attenuation[Light::Attenuation::max_att] = {0.0f, 0.0f, 0.0f};
    //     light.setValues(&position, &color, &dummy_attenuation);
    // }
    std::vector<Light> lights; {
        {
            Light test_light; {
                // float position[Light::Position::max_pos] = {0.0f, 1.0f, 2.0f};
                // float position[Light::Position::max_pos] = {2.0f, 2.0f, 2.0f};
                // float position[Light::Position::max_pos] = {20.0f, 20.0f, 8.0f};
                float position[Light::Position::max_pos] = {20.0f, 0.0f, 8.0f};

                // float color[Light::Color::max_color] = {1.6f, 1.2f, 1.6f};
                // float color[Light::Color::max_color] = { 1.6f, 1.6f, 1.6f };
                float color[Light::Color::max_color] = { 1.0f, 1.0f, 1.0f };

                // float dummy_attenuation[Light::Attenuation::max_att] = {1.0f, 0.3f, 0.4f};
                // test_light.setValues(&position, &color, &dummy_attenuation);

                // float attenuation[Light::Attenuation::max_att] = { 1.0f, 0.3f, 0.4f };
                float attenuation[Light::Attenuation::max_att] = { 1.0f, 0.02f, 0.0f };
                test_light.setValues(&position, &color, &attenuation); 
            }
            // renderers.addLights(&test_light);
            lights.push_back(test_light);
        }

        {
            const unsigned int  NUM_LIGHTS = 4;
            Light arrayLights[NUM_LIGHTS]; {

                float light_color[NUM_LIGHTS][Light::Color::max_color] = {
                    { 1.8f, 1.0f, 1.8f },  // pink
                        // float color[Light::max_color] = { 2.0f, 0.0f, 0.0f };         // red
                        // float light_color0[Light::max_color] = { 0.0f, 2.0f, 0.0f };  // green
                        // float light_pos0[Light::max_pos] = {0.0f, 1.0f, 2.0f};
                        // float light_color0[Light::max_color] = { 0.0f, 0.0f, 0.0f };  // none
                    { 1.8f, 1.8f, 1.0f },  // red + green ==> yellow
                    { 1.0f, 2.6f, 1.0f },  // green
                    { 0.6f, 0.6f, 2.2f }   // blue
                };

                float lightInitPosition[NUM_LIGHTS][Light::Position::max_pos] = {
                    { 0.0f,  2.0f, 1.8f},
                    {-2.0f,  0.0f, 1.8f},
                    { 0.0f, -2.0f, 1.8f},
                    { 2.0f,  0.0f, 1.8f} 
                };

                float default_att[Light::max_att] = { 1.0f, 0.3f, 0.4f };
                // float default_att[Light::max_att] = { 1.0f, 0.3f, 0.2f };

                for (unsigned int i = 0; i < NUM_LIGHTS; i++) {
                    arrayLights[i].setValues(&lightInitPosition[i], &light_color[i], &default_att);
                }
            }
            for (int i = 0; i < NUM_LIGHTS; i++) {
                // renderers.addLights(&lights[i]);
                lights.push_back(arrayLights[i]);
            }
        }
    }

    // Camera cam(gl_math::vec3(-1.36f, 3.15f, 4.25f), 2.65f, -0.765f);
    Camera cam(gl_math::vec3(-0.9448f, 6.760f, 5.463f), 2.23f, -0.69f);

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

#if SET_FPS_LIMIT
    double update_cycle = (float)(1.0f / (55)),
           render_cycle = (float)(1.0f / (55)),
           min_cycle = (update_cycle < render_cycle) ? (update_cycle) : (render_cycle);
#else
#endif

    Instrumentor::Get().BeginSession("main loop profiling");
    while ( win.isValid() ) {

        PROFILE_SCOPE("main loop");
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
            // // elapasedTime = elapasedTime + prevFrameTime;  // += crashes
            // prevFrameTime = now - last_wake_up_time;
            now = win.getTime();
        }

        // 1-second-update: Print dbg info
        if (now - last_1s_time > 1.0f) {
            {
                // printf("  __ 1s: sleep/wakeup: %d--%d, update/render: %d--%d \n\n", 
                //     sleep_times, wakeup_times, updated_times, rendered_times);

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

            printf("  __ 1s: %d fps\n", fps);
            fps = 0;
        }

        // When less than the amount of 'min_cycle' time has passed since the last valid loop,
        // sleep for 'min_cycle' time before the next loop to reduce power-consumption.
        //
    #if SET_FPS_LIMIT
        if (now - last_wake_up_time < min_cycle) {
            // sleep for 'min_cycle' time using the OS's api
            sleep_times++;
            continue;
        }
        else {
            wakeup_times++;
            last_wake_up_time = now;
        }
    #else
    #endif

        // Updating rountine
        // update view-matrix according to input, 
        // update model's pos, rot, scale ...
    #if SET_FPS_LIMIT
        if ( now - last_update_time >= update_cycle ) {
    #else
        {
    #endif
            PROFILE_SCOPE("Update inputs, view...");
            
            win.pollEvents();  // No-Respond if close win with mouse without this
            cam.input_update(win);
            BaseRenderer::calculateViewMatrix(cam.getPosition(), cam.getDirection(), cam.getUp());

            // Update the 4 lights according to positions of the 4 crates
            /*
            {
                // The 1st and the only entity in 'assimp_crate' is the crate model with 4 transforms
                Entity *crate = &(targets.getCrate()->entities[0]);

                // 1. update crate's 4 transforms
                if (!stop) {
                    // MultiLighsData::MoveType move_type_before = lightsPositionData.getMoveType();
                    lightsPositionsUpdate.run();

                    unsigned int offsets[] = {
                        Transform::x, Transform::y,
                        Transform::z, Transform::rot_z
                    };

                    XYZRotz xyz_rotz;

                    // Update each transform for the crate entiry
                    for (unsigned int i = 0; i < NUM_LIGHTS; i++) {

                        lightsPositionsUpdate.getPosRotz(i, &xyz_rotz);

                        // Revize the xyz info according to rot-z, the xyz from UpdatePosRotz
                        // is not rotated, rotation info is only in rotz value
                        gl_math::get_xyz_from_rotz(&xyz_rotz.pos, xyz_rotz.rot, &xyz_rotz.pos);
                            xyz_rotz.pos[Light::Position::x] += LoadTargets_03::misa_offset_x;
                            xyz_rotz.pos[Light::Position::y] += LoadTargets_03::misa_offset_y;

                        crate->setTransformValues(i, xyz_rotz.pos, offsets, ARRAY_SIZE(offsets));
                    }
                }

                // 2. update 4 lights' positions according to crate's 4 transforms
                {
                    float updated_light_pos[NUM_LIGHTS][Light::Position::max_pos];
                    for (unsigned int i = 0; i < NUM_LIGHTS; i++) {
                        for (unsigned int j = 0; j < 3; j++) {
                            updated_light_pos[i][j] = (*(crate->getTransformValues(i)))[Transform::x + j];
                        }
                    }
                    
                    for (unsigned int i = 0; i < NUM_LIGHTS; i++) {
                        lights[i].setPosition(&updated_light_pos[i]);
                    }
                }

                // 3. write the 4 lights' pos, color, and attenuation into variables to be used
                //    by the multi-lights shader
                // TODO: use something like 'addLight()' dynamically 
                // instead of manually adding lights every time before rendering. {}
            }
            //*/

            last_update_time = now;
            updated_times++;
        }

        // Render targets
    #if SET_FPS_LIMIT
        if ( now - last_render_time >= render_cycle ) {
    #else
        {
    #endif
            PROFILE_SCOPE("Render");
            /*
            float clipPlane_display_down_all[] = {0.0f, 0.0f, -1.0f, 1000.0f};
            // float clipPlane_display_down[] = {0.0f, 0.0f, -1.0f, -1.5f};
            // float clipPlane_display_up[] = { 0.0f, 0.0f, 1.0f, -2.0f };
            float clipPlane_display_down[] = { 0.0f, 0.0f, -1.0f, (targets.getWaterTiles())[0].getHeight() };
            float clipPlane_display_up[] = { 0.0f, 0.0f, 1.0f, -(targets.getWaterTiles())[0].getHeight() };
            // */
            {
                // renderers.processScene(test_light, &clipPlane_up);
                // renderers.processScene(test_light, &clipPlane_display_down_all);
                renderers.processScene(targets.getCrate()->texturedModels, lights);
            }

            {
                // float distance = 2 * (cam.getHeight() - targets.getWater()->getHeight()); {
                //     cam.setHeight(cam.getHeight() - distance);
                //     cam.inverseVerticalAngle();
                //     cam.calculateDirecRightUp();
                //     BaseRenderer::calculateViewMatrix(cam.getPosition(), cam.getDirection(), cam.getUp());
                //         targets.getWaterFbos()->bindReflectionFBO();
                //         renderers.processScene(test_light, &clipPlane_display_up);
                //         targets.getWaterFbos()->unbindCurrentFBO();
                //     cam.setHeight(cam.getHeight() + distance);
                //     cam.inverseVerticalAngle();
                //     cam.calculateDirecRightUp();
                //     BaseRenderer::calculateViewMatrix(cam.getPosition(), cam.getDirection(), cam.getUp());
                // }
            }

            {
                // targets.getWaterFbos()->bindRefractionFBO();
                // renderers.processScene(test_light, &clipPlane_display_down);
                // targets.getWaterFbos()->unbindCurrentFBO();

                // WaterFrameBuffers *waterFbos = targets.getWaterFbos();
                // unsigned int dudvTex = targets.getWaterDudvTexture();
                // unsigned int normalTex = targets.getWaterNormalTexture();
                // renderers.processWater(waterFbos, dudvTex, normalTex);  // high consumption on 1st frame ???
                // renderers.processWater(NULL, dudvTex, normalTex);       // high consumption on 1st frame ???

                renderers.processWater(
                    targets.getWaterTiles(),
                    targets.getWaterDudvTexture(),
                    targets.getWaterNormalTexture());

                // Gui not displayed, No texture provided for gui now.
                renderers.processGui(targets.getGui());
            }

            last_render_time = now;
            rendered_times++;
        }

        PROFILE_SCOPE("Swap");
        win.swapBuffers();
        PROFILE_SCOPE("misc");
        fps++;
    }

LOADER_WIN_CLEANUP:
    win.stop();
    Instrumentor::Get().EndSession();
    return 0;
}
