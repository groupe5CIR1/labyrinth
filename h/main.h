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
    struct Cell* end;
};


enum Direction {
    NONE = 0,
    WEST = 1,   //0001
    EAST = 2,   //0010
    SOUTH = 4,  //0100
    NORTH = 8,  //1000
    ALL = 15
};

enum Type {
    VOID,
    GENERATED,
    AVAILABLE,
    VISITED
};


int random(int n);

int opposite(int dir);


#endif