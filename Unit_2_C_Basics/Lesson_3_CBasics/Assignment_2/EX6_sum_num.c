//Calculate the Summation of numbers
//AOS
//Assignment 2 EX6_sum_num
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i,n,sum = 0;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		sum += i;  //sum = sum + i
	}
	printf("sum = %d\n",sum);
}
