#include "graph.h"

Graph* create_graph(const int puzzle[81]) {
    // Allocate memory for the graph
    Graph* graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        return NULL;  // Memory allocation failed
    }

    graph->vertex_count = TOTAL_CELLS;

    for (int i = 0; i < TOTAL_CELLS; i++) {
        int row, col;
        int value = puzzle[i];
        get_row_col(i, &row, &col);
        initialize_vertex(&graph->vertices[i], row, col, value);
    }

    build_sudoku_edges(graph);

    return graph;
}

void destroy_graph(Graph* graph) {
    if (graph != NULL) {
        free(graph);
    }
}

void initialize_vertex(Vertex* vertex, int row, int col, int value) {
    vertex->row = row;
    vertex->col = col;
    vertex->box = get_box_num(row, col);

    vertex->value = value; // 0 represents an empty cell.

    vertex->domain = get_domain_from_value(value);

    vertex->neighbor_count = 0;
}

bool are_neighbors(Graph* graph, int vertex1, int vertex2) {
    Vertex* v1 = &graph->vertices[vertex1];
    
    for (int i = 0; i < v1->neighbor_count; i++) {
        if (v1->neighbors[i] == vertex2) {
            return true;
        }
    }

    return false;
}

int get_vertex_index(int row, int col) {
     return (row * 9) + col;
}

void get_row_col(int index, int* row, int* col) {
    *row = index / 9;
    *col = index % 9;
}

int get_box_num(int row, int col) {
    int box_row = row / 3;
    int box_col = col / 3;
    return (box_row * 3) + box_col;
}

bool cells_conflict(int row1, int col1, int row2, int col2) {
    return (row1 == row2 || col1 == col2 || get_box_num(row1, col1) == get_box_num(row2, col2));
}

int get_domain_from_value(int value) {
    // Create bitmask with either full domain or singular value
    return value == 0 ? FULL_DOMAIN : 1 << (value - 1);
}

void build_sudoku_edges(Graph* graph) {
    Vertex* v1 = &graph->vertices[0];
    Vertex* v2 = &graph->vertices[1];
    for (int i = 0; i < TOTAL_CELLS; i++) {
        for (int j = i+1; j < TOTAL_CELLS; j++) {
            v1 = &graph->vertices[i];
            v2 = &graph->vertices[j];
            if (cells_conflict(v1->row, v1->col, v2->row, v2->col)) {
                v1->neighbors[v1->neighbor_count++] = j;
                v2->neighbors[v2->neighbor_count++] = i;
            }
        }
    }    
}