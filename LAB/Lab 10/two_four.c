#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int keys[3];            /* at most 3 keys   (indices 0, 1, 2)     */
    struct node *children[4]; /* at most 4 children (indices 0, 1, 2, 3) */
    int num_keys;
    int isLeaf;
} Node;

typedef struct tree
{
    Node *root;
} Tree;

/* -------------------------------------------------------------------
 * new_node()
 * Allocates a zeroed-out (2,4) tree node.
 * ------------------------------------------------------------------- */
Node *new_node()
{
    Node *temp = malloc(sizeof(Node));

    for (int i = 0; i < 3; i++)
    {
        temp->keys[i]     = 0;
        temp->children[i] = NULL;
    }

    temp->children[3] = NULL;   

    temp->isLeaf   = 0;
    temp->num_keys = 0;
    return temp;
}

/* -------------------------------------------------------------------
 * insert_24()
 * Inserts `val` into the (2,4) tree.
 *
 * CONCEPT — Why preemptive splitting?
 * ------------------------------------
 * In a (2,4) tree, a node can hold 1, 2, or 3 keys.  When we need to
 * promote a key into a parent (during a split), the parent must have
 * room (i.e., fewer than 3 keys).  If we split only AFTER reaching the
 * leaf, we might find a full parent and need to keep splitting upward —
 * a bottom-up cascade.
 *
 * Preemptive (top-down) splitting avoids this: whenever we encounter a
 * full node (3 keys = 4-node) on the way DOWN, we split it immediately.
 * Because the parent was already split on a prior step, it is guaranteed
 * to have room for the promoted key.  We never need to go back up.
 * ------------------------------------------------------------------- */
