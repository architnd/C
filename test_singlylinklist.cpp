#include<iostream>
using namespace std;
struct Node{
    int Data;
    struct Node* next;
};
Node* createNode(int Data){
    struct Node* n = new Node;
    n->Data = Data;
    n->next = NULL;
    return n;
}
void printList(struct Node* head){
    struct Node* temp = head;
    while (temp != NULL){
        cout << temp->Data << "\n";
        temp = temp->next;
    }
}
void printListReverse(struct Node* head){
    if (head->next !=  NULL){
        printListReverse(head->next);
    }
    cout << head->Data << "\n";
}
struct Node* ListReverse(struct Node* head){
    struct Node* current = head;
    struct Node* prev = NULL;
    struct Node* next = NULL;
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}
int main(){
    struct Node* head = createNode(15);
    struct Node* temp = head;
    temp->next = createNode(25);
    temp = temp->next;
    temp->next = createNode(35);
    temp = temp->next;
    temp->next = createNode(45);
    temp = head;
    printList(head);
    //printListReverse(head);
    head = ListReverse(head);
    printList(head);
    return 0;
}