#include<stdio.h>
#include<string.h>
struct student{
	int rno;
	char name[20];
	float perc;
};
void accept(struct student s1[60], int n){
	for (int i = 0; i < n; i++){
		printf("Enter rno:");
		scanf("%d", &s1[i].rno);
		printf("Enter name:");
		scanf("%s", s1[i].name);
		printf("Enter perc:");
		scanf("%f", &s1[i].perc);
	}
}
void display(struct student s1[60], int n){
	printf("rno \t name \t  perc\n");
	for (int i = 0; i < n; i++){
		printf("%d \t", s1[i].rno);
		printf("%s \t", s1[i].name);
		printf("%f \n", s1[i].perc);
	}
}
void bubbleSort(struct student s1[60], int n){
	int pass = 1;
	for (int i = 0; i < n-1; i++){
		for (int j = 0; j  <  n-i-1;  j++){
		
			if (s1[j].rno> s1[j+1].rno){
			struct student temp = s1[j];
			s1[j] = s1[j+1];
			s1[j+1] = temp;
			printf("Output of pass %d : \n", pass); 
			display(s1, n);
			pass++;
			}
		}
	}
	printf("Number of passess : %d \n", pass-1);
}
void selectionSort(struct student s1[60], int n){
	int pass = 1;
	for (int i = 0; i < n-1; i++){
		int minTerm = i;		
		for (int j = i+1; j < n; j++){
			if (s1[j].rno < s1[minTerm].rno){
				minTerm = j;
			}
        }
		if (minTerm != i){
			struct student temp = s1[i];
			s1[i] = s1[minTerm];
			s1[minTerm] = temp;
			printf("Output of pass %d : \n", pass); 
			display(s1, n);
			pass++;
		}
	}
	printf("Number of passess : %d \n", pass-1);
}
void insertionSort(struct student s1[60], int n) {
    int pass = 1;
    for (int i = 1; i < n; i++) {
        struct student key = s1[i];
        int j = i - 1;
        while (j >= 0 && s1[j].rno > key.rno) {
            s1[j + 1] = s1[j];
            j--;
        }
        s1[j + 1] = key;
        printf("Output of pass %d : \n", pass); 
	display(s1, n);
	pass++;
    }
    printf("Number of passess : %d \n", pass-1);
}
void shellSort(struct student s1[60], int n) {
	int pass = 1;
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			struct student temp = s1[i];
			int j;
			for (j = i; j >= gap && s1[j - gap].rno > temp.rno; j -= gap) {
				s1[j] = s1[j - gap];
			}
			s1[j] = temp;
		}
		printf("Output after gap %d (Pass %d):\n", gap, pass++);
		display(s1, n);
	}
}
int main(){
	struct student s[60];
	int n, ch;
    printf("Enter number of students: ");
	scanf("%d", &n);
	accept(s, n);
	display(s, n);
	printf("Select type of sort:\n");
	printf("1.Bubble Sort\n");
	printf("2.Selection Sort\n");
	printf("3.Insertion Sort\n");
    printf("4.Shell Sort\n");
	scanf("%d", &ch);
	switch(ch){
		case 1:
			bubbleSort(s, n);
			//display(s, n);
			break;
		case 2:
			selectionSort(s, n);
			//display(s, n);
			break;
		case 3:
			insertionSort(s, n);
			//display(s, n);
			break;
        case 4:
            shellSort(s, n);
            break;
		default:
			printf("invalid option\n");
			break;
	}
	return 0;
}