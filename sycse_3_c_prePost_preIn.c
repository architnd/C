#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

char s[MAX][MAX];
int topS = -1;

int isEmptyS() {
    if (topS == -1) {
        return 1;
    } else {
        return 0;
    }
}

int isFullS() {
    if (topS == MAX - 1) {
        return 1;
    } else {
        return 0;
    }
}

void push_str(char str[MAX]) {
    if (isFullS()) {
        printf("Stack is full!\n");
    } else {
        topS = topS + 1;
        strcpy(s[topS], str);
    }
}

void pop_str(char str[MAX]) {
    if (isEmptyS()) {
        printf("Stack is empty!\n");
        str[0] = '\0';
    } else {
        strcpy(str, s[topS]);
        topS = topS - 1;
    }
}

void pre_infix(char pre[], char infix[]) {
    int l = strlen(pre);
    char x;
    char op1[MAX], op2[MAX], E1[MAX], t[2];

    for (int i = l - 1; i >= 0; i--) {
        x = pre[i];
        if (isalpha(x) || isdigit(x)) {
            t[0] = x;
            t[1] = '\0';
            push_str(t);
        } else {
            pop_str(op1);
            pop_str(op2);
            strcpy(E1, "(");
            strcat(E1, op1);
            t[0] = x;
            t[1] = '\0';
            strcat(E1, t);
            strcat(E1, op2);
            strcat(E1, ")");
            push_str(E1);
        }
    }
    pop_str(infix);
}

void pre_postfix(char pre[], char postfix[]) {
    int l = strlen(pre);
    char x;
    char op1[MAX], op2[MAX], E1[MAX], t[2];

    for (int i = l - 1; i >= 0; i--) {
        x = pre[i];
        if (isalpha(x) || isdigit(x)) {
            t[0] = x;
            t[1] = '\0';
            push_str(t);
        } else {
            pop_str(op1);
            pop_str(op2);
            strcpy(E1, op1);
            strcat(E1, op2);
            t[0] = x;
            t[1] = '\0';
            strcat(E1, t);
            push_str(E1);
        }
    }
    pop_str(postfix);
}

int main() {
    char pre[MAX], result[MAX];
    int ch;

    printf("Enter a Prefix expression: ");
    scanf("%s", pre);

    printf("Enter your choice:\n");
    printf("1. Convert to Infix\n");
    printf("2. Convert to Postfix\n");
    scanf("%d", &ch);

    switch (ch) {
        case 1: {
            pre_infix(pre, result);
            printf("Infix Expression: %s\n", result);
            break;
        }
        case 2: {
            pre_postfix(pre, result);
            printf("Postfix Expression: %s\n", result);
            break;
        }
        default: {
            printf("Invalid choice!\n");
            break;
        }
    }

    return 0;
}
