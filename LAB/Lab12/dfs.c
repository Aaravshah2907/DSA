#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= QUEUE (unused in DFS, kept as-is) =================
typedef struct linked_list_node{
    int data;
    struct linked_list_node *next;
} ll_node;

typedef struct queue{
    ll_node *front;
    ll_node *rear;
} queue;

queue *get_queue(){
    queue *Q = (queue *)malloc(sizeof(queue));
    Q->front = NULL;
    Q->rear = NULL;
    return Q;
}

void enqueue(queue *Q, int data){
    ll_node *temp = (ll_node *)malloc(sizeof(ll_node));
    temp->data = data;
    temp->next = NULL;

    if (Q->rear == NULL){
        Q->front = temp;
        Q->rear = temp;
    } else {
        Q->rear->next = temp;
        Q->rear = temp;
    }
}

int is_empty(queue *Q){
    return Q->front == NULL;
}

int dequeue(queue *Q){
    if (is_empty(Q)){
        return -1;
    }

    ll_node *temp = Q->front;
    int data = temp->data;

    Q->front = Q->front->next;
    if (Q->front == NULL)
        Q->rear = NULL;

    free(temp);
    return data;
}

// ================= GRAPH STRUCTURES =================

typedef enum color{
    WHITE,
    GREY,
    BLACK
} color;

typedef struct graph_node{
    int data;
    color c;
} graph_node;

// adjacency list node (IMPORTANT for insertion order)
typedef struct node{
    int data;
    struct node *next;
} node;

typedef struct Graph{
    int V;
    int E;
    int **adjacency_matrix;
    node **adj_list;
    graph_node *vertices;
} Graph;

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

    // adjacency list (for insertion order DFS)
    G->adj_list = (node **)malloc(V * sizeof(node *));
    for (int i = 0; i < V; i++){
        G->adj_list[i] = NULL;
    }

    // vertices
    G->vertices = (graph_node *)malloc(V * sizeof(graph_node));
    for (int i = 0; i < V; i++){
        G->vertices[i].data = i;
        G->vertices[i].c = WHITE;
    }

    return G;
}

// ================= EDGE INSERTION =================

void add_edge(Graph *G, int u, int v){
    G->adjacency_matrix[u][v] = 1;

    node *temp = (node *)malloc(sizeof(node));
    temp->data = v;
    temp->next = NULL;

    // append at end → preserves insertion order
    if (G->adj_list[u] == NULL){
        G->adj_list[u] = temp;
    } else {
        node *curr = G->adj_list[u];
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = temp;
    }
}

// ================= DFS (INSERTION ORDER) =================

void dfs(Graph *G, int u){
    G->vertices[u].c = GREY;

    printf("%d ", G->vertices[u].data);

    node *temp = G->adj_list[u];

    while (temp != NULL){
        int v = temp->data;

        if (G->vertices[v].c == WHITE){
            dfs(G, v);
        }

        temp = temp->next;
    }

    G->vertices[u].c = BLACK;
}

// ================= MAIN =================

int main(int argc, char *argv[]){

    if (argc < 3){
        printf("Usage: %s <input_file> <source_vertex>\n", argv[0]);
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

    int s = atoi(argv[2]);

    if (s < 0 || s >= V){
        printf("Invalid source vertex\n");
        return 1;
    }

    printf("DFS Traversal starting from node %d:\n", s);
    dfs(G, s);
    printf("\n");

    return 0;
}