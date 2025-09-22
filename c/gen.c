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
    struct Cell* grid = malloc(width * height * sizeof(struct Cell));
    if (grid == NULL) {
        perror("Out of Memory error: could not allocate grid");
        exit(1);
    }
    return (struct Grid) {.cells = grid, .height = height, .width = width};
}

struct Cell init_cell(int adjacents) {
    return (struct Cell) {.adjacents = adjacents, .connections = 0, .type = GENERATED};
}

//By default, the starting cell is on top left (coordinates (0,0)).
void init_starting_cell(struct Grid* grid, struct Cell* start) {
    start->type = START;
    start->adjacents = NORTH + WEST;
    update_neighbours(grid, start);
}

void update_neighbours(struct Grid* grid, struct Cell* cell) {
    int index = cell - grid->cells;
    int x = index % grid->width;
    int y = index % grid->height;
    
    int i = ALL - cell->adjacents;
    while(i >= 1) {
        struct Cell* copy = cell;
        
        i >>= 1;
    }
}

int choose_path(int adjacents) {

}


/*
Returns the ending cell, chosen randomly.
*/
struct Cell* gen_path(struct Grid* grid, struct Cell* start) {
    struct Stack stack = stack_init();
    
}
