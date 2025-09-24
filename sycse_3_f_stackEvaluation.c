#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 50

int stack[MAX];
int top = -1;

int isEmpty() {
    return top == -1;
}

int isFull() {
    return top == MAX - 1;
}

void push(int item) {
    if (isFull()) {
        printf("Stack Overflow\n");
    }
    else {
        stack[++top] = item;
    }
}

int pop() {
    if (!isEmpty()) {
        return stack[top--];
    }
    else {
        return -1;
    }
}

int applyOp(int a, int b, char op) {
    switch(op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                printf("Division by zero\n");
                return -1;
            } else{
                return a / b;
            }
        case '%':
            if (b == 0) {
                printf("Division by zero\n");
                return -1;
            } else{
                return a % b;
            }
        case '^': {
            int result = 1;
            for (int i = 0; i < b; i++){
                result *= a;
            }
            return result;
        }
        default:
            return 0;
    }
}

int evaluatePostfix(char* postfix) {
    int i = 0;
    while (postfix[i] != '\0') {
        char ch = postfix[i];

        if (isspace(ch)) {
            i++;
            continue;
        }

        if (isdigit(ch)) {
            int num = 0;

            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            push(num);
        }
        else {
            int b = pop();
            int a = pop();
            int result = applyOp(a, b, ch);
            push(result);
            i++;
        }
    }

    return pop();  
}

int main() {
    char postfix[MAX];

    printf("Enter a postfix expression: ");
    scanf(" %[^\n]", postfix);
    getchar();

    int result = evaluatePostfix(postfix);
    printf("Result = %d\n", result);

    return 0;
}
