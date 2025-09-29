#ifndef QUEUE
#define QUEUE



struct Queue {
    int* array;        // Dynamic array
    int front;
    int size;
    int capacity;
};


struct Queue* create_queue(int initial_capacity);
void queue_push(struct Queue* queue, int value);
void free_queue(struct Queue* q);


#endif