//AOS
//EX6_Unique_NUM  //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char unique_num(int a[],int size);
int main(){
	int a[]={4,2,5,2,5,7,4},b[]={4,2,4};
	printf("Unique number in array of a is: %d\n",unique_num(a,sizeof(a)));
	printf("Unique number in array of b is: %d",unique_num(b,sizeof(b)));
	return 0;
}
char unique_num(int a[],int size){
	int uni=0 ,i;
	size = size/sizeof(a[0]);
	for(i=0;i<size;++i){
		uni = uni^a[i];
	}
	return uni;
}
