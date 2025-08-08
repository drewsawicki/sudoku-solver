#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph/graph.h"
#include "sudoku/sudoku.h"

bool load_puzzle(const char* filename, int puzzle[TOTAL_CELLS]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open puzzle file");
        return false;
    }

    int count = 0;
    while (count < TOTAL_CELLS && !feof(file)) {
        int value;
        if (fscanf(file, "%d", &value) == 1) {
            puzzle[count++] = value;
        }
    }

    fclose(file);

    if (count != TOTAL_CELLS) {
        fprintf(stderr, "Puzzle file is incorrectly formatted");
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    int puzzle[TOTAL_CELLS];

    if (!load_puzzle(filename, puzzle)) {
        return EXIT_FAILURE;
    }

    Graph* graph = create_graph(puzzle);
    if (!graph) {
        fprintf(stderr, "Failed to build graph from puzzle.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < TOTAL_CELLS; i++) {
        printf("%d ", puzzle[i]);
        if ((i + 1) % 9 == 0) printf("\n");
    }

    destroy_graph(graph);
    return EXIT_SUCCESS;
}