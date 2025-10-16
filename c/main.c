#include "../h/main.h"
#include "../h/gen.h"
#include "../h/render.h"
#include "../h/solve.h"
#include "../h/player.h"




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
    gen_path(&grid, grid.cells);

    render(grid);

    struct Cell* player = grid.cells;

    char input[6];
    bool valid_input = false;
    while (!valid_input) {
        printf(
            "\n"
            "Please choose a mode :\n"
            "- play : PLAY\n"
            "- solve : SOLVE\n"
            "- quit : QUIT\n"
        );
        scanf("%5s", input);

        if (strcmp("PLAY", input) == 0) {
            valid_input = play(&grid, &player) == 0;
        }
        else if (strcmp("SOLVE", input) == 0) {
            int method = get_solve_method();
            if (method == -1) {
                valid_input = false;
            }
            else {
                valid_input = true;
                clear_grid_type(&grid);
                printf("Solving maze...\n");
                solve(&grid, method);
                render(grid);
            }
        }
        else if (strcmp("QUIT", input) == 0) {
            valid_input = true;
            printf("Exiting...\n");
        }
        else {
            printf("Invalid input !\n");
        }
    }

    free(grid.cells);
    return 0;
}




int rand_int(int n) {
    return (int)rand()%n;
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

