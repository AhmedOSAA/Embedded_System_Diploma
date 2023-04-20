//AOS  //Lab_Pointers_To_Fun  //Pointer_Arguments
#include "stdio.h"
#include "string.h"

void swap(int *a , int *b){
	*a^=*b;
	*b^=*a;
	*a^=*b;
}

int compare (int a , int b){
	if(a>b)return 1 ;
	return -1;
}

void sort (int *a , int s , int (*compare)(int,int)){
	int i , j ;
	for(i=0 ; i<s ; i++){
		for(j=i+1;j<s;j++){
			if(compare(a[i],a[j])>0)
			{
				swap(&a[i],&a[j]);
			}
		}
	}
}

int main(){
	int a[]={5,4,7,1,9,15,0} , i , size;
	size = sizeof(a)/sizeof(*a);
	sort (a,size,compare);
	for(i=0;i<size;i++)
		printf("%d ",a[i]);
	return 0;
}

