//AOS  //Assignment_Pointers //EX4_Rev_num
#include "stdio.h"
#include "string.h"

int main(){
	int max[15];
	int *Prev = max;
	printf("Input 5 number of elements in the array :\n\n");
	for(int i=0;i<5;i++){
		printf("element-%d :",i+1);
		fflush(stdin);  fflush(stdout);
		scanf("%d",Prev++);
	}
	--Prev;
	printf("\n\nInput 5 number of elements in the array :\n\n");
	for(int i=0;i<5;i++){
		printf("element-%d : %d\n",i+1,*Prev--);
	}
	return 0;
}
