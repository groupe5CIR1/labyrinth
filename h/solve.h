#ifndef SOLVE
#define SOLVE


#include "../h/main.h"
#include "../h/queue.h"
#include "../h/stack.h"

#include <string.h>

enum SOLVE_METHOD {
    DFS,
    RHM,
    A_STAR
};


int get_solve_method();
void solve(struct Grid* grid, int method);
void solve_dfs(struct Grid* grid);
void solve_rhm(struct Grid* grid);
void solve_a_star(struct Grid* grid);


#endif