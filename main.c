#include <stdlib.h>
#include <time.h>

struct Cell {
    struct Cell* adjacent_cells[4];
};

struct Grid {
    struct Cell** cells;
    int width;
    int height;
};

enum Direction {
    NORTH,
    SOUTH,
    WEST,
    EAST
};


int main(void) {
    // Initialisation avec une graine dépendant du temps.
    srand(time(NULL));
    printf("%d", rand() % 100); // Nombre aléatoire entre 0 et 99.
}
