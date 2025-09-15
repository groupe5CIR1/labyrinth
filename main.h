#include <stdlib.h>
#include <time.h>

struct Cell {
    struct Cell* adjacent_cells[4];
};

struct Path {
    struct Cell** cells;
    int width;
    int height;
};

enum Direction {
    NORTH,
    SOUTH,
    WEST,
    EAST
};