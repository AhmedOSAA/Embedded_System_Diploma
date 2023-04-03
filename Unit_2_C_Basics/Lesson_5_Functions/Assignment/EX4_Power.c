//AOS
//EX4_Power  //Functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int power(int base,int exp);
int main(){
	int base, exp;
	printf("Enter a number: ");
	fflush(stdout);  fflush(stdin);
	scanf("%d",&base);
	printf("Enter a power: ");
	fflush(stdout);  fflush(stdin);
	scanf("%d",&exp);
	printf("%d^%d = %d",base,exp,power(base,exp));
	return 0;
}
int power(int base,int exp){
	if (exp != 0)
		return (base*power(base,exp-1));
	else return 1;
}
