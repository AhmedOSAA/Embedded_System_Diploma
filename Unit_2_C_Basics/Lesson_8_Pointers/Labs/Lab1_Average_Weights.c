//AOS  //Pointers //Lab1_Average_Weights
#include "stdio.h"

int main(){
	int x[5] , sum=0;
	int *px = x;

	for(int i=0 ; i<sizeof(x)/sizeof(int);i++){
		printf("Enter the weights: ");
		fflush(stdin);  fflush(stdout);
		scanf("%d",px+i);
	}
	printf("you entered: \n");
	for(int i=0 ; i<sizeof(x)/sizeof(int);i++){
		printf("%d\n",*px++);
	}
	px = x;
	for(int i=0 ; i<sizeof(x)/sizeof(int);i++,px++){
		sum += *px;
	}

	printf("sum = %d\n",sum/5);

	return 0;
}
