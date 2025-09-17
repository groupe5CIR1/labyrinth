/*
Logic behind the Maze generation, following the Origin Shift (tree chain) algorithm.
The Maze is a m*n grid of cells.
Each cell contains 3 values :
- (int) adjacents → indicates which cells around itself have already been generated
- (int) connections → indicates its connections to other cells (used for rendering, refer to render.c for more informations)
- (int) type → indicates the type of the cell (mostly used for rendering, refer to render.c for more informations)
Those values should be updated during Maze generation every time a cell type is edited, using update_cell().
The generation should use a stack to be able to "undo" a "move", i.e. coming back to the previous cell (refer to stack.c for more informations).
*/


#include "h/gen.h"



struct Grid init_grid(int width, int height) {

}

struct Cell init_cell(int adjacents) {
    return (struct Cell) {.adjacents = adjacents, .connections = 0, .type = GENERATED};
}

void update_cell(struct Grid* grid, struct Cell* cell) {

}

int choose_path(int adjacents) {

}