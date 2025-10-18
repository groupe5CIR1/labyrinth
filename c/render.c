/*
Main logic for the Maze rendering.
The Maze is a m*n continuous grid of cells (i.e. one continuous array, but represented as a grid).
Each cell is surrounded by walls with the characters --- and |. Those walls are defined by the (connections) value of each cell.
Each cell content is defined by its (int)type value from the enum Type :
- VOID and GENERATED should be empty
- AVAILABLE should contain the character •
- VISITED should contain the character O
- exceptions : the starting and ending cells should contain the character X

An example of how the Maze should be rendered :

+---+---+---+---+---+---+---+---+
| X |       |   |       |       |
+   +---+   +   +---+   +---+   +
| O | O   O   O |       |       |
+   +   +---+   +   +---+   +---+
| O   O |     O   O   O     |   |
+---+---+   +---+---+   +---+   +
|       |   |       | O   O |   |
+   +---+---+---+   +---+   +   +
|       |       |       | O   O |
+   +---+---+   +---+   +---+   +
|           |   | O   O   O   O |
+---+   +---+   +   +---+---+---+
|       |     •   O |       |   |
+   +---+   +---+   +---+   +   +
|               | •           X |
+---+---+---+---+---+---+---+---+

Notes :
- This maze is only an example for the rendering, this maze cannot be generated with the Origin Shift algorithm.
- the starting and ending cells are fixed, meaning that they should always render as an X (i.e. their (int)type should not override the rendering)
*/



#include "../h/render.h"

void clear_grid_type(struct Grid* grid) {
    for (int i=1; i < grid->height * grid->width; i++) {
        grid->cells[i].type = GENERATED;
    }
    grid->cells->type = VISITED;
}

char* cell_type(struct Grid grid, int type, int i) {
    if (i == 0 || &grid.cells[i] == grid.end) return " X ";      //Checks for starting and ending cells
    switch (type) {
        case VOID:      return "   ";
        case GENERATED: return "   ";
        case AVAILABLE: return " • ";
        case VISITED:   return " O ";
        default:        return "   ";
    }
}

void horizontal_border(int n) {
    for (; n>0; n--) {
        printf("+---");
    }
    printf("+\n");
}

void render(struct Grid grid) {
    horizontal_border(grid.width);

    struct Cell cell;
    int size = 4*grid.width+2;

    char* line = malloc(size);
    char* below = malloc(size);
    if (line == NULL || below == NULL) {
        printf("Out of Memory error : could not render the grid\n");
        exit(EXIT_FAILURE);
    }

    strcpy(line,"|");
    strcpy(below,"+");

    for (int i=0; i<(grid.width*grid.height); i++) {
        cell = grid.cells[i];

        strcat(line, cell_type(grid, cell.type, i));
        strcat(line, (cell.connections & EAST) ? " " : "|");

        strcat(below, (cell.connections & SOUTH) ? "   +" : "---+");

        if (i%grid.width == grid.width-1) {
            printf("%s\n",line);
            printf("%s\n",below);

            strcpy(line,"|");
            strcpy(below,"+");
        }
    }
    free(line);
    free(below);
}




