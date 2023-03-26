//AOS
//String_EX1_FreqOFelement
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int c=0;
	char s[1000],element;
	printf("Enter the string: ");
	fflush(stdin);   fflush(stdout);
	gets(s);
	printf("Enter a character to find frequency:");
	fflush(stdin);   fflush(stdout);
	scanf("%c",&element);
	for(int i=0;i<strlen(s);i++){
		if(s[i]==element) c++;
	}
	printf("Frequency of %c = %d",element,c);
}

