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
#include"h/main.h"

char cell_char(int type) {
    switch (type) {
        case VISITED:   return 'O';
        case START:     return 'X';
        case END:       return 'X';
        default:        return ' ';
    }
}

void render_grid(struct Grid grid){
    for(int i=0; i<grid.width; i++){
        printf("__");
    }
    printf("\n");
    for(int i = 0; i<grid.height*grid.width; i++){
        printf("|");
            struct Cell cell = grid.cells[i];
            printf("%c", cell_char(cell.type));
            switch(cell.connections){
                case 2: printf("");
                case 4: printf("");
                case 6: printf("");
                default: printf("__|");
        }
        if(i%grid.width == 0 && i!=0)
        printf("\n");
    }
}