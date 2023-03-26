//AOS
//Assignment 2 EX4_positive_negative
#include <stdio.h>
#include <stdlib.h>

int main() {
	float n ;
	printf("Enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&n);
	if(n<0)
		printf("%.2f is negative",n);
	else if (n>0)
		printf("%.2f is positive",n);
	else
		printf("You entered zero");
}
