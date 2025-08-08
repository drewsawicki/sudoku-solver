#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Constants
#define SUDOKU_SIZE 9
#define TOTAL_CELLS 81
#define MAX_NEIGHBORS 20
#define FULL_DOMAIN 0x1FF

typedef struct {
    int from_vertex;
    int to_vertex;
} Arc;

// Vertex structure - represents one cell in the Sudoku grid
typedef struct {
    // Position information
    int row;        // 0-8 for the 9 rows
    int col;        // 0-8 for the 9 columns
    int box;        // 0-8 for the 9 3x3 boxes (calculated as (row/3)*3 + col/3)
    
    // Value information
    int value;      // 0 = empty, 1-9 = filled with that digit
    unsigned short domain; // Possible values, updated via bitmask
    
    // Graph connectivity
    int neighbors[MAX_NEIGHBORS];  // Array of indices of connected vertices
    int neighbor_count;            // Actual number of neighbors (should always be 20)
} Vertex;

// Graph structure - represents the entire Sudoku as a graph
typedef struct {
    Vertex vertices[TOTAL_CELLS];  // All 81 cells
    int vertex_count;              // Should always be 81
} Graph;

// Function declarations
Graph* create_graph(const int puzzle[81]);
void destroy_graph(Graph* graph);
void initialize_vertex(Vertex* vertex, int row, int col, int value);
bool are_neighbors(Graph* graph, int vertex1, int vertex2);
int get_vertex_index(int row, int col);
void get_row_col(int index, int* row, int* col);
void build_sudoku_edges(Graph* graph);
bool cells_conflict(int row1, int col1, int row2, int col2);
int get_box_num(int row, int col);
int get_domain_from_value(int value);

#endif // GRAPH_H