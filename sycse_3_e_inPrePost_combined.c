// in_post,in_pre only for characters, doesn't work properly for spaces.
//code doesn't work for 2 digit nums as well.
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

void in_pre(char inexp[], char preexp[]) {
    int i, k = 0;
    char tkn;
    char temp[MAX];
    
    int j = strlen(inexp);

    for (i = j - 1; i >= 0; i--) {
        tkn = inexp[i];
        if (isalpha(tkn) || isdigit(tkn)) {
            temp[k++] = tkn;
        }
        else {
            if (tkn == ')') {
                push(tkn);
            }
            else if (tkn == '(') {
                while (!isEmpty() && peek() != ')') {
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
// POST
char s[MAX][MAX];
int topS = -1;

int isEmpty_str() {
    if (topS == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int isFull_str() {
    if (topS == MAX - 1) {
        return 1;
    }
    else {
        return 0;
    }
}


void push_str(char *str) { //changed from char str[MAX] to avoid overflow warning
    if (isFull_str()) {
        printf("Stack is full!\n");
    } else {
        topS = topS + 1;
        strcpy(s[topS], str);
    }
}

void pop_str(char str[MAX]) {
    if (isEmpty_str()) {
        printf("Stack is empty!\n");
        str[0] = '\0';
    } else {
        strcpy(str, s[topS]);
        topS = topS - 1;
    }
}

void post_infx(char postexp[MAX], char inexp[MAX]) {
    int i, l;
    char x[2], op1[MAX], op2[MAX], E1[MAX], op[2];
    l = strlen(postexp);

    for (i = 0; i < l; i++) {
        x[0] = postexp[i];
        x[1] = '\0';

        if (isalpha(x[0]) || isdigit(x[0])) {
            push_str(x);
        } else {
            pop_str(op2);
            pop_str(op1);
            E1[0] = '\0';
            strcat(E1, "(");
            strcat(E1, op1);
            op[0] = x[0]; op[1] = '\0';
            strcat(E1, op);
            strcat(E1, op2);
            strcat(E1, ")");
            push_str(E1);
        }
    }
    pop_str(inexp);
}

void post_pre(char postexp[MAX], char preexp[MAX]) {
    int i, l;
    char x[2], op1[MAX], op2[MAX], E1[MAX], op[2];
    l = strlen(postexp);

    for (i = 0; i < l; i++) {
        x[0] = postexp[i];
        x[1] = '\0';

        if (isalpha(x[0]) || isdigit(x[0])) {
            push_str(x);
        } else {
            pop_str(op2);
            pop_str(op1);
            E1[0] = '\0';
            op[0] = x[0]; op[1] = '\0';
            strcat(E1, op);
            strcat(E1, op1);
            strcat(E1, op2);
            push_str(E1);
        }
    }
    pop_str(preexp);
}

//PRE
void pre_infx(char preexp[MAX], char inexp[MAX]) {
    int i, l;
    char x[2], op1[MAX], op2[MAX], E1[MAX], op[2];
    l = strlen(preexp);

    for (i = l - 1; i >= 0; i--) {
        x[0] = preexp[i];
        x[1] = '\0';

        if (isalpha(x[0]) || isdigit(x[0])) {
            push_str(x);
        } else {
            pop_str(op1);
            pop_str(op2);
            E1[0] = '\0';
            strcat(E1, "(");
            strcat(E1, op1);
            op[0] = x[0]; op[1] = '\0';
            strcat(E1, op);
            strcat(E1, op2);
            strcat(E1, ")");
            push_str(E1);
        }
    }
    pop_str(inexp);
}

void pre_post(char preexp[MAX], char postexp[MAX]) {
    int i, l;
    char x[2], op1[MAX], op2[MAX], E1[MAX], op[2];
    l = strlen(preexp);

    for (i = l - 1; i >= 0; i--) {
        x[0] = preexp[i];
        x[1] = '\0';

        if (isalpha(x[0]) || isdigit(x[0])) {
            push_str(x);
        } else {
            pop_str(op1);
            pop_str(op2);
            E1[0] = '\0';
            strcat(E1, op1);
            strcat(E1, op2);
            op[0] = x[0]; op[1] = '\0';
            strcat(E1, op);
            push_str(E1);
        }
    }
    pop_str(postexp);
}

int main() {
    char inexp[MAX], postexp[MAX], preexp[MAX];
    int ch;

    printf("Enter your choice: \n");
    printf("1. Infix to Postfix \n");
    printf("2. Infix to Prefix\n");
    printf("3. Postfix to Infix\n");
    printf("4. Postfix to Prefix\n");
    printf("5. Prefix to Postfix\n");
    printf("6. Prefix to Infix\n");
    scanf("%d", &ch);

    switch(ch) {
        case 1:
            printf("Enter an infix expression: ");
            scanf("%s", inexp);
            in_post(inexp, postexp);
            printf("Postfix Expression: %s\n", postexp);
            break;
        case 2:
            printf("Enter an infix expression: ");
            scanf("%s", inexp);
            in_pre(inexp, preexp);
            printf("Prefix Expression: %s\n", preexp);
            break;
        case 3:
            printf("Enter a Postfix expression: ");
            scanf("%s", postexp);
            post_infx(postexp, inexp);
            printf("Infix Expression: %s\n", inexp);
            break;
        case 4:
            printf("Enter a Postfix expression: ");
            scanf("%s", postexp);
            post_pre(postexp, preexp);
            printf("Prefix Expression: %s\n", preexp);
            break;
        case 5:
            printf("Enter a Prefix expression: ");
            scanf("%s", preexp);
            pre_post(preexp, postexp);
            printf("Infix Expression: %s\n", postexp);
            break;
        case 6:
            printf("Enter a Prefix expression: ");
            scanf("%s", preexp);
            pre_infx(preexp, inexp);
            printf("Infix Expression: %s\n", inexp);
            break;
        default:
            printf("Invalid choice \n");
            break;
    }
    return 0;
}