void insert_24(Tree *tree, int val)
{
    Node *temp = tree->root;

    /* ── Case 1: empty tree ─────────────────────────────────────── */
    if (temp == NULL)
    {
        Node *myNode      = new_node();
        myNode->isLeaf    = 1;
        myNode->keys[0]   = val;
        myNode->num_keys  = 1;
        tree->root        = myNode;
        return;
    }

    /*
     * ── Case 2: non-empty tree ──────────────────────────────────
     * Walk from root toward the correct leaf.
     * `parent` tracks the node one level above `temp`.
     */
    Node *parent = NULL;

    while (temp)
    {
        /* ── Split a 4-node before descending into it ─────────── */
        if (temp->num_keys == 3)
        {
            /*
             * WHAT A 4-NODE SPLIT LOOKS LIKE:
             *
             * Before:  temp = [ k0 | k1 | k2 ]
             *                  /    |    |    \
             *                c0   c1   c2   c3
             *
             * After:
             *   temp    = [ k0 ]        (left half,  keeps c0 and c1)
             *              /    \
             *            c0    c1
             *
             *   newNode = [ k2 ]        (right half, gets  c2 and c3)
             *              /    \
             *            c2    c3
             *
             *   k1 is PROMOTED to the parent.
             *
             * Why k1 (the middle key)?  After the split, everything
             * less than k1 is in temp, everything greater is in newNode.
             * k1 belongs between them — so it goes up to the parent to
             * serve as the separator between the two halves.
             */

            Node *newNode        = new_node();
            newNode->isLeaf      = temp->isLeaf;
            newNode->children[0] = temp->children[2];
            newNode->children[1] = temp->children[3];
            newNode->keys[0]     = temp->keys[2];
            newNode->num_keys    = 1;

            temp->children[2] = NULL;
            temp->children[3] = NULL;
            temp->num_keys    = 1;   /* temp now holds only keys[0] */

            /* ── Insert promoted key (keys[1]) into parent ─────── */
            if (parent == NULL)
            {
                /*
                 * temp was the root.  Create a brand-new root above it.
                 * This is the ONLY way a (2,4) tree grows taller.
                 */
                parent              = new_node();
                parent->isLeaf      = 0;
                parent->children[0] = temp;
                parent->children[1] = newNode;
                parent->keys[0]     = temp->keys[1];
                parent->num_keys    = 1;
                tree->root          = parent;
                printf("Created new root node\n");
            }
            else
            {
                /*
                 * parent has 1 or 2 keys (never 3, because we split
                 * every 4-node proactively on the way down).
                 * Insert the promoted key in sorted order.
                 */
                if (parent->num_keys == 1)
                {
                    /* 2-node parent → 3-node parent */
                    if (parent->keys[0] > temp->keys[1])
                    {
                        parent->children[2] = parent->children[1];
                        parent->children[1] = newNode;
                        parent->keys[1]     = parent->keys[0];
                        parent->keys[0]     = temp->keys[1];
                    }
                    else
                    {
                        parent->children[2] = newNode;
                        parent->keys[1]     = temp->keys[1];
                    }
                    parent->num_keys = 2;
                }
                else   /* parent->num_keys == 2: 3-node → 4-node */
                {
                    if (parent->keys[0] > temp->keys[1])
                    {
                        parent->children[3] = parent->children[2];
                        parent->children[2] = parent->children[1];
                        parent->children[1] = newNode;
                        parent->keys[2]     = parent->keys[1];
                        parent->keys[1]     = parent->keys[0];
                        parent->keys[0]     = temp->keys[1];
                    }
                    else if (parent->keys[1] > temp->keys[1])
                    {
                        parent->children[3] = parent->children[2];
                        parent->children[2] = newNode;
                        parent->keys[2]     = parent->keys[1];
                        parent->keys[1]     = temp->keys[1];
                    }
                    else
                    {
                        parent->children[3] = newNode;
                        parent->keys[2]     = temp->keys[1];
                    }
                    parent->num_keys = 3;
                }
            }

            /*
             * After the split, update parent and temp to point to the
             * correct subtree for the next iteration.
             *
             * Two sequential loops (logically equivalent to the nested
             * loop shown in the new lab sheet PDF walkthrough):
             *   Loop A: moves parent down one level to the child we
             *           will descend into.
             *   Loop B: from that new parent, finds temp (the next
             *           node to examine in the following iteration).
             */

            /* Loop A — re-point parent */
            for (int i = 0; i <= parent->num_keys; i++)
            {
                if (val < parent->keys[i] || i == parent->num_keys)
                {
                    parent = parent->children[i];
                    break;
                }
            }

            /* Loop B — re-point temp */
            for (int i = 0; i <= parent->num_keys; i++)
            {
                if (val < parent->keys[i] || i == parent->num_keys)
                {
                    temp = parent->children[i];
                    break;
                }
            }
        }
        else
        {
            /*
             * Not a 4-node — just descend to the correct child.
             *
             * FIX 2: explicit boolean flag replaces the fragile
             * pointer-identity check of the original.
             *
             * ORIGINAL CODE (correct but opaque):
             *   parent = temp;
             *   for (int i = 0; i < parent->num_keys; i++) {
             *       if (val < parent->keys[i]) {
             *           temp = parent->children[i]; break;
             *       }
             *   }
             *   if (parent == temp)   // ← mysterious: only works because
             *                         //   parent was just set to temp above
             *       temp = parent->children[parent->num_keys];
             */
            parent = temp;
            int descended = 0;   /* did we find a child smaller than val? */

            for (int i = 0; i < parent->num_keys; i++)
            {
                if (val < parent->keys[i])
                {
                    temp      = parent->children[i];
                    descended = 1;
                    break;
                }
            }

            if (!descended)
            {
                /* val is larger than all keys → go to rightmost child */
                temp = parent->children[parent->num_keys];
            }
        }
    } /* end while(temp) */

    /*
     * ── Insert val into the leaf (now pointed to by parent) ─────
     *
     * Shift larger existing keys one position to the right to open
     * a sorted slot for val.
     */
    for (int i = parent->num_keys - 1; i >= 0; i--)
    {
        if (val < parent->keys[i])
        {
            parent->keys[i + 1] = parent->keys[i];   /* shift right */
        }
        else
        {
            parent->keys[i + 1] = val;
            break;
        }
        if (i == 0)
        {
            parent->keys[i] = val;   /* val is smaller than all keys */
        }
    }
    parent->num_keys++;
}

/* -------------------------------------------------------------------
 * print_tree() — recursive pretty-printer
 * ------------------------------------------------------------------- */
void print_tree(Node *node, int level)
{
    printf("%*s", level * 2, "");
    if (node == NULL) return;

    for (int i = 0; i < node->num_keys; i++)
        printf("%d ", node->keys[i]);
    printf("\n");

    if (!node->isLeaf)
    {
        for (int i = 0; i <= node->num_keys; i++)
            print_tree(node->children[i], level + 1);
    }
}

/* -------------------------------------------------------------------
 * main() — insert the 13 keys from the lab sheet and print the tree
 * after each insertion so the step-by-step evolution is visible.
 * ------------------------------------------------------------------- */
int main()
{
    Tree *tree = malloc(sizeof(Tree));
    tree->root = NULL;

    int keys[] = {4, 6, 14, 20, 2, 5, 10, 8, 15, 12, 18, 25, 16};

    for (int i = 0; i <= 12; i++)
    {
        insert_24(tree, keys[i]);
        printf("Tree after inserting %d\n", keys[i]);
        print_tree(tree->root, 0);
    }

    return 0;
}