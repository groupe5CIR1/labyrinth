#ifndef GEN
#define GEN


#include "h/main.h"
#include "h/stack.h"



struct Grid init_grid(int width, int height);
struct Cell init_cell(int x, int y, int width, int height);
struct Cell* init_start(struct Grid* grid);
void update_neighbours(struct Grid* grid, struct Cell* cell);
int choose_path(int adjacents);
struct Cell* gen_path(struct Grid* grid, struct Cell* from);
struct Cell* get_cell(struct Grid* grid, struct Cell* cell, int dir);
void connect_cells(struct Cell* from, struct Cell* to, int dir);


#endif