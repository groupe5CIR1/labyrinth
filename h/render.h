#ifndef RENDER
#define RENDER

#include "../h/main.h"

#include <string.h>
#include <stdio.h>

void clear_grid_type(struct Grid* grid);
char* cell_type(struct Grid grid, int type, int i);
void horizontal_border(int n);
void render(struct Grid grid);

#endif