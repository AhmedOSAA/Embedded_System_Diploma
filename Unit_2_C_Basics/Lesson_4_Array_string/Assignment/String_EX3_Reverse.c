//AOS
//String_EX3_Reverse
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int i=0;
	char s[100],r[100];
	printf("Enter the string : ");
	fflush(stdin);   fflush(stdout);
	gets(s);
	for(i=0;i<strlen(s);i++){
		r[i]=s[strlen(s)-i-1];
	}
	printf("Reverse string is: %s",r);

}
