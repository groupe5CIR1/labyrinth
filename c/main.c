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

    srand(time(NULL));

    struct Grid grid = init_grid(width, height);
    gen_path(&grid, &grid.cells);

    render(grid);


    char* input;
    printf("\n",
        "Please choose a mode :\n",
        "- play : PLAY\n",
        "- solve : SOLVE\n"
    );
    scanf("%s", input);
    if (strcmp("PLAY", input) == 0) {
        play(&grid);
    }
    if (strcmp("SOLVE", input) == 0) {

    }

    return 0;
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


