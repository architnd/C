#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int lq[SIZE];
int lfront, lrear;

void CREATEQ_LINEAR() {
    lfront = -1;
    lrear = -1;
}

int isfull_linear() {
    if (lrear == SIZE - 1) return 1;
    else return 0;
}

int isempty_linear() {
    if (lrear == lfront) return 1;
    else return 0;
}

void AddQ_linear(int elem) {
    if (isfull_linear()) {
        printf("Queue is full\n");
    } else {
        lrear++;
        lq[lrear] = elem;
        printf("Added: %d\n", elem);
    }
}

int DelQ_linear() {
    if (isempty_linear()) {
        printf("Queue is empty\n");
        return -1;
    } else {
        lfront++;
        int elem = lq[lfront];
        printf("Deleted: %d\n", elem);
        return elem;
    }
}

void DisplayQ_linear() {
    if (isempty_linear()) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements: ");
        for (int i = lfront + 1; i <= lrear; i++) {
            printf("%d ", lq[i]);
        }
        printf("\n");
    }
}

int cq[SIZE + 1];
int cfront, crear;

void CREATEQ_CIRCULAR() {
    cfront = 0;
    crear = 0;
}

int isfull_circular() {
    if ((crear + 1) % (SIZE + 1) == cfront) return 1;
    else return 0;
}

int isempty_circular() {
    if (crear == cfront) return 1;
    else return 0;
}

void AddQ_circular(int elem) {
    if (isfull_circular()) {
        printf("Queue is full\n");
    } else {
        crear = (crear + 1) % (SIZE + 1);
        cq[crear] = elem;
        printf("Added: %d\n", elem);
    }
}

int DelQ_circular() {
    if (isempty_circular()) {
        printf("Queue is empty\n");
        return -1;
    } else {
        cfront = (cfront + 1) % (SIZE + 1);
        int elem = cq[cfront];
        printf("Deleted: %d\n", elem);
        return elem;
    }
}

void DisplayQ_circular() {
    if (isempty_circular()) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements: ");
        int i = (cfront + 1) % (SIZE + 1);
        while (i != (crear + 1) % (SIZE + 1)) {
            printf("%d ", cq[i]);
            i = (i + 1) % (SIZE + 1);
        }
        printf("\n");
    }
}

int main() {
    int ch, elem, type;
    printf("Select Queue Type:\n1. Linear Queue\n2. Circular Queue\nEnter choice: ");
    scanf("%d", &type);
    switch (type) {
        case 1:
            CREATEQ_LINEAR();
            break;
        case 2:
            CREATEQ_CIRCULAR();
            break;
        default:
            printf("Invalid Queue Type\n");
            return 0;
    }
    do {
        printf("\n1. Add\n2. Delete\n3. Display\n4. Exit\nEnter operation: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter element to add: ");
                scanf("%d", &elem);
                if (type == 1)
                    AddQ_linear(elem);
                else
                    AddQ_circular(elem);
                break;
            case 2:
                if (type == 1)
                    DelQ_linear();
                else
                    DelQ_circular();
                break;
            case 3:
                if (type == 1)
                    DisplayQ_linear();
                else
                    DisplayQ_circular();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid operation\n");
        }
    } while (ch != 4);
    return 0;
}
