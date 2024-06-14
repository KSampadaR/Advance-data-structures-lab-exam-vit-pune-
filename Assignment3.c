// //3. Assignment based on TBT.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isThreaded; 
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0; 
    return newNode;
}


void insertNode(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    struct Node* current = *root;
    struct Node* parent = NULL;

    if (*root == NULL) {
        *root = newNode;
        return;
    }

    while (1) {
        parent = current;
        if (data < current->data) {
            if (current->left == NULL) {
                current->left = newNode;
                newNode->right = current;
                newNode->isThreaded = 1;
                return;
            }
            current = current->left;
        } else {
            if (current->isThreaded || current->right == NULL) {
                newNode->right = current->right;
                current->right = newNode;
                newNode->isThreaded = 1;
                return;
            }
            current = current->right;
        }
    }
}

void inorder(struct Node* root) {
    if (root == NULL) return;

    struct Node* current = root;
    while (current != NULL) {
        while (current->left != NULL)
            current = current->left;

        printf("%d ", current->data);

        if (current->isThreaded)
            current = current->right;
        else
            current = current->right;
    }
}
   
void preorder(struct Node* root) {
    if (root == NULL) return;

    struct Node* current = root;
    while (current != NULL) {
        printf("%d ", current->data);

        if (current->left != NULL)
            current = current->left;
        else if (current->isThreaded)
            current = current->right;
        else {
            while (current != NULL && !current->isThreaded)
                current = current->right;
            if (current != NULL)
                current = current->right;
        }
    }
}

void postorder(struct Node* root) {
    if (root == NULL) return;

    struct Node* current = root;
    while (current != NULL && current->left != NULL)
        current = current->left;

    while (current != NULL) {
        if (!current->isThreaded) {
            while (current->right != NULL && !current->isThreaded)
                current = current->right;
        }
        printf("%d ", current->data);

        if (current->isThreaded)
            current = current->right;
        else {
            if (current->right == NULL)
                break;
            while (current != NULL && !current->isThreaded && current->right != NULL)
                current = current->right;
            if (current != NULL)
                current = current->right;
        }
    }
}


int main() {
    struct Node* root = NULL;
    int choice, data;

    do {
        printf("\nMenu:\n");
        printf("1. Insert node\n");
        printf("2. Inorder traversal\n");
        printf("3. Preorder traversal\n");
        printf("4. Postorder traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertNode(&root, data);
                break;
            case 2:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 5);

    // TODO: Free allocated memory (optional)
    
    return 0;
}


// //       10
// //      / \
// //     5   15
// //   / \  / 
// //  3  7 12  

