# Graph Theory

## Into to Graph Representation

### Adjacency Matrix

In undirected graphs, the matrix is Symmetric. ie; $A^{T} = A$.
We may use `0` or `INT_MAX` depending on `maximising positive weigths` or `minimimizing costs` respectively.

Advantage - Look up time : $O(1)$

For a 9x9 matrix with three 1's and 78 0's. While there are only three edges, we still end up having a space complexity of $O(V^2)$, independent of the number of edges in memory. While this is efficient for dense graphs where the number of edges itself is in the order of $O(V^2)$, it is not very efficient in sparse graphs.

### Adjacency List

The adjacency-list representation of a graph G = (V, E) consists of an array of `|V|` lists, one for each vertex in V. For each vertex u, the list for u contains all the vertices v such that there is an edge (u, v) in E.

Each index of the array stores a linked list corresponding to each vertex. In order to check the presence of edges, one has to traverse the entire list of the node from which the node is incident. The advantage of an adjacency list is that the amount of memory required is $O(E)$ instead of the $O(V^2)$ required in
the case of an adjacency matrix. However, the disadvantage is that the lookup for edges is now on the worst-case $O(V)$ instead of $O(1)$ as the adjacency list can have a length of up to `|V|`. We prefer adjacency lists when the graphs are sparse.

In an undirected graph, as each edge (u,v) would appear in the list for both u and v, the sum of lengths of all the lists is equal to 2|E|. In the case of a directed graph, it would appear in only one list and thus, the sum of the lengths of all the lists is |E|. In the linked list node, we can either store the index of the vertex or a pointer to it based on what attributes are present with the nodes. (Storing pointers is similar to our tree representation.)

## Traversals

The simplest problem is to find whether one can reach a certain node `target node` t starting from `source node` s. This is called `searching`. The way to `search` for a node
is to `traverse` the entire set of nodes that are reachable from s until we reach the required destination t or we exhaust the set.

### BFS

Breadth-First Search is one of the simplest algorithms for searching a graph. It has a wide variety of applications and is a tool that would continuously be used while dealing with graphs or even some drastically diverse problems all of which can be modelled as some sort of search in a graph.

Given a source vertex `s`, BFS computes the least number of edges required to reach every reachable vertex from s. It also produces a "breadth-first tree" rooted at s containing all the reachable vertices and the shortest (in the number of hops) paths to them.
The algorithm works on both directed and undirected graphs and in the case of unweighted graphs, also yields the shortest path from s to t.

The basic principle is that all vertices are initially undiscovered and thus start out white. Each time a vertex is `discovered` we colour it `grey`. Here `discovered` means that the vertex is `seen` for the first time from any given path. And each time a vertex is `explored`, we colour it `black`. Explored
means that every neighbour of a vertex has been discovered.

The major steps of the BFS traversal algorithm are as follows:

```
BFS(G, s):
1. Start off with all nodes being white. Initialize an empty queue.
2. Mark the source s as grey and enqueue it
3. While the queue is not empty:
    a. Dequeue a node u
    b. For each white node v adjacent to u:
        i. Mark v as grey
        ii. Enqueue v
    c. Mark u as black
```

Initially, the root s is marked grey and added to the queue. Then it is explored (marked black) where its neighbours w and r are marked grey and added to the queue. Then we dequeue w, and add its undiscovered neighbours t and x to the queue. 
Note that since the neighbour s was already marked black, we did not add it to the queue again. We only add discover white nodes, paint them grey and add them to the queue. Similarly, we proceed as per the algorithm and traverse the entire graph.

### DFS

Depth-First Search works on the principle of completely exploring one path to a leaf (node from which we cannot discover any new node) before backtracking and exploring the other paths.

Suppose we are at node s with neighbours u and v. In the case of BFS, we would first discover unfollowed by v and then the neighbours of u, then the neighbours of v, … In contrast in DFS,
we would first discover all the nodes along paths from s via u before discovering v and the nodes reachable via v. It is called depth-first because we proceed as deep as we can along any given path before backtracking and exploring other paths.

```
DFS(G, s):
1. Start off with all nodes being white. Initialise an empty `stack`.
2. Mark the source 's' as grey and `push` it
3. While the `stack` is not empty:
    a. `Pop` a node u
    b. For each white node v adjacent to u:
        i. Mark v as grey
        ii. `Push` v
    c. Mark u as black
```

## Connetivity

We will deal with Digraphs for now.


