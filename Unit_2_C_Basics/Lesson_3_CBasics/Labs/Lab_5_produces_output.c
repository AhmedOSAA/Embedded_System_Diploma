//Write a program that produces the following output:
//AOS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int s, i , r = 0;
	printf("Enter start number:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&s);
	while(1){
		for(i=r;i<=s;++i)  // r is a number of round
			printf("%d",i);
		printf("\n");
		++r;
		if (r>s)break;   // Break statement
	}
}
