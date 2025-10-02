/*

*/


#include "h/solve.h"



void solve_maze(struct Grid* grid) {
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

