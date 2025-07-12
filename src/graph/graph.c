#include <graph.h>

Graph* create_graph(void) {
    // Allocate memory for the graph
    Graph* graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        return NULL;  // Memory allocation failed
    }

    graph->vertex_count = TOTAL_CELLS;

    for (int i = 0; i < TOTAL_CELLS; i++) {
        int row, col;
        get_row_col(i, &row, &col);
        initialize_vertex(&graph->vertices[i], row, col);
    }

    return graph;
}

void destroy_graph(Graph* graph) {
    if (graph != NULL) {
        free(graph);
    }
}

void initialize_vertex(Vertex* vertex, int row, int col) {
    vertex->row = row;
    vertex->col = col;
    vertex->box = get_box_num(row, col);

    vertex->value = 0;

    for (int i = 0; i < 9; i++) {
        vertex->possible[i] = true;
    }

    vertex->neighbor_count = 0;
}

void add_edge(Graph* graph, int v1, int v2) {
    Vertex* vertex1 = &graph->vertices[v1];
    Vertex* vertex2 = &graph->vertices[v2];

    vertex1->neighbors[vertex1->neighbor_count++] = v2;
    vertex2->neighbors[vertex2->neighbor_count++] = v1;
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
    // Your implementation here
}

void build_sudoku_edges(Graph* graph) {
    // Implementation here
}

int get_box_num(int row, int col) {
    // Your implementation from earlier
}
