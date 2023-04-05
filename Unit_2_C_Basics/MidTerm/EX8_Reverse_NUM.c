//AOS
//EX8_Reverse_NUM  //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse(int a[],int size);
int main(){
	int a[5]={1,2,3,4,5};
	reverse(a,sizeof(a));
	return 0;
}
void reverse(int a[],int size){
	for(int i=(size/sizeof(a[0]))-1;i>=0;--i){
		printf("%d\t",a[i]);
	}
}
