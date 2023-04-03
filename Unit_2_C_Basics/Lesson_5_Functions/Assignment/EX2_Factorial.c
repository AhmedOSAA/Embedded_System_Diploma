//AOS
//EX2_Factorial  //Functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fac(int n);
int main(){
	int n;
	printf("Enter a positive integer: ");
	fflush(stdout);  fflush(stdin);
	scanf("%d",&n);
	printf("Factorial of %d = %d",n,fac(n));
}
int fac(int n){
	if(n!=1)
		return n*fac(n-1);
	else return 1;
}
