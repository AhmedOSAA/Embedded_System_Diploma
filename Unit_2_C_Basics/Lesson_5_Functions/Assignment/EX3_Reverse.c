//AOS
//EX3_Reverse  //Functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Reverse();
int main(){
	printf("Enter a sentence: ");
	fflush(stdout);  fflush(stdin);
	Reverse();
	return 0;
}
void Reverse(){
	char c ;
	scanf("%c",&c);
	if(c != '\n'){
		Reverse();
		printf("%c",c);
	}
}
