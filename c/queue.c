#include "h/queue.h"



struct Queue* create_queue(int initial_capacity) {
    struct Queue* queue = malloc(sizeof(struct Queue));
    queue->array = malloc(initial_capacity * sizeof(int));
    queue->front = 0;
    queue->size = 0;
    queue->capacity = initial_capacity;
    return queue;
}

void queue_push(struct Queue* queue, int value) {
    // Resize if needed
    if (queue->size == queue->capacity) {
        queue->capacity *= 2;
        queue->array = realloc(queue->array, queue->capacity * sizeof(int));
    }
    
    int rear = (queue->front + queue->size) % queue->capacity;
    queue->array[rear] = value;
    queue->size++;
}

void free_queue(struct Queue* q) {
    free(q->array);
    free(q);
}