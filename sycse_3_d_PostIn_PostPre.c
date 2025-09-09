#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

char s[MAX][MAX];
int topS = -1;

int isEmpty() {
    if (topS == -1) {
        return 1;
    } else {
        return 0;
    }
}

int isFull() {
    if (topS == MAX - 1) {
        return 1;
    } else {
        return 0;
    }
}

void push(char *str) { //changed from char str[MAX] to avoid overflow warning
    if (isFull()) {
        printf("Stack is full!\n");
    } else {
        topS = topS + 1;
        strcpy(s[topS], str);
    }
}

void pop(char str[MAX]) {
    if (isEmpty()) {
        printf("Stack is empty!\n");
        str[0] = '\0';
    } else {
        strcpy(str, s[topS]);
        topS = topS - 1;
    }
}

void post_infx(char inexp[MAX], char postexp[MAX]) {
    int i, l;
    char x[2], op1[MAX], op2[MAX], E1[MAX], op[2];
    l = strlen(inexp);

    for (i = 0; i < l; i++) {
        x[0] = inexp[i];
        x[1] = '\0';

        if (isalpha(x[0]) || isdigit(x[0])) {
            push(x);
        } else {
            pop(op2);
            pop(op1);
            E1[0] = '\0';
            strcat(E1, "(");
            strcat(E1, op1);
            op[0] = x[0]; op[1] = '\0';
            strcat(E1, op);
            strcat(E1, op2);
            strcat(E1, ")");
            push(E1);
        }
    }
    pop(postexp);
}

void post_pre(char inexp[MAX], char preexp[MAX]) {
    int i, l;
    char x[2], op1[MAX], op2[MAX], E1[MAX], op[2];
    l = strlen(inexp);

    for (i = 0; i < l; i++) {
        x[0] = inexp[i];
        x[1] = '\0';

        if (isalpha(x[0]) || isdigit(x[0])) {
            push(x);
        } else {
            pop(op2);
            pop(op1);
            E1[0] = '\0';
            op[0] = x[0]; op[1] = '\0';
            strcat(E1, op);
            strcat(E1, op1);
            strcat(E1, op2);
            push(E1);
        }
    }
    pop(preexp);
}

int main() {
    char inexp[MAX], postexp[MAX], preexp[MAX];
    int ch;

    printf("Enter a Postfix expression: ");
    scanf("%s", inexp);

    printf("Enter your choice: \n");
    printf("1. Postfix to Infix\n");
    printf("2. Postfix to Prefix\n");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            post_infx(inexp, postexp);
            printf("Infix Expression: %s\n", postexp);
            break;
        case 2:
            post_pre(inexp, preexp);
            printf("Prefix Expression: %s\n", preexp);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
    return 0;
}
