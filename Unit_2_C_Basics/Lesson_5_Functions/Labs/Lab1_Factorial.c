//AOS
//Function
//Lab1_Factorial
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Factorial(int x);

int main() {
	int x;
	printf("Enter the Number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);

	 printf("Factorial(%d) = %d",x,Factorial(x));
}

int Factorial(int x){
	int f=1;
	for(int i=x;i>0;i--)f*=i;
	return f;
}
