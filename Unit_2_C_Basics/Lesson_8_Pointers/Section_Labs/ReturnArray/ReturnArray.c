//AOS  //Lab_Pointers_To_Fun //ReturnArray
#include "stdio.h"
#include "string.h"

int * getrondom (){
	static int r[10];
	int i ;

	for (i = 0 ; i <10 ; i++){
		r[i] = rand();
		printf("r[%d] = %d\n",i,r[i]);
	}
	return r;
}

int main(){
	int *p;
	int i ;

	p = getrondom();
	for (i=0;i<10;i++){
		printf("*(p+%d) : %d\n",i,p[i]);
	}
	return 0;
}
