#include "queue.h"

Queue* create_arc_queue(int capacity) {
    Queue* queue = malloc(sizeof(Queue));
    if (queue == NULL) {
        return NULL; 
    }

    queue->arcs = malloc(capacity * sizeof(Arc));
    if (queue->arcs == NULL) {
        free(queue);
        return NULL;
    }
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;

    return queue;
}

void destroy_arc_queue(Queue* queue) {
    if (queue != NULL) {
        if (queue->arcs != NULL) {
            free(queue->arcs);
        }
        free(queue);
    }
}

bool is_empty(Queue* queue) {
    if (queue == NULL) return false;

    return queue->size == 0;
}

bool enqueue(Queue* queue, Arc arc) {
    if (queue == NULL) return false;

    if (queue->size == queue->capacity) {
        return false;
    }

    queue->size++;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arcs[queue->rear] = arc;
    return true;
}

bool dequeue(Queue* queue, Arc* out) {
    if (queue == NULL) return false;

    if (queue->size == 0) {
        return false;
    }

    *out = queue->arcs[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return true;
}
