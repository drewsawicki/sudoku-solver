#include <assert.h>
#include <stdio.h>
#include "../src/graph/graph.h"

void test_get_vertex_index_and_row_col() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int index = get_vertex_index(row, col);
            int test_row, test_col;
            get_row_col(index, &test_row, &test_col);
            assert(test_row == row);
            assert(test_col == col);
        }
    }
    printf("PASS: get_vertex_index and get_row_col\n");
}

void test_get_box_num() {
    assert(get_box_num(0, 0) == 0);
    assert(get_box_num(4, 4) == 4);
    assert(get_box_num(8, 8) == 8);
    assert(get_box_num(3, 7) == 5);
    printf("PASS: get_box_num\n");
}

void test_initialize_vertex() {
    Vertex v;
    initialize_vertex(&v, 2, 3, 0);
    assert(v.row == 2);
    assert(v.col == 3);
    assert(v.box == get_box_num(2, 3));
    assert(v.domain == FULL_DOMAIN);
    assert(v.value == 0);
    assert(v.neighbor_count == 0);

    initialize_vertex(&v, 2, 3, 5);
    assert(v.domain == 1 << (5 - 1));
    printf("PASS: initialize_vertex\n");
}

void test_create_graph() {
    int puzzle[81] = {0};
    puzzle[0] = 5;
    puzzle[80] = 9;

    Graph* g = create_graph(puzzle);
    assert(g != NULL);
    assert(g->vertex_count == 81);

    assert(g->vertices[0].value == 5);
    assert(g->vertices[0].domain == (1 << 4));

    assert(g->vertices[80].value == 9);
    assert(g->vertices[80].domain == (1 << 8));

    assert(g->vertices[1].value == 0);
    assert(g->vertices[1].domain == FULL_DOMAIN);

    destroy_graph(g);
    printf("PASS: create_graph\n");
}

void test_add_edge_and_are_neighbors() {
    int puzzle[81] = {0};
    Graph* g = create_graph(puzzle);

    assert(are_neighbors(g, 0, 1));
    assert(are_neighbors(g, 1, 0));
    assert(!are_neighbors(g, 0, 12));

    destroy_graph(g);
    printf("PASS: add_edge and are_neighbors\n");
}

int main() {
    test_get_vertex_index_and_row_col();
    test_get_box_num();
    test_initialize_vertex();
    test_create_graph();
    test_add_edge_and_are_neighbors();

    printf("All graph tests passed!\n");
    return 0;
}
