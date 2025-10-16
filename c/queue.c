#include "../h/queue.h"



struct Queue* create_queue(int initial_capacity) {
    struct Queue* queue = malloc(sizeof(struct Queue));
    if (queue == NULL) {
        printf("Out of Memory error : could not allocate queue structure\n");
        exit(EXIT_FAILURE);
    }
    queue->array = malloc(initial_capacity * sizeof(int));
    if (queue->array == NULL) {
        printf("Out of Memory error : could not allocate queue array\n");
        exit(EXIT_FAILURE);
    }
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
        if (queue->array == NULL) {
            printf("Out of Memory error : could not resize queue\n");
            exit(EXIT_FAILURE);
        }
    }
    
    int rear = (queue->front + queue->size) % queue->capacity;
    queue->array[rear] = value;
    queue->size++;
}

int queue_pop(struct Queue* queue) {
    if (queue->size <= 0) {
        printf("Queue underflow error: could not pop element in Queue\n");
        exit(1);
    }
    int first = queue->array[queue->front];
    queue->front = (queue->front+1)%queue->capacity;
    queue->size--;
    return first;
}

void free_queue(struct Queue* q) {
    free(q->array);
    free(q);
}

