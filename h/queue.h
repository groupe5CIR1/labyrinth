#ifndef QUEUE
#define QUEUE

#include <stdlib.h>
#include <stdio.h>


struct Queue {
    int* array;        // Dynamic array
    int front;
    int size;
    int capacity;
};


struct Queue* create_queue(int initial_capacity);
void queue_push(struct Queue* queue, int value);
int queue_pop(struct Queue* queue);
void free_queue(struct Queue* q);


#endif