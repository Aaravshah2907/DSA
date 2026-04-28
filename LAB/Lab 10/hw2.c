/*
 
 * TASK:
 *   Given (1) the in-order traversal and (2) the post-order traversal of a
 *   binary tree, reconstruct the tree and print its level-order (BFS) output.
 *
 *
 * =============================================================================
 * CONCEPT: HOW CAN TWO TRAVERSALS UNIQUELY IDENTIFY A TREE?
 * =============================================================================
 *
 * A single traversal is not enough to reconstruct a tree.  For example,
 * in-order alone could come from many different tree shapes.  But combining
 * in-order with post-order (or pre-order) gives enough information to
 * uniquely reconstruct the tree.
 *
 * KEY INSIGHT — Post-order's last element is always the root:
 *   Post-order visits:  left subtree  →  right subtree  →  ROOT
 *   So the ROOT is always the VERY LAST element of any post-order slice.
 *
 * KEY INSIGHT — In-order splits around the root:
 *   In-order visits:  left subtree  →  ROOT  →  right subtree
 *   Once we know the root's value, everything to its LEFT in the in-order
 *   array belongs to the left subtree, and everything to its RIGHT belongs
 *   to the right subtree.
 *
 * ALGORITHM (divide and conquer, repeated recursively):
 *
 *   build(in[in_s..in_e], post[po_s..po_e]):
 *     1. root_val = post[po_e]          (last element of post-order slice)
 *     2. create a new node with value root_val
 *     3. find root_val in in[in_s..in_e] at position root_idx
 *     4. left_size  = root_idx - in_s   (number of nodes in left subtree)
 *     5. right_size = in_e - root_idx   (number of nodes in right subtree)
 *     6. root->left  = build(in[in_s .. root_idx-1],
 *                            post[po_s .. po_s+left_size-1])
 *     7. root->right = build(in[root_idx+1 .. in_e],
 *                            post[po_s+left_size .. po_e-1])
 *     8. return root
 *
 *   Base case: if the slice is empty (in_s > in_e), return NULL.
 *
 * WORKED EXAMPLE — Sample Input 1:
 *   n = 8
 *   in-order:   4  8  2  5  1  6  3  7
 *   post-order: 8  4  5  2  6  7  3  1
 *
 *   Step 1: root_val = post[7] = 1
 *   Step 3: 1 is at index 4 in in-order → root_idx = 4
 *   Step 4: left_size = 4-0 = 4  (nodes: 4, 8, 2, 5)
 *           right_size = 7-4 = 3 (nodes: 6, 3, 7)
 *
 *   Left subtree:
 *     in[0..3]   = [4,8,2,5],  post[0..3] = [8,4,5,2]
 *     root = post[3] = 2, found at index 2 in in
 *     left_size = 2 → left child's in=[4,8], post=[8,4] → root=4, left=NULL, right=8
 *                    right child's in=[5],   post=[5]   → root=5 (leaf)
 *
 *   Right subtree:
 *     in[5..7]   = [6,3,7],  post[4..6] = [6,7,3]
 *     root = post[6] = 3, found at index 6 in in (offset 1 from slice start)
 *     left child: in=[6], post=[6] → root=6 (leaf)
 *     right child: in=[7], post=[7] → root=7 (leaf)
 *
 *   Resulting tree:
 *             1
 *           /   \
 *          2     3
 *         / \   / \
 *        4   5 6   7
 *         \
 *          8
 *
 *   BFS output: 1 2 3 4 5 6 7 8  ✓  (matches Sample Output 1)
 *
 * Both sample cases have been verified by running this implementation.
 *
 * =============================================================================
 * NOTE ON VARIABLE-LENGTH ARRAYS (VLAs):
 *   `int in_order[n]` uses a VLA — valid in C99 and C11 but made optional
 *   in C23 and unsupported by MSVC.  For maximum portability, replace with:
 *       int *in_order = malloc(n * sizeof(int));
 *   and free() it before return.
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
    int height;
} Node;

typedef struct bst {
    Node *root;
} BST;

BST *new_bst()
{
    BST *bst   = malloc(sizeof(BST));
    bst->root  = NULL;
    return bst;
}

Node *new_node(int value)
{
    Node *node   = malloc(sizeof(Node));
    node->value  = value;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 0;
    return node;
}

/* -------------------------------------------------------------------
 * traverse_bfs()
 * Prints the values of the tree in level-order (breadth-first).
 *
 * Uses a fixed-size queue of 100.  This is sufficient for the given
 * sample inputs but may overflow for large trees.  A safe upper bound
 * for the queue size is 2^(height+1) - 1.  For production use, replace
 * with a dynamic queue (e.g., using the linked-list queue from Week 3).
 * ------------------------------------------------------------------- */
