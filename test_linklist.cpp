#include<iostream>
using namespace std;
struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
};
Node* createNode(int data){
    struct Node* n = new Node;
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}
int main(){
    struct Node* head = createNode(10);
    struct Node* tail = NULL; 
    struct Node* temp = head;
    
    temp->next = createNode(20);
    temp->next->prev = temp;
    
    temp = temp->next;
    temp->next = createNode(30);
    temp->next->prev = temp;

    temp = temp->next;
    temp->next = createNode(40);
    temp->next->prev = temp;
    tail = temp->next;
    temp = head;
    #if 0
    while (temp != NULL){
        cout << temp->data << "\n";
        temp = temp->next;
    }
    temp = tail;
    while (temp != NULL){
        cout << temp->data << "\n";
        temp = temp->prev;
    }
    #endif
    while (temp != NULL){
        cout << temp->data << "\n";
        if (temp->next == NULL){
            break;
        }
        temp = temp->next;
    }
    while (temp != NULL){
        cout << temp->data << "\n";
        temp = temp->prev;
    }
     
    return 0;
}