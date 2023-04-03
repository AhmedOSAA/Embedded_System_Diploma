//AOS
//Functions
//Lab3_FindName
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findName(char names[][14],int x,char name[]);

int main() {
	char name[14];
	char names[5][14]={"Alaa","Osama","Mamdouh","Samy","Hossain"};
	puts("Enter your first name:");
	fflush(stdout); fflush(stdin);
	gets(name);
	if(findName(names ,5 ,name)==1)
		puts("Welcome");
	else
		puts("Goodbye");
	}

int findName(char names[][14],int x,char name[]){
	int i ,t=0;
	for(i=0;i<x;i++){
		if (stricmp(names[i],name)==0){
			t=1;
			break;}
	}
	return t;
}
