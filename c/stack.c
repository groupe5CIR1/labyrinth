/*
Stack implementation for Maze generation, allowing to "undo" a "move", i.e. coming back to the previously generated cell.
The stack consists of a list of (int) directions from the enum Direction.
The stack should always be freed after generation.
*/

#include "../h/stack.h"



struct Stack stack_init() {
    int* list = malloc(2*sizeof(int));
    if (list == NULL ) {
        perror("Out Of Memory error: could not create Stack");
        exit(EXIT_FAILURE);
    }
    return (struct Stack) {.list = list, .size = 0, .capacity = 2};
}

void stack_destroy(struct Stack* stack) {
    free(stack->list);
    stack->size = 0;
    stack->capacity = 0;
    stack->list = NULL;
}

void stack_push(struct Stack* stack, int data) {
    if (stack->size >= stack->capacity) {
        int new_capacity = 2*stack->capacity;
        int* new_list = realloc(stack->list, new_capacity*sizeof(int));
        if (new_list == NULL) {
            perror("Out Of Memory error: could not resize Stack\n");
            exit(EXIT_FAILURE);
        }
        stack->list = new_list;
        stack->capacity = new_capacity;
    }

    stack->list[stack->size] = data;
    stack->size++;
}

int stack_pop(struct Stack* stack) {
    if (stack->size == 0) {
        perror("Stack underflow error: could not pop element in Stack\n");
        exit(EXIT_FAILURE);
    }
    int last = stack->list[stack->size-1];
    stack->size--;
    return last;
}

