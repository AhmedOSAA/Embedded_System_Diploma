//AOS  //Lab_Pointers_To_Fun //PassArray_2D //1DPointer
#include "stdio.h"
#include "string.h"
#define M 3
#define N 3

void print (int (*arr)[N]){
		for(int j=0;j<N*M;j++ ){
			printf("%d ",(*arr)[j]);
		}
}

int main(){

	int arr[][N] = {{1,2,3},{4,5,6},{7,8,9}};
	print(arr);
	return 0;
}

                   //PointerTOinteger
/*
//AOS  //Lab_Pointers_To_Fun
#include "stdio.h"
#include "string.h"
#define M 3
#define N 3

void print (int *arr){
		for(int j=0;j<N*M;j++ ){
			printf("%d ",*arr++);
		}
}

int main(){

	int arr[][N] = {{1,2,3},{4,5,6},{7,8,9}};
	print(&arr[0][0]);
	return 0;
}
*/
