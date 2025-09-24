#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode {
    char data[10];
    struct treenode *left;
    struct treenode *right;
} treenode;

void create_r(treenode *root) {
    char ch;
    printf("Do you want to add data to the left of '%s' (y/n)? ", root->data);
    scanf(" %c", &ch);
    if (ch == 'y') {
        treenode *curr = (treenode*)malloc(sizeof(treenode));
        if (curr == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
        printf("Enter data for the new left node: ");
        scanf(" %[^\n]", curr->data);
        getchar();
        curr->left = NULL;
        curr->right = NULL;
        root->left = curr;
        create_r(curr);
    }
    printf("Do you want to add data to the right of '%s' (y/n)? ", root->data);
    scanf(" %c", &ch);
    if (ch == 'y') {
        treenode *curr = (treenode*)malloc(sizeof(treenode));
        if (curr == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
        printf("Enter data for the new right node: ");
        scanf(" %[^\n]", curr->data);
        getchar();
        curr->left = NULL;
        curr->right = NULL;
        root->right = curr;
        create_r(curr);
    }
}

void create_nr(treenode *root) {
    char ch;
    treenode *temp, *curr;
    
    do {
        temp = root;
        int flag = 0;
        
        curr = (treenode*)malloc(sizeof(treenode));
        if (curr == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
        
        printf("Enter data for the new node: ");
        scanf(" %[^\n]", curr->data);
        getchar();
        curr->left = NULL;
        curr->right = NULL;
        
        while (flag == 0) {
            printf("Do you want to add data to the left or right of '%s' (l/r)? ", temp->data);
            scanf(" %c", &ch);
            
            if (ch == 'l') {
                if (temp->left == NULL) {
                    temp->left = curr;
                    flag = 1;
                } else {
                    temp = temp->left;
                }
            } else if (ch == 'r') {
                if (temp->right == NULL) {
                    temp->right = curr;
                    flag = 1;
                } else {
                    temp = temp->right;
                }
            }
        }
        printf("Do you want to add another node (y/n): ");
        scanf(" %c", &ch);
        
    } while (ch == 'y');
}

void inorder_r(treenode *root) {
    treenode *temp = root;
    if (temp != NULL) {
        inorder_r(temp->left);
        printf("%s ", temp->data);
        inorder_r(temp->right);
    }
}

void preorder_r(treenode *root) {
    treenode *temp = root;
    if (temp != NULL) {
        printf("%s ", temp->data);
        preorder_r(temp->left);
        preorder_r(temp->right);
    }
}

void postorder_r(treenode *root) {
    treenode *temp = root;
    if (temp != NULL) {
        postorder_r(temp->left);
        postorder_r(temp->right);
        printf("%s ", temp->data);
    }
}

#define STACK_SIZE 100
treenode* stack[STACK_SIZE]; 
int top = -1;

int isEmpty() {
    return top == -1;
}

void push(treenode* node) {
    if (top == STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack[++top] = node;
}

treenode* pop() {
    if (isEmpty()) {
        printf("Stack underflow!\n");
        return NULL;
    }
    treenode *node = stack[top--];
    return node;
}

void inorder_nonrec(treenode *root) {
    treenode *temp = root;
    while (1) {
        while (temp != NULL) {
            push(temp);
            temp = temp->left;
        }
        if (isEmpty()) {
            break;
        }
        temp = pop();
        printf("%s ", temp->data);
        temp = temp->right;
    }
}

void preorder_nonrec(treenode *root) {
    treenode *temp = root;
    while (1) {
        while (temp != NULL) {
            printf("%s ", temp->data);
            push(temp);
            temp = temp->left;
        }
        if (isEmpty()) {
            break;
        }
        temp = pop();
        temp = temp->right;
    }
}

void postorder_nonrec(treenode *root) {
    treenode *temp = root;
    while (1) {
        while (temp != NULL) {
            push(temp);
            temp = temp->left;
        }
        if (isEmpty()) {
            break;
        }
        if (stack[top]->right == NULL) {
            temp = pop();
            printf("%s ", temp->data);
        }
        while (!isEmpty() && stack[top]->right == temp){
            temp = pop();
            printf("%s ", temp->data);
        }
        if (isEmpty()) {
            break;
        }
        temp = stack[top]->right;
    }
}

#define QUEUE_SIZE 100
treenode* queue[QUEUE_SIZE];
int front = -1;
int rear = -1;

int isFull_q() {
    if (rear == QUEUE_SIZE - 1) return 1;
    else return 0;
}

int isEmpty_q() {
    if (rear == front) return 1;
    else return 0;
}

void enqueue(treenode* node) {
    if (isFull_q()) {
        printf("Queue is full\n");
    } else {
        rear++;
        queue[rear] = node;
    }
}

treenode* dequeue() {
    if (isEmpty_q()) {
        printf("Queue is empty\n");
        return NULL;
    } else {
        front++;
        return queue[front];
    }
}

void BFS(treenode *root) {
    treenode *temp = root;
    if (temp == NULL) {
        return;
    }
    enqueue(temp);
    while (!isEmpty_q()) {
        temp = dequeue();
        printf("%s ", temp->data);
        if (temp->left != NULL) {
            enqueue(temp->left);
        }
        if (temp->right != NULL) {
            enqueue(temp->right);
        }
    }
}

int main() {
    treenode *root = NULL;
    int choice;
    
    do {
        printf("\n1. Create Binary Tree Recursively.\n");
        printf("2. Create Binary Tree Non-Recursively.\n");
        printf("3. Inorder Traversal Recursively.\n");
        printf("4. Preorder Traversal Recursively.\n");
        printf("5. Postorder Traversal Recursively.\n");
        printf("6. Inorder Traversal Non-Recursively.\n");
        printf("7. Preorder Traversal Non-Recursively.\n");
        printf("8. Postorder Traversal Non-Recursively.\n");
        printf("9. Breadth First Traversal.\n");
        printf("10. Exit.\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice);
        
        switch(choice) {
            case 1:
                if (root != NULL) {
                    printf("Binary tree already exists.\n");
                    break;
                }
                root = (treenode*)malloc(sizeof(treenode));
                if (root == NULL) {
                    printf("Memory allocation failed!\n");
                    return 1;
                }
                printf("Enter data for the root node: ");
                scanf(" %[^\n]", root->data);
                getchar();
                root->left = NULL;
                root->right = NULL;
                
                create_r(root);
                printf("Binary tree creation complete.\n");
                break;
            case 2:
                if (root != NULL) {
                    printf("Binary tree already exists.\n");
                    break;
                }
                
                root = (treenode*)malloc(sizeof(treenode));
                if (root == NULL) {
                    printf("Memory allocation failed!\n");
                    return 1;
                }
                printf("Enter data for the root node: ");
                scanf(" %[^\n]", root->data);
                getchar();
                root->left = NULL;
                root->right = NULL;
                
                create_nr(root);
                printf("Binary tree creation complete.\n");
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorder_r(root);
                break;
            case 4:
                printf("Preorder Traversal: ");
                preorder_r(root);
                break;
            case 5:
                printf("Postorder Traversal: ");
                postorder_r(root);
                break;
            case 6:
                printf("Inorder Traversal: ");
                inorder_nonrec(root);
                break;
            case 7:
                printf("Preorder Traversal: ");
                preorder_nonrec(root);
                break;
            case 8:
                printf("Postorder Traversal: ");
                postorder_nonrec(root);
                break;
            case 9:
                printf("Breadth First Traversal: ");
                BFS(root);
                break;
            case 10:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while(choice != 10);
    return 0;
}
