/*
Department of Computer Engineering has student's club named 'Pinnacle Club'. Students of second,
third and final year of department can be granted membership on request. Similarly, one may cancel
the membership of club. First node is reserved for president of club and last node is reserved for the
secretary of the club. Write C program to maintain club member ‘s information using singly linked
list. Store student PRN and Name. Write functions to: a) Add and delete the members as well as
president or even secretary. b) Compute total number of members of club c) Display members d)
sorting of two linked list e) merging of two linked list f) Reversing using three pointers.
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int prn;
    char name[50];
    struct node *next;
};
int get_length(struct node *head) {
    int count = 0;
    struct node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
void insert_by_pos(struct node **head, int pos, int prn, const char* name) {
    int length = get_length(*head);
    if (pos > length || pos < 0) {
        printf("Cannot insert at this position.\n");
        return;
    }

    // Create new node
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newnode->prn = prn;
    strcpy(newnode->name, name);
    newnode->next = NULL;

    // Case 1: Insert at beginning (pos = 0)
    if (pos == 0) {
        newnode->next = *head;
        *head = newnode;
        return;
    }

    // Case 2: Traverse until position-1
    struct node *temp = *head;
    int i = 1;   // start from 1 because we already handled pos=0

    while (i < pos && temp != NULL) {
        temp = temp->next;
        i++;
    }

    newnode->next = temp->next;
    temp->next = newnode;
}
void create_list(struct node **head) {
    int prn;
    char name[20], ch;
    printf("Enter name of president: ");
    scanf(" %[^\n]s", name);
    printf("Enter prn of president: ");
    scanf("%d", &prn);
    insert_by_pos(head, 0, prn, name);
    printf("Enter name of secretary: ");
    scanf(" %[^\n]s", name);
    printf("Enter prn of secretary: ");
    scanf("%d", &prn);
    insert_by_pos(head, get_length(*head), prn, name);

    printf("Do you want to add another member? (y/n): ");
    scanf(" %c", &ch);
    while(ch == 'y' || ch == 'Y'){
        printf("Enter name of member: ");
        scanf(" %[^\n]s", name);
        printf("Enter prn of member: ");
        scanf("%d", &prn);
        insert_by_pos(head, get_length(*head)-1, prn, name);
        printf("Do you want to add another member? (y/n): ");
        scanf(" %c", &ch);
    }  
}
void addMember(struct node **head) {
    char designation[20], name[20], ch;
    int prn;
    printf("Enter designation (p/s/m): ");
    scanf(" %c", &ch);
    if (ch == 'p' || ch == 'P') {
        printf("Enter name of president: ");
        scanf(" %[^\n]s", name);
        printf("Enter prn of president: ");
        scanf("%d", &prn);
        insert_by_pos(head, 0, prn, name);
    } else if (ch == 's' || ch == 'S') {
        printf("Enter name of secretary: ");
        scanf(" %[^\n]s", name);
        printf("Enter prn of secretary: ");
        scanf("%d", &prn);
        insert_by_pos(head, get_length(*head), prn, name);
    } else if (ch == 'm' || ch == 'M') {
        printf("Enter name of member: ");
        scanf(" %[^\n]s", name);
        printf("Enter prn of member: ");
        scanf("%d", &prn);
        insert_by_pos(head, get_length(*head)-1, prn, name);
    } else {
        printf("Invalid designation.\n");
    }
}

void del_by_pos(struct node **head, int pos) {
    int length = get_length(*head);
    if (pos >= length || pos < 0) {
        printf("Cannot delete at this position.\n");
        return;
    }

    struct node *temp = *head;

    // Case 1: Delete at beginning (pos = 0)
    if (pos == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    // Case 2: Traverse until position-1
    int i = 1;   // start from 1 because we already handled pos=0
    struct node *prev = temp;

    while (i < pos && temp != NULL) {
        prev = temp;
        temp = temp->next;
        i++;
    }

    if (temp == NULL) return; // Position is out of bounds
    if(i == 1){
        temp = temp->next;
        prev->next = temp->next;
    }else{
        prev->next = temp->next;
    }
    
    free(temp);
}

void sort_by_prn(struct node **head) {
    int len = get_length(*head);
    if (len <= 1) return;

    struct node *prev, *temp;
    int i, j;

    for (i = 1; i < len; i++) {             
        prev = NULL;
        temp = *head;

        for (j = 0; j < len - i; j++) {     
            struct node *next = temp->next;
            if (next == NULL) break;

            if (temp->prn > next->prn) {
                // swap temp and next
                if (prev == NULL) {
                    // swapping at head
                    *head = next;
                } else {
                    prev->next = next;
                }
                temp->next = next->next;
                next->next = temp;

                // after swap, prev should point to new node
                prev = next;
            } else {
                // move forward
                prev = temp;
                temp = temp->next;
            }
        }
    }
}
void merge_lists(struct node **head, struct node **head2) {
    struct node *curr1 = *head;
    struct node *curr2 = *head2;

    if (curr1 == NULL) {
        *head = curr2;
        return;
    }
    if (curr2 == NULL) {
        return;
    }

    struct node *temp;
    int flag;

    if (curr1->prn < curr2->prn) {
        temp = curr1;
        curr1 = curr1->next;
        flag = 1;
    } else {
        temp = curr2;
        curr1 = curr2->next;
        flag = 0;
    }

    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->prn < curr2->prn) {
            temp->next = curr1;
            temp = curr1;
            curr1 = curr1->next;
        } else {
            temp->next = curr2;
            temp = curr2;
            curr2 = curr2->next;
        }
    }

    if (curr1 == NULL) {
        temp->next = curr2;
    } else if (curr2 == NULL) {
        temp->next = curr1;
    }
    
    if (flag == 1) {
        *head = *head;
        *head2 = NULL;
    } else {
        *head = *head2;
        *head2 = NULL;
    }
}
void reverse_list(struct node **head) {
    struct node *prev = NULL;
    struct node *curr = *head;
    struct node *temp = NULL;

    while (curr != NULL) {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    *head = prev;
}
void display_list(struct node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct node *temp = head;
    int i = 0;
    printf("\nPinnacle club Members: \n");
    printf("Sr. \t Name \t PRN \t Designation \n");
    while (temp != NULL) {
        if (i == 0){
            printf("%d. \t ", i+1);
            printf("%s \t ", temp->name);
            printf("%d \t ", temp->prn);
            printf("President \n");
        }else if (temp->next == NULL){
            printf("%d. \t ", i+1);
            printf("%s \t ", temp->name);
            printf("%d \t ", temp->prn);
            printf("Secretary \n");
        } else{
            printf("%d. \t ", i+1);
            printf("%s\t ", temp->name);
            printf("%d \t ", temp->prn);
            printf("Member \n");
        }
        temp = temp->next;
        i++;
    }
}
int main(){
    struct node *head = NULL;
    struct node *head2 = NULL;
    int ch, pos;
    do{
        printf("Pinnacle Club Membership:\n");
        printf("1. Create List.\n");
        printf("2. Display List.\n");
        printf("3. Add member.\n");
        printf("4. Delete member.\n");
        printf("5. Total Members\n");
        printf("6. Sort list.\n");
        printf("7. Merge lists.\n");
        printf("8. Reverse list.\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1:
                create_list(&head);
                break;
            case 2:
                display_list(head);
                break;
            case 3:
                addMember(&head);
                break;
            case 4:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                del_by_pos(&head, pos-1);
                break;
            case 5:
                printf("Total members = %d\n", get_length(head));
                break;
            case 6:
                sort_by_prn(&head);
                break;
            case 7:
                printf("Creating 2nd list:\n");
                create_list(&head2);
                printf("2nd list created. \n");
                sort_by_prn(&head);
                printf("First list sorted.\n");
                sort_by_prn(&head2);
                printf("Second list sorted.\n");
                merge_lists(&head, &head2);
                printf("Lists merged.\n");
                break;
            case 8:
                reverse_list(&head);
                break; 
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (ch != 9);
    return 0;
}