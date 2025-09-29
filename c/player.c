/*

*/



#include "h/player.h"
#include "h/main.h"

unsigned int height;
unsigned int width;

//+function to check if you're not going out of limits

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


