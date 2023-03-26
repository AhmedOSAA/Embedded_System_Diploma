//AOS
//String_EX2_length
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int len=0 , i=0;
	char s[100];
	printf("Enter a string: ");
	fflush(stdin);   fflush(stdout);
	gets(s);
	while(1){
		if(s[i]!=0)len++;
		else if(s[i]==0)break;
		i++;
	}
	printf("Length of string : %d",len);

}
