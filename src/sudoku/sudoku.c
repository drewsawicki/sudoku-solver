#include "sudoku.h"

bool is_singleton(unsigned short domain){
    if (domain != 0 && (domain & (domain - 1) == 0)) {
        return true;
    }
    return false;
}

int domain_to_value(unsigned short domain) {
    for (int i = 1; i <= 9; i++) {
        if (domain == DIGIT_TO_BIT(i)) return i;
    }
    return 0;
}

int domain_count(unsigned short domain) {
    int count = 0;
    for (int i = 1; i <= 9; i++) {
        if (domain & DIGIT_TO_BIT(i)) count++;
    }
    return count;
}

void remove_val_from_domain(Vertex* vertex, int value) {
    vertex->domain = (vertex->domain) & (~DIGIT_TO_BIT(value));
}

void enqueue_neighbors(Vertex* vertex, Queue* queue) {
    for (int i = 0; i < vertex->neighbor_count; i++) {
        Arc arc;
        arc.to_vertex = get_vertex_index(vertex->row, vertex->col);
        arc.from_vertex = vertex->neighbors[i];
        if (!enqueue(queue, arc)) {
            fprintf(stderr, "Error: queue overflow in enqueue_neighbors\n");
            exit(EXIT_FAILURE);
        }
    }
}