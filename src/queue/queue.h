#ifndef QUEUE_H
#define QUEUE_H

#include "../graph/graph.h"  // for Arc definition

typedef struct {
    Arc* arcs;
    int front;
    int rear;
    int capacity;
    int size;
} Queue;

Queue* create_arc_queue(int capacity);
void destroy_arc_queue(Queue* queue);
bool is_empty(Queue* queue);
bool enqueue(Queue* queue, Arc arc);
bool dequeue(Queue* queue, Arc* out);

#endif