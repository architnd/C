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

void pre_infx(char inexp[MAX], char postexp[MAX]) {
    int i, l;
    char x[2], op1[MAX], op2[MAX], E1[MAX], op[2];
    l = strlen(inexp);

    for (i = l - 1; i >= 0; i--) {
        x[0] = inexp[i];
        x[1] = '\0';

        if (isalpha(x[0]) || isdigit(x[0])) {
            push(x);
        } else {
            pop(op1);
            pop(op2);
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

void pre_post(char inexp[MAX], char preexp[MAX]) {
    int i, l;
    char x[2], op1[MAX], op2[MAX], E1[MAX], op[2];
    l = strlen(inexp);

    for (i = l - 1; i >= 0; i--) {
        x[0] = inexp[i];
        x[1] = '\0';

        if (isalpha(x[0]) || isdigit(x[0])) {
            push(x);
        } else {
            pop(op1);
            pop(op2);
            E1[0] = '\0';
            strcat(E1, op1);
            strcat(E1, op2);
            op[0] = x[0]; op[1] = '\0';
            strcat(E1, op);
            push(E1);
        }
    }
    pop(preexp);
}

int main() {
    char inexp[MAX], postexp[MAX], preexp[MAX];
    int ch;

    printf("Enter a Prefix expression: ");
    scanf("%s", inexp);

    printf("Enter your choice: \n");
    printf("1. Prefix to Infix\n");
    printf("2. Prefix to Postfix\n");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            pre_infx(inexp, postexp);
            printf("Infix Expression: %s\n", postexp);
            break;
        case 2:
            pre_post(inexp, preexp);
            printf("Postfix Expression: %s\n", preexp);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
    return 0;
}
