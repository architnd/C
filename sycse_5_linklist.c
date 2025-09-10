/*Department of Computer Engineering has student's club named 'Pinnacle club',Students of second,third and final year of department can be granted 
membership on request. Similarly, one may cancel the membership of the club. First node is reserved for president, last node for secretary.
Write a link list to store data of members, also
1) Add or delete members
2) Compute total members of club
3) Display members
4) sort 2 linked lists
5) merge 2 link lists
6) reverse using 3 pointers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int prn;
    char name[50];
    struct node *next;
};

void create_list(struct node *head) {
    struct node *next, *temp;
    char ch;
    
    temp = head;
    
    next = (struct node *)malloc(sizeof(struct node));
    if (next == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter name of president: ");
    scanf(" %[^\n]s", next->name);
    printf("Enter prn of president: ");
    scanf("%d", &next->prn);
    next->next = NULL;
    temp->next = next;
    temp = next;

    printf("Do you want to add another member? (y/n): ");
    scanf(" %c", &ch);

    while (ch == 'y' || ch == 'Y') {
        next = (struct node *)malloc(sizeof(struct node));
        if (next == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

        printf("Enter name: ");
        scanf(" %[^\n]s", next->name);
        printf("Enter prn: ");
        scanf("%d", &next->prn);
        next->next = NULL;
        
        temp->next = next;
        temp = next;

        printf("Do you want to add another member? (y/n): ");
        scanf(" %c", &ch);
    }
    next = (struct node *)malloc(sizeof(struct node));
    if (next == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter name of secretary: ");
    scanf(" %[^\n]s", next->name);
    printf("Enter prn of secretary: ");
    scanf("%d", &next->prn);
    next->next = NULL;
    temp->next = next;
}
int get_length(struct node *head) {
    int count = 0;
    struct node *temp = head->next;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
void addMember(struct node *head) {
    struct node *next, *temp;
    temp = head;
    next = (struct node *)malloc(sizeof(struct node));
    if (next == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter name: ");
    scanf(" %[^\n]s", next->name);
    printf("Enter prn: ");
    scanf("%d", &next->prn);
    next->next = NULL;
    temp->next = next;
}
void display_list(struct node *head) {
    if (head == NULL || head->next == NULL) {
        printf("List is empty.\n");
        return;
    }
    int l = get_length(head);
    struct node *temp = head->next;
    printf("\nPinnacle club Members: \n");
    printf("Sr. \t Name \t PRN \t Designation \n");
    int i = 1;
    while (temp != NULL) {
        if (i == 1){
            printf("%d. \t ", i);
            printf("%s \t ", temp->name);
            printf("%d \t ", temp->prn);
            printf("President \n");
        }
        else if(i == l){
            printf("%d. \t ", i);
            printf("%s \t ", temp->name);
            printf("%d \t ", temp->prn);
            printf("Secretary \n");

        } else{
            printf("%d. \t ", i);
            printf("%s\t ", temp->name);
            printf("%d \t ", temp->prn);
            printf("Member \n");
        }
        temp = temp->next;
        i++;
    }
    printf("\n");
}
int main(){
    struct node *head;
    head = (struct node *)malloc(sizeof(struct node));
    head->next = NULL;
    int ch;
    do{
        printf("\nPinnacle Club Membership:\n");
        printf("1. Create List\n");
        printf("2. Display List\n");
        printf("3. Add member\n");
        printf("4. Total Members\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1:
                create_list(head);
                break;
            case 2:
                display_list(head);
                break;
            case 3:
                addMember(head);
                break;
            case 4:
                printf("Total members = %d\n", get_length(head));
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (ch != 4);
    return 0;
}