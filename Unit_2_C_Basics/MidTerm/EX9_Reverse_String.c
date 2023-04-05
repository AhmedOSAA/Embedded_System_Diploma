//AOS
//EX9_Reverse_String  //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void rev_str(char a[]);
int main(){
	char a[100];
	printf("Enter the string: ");
	fflush(stdout);
	gets(a);
	rev_str(a);
	return 0;
}
void rev_str(char a[]){
	int endname_index= strlen(a); // this variable store the end index of name
	for(int i=strlen(a)-1;i>=0;--i){
		if(a[i]==' '||i==0){
			if(i==0)i-=1;          // to take the first name that start from a[0]
			for(int j=i+1;j<endname_index;++j){
				printf("%c",a[j]);
			}
			endname_index=i; // i is an index of space that will be an end index for name before it
			printf(" ");
		}
	}
}
