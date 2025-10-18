#ifndef GEN
#define GEN


#include "../h/main.h"
#include "../h/stack.h"

enum End_Cell_Gen_Method {
    DEFAULT,
    RANDOM
};


struct Grid init_grid(int width, int height);
struct Cell init_cell(int x, int y, int width, int height);
struct Cell* init_start(struct Grid* grid);
void update_neighbours(struct Grid* grid, struct Cell* cell);
void connect_cells(struct Cell* from, struct Cell* to, int dir);
int choose_path(int adjacents);
void gen_path(struct Grid* grid, struct Cell* from);
int get_end_cell_method();
void gen_end_cell(struct Grid* grid, int method);
void gen_deadend_end_cell(struct Grid* grid);


#endif