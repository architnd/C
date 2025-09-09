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

void post_infix(char post[], char infix[]) {
    int l = strlen(post);
    char x;
    char op1[MAX], op2[MAX], E1[MAX], t[2];

    for (int i = 0; i < l; i++) {
        x = post[i];
        if (isalpha(x) || isdigit(x)) {
            t[0] = x;
            t[1] = '\0';
            push_str(t);
        } else {
            pop_str(op2);
            pop_str(op1);
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

void post_prefix(char post[], char prefix[]) {
    int l = strlen(post);
    char x;
    char op1[MAX], op2[MAX], E1[MAX], t[2];

    for (int i = 0; i < l; i++) {
        x = post[i];
        if (isalpha(x) || isdigit(x)) {
            t[0] = x;
            t[1] = '\0';
            push_str(t);
        } else {
            pop_str(op2);
            pop_str(op1);
            t[0] = x;
            t[1] = '\0';
            strcpy(E1, t);
            strcat(E1, op1);
            strcat(E1, op2);
            push_str(E1);
        }
    }
    pop_str(prefix);
}

int main() {
    char post[MAX], result[MAX];
    int ch;

    printf("Enter a Postfix expression: ");
    scanf("%s", post);

    printf("Enter your choice:\n");
    printf("1. Convert to Infix\n");
    printf("2. Convert to Prefix\n");
    scanf("%d", &ch);

    switch (ch) {
        case 1: {
            post_infix(post, result);
            printf("Infix Expression: %s\n", result);
            break;
        }
        case 2: {
            post_prefix(post, result);
            printf("Prefix Expression: %s\n", result);
            break;
        }
        default: {
            printf("Invalid choice!\n");
            break;
        }
    }

    return 0;
}
