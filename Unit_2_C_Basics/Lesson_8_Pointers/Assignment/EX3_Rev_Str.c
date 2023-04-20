//AOS  //Assignment_Pointers //EX3_Rev_Str
#include "stdio.h"
#include "string.h"

int main(){
	char str[100];
	char *Prev = str;
	printf("Input a string: ");
	fflush(stdin); fflush(stdout);
	gets(str);

	Prev = str+(strlen(str)-1);  // Point to last char

	printf("\nReverse of the string is: ");
	for(int i=0;i<strlen(str);i++){
		printf("%c",*Prev);
		Prev--;
	}
	return 0;
}
