#ifndef RENDER
#define RENDER

#include "h/main.h"

#include <string.h>


char* cell_type(struct Grid grid, int type, int i);
void horizontal_border(int n);
void render(struct Grid grid);

#endif