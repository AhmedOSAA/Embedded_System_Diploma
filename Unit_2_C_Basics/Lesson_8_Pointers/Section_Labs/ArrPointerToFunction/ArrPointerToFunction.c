//AOS  //Lab_Pointers_To_Fun  //ArrPointerToFunction
#include "stdio.h"
#include "string.h"
int addnum(int a , int b){
	return a+b;
}
int subnum(int a , int b){
	return a-b;
}
int mulnum(int a , int b){
	return a*b;
}
int main(){
	int c , a , b ,ret ;
	int (*p[3])(int ,int ) = {addnum,subnum,mulnum};
	printf("choice 0 for add 1 for sub 2 for mul : ");
	fflush(stdin);    fflush(stdout);
	scanf("%d", &c);
	printf("Enter num 1: ");
	fflush(stdin);    fflush(stdout);
	scanf("%d", &a);
	printf("Enter num 2 : ");
	fflush(stdin);    fflush(stdout);
	scanf("%d", &b);
	ret = p[c](a,b);
	printf("Result = %d",ret);
	return 0;
}

