/*

*/


#include "../h/solve.h"
#include <time.h>

int get_solve_method() {
    char solve_input[5];
    int method = -1;
    bool valid_method = false;
    while (!valid_method) {
        printf(
            "\n"
            "Choose a solving method : \n"
            "- Depth First Search : DFS\n"
            "- Right-Hand Method : RHM\n"
            "- A* : A*\n"
            "- go back to mode choice : BACK\n"
        );
        scanf("%4s", solve_input);

        if (strcmp("BACK", solve_input) == 0) {
            printf("Going back to mode choice...\n");
            valid_method = true;
        }
        else if (strcmp("DFS", solve_input) == 0) {
            valid_method = true;
            method = DFS;
        }
        else if (strcmp("RHM", solve_input) == 0) {
            valid_method = true;
            method = RHM;
        }
        else if (strcmp("A*", solve_input) == 0) {
            valid_method = true;
            method = A_STAR;
        }
        else {
            printf("Invalid input !\n");
        }
    }
    return method;
}

void solve(struct Grid* grid, int method) {
    switch (method) {
    case DFS:
        solve_dfs(grid);
        break;
    case RHM:
        solve_rhm(grid);
        break;
    case A_STAR:
        solve_a_star(grid);
        break;
    default:
        printf("Invalid method !\nExiting...\n");
        break;
    }
}


void solve_dfs(struct Grid* grid) {
    int n = grid->width * grid->height;

    int* visited = malloc(n * sizeof(int));
    int* parent  = malloc(n * sizeof(int));
    if (!visited || !parent) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i]  = -1;
    }

    int start_idx = 0;
    int end_idx   = n - 1;

    struct Queue* q = create_queue(64);
    queue_push(q, start_idx);
    visited[start_idx] = 1;

    while (q->size > 0) {
        int cur = queue_pop(q);
        if (cur == end_idx) break;

        struct Cell* cell = &grid->cells[cur];
        int x = cur % grid->width;
        int y = cur / grid->width;

        struct { int dir, dx, dy; } moves[4] = {
            {WEST,  -1,  0},
            {EAST,   1,  0},
            {SOUTH,  0,  1},
            {NORTH,  0, -1}
        };

        for (int i = 0; i < 4; i++) {
            if (cell->connections & moves[i].dir) {
                int nx = x + moves[i].dx;
                int ny = y + moves[i].dy;
                if (nx < 0 || nx >= grid->width || ny < 0 || ny >= grid->height) continue;
                int next = ny * grid->width + nx;
                if (!visited[next]) {
                    visited[next] = 1;
                    parent[next]  = cur;
                    queue_push(q, next);
                }
            }
        }
    }

    // Mark path
    for (int p = end_idx; p != -1; p = parent[p]) {
        if (grid->cells[p].type == GENERATED)
            grid->cells[p].type = VISITED;
    }

    free_queue(q);
    free(visited);
    free(parent);
}


void solve_rhm(struct Grid* grid) {
    /*
    The Right-Hand Method is an algorithm that only works for perfect mazes. It works by always keeping the right hand (also works with the left hand) on a wall, i.e. always go right. Because the maze is perfect (no loop), this algorithm ensures that every cell is checked until the end is found.
    This implementation tracks the right-hand orientation in (int)facing.
    The starting orientation should be SOUTH, because the starting position is the top-left corner of the maze.
    The idea is to check the cell on the right, and keep turning left as long as no valid cell has been found.
    If no valid cell has been found (dead end), turn back to the previous cell, and repeat the aglorithm.
    The resulting path is stored in (struct Stack)stack, and each cell type along that path is modified for rendering purposes.
    For now, the (struct Stack)stack is freed at the end of the algorithm, as there is no use for it.
    */
    struct Stack stack = stack_init();
    struct Cell* cell = grid->cells;
    struct Cell* neighbour;
    int dirs[] = {SOUTH, WEST, NORTH, EAST};
    int facing = 0;
    while (cell != grid->end) {
        neighbour = get_cell(grid, cell, dirs[facing]);
        if (!neighbour || !(cell->connections & dirs[facing])) {
            facing = (facing + 3) % 4;      //decrement facing index = rotate to the left
        }
        else {
            if (stack.list[stack.size-1] == opposite(dirs[facing])) {
                cell->type = GENERATED;
                stack_pop(&stack);
            }
            else {
                cell->type = VISITED;
                stack_push(&stack, dirs[facing]);
            }
            cell = neighbour;
            facing = (facing + 1) % 4;      //increment facing index = rotate to the right
        }
    }
    stack_destroy(&stack);
}


void solve_a_star(struct Grid* grid) {
    (void)grid;     //unused for now
}

