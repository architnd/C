#include<stdio.h>
#include<malloc.h>
struct myStruct{
    char x;
    long a, b;
    char c, d, e, f;
    //int x;
};
void swap(int *a, int  *b){
    int temp = *a;
    *a  = *b;
    *b = temp;
}
char* myMalloc(){
    char *temp = malloc(1024);
    return temp;
}
void myMalloc2(char **c){
    *c = malloc(1024);
}
int main(){

    unsigned char *ptr = malloc(1024);
    unsigned char *temp = ptr;
    #if 0
    for (int i = 0; i < 256; i++){
        //ptr[i] = i;

        //*(ptr + i) = i;

        *temp = i;
        temp++;
    }
    temp = ptr;
    for (int i = 0; i < 256; i++){
        printf(" %d \n", temp[i]);
    }
    #endif
    #if 0
    int *ptr1 = (int*)ptr;
    for (int i = 0; i < 256; i++){
        *ptr1 = i;
        ptr1++;
    }
    ptr1 = (int*)ptr;
    for (int i = 0; i < 256; i++){
        printf(" %d \n", ptr1[i]);
    }
    free(ptr);
    #endif
    //
    int x = 10, y = 20;
    swap(&x, &y);
    printf(" %d %d \n", x, y);
    //
    char *ptr2 = myMalloc();
    char *ptr3;
    myMalloc2(&ptr3);
    //
    char *(*func)() = myMalloc;
    char *ptr4 = func();

    void (*func2)() = myMalloc2;
    char *ptr5;
    func2(&ptr5);

    printf(" %ld \n", sizeof(struct myStruct));
    return 0;
}