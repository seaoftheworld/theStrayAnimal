// #pragma once

#include <fstream>  // std::ifstream
#include <string>   // std::string, std::getLine()

#include "LevelData.h"

// #define FILE_UNIT_DATA_BYTES  (6)  // 00 0x, 00 0y, 00 0n
// #define FILE_CRATE_DATA_BYTES (4)  // 00 0x, 00 0y

#define COORD_TO_IDX(x, y) ((y) * MAX_WIDTH + (x))
#define IDX_TO_COORD_X(idx) ((idx) % MAX_WIDTH)
#define IDX_TO_COORD_Y(idx) ((idx) / MAX_WIDTH)

// enum GridCell area_data[MAX_WIDTH * MAX_HEIGHT];
// CratesData crates_data;
// GoalsData goals_data;

struct AreaData {
    const static unsigned int num_cells = MAX_CELL_NUM;
    enum GridCell cell[MAX_CELL_NUM];

    AreaData() {
        clear();
    }

    void clear() {
        for (unsigned int i = 0; i < num_cells; i++) {
            cell[i] = GridCell::empty;
        }   
    }
};

struct CrateData {
    unsigned short xy_pos_idx = 0;
    float z = 0;
};
struct CratesData {
    CrateData crate[MAX_NUM_CRATES];
    unsigned int num = 0;

    void clear() {
        for (unsigned int i = 0; i < MAX_NUM_CRATES; i++) {
            crate[i].xy_pos_idx = 0;
            crate[i].z = 0;
        }
        num = 0;
    }
};

struct GoalsData {
    // unsigned int num = 0, offset = 0;
    Coordinate goal[MAX_NUM_GOALS];
    bool remain[MAX_NUM_GOALS];
    unsigned int num;

    GoalsData() {
        clear();
    }

    void clear() {
        for (int i = 0; i < MAX_NUM_GOALS; i++) {
            remain[i] = false;
        }
        num = 0;
    }
};

enum LevelFileError {
    level_file_not_found = 0, 
    level_file_not_enough_bytes,
    level_file_header_error,
    level_file_num_bytes_error,
    level_file_end_error,
    level_file_error_max
};

class TheStrayAnimal {

    AreaData area_data;      // used for rendering ground, and used as collision-data, rename tobe: collision_data ???
    CratesData crates_data;  // used for rendering crates
    GoalsData goals_data;

    unsigned int player_pos_idx = 0;

    // enum GridCell get_destination_cell_info(unsigned int curr_pos_idx, MoveDirection move, unsigned int *dest_pos_idx);
    unsigned int get_destination_cell_info(unsigned int curr_pos_idx, MoveDirection move, enum GridCell *dest_cell);

public:
    // unsigned int update_crate(unsigned int curr_pos_idx, MoveDirection move);

    // unsigned int update_player(unsigned int curr_pos_idx, MoveDirection move);
    // void update_player(unsigned int curr_pos_idx, MoveDirection move);
    unsigned short update_player_collison_crates(MoveDirection move);
    unsigned short updateGoals(unsigned short *reached_goal);

private:
    LevelFileError verifyLevelData(const std::string &file_path);
public:
    LevelFileError setLevelData(const std::string &file_path);
    void clearLevelData();

public:
    unsigned int getPlayerPosition() { return player_pos_idx; }

    CratesData *getCratesData() { return &crates_data; }
     GoalsData *getGoalsData() { return &goals_data; }
      AreaData *getAreaData() { return &area_data; }

public:
    void printPlayerPosition() {
        printf("player: (%d, %d)\n", IDX_TO_COORD_X(player_pos_idx), IDX_TO_COORD_Y(player_pos_idx));
    }

    void printLevelData() {
        printf("\n\n");
        for (int i = MAX_HEIGHT - 1; i >= 0; i--) {

            printf("%2d: ", i);
            for (int j = 0; j < MAX_WIDTH; j++) {

                if (COORD_TO_IDX(j, i) == player_pos_idx) {
                    printf(" P,");
                }
                else {
                    // printf("(%2d,%2d) %2d  ", j, i, area_data.cell[ COORD_TO_IDX(j, i) ]);
                    printf("%2d,", area_data.cell[ COORD_TO_IDX(j, i) ]);
                }
            }
            printf("\n\n");
        }

        for (int i = 0; i < crates_data.num; i++) {
            printf("(%d, %d, %2f), ", \
                IDX_TO_COORD_X(crates_data.crate[i].xy_pos_idx), \
                IDX_TO_COORD_Y(crates_data.crate[i].xy_pos_idx),\
                crates_data.crate[i].z\
            );
        }
        printf("\n\n\n\n");
    }

    void printGoalsData() {
        for (int i = 0; i < goals_data.num; i++) {
            printf("(%d, %d), ", goals_data.goal[i].x, goals_data.goal[i].y);
        }
        printf("\n\n");
    }
};

// ------------------------------------------
/*
enum UnitData {
    data0 = 0, data1, data2, data3, data_max
};

struct LevelUnit {
    Coordinate position;
    UnitData data = data0;
};

struct Crate {
    Coordinate position;
};

class PorterLevel {
private:
    // scene data
    LevelUnit unit[MAX_WIDTH * MAX_HEIGHT];
    
    // crate data
    unsigned int valide_crate_num;
    Crate crate[MAX_CRATE_NUM];


private:
    void setSceneData(std::ifstream &fstream);
    void setCrateData(std::ifstream &fstream);

    void clearSceneData() {
        // use std::fill(n) to fill the array   
    }
    void clearCrateData() {
    }

    unsigned int num_crates_in_file = 0,
                 num_units_in_file = 0, 
                 file_offset = 0;

public:

    void setLevelData(const std::string &file_path);
    void clearLevelData();

    void printSceneData() {
        printf("\n\n");
        for (int i = 0; i < MAX_HEIGHT; i++) {

            printf("row-%2d: ", i);
            for (int j = 0; j < MAX_WIDTH; j++) {
                printf("(%2d, %2d),%2d  ", j, i, unit[j + i * MAX_WIDTH].data);
            }
            printf("\n\n");
        }
        printf("\n\n\n\n");
    }


    void printCrateData() {
    }
};
//*/
