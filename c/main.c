#include "h/main.h"
#include "h/gen.h"
#include "h/render.h"
#include "h/solve.h"
#include "h/player.h"




int main(void) {
    srand(time(NULL));
}




int random(int n) {
    return rand()%n;
}

int opposite(int dir) {
    switch(dir) {
        case WEST: return EAST;
        case EAST: return WEST;
        case NORTH: return SOUTH;
        case SOUTH: return NORTH;
        default: return NONE;
    }
}


