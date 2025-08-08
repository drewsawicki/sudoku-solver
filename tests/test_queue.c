#include <stdio.h>
#include <assert.h>
#include "../src/queue/queue.h"

Arc make_arc(int from, int to) {
    Arc arc;
    arc.from_vertex = from;
    arc.to_vertex = to;
    return arc;
}

void test_create_destroy() {
    Queue* queue = create_arc_queue(10);
    assert(queue != NULL);
    assert(queue->capacity == 10);
    assert(queue->size == 0);
    assert(queue->front == 0);
    assert(queue->rear == -1);

    destroy_arc_queue(queue);
    printf("test_create_destroy passed.\n");
}

void test_enqueue_dequeue() {
    Queue* queue = create_arc_queue(3);
    assert(queue != NULL);

    Arc a1 = make_arc(0, 1);
    Arc a2 = make_arc(1, 2);
    Arc a3 = make_arc(2, 3);

    assert(enqueue(queue, a1));
    assert(enqueue(queue, a2));
    assert(enqueue(queue, a3));
    assert(!enqueue(queue, make_arc(3, 4))); 

    Arc out;
    assert(dequeue(queue, &out));
    assert(out.from_vertex == 0 && out.to_vertex == 1);

    assert(dequeue(queue, &out));
    assert(out.from_vertex == 1 && out.to_vertex == 2);

    assert(dequeue(queue, &out));
    assert(out.from_vertex == 2 && out.to_vertex == 3);

    assert(!dequeue(queue, &out));

    destroy_arc_queue(queue);
    printf("test_enqueue_dequeue passed.\n");
}

void test_wraparound() {
    Queue* queue = create_arc_queue(2);
    assert(queue != NULL);

    Arc a1 = make_arc(5, 6);
    Arc a2 = make_arc(7, 8);

    assert(enqueue(queue, a1));
    assert(enqueue(queue, a2));
    assert(!enqueue(queue, make_arc(9, 10))); 

    Arc out;
    assert(dequeue(queue, &out));
    assert(out.from_vertex == 5 && out.to_vertex == 6);

    assert(enqueue(queue, make_arc(11, 12)));
    assert(dequeue(queue, &out));
    assert(out.from_vertex == 7 && out.to_vertex == 8);

    assert(dequeue(queue, &out));
    assert(out.from_vertex == 11 && out.to_vertex == 12);

    destroy_arc_queue(queue);
    printf("test_wraparound passed.\n");
}

void test_is_empty() {
    Queue* queue = create_arc_queue(1);
    assert(queue != NULL);
    assert(is_empty(queue));

    Arc arc = make_arc(1, 2);
    assert(enqueue(queue, arc));
    assert(!is_empty(queue));

    Arc out;
    assert(dequeue(queue, &out));
    assert(is_empty(queue));

    destroy_arc_queue(queue);
    printf("test_is_empty passed.\n");
}

int main() {
    test_create_destroy();
    test_enqueue_dequeue();
    test_wraparound();
    test_is_empty();

 printf("All queue tests passed!\n");
    return 0;
}