//AOS  //Lab_Pointers_To_Fun //PassArray_2D //Normal
#include "stdio.h"
#include "string.h"
#define M 3
#define N 3

void print (int arr[M][N]){
	for(int i = 0 ; i<M ; i++){
		for(int j=0;j<N;j++){
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
}

int main(){

	int arr[][N] = {{1,2,3},{4,5,6},{7,8,9}};
	print(arr);

	return 0;
}
