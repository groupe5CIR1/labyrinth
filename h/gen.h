#ifndef GEN
#define GEN


#include "h/main.h"
#include "h/stack.h"



struct Grid init_grid(int width, int height);
struct Cell init_cell(int adjacents);
void init_starting_cell(struct Grid* grid, struct Cell* start);
void update_neighbours(struct Grid* grid, struct Cell* cell);
int choose_path(int adjacents);
struct Cell* gen_path(struct Grid* grid, struct Cell* start);


#endif