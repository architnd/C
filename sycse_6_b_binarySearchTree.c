#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BST {
    char word[10];
    char meaning[20];
    struct BST *left;
    struct BST *right;
} BST;

void create(BST **root) {
    *root = (BST*)malloc(sizeof(BST));
    if (*root == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter word for the root node: ");
    scanf(" %[^\n]", (*root)->word);
    getchar();
    printf("Enter meaning for the root node: ");
    scanf(" %[^\n]", (*root)->meaning);
    getchar();

    (*root)->left = NULL;
    (*root)->right = NULL;

    char ch;
    do {
        printf("Do you want to add another node (y/n)? ");
        scanf(" %c", &ch);
        if(ch == 'y'){
            BST *temp = *root;
            int flag = 0;

            BST *curr = (BST*)malloc(sizeof(BST));
            if (curr == NULL) {
                printf("Memory allocation failed!\n");
                return;
            }

            printf("Enter word for the new node: ");
            scanf(" %[^\n]", curr->word);
            getchar();
            printf("Enter meaning for the new node: ");
            scanf(" %[^\n]", curr->meaning);
            getchar();

            curr->left = NULL;
            curr->right = NULL;

            while (flag == 0) {
                if (strcmp(curr->word, temp->word) < 0) {
                    if (temp->left == NULL) {
                        temp->left = curr;
                        flag = 1;
                    } else {
                        temp = temp->left;
                    }
                } else {
                    if (temp->right == NULL) {
                        temp->right = curr;
                        flag = 1;
                    } else {
                        temp = temp->right;
                    }
                }
            }
        }        
    } while (ch == 'y');
}

int search_r(BST *temp, char keyword[]) {
    int f = 0;
    if (temp != NULL) {
        int cmp = strcmp(keyword, temp->word);
        if (cmp == 0) {
            return 1;
        }
        if (cmp < 0) {
            f = search_r(temp->left, keyword);
        }
        if (cmp > 0) {
            f = search_r(temp->right, keyword);
        }
    }
    return f;
}

void search(BST *root) {
    int flag = 0;
    char keyword[10];

    printf("Enter string to be searched: ");
    scanf(" %[^\n]", keyword);
    getchar();

    flag = search_r(root, keyword);

    if (flag == 1) {
        printf("Keyword found.\n");
    } else {
        printf("Keyword not found.\n");
    }
}

void search_nr(BST *root) {
    int flag = 0;
    BST *temp = root;
    char keyword[10];

    printf("Enter string to be searched: ");
    scanf(" %[^\n]", keyword);
    getchar();
    
    while (flag == 0 && temp != NULL) {
        if (strcmp(keyword, temp->word) == 0) {
            flag = 1;
            break;
        } else if (strcmp(keyword, temp->word) < 0) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    
    if (flag == 1) {
        printf("Keyword found.\n");
    } else {
        printf("Keyword not found.\n");
    }
}

void insert_keyword(BST **root) {
    BST *temp = *root;
    int flag = 0;

    BST *curr = (BST*)malloc(sizeof(BST));
    if (curr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter word for the new node: ");
    scanf(" %[^\n]", curr->word);
    getchar();
    printf("Enter meaning for the new node: ");
    scanf(" %[^\n]", curr->meaning);
    getchar();

    curr->left = NULL;
    curr->right = NULL;

    while (flag == 0) {
        if (strcmp(curr->word, temp->word) < 0) {
            if (temp->left == NULL) {
                temp->left = curr;
                flag = 1;
            } else {
                temp = temp->left;
            }
        } else {
            if (temp->right == NULL) {
                temp->right = curr;
                flag = 1;
            } else {
                temp = temp->right;
            }
        }
    }
}

void delete_keyword(BST **root) {
    BST *parent = NULL;
    BST *curr = *root;
    char keyword[10];

    printf("Enter the keyword to delete: ");
    scanf(" %[^\n]", keyword);
    getchar();

    // Search for the keyword
    while (curr != NULL && strcmp(keyword, curr->word) != 0) {
        parent = curr;
        if (strcmp(keyword, curr->word) < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (curr == NULL) {
        printf("Keyword not found.\n");
        return;
    }

    // Deletion of root
    if (curr == *root) {
        if (curr->right == NULL) {
            *root = curr->left;
        }
        else if (curr->left == NULL) {
            *root = curr->right;
        }
        else if (curr->right != NULL && curr->left != NULL) {
            BST *temp = curr->left;
            *root = curr->right;
            BST *s = curr->right;
            while (s->left != NULL) {
                s = s->left;
            }
            s->left = temp;
        }
    }

    else {
        // deletion of a leaf
        if (curr->left == NULL && curr->right == NULL) {
            if (parent->left == curr)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        // deletion of a node with single child
        else if (curr->left == NULL) {
            if (parent->left == curr)
                parent->left = curr->right;
            else
                parent->right = curr->right;
        }
        else if (curr->right == NULL) {
            if (parent->left == curr)
                parent->left = curr->left;
            else
                parent->right = curr->left;
        }
        // deletion of a node with two children
        else {
            BST *s = curr->right;
            BST *temp = curr->left;
            while (s->left != NULL) {
                s = s->left;
            }
            s->left = temp;

            if (parent->left == curr)
                parent->left = curr->right;
            else
                parent->right = curr->right;
        }
    }
    curr->left = NULL;
    curr->right = NULL;
    free(curr);

    printf("Keyword deleted successfully.\n");
}

void mirror_r(BST *root) {
    if (root == NULL) {
        return;
    }
    BST *temp = root->left;
    root->left = root->right;
    root->right = temp;
    if (root->left != NULL) {
        mirror_r(root->left);
    }
    if (root->right != NULL) {
        mirror_r(root->right);
    }
}

#define QUEUE_SIZE 100
BST* queue[QUEUE_SIZE];
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

void enqueue(BST* node) {
    if (isFull_q()) {
        printf("Queue is full\n");
    } else {
        rear++;
        queue[rear] = node;
    }
}

BST* dequeue() {
    if (isEmpty_q()) {
        printf("Queue is empty\n");
        return NULL;
    } else {
        front++;
        return queue[front];
    }
}

void dispbfs(BST *root) {
    BST *temp = root;
    if (temp == NULL) {
        return;
    }
    enqueue(temp);
    while (!isEmpty_q()) {
        temp = dequeue();
        printf("%s ", temp->word);
        if (temp->left != NULL) {
            enqueue(temp->left);
        }
        if (temp->right != NULL) {
            enqueue(temp->right);
        }
    }
}

void mirror_nr(BST *root) {
    BST *temp = root;
    if (temp == NULL) {
        return;
    }
    enqueue(temp);
    while (!isEmpty_q()) {
        temp = dequeue();
        BST *temp_swap = temp->left;
        temp->left = temp->right;
        temp->right = temp_swap;
        if (temp->left != NULL) {
            enqueue(temp->left);
        }
        if (temp->right != NULL) {
            enqueue(temp->right);
        }
    } 
}

BST* copy_r(BST *root) {
    BST *temp = NULL;
    if (root != NULL) {
        temp = (BST*)malloc(sizeof(BST));
        strcpy(temp->word, root->word);
        strcpy(temp->meaning, root->meaning);
        temp->left = copy_r(root->left);
        temp->right = copy_r(root->right);
    }
    return temp;
}

#define STACK_SIZE 100

BST* stack1[STACK_SIZE]; 
int top1 = -1;

BST* stack2[STACK_SIZE];
int top2 = -1;

int isempty1() {
    return top1 == -1;
}

void push1(BST* node) {
    if (top1 == STACK_SIZE - 1) {
        printf("Stack 1 overflow!\n");
        return;
    }
    stack1[++top1] = node;
}

BST* pop1() {
    if (isempty1()) {
        return NULL;
    }
    BST *node = stack1[top1--];
    return node;
}

int isempty2() {
    return top2 == -1;
}

void push2(BST* node) {
    if (top2 == STACK_SIZE - 1) {
        printf("Stack 2 overflow!\n");
        return;
    }
    stack2[++top2] = node;
}

BST* pop2() {
    if (isempty2()) {
        return NULL;
    }
    BST *node = stack2[top2--];
    return node;
}

BST* copy_nr(BST *root2) {
    BST *root1 = NULL;
    
    if (root2 == NULL) {
        return NULL;
    }

    root1 = (BST*)malloc(sizeof(BST));
    if (root1 == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    BST *temp1 = root1;
    BST *temp2 = root2;

    strcpy(temp1->word, temp2->word);
    strcpy(temp1->meaning, temp2->meaning);

    while (1) {
        while (temp2 != NULL) {
            if (temp2->left != NULL) {
                temp1->left = (BST*)malloc(sizeof(BST));
                if (temp1->left == NULL) {
                    printf("Memory allocation failed!\n");
                    return NULL;
                }
                strcpy(temp1->left->word, temp2->left->word);
                strcpy(temp1->left->meaning, temp2->left->meaning);
            } else {
                temp1->left = NULL;
            }
            
            if (temp2->right != NULL) {
                temp1->right = (BST*)malloc(sizeof(BST));
                if (temp1->right == NULL) {
                    printf("Memory allocation failed!\n");
                    return NULL;
                }
                strcpy(temp1->right->word, temp2->right->word);
                strcpy(temp1->right->meaning, temp2->right->meaning);
            } else {
                temp1->right = NULL;
            }

            push1(temp1);
            push2(temp2);

            temp1 = temp1->left;
            temp2 = temp2->left;
        }
        
        if (isempty2()) {
            break;
        } else {
            temp1 = pop1();
            temp2 = pop2();

            temp1 = temp1->right;
            temp2 = temp2->right;
        }
    }
    return root1;
}

int main() {
    BST *root = NULL;
    BST *copied_root = NULL;
    int ch, ch1;
    char keyword[10];

    do {
        printf("\nDictionary Menu :-\n");
        printf("1. Create a dictionary.\n");
        printf("2. Search a keyword (recursively).\n");
        printf("3. Search a keyword (non-recursively).\n");
        printf("4. Insert a keyword.\n");
        printf("5. Delete a keyword.\n");
        printf("6. Mirror the dictionary (recursively).\n");
        printf("7. Mirror the dictionary (non-recursively).\n");
        printf("8. Copy the dictionary (recursively).\n");
        printf("9. Copy the dictionary (non-recursively).\n");
        printf("10. Display the dictionary (BFS).\n");
        printf("11. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1:
                if (root != NULL) {
                    printf("Dictionary already exists.\n");
                    break;
                } else {
                    create(&root);
                    printf("Dictionary created.\n");
                }
                break;
            case 2:
                search(root);
                break;
            case 3:
                search_nr(root);
                break;
            case 4:
                if(root == NULL){
                    printf("Create A Dictionary First");
                    break;
                }
                insert_keyword(&root);
                printf("Keyword Inserted.\n");
            case 5:
                if(root == NULL){
                    printf("Create A Dictionary First");
                    break;
                }
                delete_keyword(&root);
                printf("Keyword Deleted.\n");
            case 6:
                if(root == NULL){
                    printf("Create a dictionary first.\n");
                    break;
                }
                mirror_r(root);
                printf("Dictionary mirrored recursively.\n");
                break;
            case 7:
                if(root == NULL){
                    printf("Create a dictionary first.\n");
                    break;
                }
                mirror_nr(root);
                printf("Dictionary mirrored non-recursively.\n");
                break;
            case 8:
                if(root == NULL){
                    printf("Create a dictionary first.\n");
                    break;
                }
                copied_root = copy_r(root);
                if (copied_root != NULL) {
                    printf("Dictionary copied recursively.\n");
                }
                break;
            case 9:
                if(root == NULL){
                    printf("Create a dictionary first.\n");
                    break;
                }
                copied_root = copy_nr(root);
                if (copied_root != NULL) {
                    printf("Dictionary copied non-recursively.\n");
                }
                break;
            case 10:
                if (root == NULL) {
                    printf("Dictionary is empty.\n");
                    break;
                }
                if (copied_root != NULL){
                    printf("\nDo you want to display: \n1. Original Dictionary.\n2.Copied Dictionary.\n");
                    scanf("%d", &ch1);
                    if(ch1 == 1){
                        printf("Displaying dictionary (BFS): \n");
                        dispbfs(root);
                        printf("\n");
                    }
                    else if(ch1 == 2){
                        printf("Displaying copied dictionary (BFS): \n");
                        dispbfs(copied_root);
                        printf("\n");
                    }
                }else{
                    printf("Displaying dictionary (BFS): \n");
                    dispbfs(root);
                    printf("\n");
                }
                break;
            case 11:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (ch != 11);

    return 0;
}