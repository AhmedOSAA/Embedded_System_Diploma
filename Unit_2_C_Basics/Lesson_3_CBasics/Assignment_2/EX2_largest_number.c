//AOS
//Assignment 2 EX2_largest_number
#include <stdio.h>
#include <stdlib.h>

int main() {
	float n1,n2,n3,larg_num ;
	printf("Enter three number: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f",&n1,&n2,&n3);
	larg_num= (n1>n2)? n1:n2;
	larg_num= (larg_num>n3)? larg_num:n3;
	printf("Largest number = %.2f",larg_num);
}
