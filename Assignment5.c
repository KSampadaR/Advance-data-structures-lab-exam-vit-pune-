#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* findNode(Node* node, int key) {
    if (node == NULL || node->key == key)
        return node;

    if (key < node->key)
        return findNode(node->left, key);
    else
        return findNode(node->right, key);
}

Node* performRightRotation(Node* root, int key) {
    Node* node = findNode(root, key);

    if (node == NULL) {
        printf("Node with key %d not found!\n", key);
        return root;
    }

    if (node->left == NULL) {
        printf("Cannot perform Right Rotation. No left child found for the node with key %d.\n", key);
        return root;
    }

    Node* newRoot = rightRotate(node);

    printf("Right Rotation performed on the node with key %d.\n", key);
    return newRoot;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


Node* performLeftRotation(Node* root, int key) {
    Node* node = findNode(root, key);

    if (node == NULL) {
        printf("Node with key %d not found!\n", key);
        return root;
    }

    if (node->right == NULL) {
        printf("Cannot perform Left Rotation. No right child found for the node with key %d.\n", key);
        return root;
    }

    Node* newRoot = leftRotate(node);

    printf("Left Rotation performed on the node with key %d.\n", key);
    return newRoot;
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node* node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->key);
        inorder(node->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, key;

    do {
        printf("\n1. Insert\n2. Display (Inorder)\n3. Perform Right Rotation\n4. Perform Left Rotation\n5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Enter the key of the node to perform Right Rotation: ");
                scanf("%d", &key);
                root = performRightRotation(root, key);
                break;
            case 4:
                printf("Enter the key of the node to perform Left Rotation: ");
                scanf("%d", &key);
                root = performLeftRotation(root, key);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}


//       50
//      /  \
//    30    70
//   /  \   /
//  20  40 60
