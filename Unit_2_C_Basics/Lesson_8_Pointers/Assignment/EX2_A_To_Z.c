//AOS  //Assignment_Pointers //EX2_A_To_Z
#include "stdio.h"
#include "string.h"

int main(){
	char alph[27];
	char *pA = alph;
	for(int i=0;i<26;i++){
		*pA = 'A' + i;
		pA++;
	}

	pA = alph;

	printf("The Alphabets are :\n\n");
	for(int i=0;i<26;i++){
		printf("%c  ",*pA);
		pA++;
	}
	return 0;
}
