#include "TheStrayAnimal.h"

#define ACTIVE_CRATE_Z (1.0f)

unsigned int TheStrayAnimal::get_destination_cell_info(unsigned int curr_pos_idx, MoveDirection move, enum GridCell *dest_cell) {

    GridCell dest_cell_info = GridCell::grid_cell_max;
    unsigned int dest_pos_idx = curr_pos_idx;

    if (curr_pos_idx >= area_data.num_cells) {
        return dest_pos_idx;
    }

    unsigned int x = IDX_TO_COORD_X(curr_pos_idx), 
                 y = IDX_TO_COORD_Y(curr_pos_idx);

    switch (move)
    {
    case up:
        if (y == MAX_HEIGHT - 1) {
            // shall not be empty, shall be max(out of boundary), empty is accessible for crate tobe put there, max is not
            // *dest_cell = GridCell::grid_cell_max;  
        }
        else {
            // y++;
            // result = area_data.cell[COORD_TO_IDX(x, y)];
            dest_pos_idx = curr_pos_idx + MAX_WIDTH;
            *dest_cell = area_data.cell[dest_pos_idx];
        }
        break;

    case down:
        if (y == 0) {
        }
        else {
            // y--;
            // result = area_data.grid[COORD_TO_IDX(x, y)];
            dest_pos_idx = curr_pos_idx - MAX_WIDTH;
            *dest_cell = area_data.cell[dest_pos_idx];
        }
        break;

    case left:
        if (x == 0) {
        }
        else {
            // x--;
            // result = area_data.grid[COORD_TO_IDX(x, y)];
            dest_pos_idx = --curr_pos_idx;
            *dest_cell = area_data.cell[dest_pos_idx];
        }
        break;

    case right:
        if (x == MAX_WIDTH - 1) {
        }
        else {
            // x++;
            // result = area_data.grid[COORD_TO_IDX(x, y)];
            dest_pos_idx = ++curr_pos_idx;
            *dest_cell = area_data.cell[dest_pos_idx];
        }
        break;

    case move_direc_max:
    default:
        break;
    }

    return dest_pos_idx;
}

unsigned short TheStrayAnimal::updateGoals(unsigned short *reached_goal) {
    unsigned short remains = 0;

    for (unsigned int i = 0; i < goals_data.num; i++) {
        if (!goals_data.remain[i]) {
            continue;
        }

        if ( player_pos_idx == COORD_TO_IDX(goals_data.goal[i].x, goals_data.goal[i].y) ) {
            goals_data.remain[i] = false;

            if (reached_goal) {
                *reached_goal = i;
            }
            break;
        }
    }

    for (int i = 0; i < goals_data.num; i++) {
        if (goals_data.remain[i]) {
            remains++;
            // break;
        }
    }

    return remains;
}

// unsigned short TheStrayAnimal::updateGoals_opt(unsigned short *reached_goal) {
//     unsigned short remains = 0;

//     for (int i = 0; i < goals_data.num; i++) {
//         if (goals_data.remain[i]) {
//             remains++;
//         }
//     }
//     if (!remains) {
//         return remains;
//     }

//     for (unsigned int i = 0; i < goals_data.num; i++) {
//         if (!goals_data.remain[i]) {
//             continue;
//         }

//         if ( player_pos_idx == COORD_TO_IDX(goals_data.goal[i].x, goals_data.goal[i].y) ) {
//             goals_data.remain[i] = false;

//             if (reached_goal) {
//                 *reached_goal = i;
//             }
//             break;
//         }
//     }

//     return remains;
// }

