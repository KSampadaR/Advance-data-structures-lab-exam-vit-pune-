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



int countLeafNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    } else {
        return countLeafNodes(root->left) + countLeafNodes(root->right);
    }
}

int countNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
}

void printLeafNodes(struct Node* root) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->key);
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

void mirrorImage(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* temp;

    mirrorImage(root->left);
    mirrorImage(root->right);

    // Swap left and right pointers
    temp = root->left;
    root->left = root->right;
    root->right = temp;
}

int heightUsingQueue(struct Node* root) {
    if (root == NULL) {
        return 0;
    }

    int height = 0;
    struct Node* queue[100];
    int front = -1, rear = -1;

    queue[++rear] = root;
    queue[++rear] = NULL; 

    while (front != rear) {
        struct Node* current = queue[++front];
        if (current == NULL) {
            if (front != rear) {
                queue[++rear] = NULL;
            }
            height++;
        } else {
            if (current->left != NULL) {
                queue[++rear] = current->left;
            }
            if (current->right != NULL) {
                queue[++rear] = current->right;
            }
        }
    }

    return height;
}

void displayLevelWise(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* queue[100];
    int front = -1, rear = -1;

    queue[++rear] = root;
    queue[++rear] = NULL; // NULL as a marker for levels

    while (front != rear) {
        struct Node* current = queue[++front];
        if (current == NULL) {
            printf("\n");
            if (front != rear) {
                queue[++rear] = NULL;
            }
        } else {
            printf("%d ", current->key);
            if (current->left != NULL) {
                queue[++rear] = current->left;
            }
            if (current->right != NULL) {
                queue[++rear] = current->right;
            }
        }
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("Menu:\n");
        printf("1. Insert\n2. Count Leaf Nodes\n3. Display Total Number of Nodes\n4. Display Leaf Nodes\n5. Mirror Image\n6. Height (Using Queue)\n7. Level Wise Display(Mirror Image)\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Total Number of Nodes: %d\n", countNodes(root));
                break;
            case 3:
                printf("Leaf Nodes Count: %d\n", countLeafNodes(root));
                break;
            case 4:
                printf("Leaf Nodes: ");
                printLeafNodes(root);
                printf("\n");
                break;
            case 5:
                printf("Generating Mirror Image...\n");
                mirrorImage(root);
                printf("Mirror Image Generated.\n");
                break;
            case 6:
                printf("Height of the Tree (Using Queue): %d\n", heightUsingQueue(root));
                break;
            case 7:
                printf("Level Wise Display:\n");
                displayLevelWise(root);
                printf("\n");
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}


 //       10
 //      /  \
 //     6    14
 //    / \   /
 //   4   8 12
