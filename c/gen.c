/*
Logic behind the Maze generation, following the Randomized Depth-First Search algorithm.
The Maze is a m*n grid of cells.
Each cell contains 3 values :
- (int) adjacents → indicates which cells around itself have already been generated
- (int) connections → indicates its connections to other cells (used for rendering, refer to render.c for more informations)
- (int) type → indicates the type of the cell (mostly used for rendering, refer to render.c for more informations)
Those values should be updated during Maze generation every time a cell type is edited, using update_cell().
*/


#include "h/gen.h"



struct Grid init_grid(int width, int height) {

}

struct Cell init_cell(int adjacents) {

}

void update_cell(struct Grid* grid, struct Cell* cell) {

}

int choose_path(int adjacents) {

}