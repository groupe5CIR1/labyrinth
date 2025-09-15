#include <stdlib.h>
#include <time.h>

struct Cell {
    int adjacents;
};

struct Path {
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