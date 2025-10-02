/*

*/



#include "h/player.h"



int player_input() {
    char input[8];

    printf("Enter move : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "z") == 0)    return NORTH;
    if (strcmp(input, "q") == 0)    return WEST;
    if (strcmp(input, "s") == 0)    return SOUTH;
    if (strcmp(input, "d") == 0)    return EAST;
    if (strcmp(input, "STOP") == 0) return ALL;
    return NONE;
}

int input_checks(int connections) {
    int dir;
    bool bl;
    do {
        dir = player_input();
        if (dir == ALL)  {
            printf("Exiting the game.\n");
            exit(0);
        }
        bl = dir && (connections & dir);
        if (!bl) {
            printf("Invalid input. Please use the following inputs :\n");
            if (connections & NORTH)  printf("- z : go NORTH\n");
            if (connections & WEST)   printf("- q : go WEST\n");
            if (connections & SOUTH)  printf("- s : go SOUTH\n");
            if (connections & EAST)   printf("- d : go EAST\n");
            printf("- STOP : stop playing the game\n");
        }
    } while (!bl);
    return dir;
}

void update_neighbours_type(struct Grid* grid, struct Cell* cell, bool remove) {
    struct Cell* neighbour;
    cell->type = remove ? AVAILABLE : VISITED;
    for (int d=WEST; d<=NORTH; d<<=1) {
        if (cell->connections & d) {
            neighbour = get_cell(grid, cell, d);
            if (neighbour->type != VISITED) {
                neighbour->type = remove ? GENERATED : AVAILABLE;
            }
        }
    }
}

void play(struct Grid* grid) {
    struct Cell* cell = grid->cells;
    struct Stack stack = stack_init();
    int dir;
    bool first_move = true;
    while(cell != &grid->cells[grid->height*grid->width-1]) {
        dir = input_checks(cell->connections);
        if (!first_move && (dir == opposite(stack.list[stack.size-1]))) {
            stack_pop(&stack);
        } else {
            first_move = false;
            stack_push(&stack, dir);
        }
        update_neighbours_type(grid, cell, true);
        cell = get_cell(grid, cell, dir);
        update_neighbours_type(grid, cell, false);

        render(*grid);
    }
    printf("Congratulations ! You have completed the Maze !\n");
}
































/*
@Deprecated
void update_index(int width ,int connections, int *current_index){
    switch(connections){
        case NORTH: *current_index -= width; break;
        case SOUTH: *current_index += width; break;
        case EAST: *current_index++; break;
        case WEST: *current_index--; break;
    }
}

void move_player(struct Grid* grid, int* player_index, char input) {
    struct Cell* current = &grid->cells[*player_index];

    int dir = NONE;
    switch (tolower(input)) {
        case 'z': dir = NORTH; break;
        case 's': dir = SOUTH; break;
        case 'q': dir = WEST;  break;   
        case 'd': dir = EAST;  break;
        default:
            printf("Invalid input. Use W/A/S/D.\n");
            return;
    }
    if(!((*player_index+1)%grid->width==0 
        || grid->width > *player_index 
        || player_index > grid->width*(grid->height-1) 
        || (*player_index-1)%grid->width 
        || player_index ==0)
    ){
        update_index(grid->width, current->connections, player_index);
    }
    
    }
*/

