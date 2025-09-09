#include <stdio.h>

#define MAX 10
#define MAXNZ 30

void accept(int row, int col, int A[MAX][MAX]) {
    printf("Enter the Matrix values:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &A[i][j]);
        }
    }
}

void display1(int row, int col, int A[MAX][MAX]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf(" %d \t", A[i][j]);
        }
        printf("\n");
    }
}

void display2(int S[MAXNZ][3], int nz) {
    for (int i = 0; i <= nz; i++) {
        printf("%d \t %d \t %d \n", S[i][0], S[i][1], S[i][2]);
    }
}

void simpleTranspose(int S[MAXNZ][3], int T[MAXNZ][3], int nz) {
    int m = S[0][0], n = S[0][1], t = S[0][2];
    T[0][0] = n;
    T[0][1] = m;
    T[0][2] = t;
    if (t <= 0) return;
    int q = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= t; j++) {
            if (S[j][1] == i) {
                T[q][0] = S[j][1];
                T[q][1] = S[j][0];
                T[q][2] = S[j][2];
                q++;
            }
        }
    }
}

void fastTranspose(int S[MAXNZ][3], int T[MAXNZ][3], int nz) {
    int m = S[0][0], n = S[0][1], t = S[0][2];
    T[0][0] = n;
    T[0][1] = m;
    T[0][2] = t;
    if (t <= 0) return;

    int T1[MAX] = {0}, T2[MAX];

    for (int i = 1; i <= t; i++) {
        int col = S[i][1];
        T1[col]++;
    }

    T2[0] = 1;
    for (int i = 1; i < n; i++) {
        T2[i] = T2[i - 1] + T1[i - 1];
    }

    for (int i = 1; i <= t; i++) {
        int col = S[i][1];
        int pos = T2[col];
        T[pos][0] = S[i][1];
        T[pos][1] = S[i][0];
        T[pos][2] = S[i][2];
        T2[col]++;
    }
}

int main(void) {
    int row, col, ch;
    printf("Enter number of rows, cols: ");
    if (scanf("%d %d", &row, &col) != 2) return 0;

    int M[MAX][MAX];
    accept(row, col, M);

    printf("\nInitial Matrix:\n");
    display1(row, col, M);

    int k = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (M[i][j] != 0) k++;

    int nz = k;
    int S[MAXNZ][3], T[MAXNZ][3];

    S[0][0] = row;
    S[0][1] = col;
    S[0][2] = nz;

    int p = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (M[i][j] != 0) {
                S[p][0] = i;
                S[p][1] = j;
                S[p][2] = M[i][j];
                p++;
            }
        }
    }

    printf("\nCompact Sparse Matrix:\n");
    display2(S, nz);

    printf("\nEnter Type of Transpose:\n");
    printf("1. Simple Transpose\n");
    printf("2. Fast Transpose\n");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            simpleTranspose(S, T, nz);
            printf("\nSimple Transpose (Triple form):\n");
            display2(T, nz);
            break;
        case 2:
            fastTranspose(S, T, nz);
            printf("\nFast Transpose (Triple form):\n");
            display2(T, nz);
            break;
        default:
            printf("Invalid option\n");
            break;
    }

    return 0;
}