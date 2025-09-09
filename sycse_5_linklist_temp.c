#include <stdio.h>
#include <stdlib.h>

// Data structure for a node in a singly linked list
struct node {
    int data;
    struct node *next;
};

// Global head pointer
struct node *head = NULL;

// Function to create a new linked list
void create_list() {
    struct node *next, *temp;
    char choice = 'y';
    
    // Allocate a head node
    if (head == NULL) {
        head = (struct node *)malloc(sizeof(struct node));
        head->next = NULL;
    }
    
    temp = head;
    
    while (choice == 'y' || choice == 'Y') {
        // Allocate memory for the new node
        next = (struct node *)malloc(sizeof(struct node));
        if (next == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

        printf("Enter data: ");
        scanf("%d", &next->data);
        next->next = NULL;
        
        temp->next = next;
        temp = next;

        printf("Do you want to add another node? (y/n): ");
        scanf(" %c", &choice);
    }
}

// Function to display the linked list
void display_list() {
    if (head == NULL || head->next == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    struct node *temp = head->next;
    printf("\n--- Linked List --- \n");
    while (temp != NULL) {
        printf("Data: %d\n", temp->data);
        temp = temp->next;
    }
    printf("--------------------\n");
}

// Function to get the length of the linked list
int get_length() {
    int count = 0;
    struct node *temp = head->next;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Function to insert a node at a given position
void insert_by_position() {
    int pos;
    printf("Enter position to insert: ");
    scanf("%d", &pos);

    int length = get_length();
    if (pos > length + 1) {
        printf("Cannot insert at this position.\n");
        return;
    }
    
    struct node *temp = head;
    int i = 1;
    
    struct node *next = (struct node *)malloc(sizeof(struct node));
    if (next == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter data for the new node: ");
    scanf("%d", &next->data);
    
    while (temp != NULL && i < pos) {
        i++;
        temp = temp->next;
    }
    
    next->next = temp->next;
    temp->next = next;
    printf("Node inserted successfully.\n");
}

// Function to delete a node at a given position
void delete_by_position() {
    int pos;
    printf("Enter position of the node to delete: ");
    scanf("%d", &pos);

    int length = get_length();
    if (pos > length || pos <= 0) {
        printf("Cannot delete from this position.\n");
        return;
    }
    
    struct node *prev = head;
    struct node *temp = head->next;
    int i = 1;
    
    while (temp != NULL && i < pos) {
        i++;
        prev = temp;
        temp = temp->next;
    }
    
    prev->next = temp->next;
    temp->next = NULL;
    free(temp);
    
    printf("Node deleted successfully.\n");
}

// Function to reverse the linked list
void reverse_list() {
    struct node *prev = NULL;
    struct node *temp = head->next;
    struct node *next = NULL;
    
    while (temp != NULL) {
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    
    head->next = prev;
    printf("List reversed successfully.\n");
}

// Main function to run the program
int main() {
    int choice;
    do {
        printf("\n--- Singly Linked List Operations ---\n");
        printf("1. Create a List\n");
        printf("2. Display the List\n");
        printf("3. Get List Length\n");
        printf("4. Insert a Node by Position\n");
        printf("5. Delete a Node by Position\n");
        printf("6. Reverse the List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                create_list();
                break;
            case 2:
                display_list();
                break;
            case 3:
                printf("\nTotal number of nodes: %d\n", get_length());
                break;
            case 4:
                insert_by_position();
                break;
            case 5:
                delete_by_position();
                break;
            case 6:
                reverse_list();
                break;
            case 7:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
    // Free all allocated memory before exiting
    struct node *temp = head;
    while (temp != NULL) {
        struct node *next = temp->next;
        free(temp);
        temp = next;
    }
    head = NULL;
    
    return 0;
}