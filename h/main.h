#ifndef MAIN
#define MAIN

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


struct Cell {
    int adjacents;
    int connections;
    int type;
};

struct Grid {
    struct Cell* cells;
    int width;
    int height;
};


enum Direction {
    NONE = 0,
    WEST = 1,
    EAST = 2,
    SOUTH = 4,
    NORTH = 8,
    ALL = 15
};

enum Type {
    VOID,
    GENERATED,
    VISITED,
    START,
    END
};


int random(int n);


#endif