#include <stdio.h>
#define MAX 5   // stack size

int stack[MAX];
int top = -1;

int isEmpty() {
    if (top == -1)
        return 1;
    else
        return 0;
}

int isFull() {
    if (top == MAX - 1)
        return 1;
    else
        return 0;
}

void push(int item) {
    if (isFull()) {
        printf("Stack is Full, Cannot push %d\n", item);
    }
    else {
        top++;
        stack[top] = item;
        printf("%d pushed into stack\n", item);
    }
}

int pop() {
    if (isEmpty()) {
        printf("Stack is Empty, Cannot pop\n");
        return -1;
    }
    else {
        int item = stack[top];
        top--;
        return item;
    }
}

int peek() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return -1;
    }
    else {
        return stack[top];
    }
}

void display() {
    if (isEmpty()) {
        printf("Stack is empty\n");
    }
    else {
        printf("Stack elements: ");
        for (int i = top; i >= 0; i--) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

int main() {
    int choice, item;

    do {
        printf("\nSTACK MENU :-\n");
        printf("1.Push\n");
        printf("2.Pop\n");
        printf("3.Peek\n");
        printf("4.Display stack\n");
        printf("5.Check if stack is empty\n");
        printf("6.Check if stack is full\n");
        printf("7.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &item);
                push(item);
                break;
            case 2:
                item = pop();
                if (item != -1)
                    printf("Popped element: %d\n", item);
                break;
            case 3:
                item = peek();
                if (item != -1)
                    printf("Top element: %d\n", item);
                break;
            case 4:
                display();
                break;
            case 5:
                if (isEmpty())
                    printf("Stack is empty\n");
                else
                    printf("Stack is not empty\n");
                break;
            case 6:
                if (isFull())
                    printf("Stack is full\n");
                else
                    printf("Stack is not full\n");
                break;
            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 7);

    return 0;
}
