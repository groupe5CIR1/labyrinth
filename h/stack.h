#ifndef STACK
#define STACK


#include <stdio.h>
#include <stdlib.h>


struct Stack {
    int* list;
    int size;
    int capacity;
};



struct Stack stack_init();
void stack_destroy(struct Stack* stack);
void stack_push(struct Stack* stack, int data);
int stack_pop(struct Stack* stack);


#endif