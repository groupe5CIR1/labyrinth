#include "main.h"



int main(void) {
    srand(time(NULL));
}


int random(int n) {
    return rand()%n;
}