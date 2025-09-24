#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tbtnode{
    char data[10];
    int lbit, rbit;
    struct tbtnode *leftc;
    struct tbtnode *rightc;
} tbtnode;

void create(tbtnode **head){
    char ch, ch1;
    tbtnode *temp, *curr;
    tbtnode *root = (tbtnode*)malloc(sizeof(tbtnode));
    if (root == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter data for the root node: ");
    scanf(" %[^\n]", root->data);
    getchar();
    (*head)->lbit = 1;
    root->leftc = *head;
    root->rightc = *head;
    root->lbit = 0;
    root->rbit = 0;
    (*head)->leftc = root;
    do{
        printf("Do you want to add another node (y/n)? ");
        scanf(" %c", &ch);
        if (ch == 'y'){
            int flag = 0;
            temp = root;
            curr = (tbtnode*)malloc(sizeof(tbtnode));
            if (root == NULL) {
                printf("Memory allocation failed!\n");
                return;
            }
            printf("Enter data for new node: ");
            scanf(" %[^\n]", curr->data);
            curr->lbit = 0;
            curr->rbit = 0;
            while (flag == 0){
                printf("Do you want to add data to the left or right of '%s' (l/r)? ", temp->data);
                scanf(" %c", &ch1);
                if (ch1 == 'l'){
                    if (temp->lbit == 0){
                        curr->rightc = temp;
                        curr->leftc = temp->leftc;
                        temp->leftc = curr;
                        temp->lbit = 1;
                        flag = 1;
                    }else{
                        temp = temp->leftc;
                    }
                }
                if (ch1 == 'r'){
                    if (temp->rbit == 0){
                        curr->leftc = temp;
                        curr->rightc = temp->rightc;
                        temp->rightc = curr;
                        temp->rbit = 1;
                        flag = 1;
                    }else{
                        temp = temp->rightc;
                    }
                }
            }
        }
    }while(ch == 'y');
}

tbtnode* inordesucc(tbtnode *temp){
    tbtnode *x = temp->rightc;
    if (temp->rbit == 1){
        while (x->lbit == 1){
            x = x->leftc;
        }
    }
    return x;
}

void inorder(tbtnode *head){
    tbtnode *temp = head;
    while (1){
        temp = inordesucc(temp);
        if (temp == head) break;
        printf(" %s", temp->data);
    }
}

void preorder(tbtnode *head){
    tbtnode *temp = head->leftc;
    while (temp != head){
        printf(" %s", temp->data);
        while(temp->lbit != 0){
            temp = temp->leftc;
            printf(" %s", temp->data);
        }
        while(temp->rbit == 0){
            temp = temp->rightc;
        }
        temp = temp->rightc;
    }
}

int main(){
    int ch;
    tbtnode *head = (tbtnode*)malloc(sizeof(tbtnode));
    if (head == NULL){
        printf("Memory allocation failed! \n");
        return 1;
    }
    head->rbit = 1;
    head->lbit = 0;
    head->leftc = head;
    head->rightc = head;
     do {
        printf("\n1. Create Threaded Binary Tree.\n");
        printf("2. Inorder Traversal.\n");
        printf("3. Preorder Traversal.\n");
        printf("4. Exit.\n");
        printf("Enter your choice: ");
        scanf(" %d", &ch);
        
        switch(ch) {
            case 1:
                if (head->leftc != head) {
                    printf("Binary tree already exists.\n");
                    break;
                }
                create(&head);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(head);
                printf("\n");
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorder(head);
                printf("\n");
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while(ch != 4);
    return 0;

}