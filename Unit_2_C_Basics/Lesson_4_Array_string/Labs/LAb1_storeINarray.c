//AOS
//LAb1_storeINarray
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i;
	float degree[10];
	for (i=0;i<10;i++){
		printf("Enter student %d degree :",i+1);
		fflush(stdin);   fflush(stdout);
		scanf("%f",&degree[i]);
	}
	for(i=0;i<10;i++){
		printf("Student %d degree is : %f\n",i+1,degree[i]);
	}

}

