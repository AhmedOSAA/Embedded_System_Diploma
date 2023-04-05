//AOS
//EX4_Reverse_Digits  //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum_dig(char n[]);

int main(){
	char n[100];
	printf("Enter the number: ");
	fflush(stdin); fflush(stdout);
	gets(n);							// take the number as string
	printf("Reverse Of Digits = %d",sum_dig(n));
	return 0;
}
int sum_dig(char n[]){
	char t[100];
	for(int i=strlen(n)-1;i>=0;--i){
		t[strlen(n)-i-1]=n[i];     // store the char reversely
	}
	return atoi(t) ;   // Return the revered digits as an integer number by (atoi)
}
