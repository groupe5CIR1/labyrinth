#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


struct Cell {
    int adjacents;
};

struct Grid {
    struct Cell** cells;
    int width;
    int height;
};


enum Direction {
    NORTH = 1,
    SOUTH = 2,
    WEST = 4,
    EAST = 8
};


int random(int n);

struct Grid init_grid();

struct Cell init_cell(int adjacents);

void updateNeighbours(struct Grid* grid, struct Cell* cell);

int choose_path(int adjacents);






