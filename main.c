#include "main.h"



int main(void) {
    // Initialisation avec une graine dépendant du temps.
    srand(time(NULL));
    printf("%d", rand() % 100); // Nombre aléatoire entre 0 et 99.
}


