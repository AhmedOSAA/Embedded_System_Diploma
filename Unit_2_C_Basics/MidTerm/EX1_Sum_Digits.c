//AOS
//EX1_Sum_digits  //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum_dig(char n[]);

int main(){
	char n[100];
	printf("Enter the number: ");
	fflush(stdin); fflush(stdout);
	gets(n);							// take the number as string
	printf("Sum Of Digits = %d",sum_dig(n));
	return 0;
}
int sum_dig(char n[]){
	int sum =0;
	char t[1];
	for(int i=0;i<strlen(n);i++){
		t[0]=n[i];     // take each digit alone
		sum += atoi(t);  // convert the digit to integer
	}
	return sum ;
}
