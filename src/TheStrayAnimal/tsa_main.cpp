// To use OpenGL, Libs depended on are: 
// 1. glfw (included in WindowSystem.h)
// 2. gl3w (included in Renderer.h)
// 3. gl_math

#define __USE_INLINE_METHODS__
#include "WindowSystem/WindowSystem.h"

#include "TSA_WrappingRenderer.h"
#include "TSA_LoadTargets.h"
    //#include "TheStrayAnimal.h"

#include <iostream>
#include <stdio.h>

#define SET_FPS_LIMIT (1)
    // #if SET_FPS_LIMIT
    // #else
    // #endif

enum InputResult {
    input_none = 0, input_up, input_down, input_left, input_right, input_max
};
InputResult input_result = InputResult::input_none;

int tsa_main() {
	printf("  __Made for heiduzi to find home.\n");

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
    // set the renderers for the scene
    // ---------------------------------
    Loader loader;
    TSA_WrappingRenderer renderers(loader); 
    {
        if (!renderers.entityRenderer.ready()) {
            win.stop();
            return -1;
        }
        // if (!renderers.picRenderer.ready()) {
        //     win.stop();
        //     return -1;
        // }
        if (!renderers.skyboxRenderer.ready()) {
            win.stop();
            return -1;
        }

        if (!renderers.waterRenderer.ready()) {
            win.stop();
            return -1;
        }

        // printf("shaders init done, press anything to continue ...\n\n"); {
        //     int dbg;
        //     scanf("%d", &dbg);
        // }
    }
    renderers.specificSettingsOn();

    // ---------------------------------
    // set the lights for the scene
    // ---------------------------------
    const unsigned short NUM_LIGHTS = 5; {

        Light light[NUM_LIGHTS];

        float pos[NUM_LIGHTS][Light::Position::max_pos] = {
            { 20.0f,   0.0f, 25.0f},  // x+
            {  0.0f,  20.0f, 25.0f},  // y+
            {-20.0f,   0.0f, 25.0f},  // x-
            {  0.0f, -20.0f, 25.0f},  // y-
            {  0.0f, -20.0f, 1.0f}    // y-
        };

        // float color[Light::Color::max_color] = {1.6f, 1.2f, 1.6f};
        // float color[Light::Color::max_color] = { 1.6f, 1.6f, 1.6f };
        float color[NUM_LIGHTS][Light::Color::max_color] = {
            { 1.0f, 1.0f, 0.6f },   // yellow
            { 0.9f, 1.0f, 0.9f },   // green
            { 1.0f, 1.0f, 1.0f },
            { 0.6f, 0.6f, 1.0f },   // blue
            { 1.0f, 1.0f, 1.0f }    // white
        };
        float attenuation[Light::Attenuation::max_att] = { 2.0f, 0.02f, 0.0f };

        for (int i = 0; i < NUM_LIGHTS; i++) {
            light[i].setValues(&pos[i], &color[i], &attenuation);
            renderers.addLights(&light[i]);
        }
    }

    // Camera cam(gl_math::vec3(-0.9448f, 6.760f, 5.463f), 2.23f, -0.69f);
    // Camera cam(gl_math::vec3(0.46, -2.42, 3.0), 0.0f, -0.835f);
    // Camera cam(gl_math::vec3(-1.9, -4.3, 4.6), 0.665f, -0.72f);
    // Camera cam(gl_math::vec3(1.0, -3.64, 2.45), 0.48f, -0.6f);
    Camera cam(gl_math::vec3(0.005, -3.0, 2.45), 0.6f, -0.7f);


    // ---------------------------------
    // prepare to read the level data
    // ---------------------------------
    unsigned short level = 0;

    bool levels_all_passed = false, 
         level_file_error = false,
         quit_game = false;

    TheStrayAnimal heiduzi;

    while ( !quit_game && !levels_all_passed && !level_file_error ) {

        bool goals_all_reached = false,
             load_next_leveL = false;

        // Without this line, when loading next level, the software will crash 
        // because the rendering-objects(ground, crate, player) 
        // from the previous level are gone (when 'targets' setData() is called):
        renderers.entityRenderer.clearEntities();
        TSA_LoadTargets targets(loader);

        unsigned short NUM_CRATES = 0;
        heiduzi.clearLevelData();

        // ---------------------------------
        // read the level data
        // ---------------------------------
        level++; {
            std::string prefix = "levels/test", suffix = ".hex";
            std::string num = std::to_string(level);

            std::string level_file = prefix + num + suffix;
            LevelFileError info = heiduzi.setLevelData(level_file);

            if (info == level_file_not_found && level != 1) {
                printf("level-%d file not exist, taken as all levels passed !\n", level);
                levels_all_passed = true;
            }
            else if (info == level_file_not_found && level == 1) {
                printf("level-%d file not exist, none level exit !\n", level);
                level_file_error = true;
            }
            else if (info != level_file_error_max) {
                printf("level-%d file returned error-code: %d !\n", level, info);
                level_file_error = true;
            }
            else {
                printf("level-%d loaded.\n\n\n\n", level);
                // heiduzi.printLevelData();
                // heiduzi.printGoalsData();
            }
        }

        if (level_file_error || levels_all_passed) {
            break;
        }
        else {
            NUM_CRATES = heiduzi.getCratesData()->num;
            // printf("level's crates num: %d", NUM_CRATES);

            targets.setData(heiduzi);

            renderers.entityRenderer.addEntity(targets.getOriginSquare());

            for (auto ground_entity = targets.getGround()->entities.begin(); ground_entity != targets.getGround()->entities.end(); ground_entity++) {
                renderers.entityRenderer.addEntity(&(*ground_entity));
            }
            for (auto crate_entity = targets.getCrate()->entities.begin(); crate_entity != targets.getCrate()->entities.end(); crate_entity++) {
                renderers.entityRenderer.addEntity(&(*crate_entity));
            }
            for (auto goal_entity = targets.getGoal()->entities.begin(); goal_entity != targets.getGoal()->entities.end(); goal_entity++) {
                renderers.entityRenderer.addEntity(&(*goal_entity));
            }

            for (auto player_entity = targets.getPlayer()->entities.begin(); player_entity != targets.getPlayer()->entities.end(); player_entity++) {
                renderers.entityRenderer.addEntity(&(*player_entity));
            }

            renderers.skyboxRenderer.setSkybox(targets.getSkybox());

            for (int i = 0; i < targets.getWaterTilesNum(); i++) {
                renderers.waterRenderer.addWaterTile(&(targets.getWaterTiles())[i]);
            }

            // renderers.guiRenderer.addGui(&(targets.getGui()[0]));
            // renderers.guiRenderer.addGui(&(targets.getGui()[1]));
            // renderers.guiRenderer.addGui(&(targets.getGui()[2]));
            // renderers.guiRenderer.addGui(&(targets.getGui()[3]));   
        }

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

            //*
            float clipPlane_display_down_all[] = {0.0f, 0.0f, -1.0f, 1000.0f};
            // float clipPlane_display_down[] = {0.0f, 0.0f, -1.0f, -1.5f};
            // float clipPlane_display_up[] = { 0.0f, 0.0f, 1.0f, -2.0f };
            // float clipPlane_display_down[] = { 0.0f, 0.0f, -1.0f, (targets.getWaterTiles())[0].getHeight() };
            // float clipPlane_display_up[] = { 0.0f, 0.0f, 1.0f, -(targets.getWaterTiles())[0].getHeight() };
            //*/

        // BeginSession() and EndSession() Used in paires
        // Instrumentor::Get().BeginSession("main loop profiling");
        // while ( win.isValid() ) {
        static bool first; first = true;
        while ( !load_next_leveL && !quit_game ) {

            PROFILE_SCOPE("main loop");

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
            static bool stop = false;
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

                {
                    // unsigned short et_idx = 0;
                    // float rot_z_step = 0.785f;

                    // static bool increase = false;
                    
                    // for (auto itr = assimp_misa.entities.begin(); itr != assimp_misa.entities.end(); itr++) {
                    //     float delta_rot_z = ( increase ) ? (rot_z_step) : (-rot_z_step);
                    //     (*itr).increaseRotation(et_idx, 0.0f, 0.0f, delta_rot_z);
                    // }

                    // if ((*assimp_misa.entities[0].getInfo(et_idx))[Entity::transform::rot_z] > 3.14f) {
                    //     // printf("rot_z max: %f\n", (*assimp_misa.entities[0].getInfo(et_idx))[Entity::transform::rot_z]);
                    //     increase = false;
                    // }
                    // else if ((*assimp_misa.entities[0].getInfo(et_idx))[Entity::transform::rot_z] < -3.14f) {
                    //     // printf("rot_z min: %f\n", (*assimp_misa.entities[0].getInfo(et_idx))[Entity::transform::rot_z]);
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
                    if (i > 0) {
                        stop = false;
                        i = 0;
                    }
                }
            }

            // When less than the amount of 'min_cycle' time has passed since the last valid loop,
            // sleep for 'min_cycle' time before the next loop for power-consumption.
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

            // Read input
            // update view-matrix according to input, 
            // update entity pos, rot, scale...  
            // and the others...
        #if SET_FPS_LIMIT
            // if ( now - last_update_time >= update_cycle ) {
            {
        #else
            {
        #endif

                PROFILE_SCOPE("Update inputs, view...");
                
                win.pollEvents();  // not respond when close win with mouse without this
                if ( !win.isValid() ) {
                    quit_game = true;
                }

                cam.input_update(win);
                BaseRenderer::calculateViewMatrix(cam.getPosition(), cam.getDirection(), cam.getUp());

                // Game Input(up, down, left, right) update
                static unsigned char prev_input = 0;
                static unsigned char curr_input = 0; {

                    if (goals_all_reached && win.getKey( WIN_SYS_KEY_N )) {
                        load_next_leveL = 1;
                    }

                    if ( win.getKey( WIN_SYS_KEY_W ) == WIN_SYS_PRESS ) {
                    // if ( glfwGetKey(m_GLFWWindowPointer, GLFW_KEY_W) == (GLFW_PRESS) ) {
                        curr_input = 1;
                    }
                    else if ( win.getKey( WIN_SYS_KEY_S ) == WIN_SYS_PRESS ) {
                        curr_input = 2;
                    }
                    else if ( win.getKey( WIN_SYS_KEY_A ) == WIN_SYS_PRESS ) {
                        curr_input = 3;
                    }
                    else if ( win.getKey( WIN_SYS_KEY_D ) == WIN_SYS_PRESS ) {
                        curr_input = 4;
                    }
                    else {
                        curr_input = 0;
                    }

                    // if ( win.getKey( WIN_SYS_KEY_W ) == WIN_SYS_RELEASE && temp_input_status == 1 ) {
                    if ( curr_input == 1 && prev_input == 0 ) {
                        printf("Up\n\n");
                        // temp_input_status = 0;
                        input_result = InputResult::input_up;
                    }
                    // else if ( win.getKey( WIN_SYS_KEY_S ) == WIN_SYS_RELEASE && temp_input_status == 2 ) {
                    else if ( curr_input == 2 && prev_input == 0 ) {
                        printf("Down\n\n");
                        // temp_input_status = 0;
                        input_result = InputResult::input_down;
                    }
                    // else if ( win.getKey( WIN_SYS_KEY_A ) == WIN_SYS_RELEASE && temp_input_status == 3 ) {
                    else if ( curr_input == 3 && prev_input == 0 ) {
                        printf("Left\n\n");
                        // temp_input_status = 0;
                        input_result = InputResult::input_left;
                    }
                    // else if ( win.getKey( WIN_SYS_KEY_D ) == WIN_SYS_RELEASE && temp_input_status == 4 ) {
                    else if ( curr_input == 4 && prev_input == 0 ) {
                        printf("Right\n\n");
                        // temp_input_status = 0;
                        input_result = InputResult::input_right;
                    }
                    else {
                        input_result = InputResult::input_none;
                    }

                    // if (win.getKey(WIN_SYS_KEY_V) == WIN_SYS_PRESS) {
                    //     // float KEY_MOVE_SPEED = .01f;
                    //     printf("cam  position: %f, %f, %f\n", position.x, position.y, position.z);
                    //     printf("h angle      : %f\n", hAngle);
                    //     printf("v angle      : %f\n\n", vAngle);
                    //     printf("cam direction: %f, %f, %f\n", direc.x, direc.y, direc.z);
                    //     printf("cam        up: %f, %f, %f\n\n\n", up.x, up.y, up.z);
                    // }

                    prev_input = curr_input;
                }

                last_update_time = now;
                updated_times++;
            }

            // Update games's data(area_data, crates_data, goals_data) according to input
        #if SET_FPS_LIMIT
            if ( now - last_update_time >= update_cycle || input_result != input_none ) {
        #else
            {
        #endif
                unsigned short updated_crate_idx = NUM_CRATES, 
                               reached_goal = MAX_NUM_GOALS,
                               remained_goals = MAX_NUM_GOALS;

                // update player's position, collision data, and crates's position data
                switch (input_result) {
                    case InputResult::input_up:
                        updated_crate_idx = heiduzi.update_player_collison_crates(MoveDirection::up);
                        remained_goals = heiduzi.updateGoals(&reached_goal);
                        // printf("aaaa Updated crate: %d\n", updated_crate_idx);
                        // heiduzi.printLevelData();

                        // update player's transform
                        targets.updatePlayer(heiduzi.getPlayerPosition(), 0.0f);
                    break;

                    case InputResult::input_down:
                        updated_crate_idx = heiduzi.update_player_collison_crates(MoveDirection::down);
                        remained_goals = heiduzi.updateGoals(&reached_goal);
                        // heiduzi.printLevelData();

                        // update player's transform
                        targets.updatePlayer(heiduzi.getPlayerPosition(), 3.14f);
                    break;

                    case InputResult::input_left:
                        updated_crate_idx = heiduzi.update_player_collison_crates(MoveDirection::left);
                        remained_goals = heiduzi.updateGoals(&reached_goal);
                        // heiduzi.printLevelData();

                        // update player's transform
                        targets.updatePlayer(heiduzi.getPlayerPosition(), 3.14f / 2.0f);
                    break;

                    case InputResult::input_right:
                        updated_crate_idx = heiduzi.update_player_collison_crates(MoveDirection::right);
                        remained_goals = heiduzi.updateGoals(&reached_goal);
                        // heiduzi.printLevelData();

                        // update player's transform
                        targets.updatePlayer(heiduzi.getPlayerPosition(), 3.14f / 2.0f + 3.14f);
                    break;

                    case InputResult::input_none:
                    default:
                    break;
                }

                // update crate's transform if any has been moved
                if (updated_crate_idx < NUM_CRATES) {
                    // printf("bbbb Updated crate: %d\n", updated_crate_idx);
                    targets.updateCrate(heiduzi.getCratesData(), updated_crate_idx);
                }

                if (reached_goal < MAX_NUM_GOALS) {
                    targets.deleteGoal(heiduzi.getGoalsData(), reached_goal);
                }

                if (!remained_goals) {
                    //... ...
                    printf("you WIN !!!\n");
                    printf("input \'N\' to load next level\n");
                    goals_all_reached = 1;
                }
            }

            // Render entities according to updated data
        #if SET_FPS_LIMIT
            if ( now - last_render_time >= render_cycle ) {
        #else
            {
        #endif
                PROFILE_SCOPE("Render scene");

                // renderers.processScene(test_light, &clipPlane_up);
                renderers.processScene(&clipPlane_display_down_all);

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

                PROFILE_SCOPE("Render water");
                // targets.getWaterFbos()->bindRefractionFBO();
                // renderers.processScene(test_light, &clipPlane_display_down);
                // targets.getWaterFbos()->unbindCurrentFBO();

                    // WaterFrameBuffers *waterFbos = targets.getWaterFbos();
                    unsigned int dudvTex = 0, normalTex = 0;
                    targets.getWaterTextures(dudvTex, normalTex);
                    // renderers.processWater(waterFbos, dudvTex, normalTex);  // high consumption on 1st frame ???
                    renderers.processWater(NULL, dudvTex, normalTex);          // high consumption on 1st frame ???

                    // renderers.processGui();

                last_render_time = now;
                rendered_times++;
            }

            {
                PROFILE_SCOPE("Swap");
                win.swapBuffers();
            }

            {
                PROFILE_SCOPE("misc");
                fps++;
            }
        }
    }

// LOADER_WIN_CLEANUP:
    if (quit_game) {
        printf("game is quit\n");
    }
    else if (levels_all_passed) {
        printf("game levels all passed !!!\n");
    }
    else {
    }

    loader.cleanUp();
    win.stop();
    // Instrumentor::Get().EndSession();
    return 0;
}


    /*
    bool input_up = false, input_down = false, 
         input_left = false, input_right = false;

    while (!glfwWindowShouldClose(m_GLFWWindowPointer)) {

        // Input update
        static unsigned char temp_input_status = 0;

        glfwPollEvents();  // not respond when close win with mouse without this
        {
            // if (win.getKey( WIN_SYS_KEY_R ) == WIN_SYS_PRESS) {
            if ( glfwGetKey(m_GLFWWindowPointer, GLFW_KEY_W) == (GLFW_PRESS) ) {
                // printf("Up\n\n");
                temp_input_status = 1;
            }
            else if ( glfwGetKey(m_GLFWWindowPointer, GLFW_KEY_S) == (GLFW_PRESS) ) {
                // printf("Down\n\n");
                temp_input_status = 2;
            }
            else if ( glfwGetKey(m_GLFWWindowPointer, GLFW_KEY_A) == (GLFW_PRESS) ) {
                // printf("Left\n\n");
                temp_input_status = 3;
            }
            else if ( glfwGetKey(m_GLFWWindowPointer, GLFW_KEY_D) == (GLFW_PRESS) ) {
                // printf("Right\n\n");
                temp_input_status = 4;
            }

            if ( glfwGetKey(m_GLFWWindowPointer, GLFW_KEY_W) == (GLFW_RELEASE) && temp_input_status == 1 ) {
                printf("Up\n\n");
                temp_input_status = 0;
                input_result = InputResult::input_up;
            }
            else if ( glfwGetKey(m_GLFWWindowPointer, GLFW_KEY_S) == (GLFW_RELEASE) && temp_input_status == 2 ) {
                printf("Down\n\n");
                temp_input_status = 0;
                input_result = InputResult::input_down;
            }
            else if ( glfwGetKey(m_GLFWWindowPointer, GLFW_KEY_A) == (GLFW_RELEASE) && temp_input_status == 3 ) {
                printf("Left\n\n");
                temp_input_status = 0;
                input_result = InputResult::input_left;
            }
            else if ( glfwGetKey(m_GLFWWindowPointer, GLFW_KEY_D) == (GLFW_RELEASE) && temp_input_status == 4 ) {
                printf("Right\n\n");
                temp_input_status = 0;
                input_result = InputResult::input_right;
            }
            else {
                input_result = InputResult::input_none;
            }

            // if (win.getKey(WIN_SYS_KEY_V) == WIN_SYS_PRESS) {
            //     // float KEY_MOVE_SPEED = .01f;
            //     printf("cam  position: %f, %f, %f\n", position.x, position.y, position.z);
            //     printf("h angle      : %f\n", hAngle);
            //     printf("v angle      : %f\n\n", vAngle);
            //     printf("cam direction: %f, %f, %f\n", direc.x, direc.y, direc.z);
            //     printf("cam        up: %f, %f, %f\n\n\n", up.x, up.y, up.z);
            // }
        }

        // Update
        switch (input_result) {
            case InputResult::input_up:
                heiduzi.update_player(MoveDirection::up);
            break;

            case InputResult::input_down:
                heiduzi.update_player(MoveDirection::down);
            break;

            case InputResult::input_left:
                heiduzi.update_player(MoveDirection::left);
            break;

            case InputResult::input_right:
                heiduzi.update_player(MoveDirection::right);
            break;

            case InputResult::input_none:
            defalt:
            break;
        }

        // CLI Render
        if (input_result != InputResult::input_none) {
            heiduzi.printPlayerPosition();
            heiduzi.printAreaData();
        }

        // 3D Render
        tsDraw();
        glfwSwapBuffers(m_GLFWWindowPointer);

    }

    tsDeInit();

    glfwDestroyWindow(m_GLFWWindowPointer);
    glfwTerminate();
    return 0;
    //*/
