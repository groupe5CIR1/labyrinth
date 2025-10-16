/*
Logic behind the Maze generation, following the Origin Shift (tree chain) algorithm.
The Maze is a m*n grid of cells.
Each cell contains 3 values :
- (int) adjacents → indicates which cells around itself have already been generated
- (int) connections → indicates its connections to other cells (used for rendering, refer to render.c for more informations)
- (int) type → indicates the type of the cell (mostly used for rendering, refer to render.c for more informations)
Those values should be updated during Maze generation every time a cell type is modified, using update_cell().
The generation uses a stack to be able to "undo" a "move", i.e. coming back to the previous cell (refer to stack.c for more informations).
*/


#include "h/gen.h"



struct Grid init_grid(int width, int height) {
    struct Cell* grid = malloc(width * height * sizeof(struct Cell));
    if (grid == NULL) {
        perror("Out of Memory error: could not allocate grid");
        exit(1);
    }
    for (int i=0; i<width*height; i++) {
        int x = i % width;
        int y = i / width;
        grid[i] = init_cell(x, y, width, height);
    }
    return (struct Grid) {.cells = grid, .height = height, .width = width, .end = NULL};
}

struct Cell init_cell(int x, int y, int width, int height) {
    int adjacents =         //boundary checks
        (x == 0 ?           WEST : 0) |
        (x == width-1 ?     EAST : 0) |
        (y == 0 ?           NORTH : 0) |
        (y == height-1 ?    SOUTH : 0);

    return (struct Cell) {.adjacents = adjacents, .connections = 0, .type = VOID};
}

//By default, the starting cell is on top left (coordinates (0,0)).
struct Cell* init_start(struct Grid* grid) {
    struct Cell* start = &grid->cells;
    start->type = VISITED;
    start->adjacents = NORTH + WEST;
    update_neighbours(grid, start);
    return start;
}

void update_neighbours(struct Grid* grid, struct Cell* cell) {
    int dir = ALL - cell->adjacents;
    int dirs[] = {-1, 1, grid->width, -grid->width};
    int opp[] = {EAST, WEST, NORTH, SOUTH};
    int i = 0;
    while(dir) {
        if (dir & 1) {
            struct Cell* neighbour = cell + dirs[i];
            neighbour->adjacents |= opp[i];
        }
        dir >>= 1;
        i++;
    }
}

int choose_path(int adjacents) {
    int dirs = ALL - adjacents;
    if (!dirs) return 0;

    int n = 0, bit = 1;
    for (int i=0; i<4; i++, bit<<=1) {
        if(dirs & bit) n++;
    }
    int r = random(n);

    bit = 1;
    for (int i=0; i<4; i++, bit<<=1) {
        if (dirs & bit && --r < 0) return bit;
    }

    return 0;   //Should never be reached
}


void gen_path(struct Grid* grid, struct Cell* from) {
    /*
    Generates the maze following the Origin Shift algorithm. Refer to the head comment for more informations.
    The ending cell is currently defined as the bottom-right cell.
    */
    struct Stack stack = stack_init();
    from = init_start(grid);
    int size = grid->height * grid->width;

    struct Cell* to;
    int visited = 1, dir;

    while (visited < size) {
        dir = choose_path(from->adjacents);
        if (!dir) {
            dir = stack_pop(&stack);
            from = get_cell(grid, from, opposite(dir));
        } else {
            stack_push(&stack, dir);
            to = get_cell(grid, from, dir);
            connect_cells(from, to, dir);
            update_neighbours(grid, to);
            from = to;
            visited++;
        }
    }

    grid->end = &grid->cells[size-1];
}

struct Cell* get_cell(struct Grid* grid, struct Cell* cell, int dir) {
    int i = cell - grid->cells;
    int x = i % grid->width;
    int y = i / grid->width;

    if (dir == WEST  && x > 0)              return cell - 1;
    if (dir == EAST  && x < grid->width-1)  return cell + 1;
    if (dir == NORTH && y > 0)              return cell - grid->width;
    if (dir == SOUTH && y < grid->height-1) return cell + grid->width;

    return NULL; // out of bounds
}

void connect_cells(struct Cell* from, struct Cell* to, int dir) {
    from->adjacents |= dir;
    from->connections |= dir;
    to->connections |= opposite(dir);
    to->type = GENERATED;
}