// unsigned int TheStrayAnimal::update_crate(unsigned int curr_pos_idx, MoveDirection move) {}
unsigned short TheStrayAnimal::update_player_collison_crates(MoveDirection move) {

    unsigned short updated_crate_idx = crates_data.num;

    enum GridCell dest_cell = GridCell::grid_cell_max;
    unsigned int dest_pos_idx = get_destination_cell_info(player_pos_idx, move, &dest_cell);

    switch (dest_cell) {

        case GridCell::grid_cell_max:
        case GridCell::empty:
        default:
            // player does not move
        break;

        case GridCell::ground_only:
        case GridCell::crate_only:
            player_pos_idx = dest_pos_idx;  // player moves to new postion
        break;

        case GridCell::crate_on_ground:
        case GridCell::crate_on_crate: {

            enum GridCell cell_ajacent_to_crate = GridCell::grid_cell_max;
            unsigned int cell_ajacent_to_crate_pos = \
                get_destination_cell_info(dest_pos_idx, move, &cell_ajacent_to_crate);
            float crate_z = 0.0f;

                if (cell_ajacent_to_crate == GridCell::crate_on_ground || \
                    cell_ajacent_to_crate == GridCell::crate_on_crate || \
                    cell_ajacent_to_crate == GridCell::grid_cell_max) {
                    // player does not move
                }
                else {
                    player_pos_idx = dest_pos_idx;  // player moves to new position

                    // update area_data's crates status ... ...
                    area_data.cell[player_pos_idx] = \
                        (area_data.cell[player_pos_idx] == GridCell::crate_on_ground) ? (GridCell::ground_only) : (GridCell::crate_only);

                    if (cell_ajacent_to_crate == GridCell::empty) {
                        area_data.cell[cell_ajacent_to_crate_pos] = GridCell::crate_only;
                    }
                    else if (cell_ajacent_to_crate == GridCell::ground_only) {
                        area_data.cell[cell_ajacent_to_crate_pos] = GridCell::crate_on_ground;
                        crate_z = ACTIVE_CRATE_Z;
                    }
                    else if (cell_ajacent_to_crate == GridCell::crate_only) {
                        area_data.cell[cell_ajacent_to_crate_pos] = GridCell::crate_on_crate;
                        crate_z = ACTIVE_CRATE_Z;
                    }
                    else {}

                    // update crates_data accordingly, this will be used for rendering
                    for (int i = 0; i < crates_data.num; i++) {
                        if ( crates_data.crate[i].xy_pos_idx == player_pos_idx && crates_data.crate[i].z == ACTIVE_CRATE_Z ) {
                            printf("target crate idx, old/new-pos: %d, %d ==> %d\n", i, player_pos_idx, cell_ajacent_to_crate_pos);
                            crates_data.crate[i].xy_pos_idx = cell_ajacent_to_crate_pos;
                            crates_data.crate[i].z = crate_z;

                            updated_crate_idx = i;
                        }
                    }
                }
        }
        break;
    }
    return updated_crate_idx;
}



const unsigned short size_header = 2,
                     size_cells_num = 2,
                     size_goals_num = 2,
                     size_player_pos = 4,
                     size_end = 2;

const unsigned short offset_for_cell_num = 2;
unsigned short cells_num = 0;

unsigned short offset_for_goal_num = 0;
unsigned short goals_num = 0;

unsigned short offset_for_player_init_pos, 
               player_init_x = 0, 
               player_init_y = 0;

