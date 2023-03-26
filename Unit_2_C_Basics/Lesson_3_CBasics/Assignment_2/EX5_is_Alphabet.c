//AOS
//Assignment 2 EX5_is_Alphabet
#include <stdio.h>
#include <stdlib.h>

int main() {
	char c ;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	if(c>='a'&&c<='z')
		printf("%c is an alphabet",c);
	else
		printf("%c is not an alphabet",c);
}
