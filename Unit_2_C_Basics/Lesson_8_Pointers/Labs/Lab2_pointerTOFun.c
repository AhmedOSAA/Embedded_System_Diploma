//AOS  //Pointers //Lab2_pointerTOFun
#include "stdio.h"
#include "string.h"
void check (char* a ,char* b,int(*cmp)(const char*, const char*));

int main(){
	char s1[80], s2[80];
	int (*p)(const char* ,const char* );
	p=strcmp;
	printf("Enter two string \n");
	fflush(stdin); fflush(stdout);
	gets(s1);
	fflush(stdin); fflush(stdout);
	gets(s2);
	check(s1,s2,p);
	return 0;
}

void check (char* a ,char* b,int(*cmp)(const char*, const char*)){
	printf("Testing for equality.\n");
	if(!cmp(a,b))printf("Equal");
	else printf("Not Equal");
}
