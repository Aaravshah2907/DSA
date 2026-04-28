#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
} Node;

typedef struct bst {
    Node *root;
} BST;

BST *new_bst() {
    BST *bst = malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

Node *new_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->height = 1;
    return node;
}

void traverse_in_order(Node *node){
    if (node == NULL){
        return;
    }
    traverse_in_order(node->left);
    printf("%d ", node->value);
    traverse_in_order(node->right);
}

void insert(BST *bst, int value){
    Node *node = new_node(value);
    if (bst->root == NULL) {
        bst->root = node;
        return;
    }
    Node *current = bst->root;
    while (current != NULL) {
        if (value < current->value){
            if (current->left == NULL) {
                current->left = node;
                return;
            }
            current = current->left;
        } 
        else {
            if (current->right == NULL) {
                current->right = node;
                return;
            }
            current = current->right;
        }
    }
}

int search(BST *bst, int key){
    Node *current = bst->root;
    while (current != NULL) {
        if (key == current->value) {
            return 1;
        } 
        else if (key < current->value) {
            current = current->left;
        } 
        else {
            current = current->right;
        }
    }
    return 0;
}

int find_min(BST *bst){
    Node *current = bst->root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->value;
}

int find_max(BST *bst){
    Node *current = bst->root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->value;
}

Node *predecessor(Node *node){
    if (node->left == NULL){
        return NULL;
    }
    Node *current = node->left;
    while (current->right != NULL){
        current = current->right;
    }
    return current;
}

Node *successor(Node *node){
    if (node->right == NULL){
        return NULL;
    }
    Node *current = node->right;
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}