LevelFileError TheStrayAnimal::verifyLevelData(const std::string &file_path) {

    unsigned int num_input_bytes = 0; 
    unsigned short file_offset = 0;
    char byte[2]; 

    LevelFileError error = level_file_error_max;

    std::ifstream stream; stream.open(file_path);
    if (!stream.is_open()) {
        printf("file: %s not found\n", file_path.c_str());
        error = level_file_not_found;
        goto RETURN_ERROR_INFO;
    }
    stream.close();
    printf("file: \'%s\' found.\n", file_path.c_str());

    stream.open(file_path, std::ios_base::binary); {
        if (stream.bad()) {
            printf("file: %s is bad-stream\n", file_path.c_str());
            error = level_file_not_found;
            goto RETURN_ERROR_INFO;
        }
        num_input_bytes = stream.rdbuf()->pubseekoff(0, std::ios_base::end);

        // aa55, cells_num, 6 * num bytes, goals_num, 6 * num_bytes, player_int_xy, 55aa
        if (num_input_bytes < size_header + \
                              size_cells_num + 6 + size_goals_num + 6 + \
                              size_player_pos + size_end) {  
            printf("File size not enough!\n");
            error = level_file_not_enough_bytes;
            goto RETURN_ERROR_INFO;
        }

        // 1. Check the first 2 bytes are 0xaa55
        stream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
        stream.read(byte, 2);
        if ((unsigned char)byte[0] != 0xaa || (unsigned char)byte[1] != 0x55) {
            printf("invalid file-head (not 0xaa55): 0x%2x, 0x%2x\n", byte[0], byte[1]);
            error = level_file_header_error;
            goto RETURN_ERROR_INFO;
        }

        // 2. Check the last 2 bytes are 0x55aa
        file_offset = (num_input_bytes - 1) - 1;
        stream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
        stream.read(byte, 2);
        if ((unsigned char)byte[0] != 0x55 || (unsigned char)byte[1] != 0xaa) {
            printf("invalid file-end (not 0x55aa): 0x%2x, 0x%2x\n", byte[0], byte[1]);
            error = level_file_end_error;
            goto RETURN_ERROR_INFO;
        }

        // 3. File bytes num calculation
        stream.rdbuf()->pubseekoff(offset_for_cell_num, std::ios_base::beg);
        stream.read(byte, 2);
        cells_num = (byte[1] << 8) | byte[0];
        printf("cells_num: %d\n", cells_num);

        offset_for_goal_num = 2 + 2 + cells_num * 6;
        stream.rdbuf()->pubseekoff(offset_for_goal_num, std::ios_base::beg);
        stream.read(byte, 2);
        goals_num = (byte[1] << 8) | byte[0];
        printf("goals_num: %d\n", goals_num);

        if (num_input_bytes != size_header + \
                               size_cells_num + cells_num * 6 + \
                               size_goals_num + goals_num * 6 + \
                               size_player_pos + size_end) {
            printf("File size error: %d!\n", num_input_bytes);

            error = level_file_num_bytes_error;
            goto RETURN_ERROR_INFO;
        }
    }

RETURN_ERROR_INFO:
    stream.close();
    return error;
}

void TheStrayAnimal::clearLevelData() {
    crates_data.clear();
    goals_data.clear();
    area_data.clear();
}

