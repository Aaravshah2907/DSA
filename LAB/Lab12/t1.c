/*
    Here graphs are provided in files input0.txt, input1.txt and input2.txt
    The first line contains the number of vertices |V|
    The second line contains the number of edges |E|
    The next |E| lines contain the edges in the form of "u v"
    where u and v are the indices representing the vertices (0-indexed)

    The graph is directed and unweighted

    Write a program that reads the graph from the file and prints the adjacency matrix
    and the adjacency list of the graph

    Here we are defining a graph as a structure with the following fields:
    int V: number of vertices
    int E: number of edges
    int **adjacency_matrix: a 2D array of size V x V
    int **adjacency_list: an array of size V, each element of which is a linked list

    You are given incomplete code in t1.c. Complete the code to get the desired output.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // To handle file reading properly.

typedef struct linked_list_node {
    int data;
    struct linked_list_node *next;
} ll_node;

struct Graph {
    int V;
    int E;
    int **adjacency_matrix;
    ll_node **adjacency_list;
};

struct Graph *get_graph(int V, int E){
    struct Graph *G = (struct Graph *)malloc(sizeof(struct Graph));
    G->V = V;
    G->E = E;

    // Allocate memory for the adjacency matrix (V x V int array)
    G->adjacency_matrix = (int **)malloc(V * sizeof(int *));

    // Allocate memory for each row of the adjacency matrix
    for (int i = 0; i < V; i++){

        // Initialize the allocated row to 0 (Do not visit all elements. Use the <string.h> function bzero or memset)
        G->adjacency_matrix[i] = (int *)malloc(V * sizeof(int));
        memset(G->adjacency_matrix[i], 0, V * sizeof(int)); 
    }
    // Allocate memory for the adjacency list  (V linked lists of type ll_node)
    G->adjacency_list = (ll_node **)malloc(V * sizeof(ll_node *));

    // Initialize all the linked lists to NULL (Will bzero or memset work here? Why or why not?)
    for (int i = 0; i < V; i++){
        G->adjacency_list[i] = NULL; // initialize all lists to NULL
    }

    return G; // Empty Graph Pointer Returned.
}

void add_edge_adj_matrix(struct Graph *G, int u, int v) {
    // Add an edge from u to v in the adjacency matrix
    G->adjacency_matrix[u][v] = 1; // Directed Graph in play here.

}

void add_edge_adj_list(struct Graph *G, int u, int v) {
    // Add an edge from u to v in the adjacency list. Use the ll_node structure defined above
    ll_node *new_node = (ll_node *)malloc(sizeof(ll_node));
    new_node->data = v;
    new_node->next = NULL;

    // Insert at beginning (simple and efficient)
    new_node->next = G->adjacency_list[u];
    G->adjacency_list[u] = new_node;

}

void print_adj_matrix(struct Graph *G) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {
            printf("%d ", G->adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

void print_adj_list(struct Graph *G) {
    printf("Adjacency List:\n");
    for (int i = 0; i < G->V; i++) {
        printf("%d: ", i);
        ll_node *temp = G->adjacency_list[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    // Accepted as param

    if (argc < 2){
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("Error opening file.\n");
        return 1;
    }

    int V, E;
    fscanf(fp, "%d", &V);
    fscanf(fp, "%d", &E);

    struct Graph *G = get_graph(V, E);
    for (int i = 0; i < E; i++) {
        int u, v;
        fscanf(fp, "%d %d", &u, &v);
        add_edge_adj_matrix(G, u, v);
        add_edge_adj_list(G, u, v);
    }
    print_adj_matrix(G);
    print_adj_list(G);
    return 0;
}