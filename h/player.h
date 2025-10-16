#ifndef PLAYER
#define PLAYER

#include "../h/main.h"
#include "../h/gen.h"

#include <string.h>


int player_input();
int input_checks(int connections);
void update_neighbours_type(struct Grid* grid, struct Cell* cell, bool remove);
int play(struct Grid* grid, struct Cell** player);


#endif