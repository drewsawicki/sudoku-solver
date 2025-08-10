#ifndef SUDOKU_H
#define SUDOKU_H

#include "../queue/queue.h"
#include <stdbool.h>

#define FULL_DOMAIN 0x1FF
#define DIGIT_TO_BIT(d) (1 << ((d) - 1))
#define MAX_QUEUE_SIZE 1000

// Domain utilities
bool is_singleton(unsigned short domain);
int domain_to_value(unsigned short domain);
int domain_count(unsigned short domain);
void enqueue_neighbors(Vertex* vertex, Queue* queue);
void remove_val_from_domain(Vertex* vertex, int value);

// AC-3 solver
bool ac3_solve(Graph* graph);
bool revise(Graph* graph, int vertex1, int vertex2);

// Utilities
void print_domains(Graph* g);
void is_solved(Graph* g);

#endif // SUDOKU_H