void traverse_bfs(Node *node)
{
    if (node == NULL) return;

    Node *queue[100];
    int front = 0;
    int back  = 0;

    queue[back++] = node;

    while (front != back)
    {
        Node *current = queue[front++];
        printf("%d ", current->value);
        if (current->left  != NULL) queue[back++] = current->left;
        if (current->right != NULL) queue[back++] = current->right;
    }
}

/* -------------------------------------------------------------------
 * build_tree_helper()
 *
 * Recursively reconstructs the subtree whose:
 *   in-order   slice is  in_order  [in_s .. in_e]
 *   post-order slice is  post_order[po_s .. po_e]
 *
 * Parameters:
 *   in_order   — the full in-order array (we only look at [in_s..in_e])
 *   in_s       — start index of this call's in-order slice (inclusive)
 *   in_e       — end   index of this call's in-order slice (inclusive)
 *   post_order — the full post-order array
 *   po_s       — start index of this call's post-order slice (inclusive)
 *   po_e       — end   index of this call's post-order slice (inclusive)
 *
 * Returns: pointer to the root of the reconstructed subtree, or NULL
 *          if the slice is empty.
 * ------------------------------------------------------------------- */
static Node *build_tree_helper(
    int *in_order,   int in_s, int in_e,
    int *post_order, int po_s, int po_e)
{
    /* Base case: empty slice → no node */
    if (in_s > in_e || po_s > po_e)
        return NULL;

    /*
     * Step 1: The root of this subtree is the LAST element of its
     * post-order slice.  Post-order always ends with the root.
     */
    int root_val = post_order[po_e];
    Node *root   = new_node(root_val);

    /*
     * Step 2: Find root_val in the in-order slice.
     * Everything to its LEFT  → left subtree.
     * Everything to its RIGHT → right subtree.
     */
    int root_idx = in_s;   /* index of root_val within in_order */
    for (int i = in_s; i <= in_e; i++)
    {
        if (in_order[i] == root_val)
        {
            root_idx = i;
            break;
        }
    }

    /*
     * Step 3: Calculate the size of the left subtree.
     * We need this to correctly slice the post-order array.
     */
    int left_size = root_idx - in_s;

    /*
     * Step 4: Recurse on the left subtree.
     *
     * In-order   slice: in_order[in_s .. root_idx-1]
     *   (all elements to the left of the root in in-order)
     *
     * Post-order slice: post_order[po_s .. po_s+left_size-1]
     *   (the first left_size elements of the post-order slice,
     *    which correspond exactly to the left subtree's traversal)
     *
     * WHY? Post-order visits left subtree first, then right, then root.
     * So the first `left_size` elements of any post-order slice always
     * belong to the left subtree.
     */
    root->left = build_tree_helper(
        in_order,   in_s,              root_idx - 1,
        post_order, po_s,              po_s + left_size - 1);

    /*
     * Step 5: Recurse on the right subtree.
     *
     * In-order   slice: in_order[root_idx+1 .. in_e]
     *   (all elements to the right of the root in in-order)
     *
     * Post-order slice: post_order[po_s+left_size .. po_e-1]
     *   (what remains after the left slice and before the root po_e)
     */
    root->right = build_tree_helper(
        in_order,   root_idx + 1,      in_e,
        post_order, po_s + left_size,  po_e - 1);

    return root;
}

/* -------------------------------------------------------------------
 * build_tree()
 * Public wrapper — kicks off the recursive reconstruction using the
 * full arrays [0 .. n-1].
 *
 * This is the function that was a stub in the original hw2.c.
 * ------------------------------------------------------------------- */
Node *build_tree(int *in_order, int *post_order, int n)
{
    return build_tree_helper(in_order, 0, n - 1,
                             post_order, 0, n - 1);
}

/* -------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------- */
int main()
{
    int n;
    scanf("%d", &n);

    /* VLA — see portability note at top of file */
    int in_order[n];
    int post_order[n];

    for (int i = 0; i < n; i++) scanf("%d", &in_order[i]);
    for (int i = 0; i < n; i++) scanf("%d", &post_order[i]);

    BST *bst  = new_bst();
    bst->root = build_tree(in_order, post_order, n);

    traverse_bfs(bst->root);
    printf("\n");
    return 0;
}