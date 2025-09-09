#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

char stack[MAX];
int top = -1;

int isEmpty() {
    if (top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int isFull() {
    if (top == MAX - 1) {
        return 1;
    }
    else {
        return 0;
    }
}

void push(char item) {
    if (isFull()) {
        printf("Stack Overflow\n");
    }
    else {
        top = top + 1;
        stack[top] = item;
    }
}

char pop() {
    char temp;
    if (!isEmpty()) {
        temp = stack[top];
        top = top - 1;
        return temp;
    }
    else {
        return '\0';
    }
}

char peek() {
    if (top == -1) {
        return '\0';
    }
    else {
        return stack[top];
    }
}

// for Postfix
int icp(char ch) {
    if (ch == '+' || ch == '-') return 1;
    else if (ch == '/' || ch == '*' || ch == '%') return 2;
    else if (ch == '^') return 4;
    else if (ch == '(') return 5;
    else return 0;
}

int isp(char ch) {
    if (ch == '+' || ch == '-') return 1;
    else if (ch == '/' || ch == '*' || ch == '%') return 2;
    else if (ch == '^') return 3;
    else return 0;
}

// for Prefix
int icp1(char ch) {
    if (ch == '+' || ch == '-') return 1;
    else if (ch == '/' || ch == '*' || ch == '%') return 2;
    else if (ch == '^') return 3;
    else if (ch == '(') return 5;
    else return 0;
}

int isp1(char ch) {
    if (ch == '+' || ch == '-') return 1;
    else if (ch == '/' || ch == '*' || ch == '%') return 2;
    else if (ch == '^') return 4;
    else return 0;
}
#if 0
void reverseString(char str[]) {
    int i = 0, j = strlen(str) - 1;
    char temp;

    while (i < j) {

        temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        if (str[i] == '(') str[i] = ')';
        else if (str[i] == ')') str[i] = '(';

        if (str[j] == '(') str[j] = ')';
        else if (str[j] == ')') str[j] = '(';

        i++;
        j--;
    }

    // for odd length
    if (i == j) {
        if (str[i] == '(') str[i] = ')';
        else if (str[i] == ')') str[i] = '(';
    }
}
#endif

void in_post(char inexp[], char postexp[]) {
    int i = 0, k = 0;
    char tkn;

    while ((tkn = inexp[i]) != '\0') {
        if (isalpha(tkn) || isdigit(tkn)) {
            postexp[k++] = tkn;
        }
        else {
            if (tkn == '(') {
                push(tkn);
            }
            else if (tkn == ')') {
                while (!isEmpty() && peek() != '(') {
                    postexp[k++] = pop();
                }
                pop();
            }
            else {
                while (!isEmpty() && isp(peek()) >= icp(tkn)) {
                    postexp[k++] = pop();
                }
                push(tkn);
            }
        }
        i++;
    }

    while (!isEmpty()) {
        postexp[k++] = pop();
    }
    postexp[k] = '\0';
}
#if 0
void in_pre(char inexp[], char preexp[]) {
    int i = 0, k = 0;
    char tkn;

    reverseString(inexp);

    while ((tkn = inexp[i]) != '\0') {
        if (isalpha(tkn) || isdigit(tkn)) {
            preexp[k++] = tkn;
        }
        else {
            if (tkn == '(') {
                push(tkn);
            }
            else if (tkn == ')') {
                while (!isEmpty() && peek() != '(') {
                    preexp[k++] = pop();
                }
                pop(); 
            }
            else {
                while (!isEmpty() && isp1(peek()) >= icp1(tkn)) {
                    preexp[k++] = pop();
                }
                push(tkn);
            }
        }
        i++;
    }

    while (!isEmpty()) {
        preexp[k++] = pop();
    }
    preexp[k] = '\0';

    reverseString(preexp);
}
#endif
#if 0
void in_pre(char inexp[], char preexp[]) {
    int i, k = 0;
    char tkn;

    for (i = strlen(inexp) - 1; i >= 0; i--) {
        tkn = inexp[i];

        if (tkn == '(') tkn = ')';
        else if (tkn == ')') tkn = '(';

        
        if (isalpha(tkn) || isdigit(tkn)) {
            preexp[k++] = tkn;
        }
        else {
            if (tkn == '(') {
                push(tkn);
            }
            else if (tkn == ')') {
                while (!isEmpty() && peek() != '(') {
                    preexp[k++] = pop();
                }
                pop();
            }
            else {
                while (!isEmpty() && isp1(peek()) >= icp1(tkn)) {
                    preexp[k++] = pop();
                }
                push(tkn);
            }
        }
    }

    while (!isEmpty()) {
        preexp[k++] = pop();
    }
    preexp[k] = '\0';

}
#endif
#if 1
void in_pre(char inexp[], char preexp[]) {
    int i, k = 0;
    char tkn;
    char temp[MAX];
    
    int j = strlen(inexp);

    for (i = j - 1; i >= 0; i--) {
        tkn = inexp[i];

        if (tkn == '(') tkn = ')';
        else if (tkn == ')') tkn = '(';

        if (isalpha(tkn) || isdigit(tkn)) {
            temp[k++] = tkn;
        }
        else {
            if (tkn == '(') {
                push(tkn);
            }
            else if (tkn == ')') {
                while (!isEmpty() && peek() != '(') {
                    temp[k++] = pop();
                }
                pop();
            }
            else {
                while (!isEmpty() && isp1(peek()) >= icp1(tkn)) {
                    temp[k++] = pop();
                }
                push(tkn);
            }
        }
    }

    while (!isEmpty()) {
        temp[k++] = pop();
    }
    temp[k] = '\0';

    j = 0;
    for (i = k - 1; i >= 0; i--) {
        preexp[j++] = temp[i];
    }
    preexp[j] = '\0';
}

#endif

int main() {
    char inexp[MAX], postexp[MAX], preexp[MAX];
    int ch;

    printf("Enter an infix expression: ");
    scanf("%s", inexp);

    printf("Enter your choice: \n");
    printf("1. Postfix \n");
    printf("2. Prefix \n");
    scanf("%d", &ch);

    switch(ch) {
        case 1:
            in_post(inexp, postexp);
            printf("Postfix Expression: %s\n", postexp);
            break;
        case 2:
            in_pre(inexp, preexp);
            printf("Prefix Expression: %s\n", preexp);
            break;
        default:
            printf("Invalid choice \n");
            break;
    }

    return 0;
}