LevelFileError TheStrayAnimal::setLevelData(const std::string &file_path) {

    unsigned short file_offset = 0;
    char byte[2]; 

    LevelFileError error = verifyLevelData(file_path);
    if (error != level_file_error_max) {
        return error;
    }

    std::ifstream stream; stream.open(file_path, std::ios_base::binary); {

        // 4. Load cells data from the file into the member-variable: area_data(collision_data), crates_data
        {
            file_offset = offset_for_cell_num + size_cells_num;  // cell_num occupies 2 bytes

            for (int i = 0; i < cells_num && i < area_data.num_cells; i++) {
                unsigned short x, y, value;

                stream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
                stream.read(byte, 2); x = (byte[1] << 8) | byte[0];
                if (x >= MAX_WIDTH) {
                    continue;
                }
                file_offset += 2;

                stream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
                stream.read(byte, 2); y = (byte[1] << 8) | byte[0];
                if (y >= MAX_HEIGHT) {
                    continue;
                }
                file_offset += 2;

                stream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
                stream.read(byte, 2); value = (byte[1] << 8) | byte[0];
                file_offset += 2;

                switch (value)
                {
                case 0:
                    area_data.cell[COORD_TO_IDX(x, y)] = GridCell::empty;
                    break;
                case 1:
                    area_data.cell[COORD_TO_IDX(x, y)] = GridCell::ground_only;
                    break;
                case 2:
                    area_data.cell[COORD_TO_IDX(x, y)] = GridCell::crate_on_ground;
                    crates_data.crate[crates_data.num].xy_pos_idx = COORD_TO_IDX(x, y);
                    crates_data.crate[crates_data.num].z = ACTIVE_CRATE_Z;
                    crates_data.num++;
                    break;
                case 3:
                    area_data.cell[COORD_TO_IDX(x, y)] = GridCell::crate_only;
                    crates_data.crate[crates_data.num].xy_pos_idx = COORD_TO_IDX(x, y);
                    crates_data.crate[crates_data.num].z = 0.0f;
                    crates_data.num++;
                    break;
                case 4:
                    area_data.cell[COORD_TO_IDX(x, y)] = GridCell::crate_on_crate;
                    crates_data.crate[crates_data.num].xy_pos_idx = COORD_TO_IDX(x, y);
                    crates_data.crate[crates_data.num].z = ACTIVE_CRATE_Z;
                    crates_data.num++;
                    crates_data.crate[crates_data.num].xy_pos_idx = COORD_TO_IDX(x, y);
                    crates_data.crate[crates_data.num].z = 0.0f;
                    crates_data.num++;
                    break;
                default:
                    area_data.cell[COORD_TO_IDX(x, y)] = GridCell::grid_cell_max;
                    break;
                }
            }
        }

        // 5. Load goals data from the file into the member-variable: goals_data
        goals_data.num = goals_num; {

            if (goals_data.num > MAX_NUM_GOALS) {
                goals_data.num = MAX_NUM_GOALS;
            }

            file_offset = offset_for_goal_num + size_goals_num;  // goal_num occupies 2 bytes
            for (int i = 0; i < goals_data.num; i++) {
                unsigned short x, y;

                stream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
                stream.read(byte, 2); x = (byte[1] << 8) | byte[0];
                file_offset += 2;

                stream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
                stream.read(byte, 2); y = (byte[1] << 8) | byte[0];
                file_offset += 4;

                goals_data.goal[i].x = x;
                goals_data.goal[i].y = y;
                goals_data.remain[i] = true;
            }
        }

        // Get player's init xy position
        offset_for_player_init_pos = 2 + 2 + cells_num * 6 + 2 + goals_num * 6;
        stream.rdbuf()->pubseekoff(offset_for_player_init_pos, std::ios_base::beg);
        stream.read(byte, 2);
        player_init_x = (byte[1] << 8) | byte[0];
        offset_for_player_init_pos += 2;

        stream.rdbuf()->pubseekoff(offset_for_player_init_pos, std::ios_base::beg);
        stream.read(byte, 2);
        player_init_y = (byte[1] << 8) | byte[0];

        player_pos_idx = COORD_TO_IDX(player_init_x, player_init_y);
        printf("player init xy: %d, %d\n", IDX_TO_COORD_X(player_pos_idx), IDX_TO_COORD_Y(player_pos_idx));
        printf("crates num: %d\n", crates_data.num);
    }

    stream.close();
    return error;
}

