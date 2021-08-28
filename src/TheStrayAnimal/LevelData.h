#pragma once

#define MAX_NUM_CRATES (20)
#define MAX_NUM_GOALS  (10)

#define MAX_WIDTH  (20)
#define MAX_HEIGHT (15)
#define MAX_CELL_NUM ((MAX_WIDTH) * (MAX_HEIGHT))

enum MoveDirection {
    up, down, left, right, move_direc_max
};

enum GridCell {
    empty = 0, ground_only, crate_on_ground, crate_only, crate_on_crate, grid_cell_max
};

struct Coordinate {
    int x, y;
};
