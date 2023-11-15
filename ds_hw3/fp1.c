#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

struct Edge {
    int src, dest, weight;
};
struct Subset {
    int parent;
    int rank;
};
int compareEdges(const void* a, const void* b) {
    struct Edge* edge1 = (struct Edge*)a;
    struct Edge* edge2 = (struct Edge*)b;
    return edge1->weight - edge2->weight;
}
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
void kruskalMST(struct Edge edges[], int numVertices, int numEdges) {
    struct Edge* result = (struct Edge*)malloc((numVertices - 1) * sizeof(struct Edge)); // Stores the resulting MST
    int e = 0;
    int i = 0;

    qsort(edges, numEdges, sizeof(struct Edge), compareEdges);
    struct Subset* subsets = (struct Subset*)malloc(numVertices * sizeof(struct Subset));
    for (int v = 0; v < numVertices; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    while (e < numVertices - 1 && i < numEdges) {
        struct Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }
    free(subsets);
    FILE* fp = fopen("fp1_result.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    for (int i = 0; i < e; i++) {
        fprintf(fp, "%d %d %d\n", result[i].src, result[i].dest, result[i].weight);
    }
    int totalCost = 0;
    for (int i = 0; i < e; i++) {
        totalCost += result[i].weight;
    }

    fprintf(fp, "%d\n", totalCost);

    bool connected = (e == numVertices - 1);

    if (connected) {
        fprintf(fp, "CONNECTED\n");
    } else {
        fprintf(fp, "DISCONNECTED\n");
    }

    fclose(fp);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: %s input_filename\n", argv[0]);
        return 1;
    }
    char* filename = argv[1];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("The input file does not exist.\n");
        return 1;
    }

    int numVertices;
    fscanf(file, "%d", &numVertices);

    int numEdges;
    fscanf(file, "%d", &numEdges);

    struct Edge* edges = (struct Edge*)malloc(numEdges * sizeof(struct Edge));
    for (int i = 0; i < numEdges; i++) {
        fscanf(file, "%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    fclose(file);

    clock_t start = clock();

    kruskalMST(edges, numVertices, numEdges);

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("output written to fp1_result.txt.\n");
    printf("running time: %f seconds\n", cpu_time_used);

    free(edges);

    return 0;
}

