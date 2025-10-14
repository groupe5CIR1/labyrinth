#include "h/main.h"
#include "h/gen.h"
#include "h/render.h"
#include "h/solve.h"
#include "h/player.h"




int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Incorrect syntax, please use the following : ./%s HEIGHT WIDTH\n", argv[0]);
        return 1;
    }

    int height = atoi(argv[1]);
    int width = atoi(argv[2]);
    if (width < 1 && height < 1) {
        printf("Incorrect values, width and height must be positive integers\n");
        return 1;
    }

    struct Grid grid = init_grid(width, height);
    gen_path(&grid, &grid.cells);

    render(grid);

    //completer avec scanf pour choisir le mode (player ou solve, et quelle methode de solve)


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


