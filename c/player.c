/*
Logic behind the player movements in the Maze.
The player should be able to continue playing after coming back to the mode menu.
Each time the player moves to a cell, the surrounding cells' type should be updated to show where the player is allowed to go.
The player's path should also be shown by updating the cells' type, and is stored in a (struct Stack*)stack.
*/



#include "../h/player.h"
#include "../h/render.h"



int player_input() {
    char input[5];

    printf("Enter move : ");
    scanf("%4s",input);
    to_uppercase(input);

    if (strcmp(input, "Z") == 0)    return NORTH;
    if (strcmp(input, "Q") == 0)    return WEST;
    if (strcmp(input, "S") == 0)    return SOUTH;
    if (strcmp(input, "D") == 0)    return EAST;
    if (strcmp(input, "BACK") == 0) return ALL;
    return NONE;
}

int input_checks(int connections) {
    int dir;
    bool bl;
    do {
        dir = player_input();
        if (dir == ALL)  {
            printf("Exiting the game...\n");
            return -1;
        }
        bl = dir && (connections & dir);
        if (!bl) {
            printf("Invalid input. Please use the following inputs :\n");
            if (connections & NORTH)  printf("- go NORTH : Z\n");
            if (connections & WEST)   printf("- go WEST : Q\n");
            if (connections & SOUTH)  printf("- go SOUTH : S\n");
            if (connections & EAST)   printf("- go EAST : D\n");
            printf("- go back to mode choice : BACK\n");
        }
    } while (!bl);
    return dir;
}

void update_neighbours_type(struct Grid* grid, struct Cell* cell, bool remove) {
    /*
    Updates neighbouring cells' type upon a player move.
    More specifically, each neighbouring cell will update its type depending on whether the move is forward or backward.
    This is used specifically for rendering purposes, see render.c for more informations.
    */
    struct Cell* neighbour;
    if (!remove) cell->type = VISITED;
    for (int d=WEST; d<ALL; d<<=1) {
        if (cell->connections & d) {
            neighbour = get_cell(grid, cell, d);
            if (neighbour->type != VISITED) {
                neighbour->type = remove ? GENERATED : AVAILABLE;
            }
        }
    }
}

int play(struct Grid* grid, struct Cell** cell) {
    /*
    Allows the player to move in the maze.
    Returns :
    - (0) : the game is completed.
    - (-1) : stop playing.
    */
    update_neighbours_type(grid, *cell, false);
    render(*grid);
    struct Stack stack = stack_init();
    int dir;
    bool first_move = true;
    while(*cell != grid->end) {
        dir = input_checks((*cell)->connections);
        if (dir == -1) return -1;

        if (!first_move && (dir == opposite(stack.list[stack.size-1]))) {
            stack_pop(&stack);
            (*cell)->type = AVAILABLE;
        } else {
            first_move = false;
            stack_push(&stack, dir);
        }
        update_neighbours_type(grid, *cell, true);
        (*cell) = get_cell(grid, *cell, dir);
        update_neighbours_type(grid, *cell, false);

        render(*grid);
    }
    printf("Congratulations ! You have completed the Maze !\n");
    return 0;
}

