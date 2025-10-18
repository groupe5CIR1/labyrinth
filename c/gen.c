/*
Logic behind the Maze generation, following the Origin Shift (tree chain) algorithm.
The Maze is a m*n grid of cells.
Each cell contains 3 values :
- (int) adjacents → bitmask of (enum)Directions, indicating which cells around itself have already been generated
- (int) connections → bitmask of (enum)Directions, indicating its connections to other cells
- (int) type → indicates the type of the cell (mostly used for rendering, refer to render.c for more informations)
Those values should be updated during Maze generation each time a new cell is generated, using update_neighbours().
The generation uses a stack to be able to "undo" a "move", i.e. coming back to the previous cell (refer to stack.c for more informations).
The player can choose where the ending cell should be generated, the default being bottom right (refer to gen_deadend_end_cell() for more informations).
*/


#include "../h/gen.h"



struct Grid init_grid(int width, int height) {
    struct Cell* grid = malloc(width * height * sizeof(struct Cell));
    if (grid == NULL) {
        perror("Out of Memory error: could not allocate grid\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<width*height; i++) {
        int x = i % width;
        int y = i / width;
        grid[i] = init_cell(x, y, width, height);
    }
    return (struct Grid) {.cells = grid, .height = height, .width = width, .end = NULL};
}

struct Cell init_cell(int x, int y, int width, int height) {
    /*
    Upon being initialized, cells consider boundaries as adjacent generated cells.
    */
    int adjacents =
        (x == 0 ?           WEST : 0)  |
        (x == width-1 ?     EAST : 0)  |
        (y == 0 ?           NORTH : 0) |
        (y == height-1 ?    SOUTH : 0);

    return (struct Cell) {.adjacents = adjacents, .connections = 0, .type = VOID};
}

struct Cell* init_start(struct Grid* grid) {
    /*
    By default, the starting cell is on top left (first cell).
    */
    struct Cell* start = grid->cells;
    start->type = VISITED;
    start->adjacents = NORTH + WEST;
    update_neighbours(grid, start);
    return start;
}

void update_neighbours(struct Grid* grid, struct Cell* cell) {
    /*
    Updates the (int)adjacent value of each surrounding cell.
    Called upon cell generation.
    */
    for (int dir=1; dir<ALL; dir<<=1) {
        struct Cell* neighbour = get_cell(grid, cell, dir);
        if (neighbour) neighbour->adjacents |= opposite(dir);
    }
}

void connect_cells(struct Cell* from, struct Cell* to, int dir) {
    from->adjacents |= dir;
    from->connections |= dir;
    to->connections |= opposite(dir);
    to->adjacents |= opposite(dir);
    to->type = GENERATED;
}

int choose_path(int adjacents) {
    /*
    This function takes the (int)adjacents value of a cell (= all of the generated directions), and chooses randomly a direction that isn't in (int)adjacents.
    More specifically, during generation of the maze, the current cell must choose an adjacent cell that isn't alerady generated, to continue the generation process.
    If no valid cell has been found (every adjacent cell has been generated <=> (int)adjacents == ALL), the function should return NONE.
    The idea behind this algorithm is to iterate through each bit of the non-generated directions to know how many directions are available, and choose a random bit among them.
    */
    if (adjacents == ALL) return NONE;
    int dirs = ALL - adjacents;
    int r = rand_int(bitcount(dirs));
    for (int dir=1; dir<ALL; dir<<=1) {
        if (dirs & dir && --r < 0) return dir;
    }
    return NONE;   //Should never be reached
}

struct Cell* get_last_available_cell(struct Grid* grid, struct Cell* cell, struct Stack* stack) {
    /*
    Finds the last cell of the (struct Stack*)stack that isn't surrounded by generated cells (i.e. its (int)adjacent value isn't ALL).
    */
    while(cell->adjacents == ALL) {
        cell = get_cell(grid, cell, opposite(stack_pop(stack)));
    }
    return cell;
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
            from = get_last_available_cell(grid, from, &stack);
        } else {
            stack_push(&stack, dir);
            to = get_cell(grid, from, dir);
            connect_cells(from, to, dir);
            update_neighbours(grid, to);
            from = to;
            visited++;
        }
    }
    stack_destroy(&stack);
}


int get_end_cell_method() {
    char input[8];
    int method;
    bool valid_method = false;
    while (!valid_method) {
        printf(
            "\n"
            "Choose an end cell generation method :\n"
            "- bottom-right cell : DEFAULT\n"
            "- random dead-end : RANDOM\n"
            "- info : INFO\n"
            "- quit : QUIT\n"
        );
        scanf("%7s",input);
        to_uppercase(input);
        if (strcmp(input, "QUIT") == 0) {
            printf("Exiting game...\n");
            valid_method = true;
            method = -1;
        }
        else if (strcmp(input, "INFO") == 0) {
            printf(
                "\n"
                "- DEFAULT : generates the ending cell at the bottom-right corner of the Maze\n"
                "- RANDOM : generates the ending cell at a random dead end of the maze, with a bias (quadratic) towards the bottom right cell\n"
            );
        }
        else if (strcmp(input, "DEFAULT") == 0) {
            valid_method = true;
            method = DEFAULT;
        }
        else if (strcmp(input, "RANDOM") == 0) {
            valid_method = true;
            method = RANDOM;
        }
        else {
            printf("Invalid input !\n");
        }
    }
    return method;
}

void gen_end_cell(struct Grid* grid, int method) {
    int size = grid->height * grid->width;
    switch (method) {
    case DEFAULT :
        grid->end = &grid->cells[size-1];
        break;
    case RANDOM :
        gen_deadend_end_cell(grid);
        break;
    default :
        grid->end = &grid->cells[size-1];
        break;
    }
}

void gen_deadend_end_cell(struct Grid* grid) {
    /*
    This function randomly generates the ending cell of the grid, with a quadratic bias towards the furthest cells.
    The idea is to store all of the dead end cells (only one connection) in an array, and randomly iterate through the array.
    At each iteration, the cell's manhattan distance is calculated, and a quadratic function is applied accordingly.
    This quadratic function ensures that the further the cell is, the more chances it has to be chosen, until reaching 100% for the very furthest cells.
    If no dead end has been chosen (very unlikely), a random one is chosen instead (no bias).
    */
    int size = grid->height * grid->width;
    int max_dist = (grid->width - 1) + (grid->height - 1);
    int* dead_ends = malloc(size * sizeof(int));
    if (!dead_ends) {
        perror("Out Of Memory error : could not allocate corner cells.\n");
        exit(EXIT_FAILURE);
    }
    int n=0;
    printf("Finding dead ends...\n");
    for (int i=1; i<size; i++) {
        if (bitcount(grid->cells[i].connections) == 1) {
            dead_ends[n] = i;
            n++;
        }
    }
    int r, i, manhattan_distance, weight;
    while (!grid->end && n>0) {
        r = rand_int(n);
        i = dead_ends[r];
        manhattan_distance = i % grid->width + i / grid->width;
        weight = (int)(max_dist * max_dist * 2 / (manhattan_distance * manhattan_distance + 1));
        if (rand_int(weight) <= 1) {
            grid->end = &grid->cells[i];
        }
        else {
            for (int j=r; j<n-1; j++) {
                dead_ends[j] = dead_ends[j+1];
            }
            n--;
        }
    }
    if (!grid->end) {
        printf("Failed to generate end cell with quadratic bias. Generating randomly...\n");
        grid->end = &grid->cells[dead_ends[0]];
    }
    free(dead_ends);
}

