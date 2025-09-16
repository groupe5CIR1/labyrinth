/*
Main logic for the Maze rendering.
The Maze is a m*n grid of cells.
Each cell is surrounded by walls with the characters _ and |. Those walls are defined by the (connections) variable of each cell.
Eachc cell content is defined by its (type) variable from the enum Type :
- VOID and GENERATED should be empty
- VISITED should contain the character O
- START and END should contain the character X
*/

#include "h/render.h"