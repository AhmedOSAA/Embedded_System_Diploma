//AOS
//Assignment 2 EX8_simple_calc
#include <stdio.h>
#include <stdlib.h>

int main() {
	char c;
	float n1,n2;
	try_again:
	printf("Enter operator either + or - or * or /: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	printf("Enter two operands: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&n1,&n2);
	switch(c){
	case'+':
	{
		printf("%.1f + %.1f = %.1f",n1,n2,n1+n2);
	}
	break;
	case'-':
	{
		printf("%.1f - %.1f = %.1f",n1,n2,n1-n2);
	}
	break;
	case'*':
	{
		printf("%.1f * %.1f = %.1f",n1,n2,n1*n2);
	}
	break;
	case'/':
	{
		printf("%.1f / %.1f = %.1f",n1,n2,n1/n2);
	}
	break;
	default:{
		printf("Error! operator is not correct pls try again\n");
		goto try_again;  // goto statement
	}
	}
}


