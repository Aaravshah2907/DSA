#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= COLORS =================
typedef enum color{
    WHITE,
    GREY,
    BLACK
} color;

// ================= GRAPH NODE =================
typedef struct graph_node{
    int data;
    color c;
    int d;        // discovery time
    int f;        // finish time
    int parent;   // predecessor
} graph_node;

// ================= GRAPH =================
typedef struct Graph{
    int V;
    int E;
    int **adjacency_matrix;
    graph_node *vertices;
} Graph;

// ================= GLOBAL TIMER =================
int time_counter = 0;

// ================= GRAPH CREATION =================
Graph *get_graph(int V, int E){

    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->V = V;
    G->E = E;

    // adjacency matrix
    G->adjacency_matrix = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++){
        G->adjacency_matrix[i] = (int *)malloc(V * sizeof(int));
        memset(G->adjacency_matrix[i], 0, V * sizeof(int));
    }

    // vertices
    G->vertices = (graph_node *)malloc(V * sizeof(graph_node));

    for (int i = 0; i < V; i++){
        G->vertices[i].data = i;
        G->vertices[i].c = WHITE;
        G->vertices[i].d = 0;
        G->vertices[i].f = 0;
        G->vertices[i].parent = -1;
    }

    return G;
}

// ================= EDGE INSERTION =================
void add_edge(Graph *G, int u, int v){
    G->adjacency_matrix[u][v] = 1;
}

// ================= CLRS DFS VISIT =================
void recDFSVisit(Graph *G, int u){

    time_counter++;
    G->vertices[u].d = time_counter;
    G->vertices[u].c = GREY;

    printf("%d ", G->vertices[u].data); // optional traversal output

    for (int v = 0; v < G->V; v++){
        if (G->adjacency_matrix[u][v] == 1 &&
            G->vertices[v].c == WHITE){

            G->vertices[v].parent = u;
            recDFSVisit(G, v);
        }
    }

    G->vertices[u].c = BLACK;

    time_counter++;
    G->vertices[u].f = time_counter;
}

// ================= CLRS DFS (FOREST) =================
void recDFS(Graph *G){

    // initialization (important in CLRS)
    for (int i = 0; i < G->V; i++){
        G->vertices[i].c = WHITE;
        G->vertices[i].parent = -1;
    }

    time_counter = 0;

    // DFS forest (handles disconnected graphs)
    for (int u = 0; u < G->V; u++){
        if (G->vertices[u].c == WHITE){
            recDFSVisit(G, u);
        }
    }
}

// ================= MAIN =================
int main(int argc, char *argv[]){

    if (argc < 2){
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("Error opening file\n");
        return 1;
    }

    int V, E;
    fscanf(fp, "%d", &V);
    fscanf(fp, "%d", &E);

    Graph *G = get_graph(V, E);

    for (int i = 0; i < E; i++){
        int u, v;
        fscanf(fp, "%d %d", &u, &v);
        add_edge(G, u, v);
    }

    fclose(fp);

    printf("CLRS DFS Traversal:\n");
    recDFS(G);
    printf("\n\n");

    // Optional: print timestamps + parents
    printf("Node  d  f  parent\n");
    for (int i = 0; i < V; i++){
        printf("%d     %d  %d  %d\n",
            i,
            G->vertices[i].d,
            G->vertices[i].f,
            G->vertices[i].parent);
    }

    return 0;
}