void delete(BST *bst, Node *node){
    if (node == NULL)
        return;
    if (node->left == NULL && node->right == NULL){
        // Node is a leaf
        Node* current = bst->root;
        while (current != NULL){
            if (current->left == node){
                current->left = NULL;
                break;
            }
            if (current->right == node){
                current->right = NULL;
                break;
            }
            if (node->value < current->value){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        free(node);
        return;
    }
    
    if (node->left == NULL){
        // Node only has right child
        Node* current = bst->root;
        if (current == node){
            bst->root = node->right;
            free(node);
            return;
        }
        while (current != NULL){
            if (current->left == node){
                current->left = node->right;
                break;
            }
            if (current->right == node){
                current->right = node->right;
                break;
            }
            if (node->value < current->value){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        free(node);
        return;
    }

    if (node->right == NULL){
        // Node only has left child
        Node* current = bst->root;
        if (current == node){
            bst->root = node->left;
            free(node);
            return;
        }
        while (current != NULL){
            if (current->left == node){
                current->left = node->left;
                break;
            }
            if (current->right == node){
                current->right = node->left;
                break;
            }
            if (node->value < current->value){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        free(node);
        return;
    }

    // Node has both children
    Node *temp = successor(node);
    node->value = temp->value;
    delete(bst, temp);
    return;
}

int getHeight(Node *n){
    return (n == NULL) ? 0 : n->height;
}

int getBalance(Node *n){
    return (n == NULL) ? 0 : getHeight(n->left) - getHeight(n->right);
}

void updateHeight(Node *n){
    n->height = 1 + (getHeight(n->left) > getHeight(n->right) ? getHeight(n->left) : getHeight(n->right));
}

Node *rotate_left(Node *x){
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    if (T2) T2->parent = x;

    y->parent = x->parent;
    x->parent = y;

    updateHeight(x);
    updateHeight(y);

    if (y->parent != NULL) {
        if (y->parent->left == x)
            y->parent->left = y;
        else if (y->parent->right == x)
            y->parent->right = y;
    }

    return y;
}

Node *rotate_right(Node *x){
    Node *y = x->left;
    Node *T2 = y->right;

    y->right = x;
    x->left = T2;

    if (T2) T2->parent = x;

    y->parent = x->parent;
    x->parent = y;

    updateHeight(x);
    updateHeight(y);

    if (y->parent != NULL) {
        if (y->parent->left == x)
            y->parent->left = y;
        else if (y->parent->right == x)
            y->parent->right = y;
    }

    return y;
}

Node *insertAVL(Node *node, int value){
    if (node == NULL){
        return new_node(value);
    }

    if (value < node->value){
        node->left = insertAVL(node->left, value);
    }
    else{
        node->right = insertAVL(node->right, value);
    }

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left)  : getHeight(node->right));

    int balance = getBalance(node);

    // LL
    if (balance > 1 && value < node->left->value)
        return rotate_right(node);

    // RR
    if (balance < -1 && value > node->right->value)
        return rotate_left(node);

    // LR
    if (balance > 1 && value > node->left->value){
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // RL
    if (balance < -1 && value < node->right->value){
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

Node* insertAVL_iter(Node* root, int value) {
    Node* current = root;
    Node* parent = NULL;

    // Step 1: Normal BST insert
    while (current) {
        parent = current;
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    Node* newNode = new_node(value);
    newNode->parent = parent;

    if (!parent)
        return newNode; // tree was empty

    if (value < parent->value)
        parent->left = newNode;
    else
        parent->right = newNode;

    // Step 2: Backtrack and rebalance
    current = newNode;
    while (current) {
        updateHeight(current);
        int balance = getBalance(current);

        Node* newRoot = current;

        // LL
        if (balance > 1 && getBalance(current->left) >= 0)
            newRoot = rotate_right(current);

        // LR
        else if (balance > 1 && getBalance(current->left) < 0) {
            current->left = rotate_left(current->left);
            newRoot = rotate_right(current);
        }

        // RR
        else if (balance < -1 && getBalance(current->right) <= 0)
            newRoot = rotate_left(current);

        // RL
        else if (balance < -1 && getBalance(current->right) > 0) {
            current->right = rotate_right(current->right);
            newRoot = rotate_left(current);
        }

        // reconnect to parent (rotation already updated child pointers)
        if (!newRoot->parent)
            root = newRoot;

        current = newRoot->parent; // move up correctly
    }

    return root;
}

int isAVL(Node *node){
    if (node == NULL)
        return 1;

    int balance = getHeight(node->left) - getHeight(node->right);

    if (balance > 1 || balance < -1)
        return 0;

    return isAVL(node->left) && isAVL(node->right);
}

void bfs(Node *root){
    if (root == NULL)
        return;

    Node *queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear){
        Node *current = queue[front++];
        printf("%d ", current->value);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

Node* deleteAVL(Node* node, int value){
    if (node == NULL)
        return NULL;

    // STEP 1: Normal BST delete
    if (value < node->value)
        node->left = deleteAVL(node->left, value);

    else if (value > node->value)
        node->right = deleteAVL(node->right, value);

    else{
        // node found
        if (node->left == NULL || node->right == NULL){
            Node *temp = node->left ? node->left : node->right;

            if (temp == NULL){
                // no child
                free(node);
                return NULL;
            }
            else{
                // one child
                *node = *temp;
                free(temp);
            }
        }
        else{
            // two children
            Node *temp = predecessor(node);
            node->value = temp->value;
            node->left = deleteAVL(node->left, temp->value);
        }
    }

    // STEP 2: Update height
    node->height = 1 + (getHeight(node->left) > getHeight(node->right)? getHeight(node->left) : getHeight(node->right));

    // STEP 3: Get balance
    int balance = getBalance(node);

    // STEP 4: Rebalance
    // LL
    if (balance > 1 && getBalance(node->left) >= 0)
        return rotate_right(node);

    // LR
    if (balance > 1 && getBalance(node->left) < 0){
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // RR
    if (balance < -1 && getBalance(node->right) <= 0)
        return rotate_left(node);

    // RL
    if (balance < -1 && getBalance(node->right) > 0){
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

Node* deleteAVL_iter(Node *root, int value){
    Node *node = root;

    // STEP 1: Find node
    while (node && node->value != value){
        if (value < node->value)
            node = node->left;
        else
            node = node->right;
    }

    if (node == NULL)
        return root; // not found

    // STEP 2: If node has 2 children → replace with predecessor
    if (node->left && node->right){
        Node *pred = node->left;
        while (pred->right)
            pred = pred->right;

        node->value = pred->value;
        node = pred; // now delete predecessor
    }

    // STEP 3: Node has at most one child
    Node *child = (node->left) ? node->left : node->right;

    if (child)
        child->parent = node->parent;

    if (node->parent == NULL)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;

    Node *current = node->parent;
    free(node);

    // STEP 4: Rebalance upwards
    while (current != NULL){
        updateHeight(current);
        int balance = getBalance(current);

        Node *newRoot = current;

        // LL
        if (balance > 1 && getBalance(current->left) >= 0)
            newRoot = rotate_right(current);

        // LR
        else if (balance > 1){
            current->left = rotate_left(current->left);
            newRoot = rotate_right(current);
        }

        // RR
        else if (balance < -1 && getBalance(current->right) <= 0)
            newRoot = rotate_left(current);

        // RL
        else if (balance < -1){
            current->right = rotate_right(current->right);
            newRoot = rotate_left(current);
        }

        // reconnect to parent
        if (newRoot->parent == NULL)
            root = newRoot;
        else if (newRoot->parent->left == current)
            newRoot->parent->left = newRoot;
        else
            newRoot->parent->right = newRoot;

        current = newRoot->parent;
    }

    return root;
}

// Driver program to test the above functions (feel free to play around with this)
/*int main(){
    BST *bst = new_bst();

    // Insert 1 to 9 using AVL insert
    for (int i = 1; i <= 9; i++)
    {
        bst->root = insertAVL(bst->root, i);
    }

    printf("In-order traversal:\n");
    traverse_in_order(bst->root);

    printf("\n\nBreadth-first traversal:\n");
    bfs(bst->root);

    // Check AVL property
    if (isAVL(bst->root))
        printf("\n\nTree is an AVL tree\n");
    else
        printf("\n\nTree is NOT an AVL tree\n");

    return 0;
}
    */
int main() {
    Node *root = NULL;

    //printf("Starting AVL insertions...\n");
    for (int i = 1; i <= 9; i++) {
        root = insertAVL_iter(root, i);
        //printf("Inserted %d\n", i);
    }

    //printf("Insertions done\n");

    printf("In-order traversal after insertions:\n");
    traverse_in_order(root);
    printf("\n\nBreadth-first traversal:\n");
    bfs(root);
    printf("\n");

    printf("\nIs AVL? %d\n", isAVL(root));

    root = deleteAVL_iter(root, 6);
    printf("Deleted 6\n");

    root = deleteAVL_iter(root, 7);
    printf("Deleted 7\n\n");

    printf("In-order traversal after deletions:\n");
    traverse_in_order(root);
    printf("\n");

    printf("Breadth-first traversal after deletions:\n");
    bfs(root);
    printf("\n");

    printf("\nIs AVL? %d\n", isAVL(root));
}