/*
void PorterLevel::setSceneData(std::ifstream &fstream) {
    // use std::fill(n) to fill the unit[] array according to 
    // input file: (x, y)-data ==> unit[x, y] = data

    // std::string source = "hex_test", line;
    // std::ifstream filePath;

    unsigned int unit_count = 0;
    char byte[2];
    
    file_offset = 0 + 0x10;  // addr 00 ~ 0f are head of the level-file

    while (1) {

        if (unit_count >= num_units_in_file) {
            break;
        }

        unsigned int x, y, data; {
            // assign values from input level file ... ...
            fstream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
            fstream.read(byte, 2);
            x = ((unsigned char)byte[0] << 8) | ((unsigned char)byte[1]);
            file_offset += 2;

            fstream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
            fstream.read(byte, 2);
            y = ((unsigned char)byte[0] << 8) | ((unsigned char)byte[1]);
            file_offset += 2;

            fstream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
            fstream.read(byte, 2);
            data = ((unsigned char)byte[0] << 8) | ((unsigned char)byte[1]);
            file_offset += 2;

            unit_count++;

            printf("x, y, data: %d, %d, %d\n", x, y, data);
        }

        if (x >= MAX_WIDTH || y >= MAX_HEIGHT || data >= UnitData::data_max) {
            continue;
        }

        // unit[x + y * MAX_WIDTH].data = data;
        switch(data) {
            case 0:
                unit[x + y * MAX_WIDTH].data = data0;
            break;

            case 1:
                unit[x + y * MAX_WIDTH].data = data1;
            break;

            case 2:
                unit[x + y * MAX_WIDTH].data = data2;
            break;

            case 3:
                unit[x + y * MAX_WIDTH].data = data3;
            break;

            default:
            break;
        }
    }
}

void PorterLevel::setCrateData(std::ifstream &fstream) {

    // use std::fill(n) to fill the crate[] array and valid_crate_num
    // according to input file
    char byte[2];

    unsigned int crate_count = 0, crate_idx = 0;
    while (1) {

        if (crate_count >= num_crates_in_file) {
            break;
        }

        unsigned int x, y; {
            // assign values from input level file ... ...
            fstream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
            fstream.read(byte, 2);
            x = ((unsigned char)byte[0] << 8) | ((unsigned char)byte[1]);
            file_offset += 2;

            fstream.rdbuf()->pubseekoff(file_offset, std::ios_base::beg);
            fstream.read(byte, 2);
            y = ((unsigned char)byte[0] << 8) | ((unsigned char)byte[1]);
            file_offset += 2;

            printf("crate (x, y): %d, %d\n", x, y);
            crate_count++;
        }

        if (x >= MAX_WIDTH || y >= MAX_HEIGHT) {
            continue;
        }
        crate[crate_idx].position.x = x;
        crate[crate_idx++].position.y = y;
    }
}
//*/

// unsigned int TheStrayAnimal::update_player(unsigned int curr_pos_idx, MoveDirection move) {
// void TheStrayAnimal::update_player(unsigned int curr_pos_idx, MoveDirection move) {

//     enum GridCell dest_cell = GridCell::grid_cell_max;
//     unsigned int new_pos_idx = 0, dest_pos_idx = get_destination_cell_info(curr_pos_idx, move, &dest_cell);

//     switch (dest_cell) {

//         case GridCell::grid_cell_max:
//         case GridCell::empty:
//         default:
//             new_pos_idx = curr_pos_idx;  // player does not move
//         break;

//         case GridCell::ground_only:
//         case GridCell::crate_only:
//             new_pos_idx = dest_pos_idx;  // player moves to new postion
//         break;

//         case GridCell::crate_on_ground:
//         case GridCell::crate_on_crate: {

//             enum GridCell cell_ajacent_to_crate = GridCell::grid_cell_max;
//             unsigned int cell_ajacent_to_crate_pos = \
//                 get_destination_cell_info(dest_pos_idx, move, &cell_ajacent_to_crate);

//                 if (cell_ajacent_to_crate == GridCell::crate_on_ground || \
//                     cell_ajacent_to_crate == GridCell::crate_on_crate || \
//                     cell_ajacent_to_crate == GridCell::grid_cell_max) {
//                     new_pos_idx = curr_pos_idx;  // player does not move
//                 }
//                 else {
//                     // update player position
//                     new_pos_idx = dest_pos_idx;  // player moves to new position

//                     // update crates data for the whole area ... ...
//                     area_data.cell[dest_pos_idx] = \
//                         (area_data.cell[dest_pos_idx] == GridCell::crate_on_ground) ? (GridCell::ground_only) : (GridCell::crate_only);

//                     if (cell_ajacent_to_crate == GridCell::empty) {
//                         area_data.cell[cell_ajacent_to_crate_pos] = GridCell::crate_only;
//                     }
//                     else if (cell_ajacent_to_crate == GridCell::ground_only) {
//                         area_data.cell[cell_ajacent_to_crate_pos] = GridCell::crate_on_ground;
//                     }
//                     else if (cell_ajacent_to_crate == GridCell::crate_only) {
//                         area_data.cell[cell_ajacent_to_crate_pos] = GridCell::crate_on_crate;
//                     }
//                     else {}
//                 }
//         }
//         break;
//     }

//     // return new_pos_idx;
//     player_pos_idx = new_pos_idx;
// }
