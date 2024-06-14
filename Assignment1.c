#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int key) {
    struct Node* new_node = createNode(key);

    if (root == NULL) {
        return new_node;
    }

    struct Node* current = root;
    while (1) {
        if (key < current->key) {
            if (current->left == NULL) {
                current->left = new_node;
                return root;
            } else {
                current = current->left;
            }
        } else if (key > current->key) {
            if (current->right == NULL) {
                current->right = new_node;
                return root;
            } else {
                current = current->right;
            }
        }
    }
}

struct Node* findMin(struct Node* node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct Node* delete(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    struct Node* parent = NULL;
    struct Node* current = root;

    while (current) {
        if (key == current->key) {
            break;
        }
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return root;
    }

    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            free(root);
            return NULL;
        }
        if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    } else if (current->left == NULL || current->right == NULL) {
        struct Node* temp = (current->left != NULL) ? current->left : current->right;
        if (parent == NULL) {
            free(root);
            return temp;
        }
        if (parent->left == current) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        free(current);
    } else {
        struct Node* temp = findMin(current->right);
        current->key = temp->key;
        current->right = delete(current->right, temp->key);
    }

    return root;
}

struct Node* find(struct Node* root, int key) {
    struct Node* current = root;
    while (current) {
        if (key == current->key) {
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

void preorderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (1) {
        while (current != NULL) {
            printf("%d ", current->key);
            if (current->right != NULL) {
                stack[++top] = current->right;
            }
            current = current->left;
        }
        if (top == -1) {
            break;
        }
        current = stack[top--];
    }
}

void inorderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->key);
        current = current->right;
    }
}

void postorderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1;
    int top2 = -1;
    struct Node* current = root;
    stack1[++top1] = current;

    while (top1 != -1) {
        current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL) {
            stack1[++top1] = current->left;
        }
        if (current->right != NULL) {
            stack1[++top1] = current->right;
        }
    }

    while (top2 != -1) {
        printf("%d ", stack2[top2--]->key);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("Menu:\n");
        printf("1. Insert\n2. Delete\n3. Find\n4. Pre-order Traversal\n5. In-order Traversal\n6. Postorder Traversal\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = delete(root, key);
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                if (find(root, key)) {
                    printf("Key found in the tree.\n");
                } else {
                    printf("Key not found in the tree.\n");
                }
                break;
            case 4:
                printf("BST Pre-order Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("BST In-order Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("BST Post-order Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}


//        10
  //     /  \
        6    14
  //   / \   /
 //   4   8 12

//
 

