//AOS
//Assignment 2 EX7_factorial_num
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i,n,sum = 1;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	if(n>0){
		for(i=1;i<=n;i++){
			sum *= i;
		}
		printf("Factorial = %d\n",sum);
	}
	else if (n==0){
		printf("Factorial = 1");}
	else{
		printf("Error!!! Factorial of negative number doesn't exist.");}
}

