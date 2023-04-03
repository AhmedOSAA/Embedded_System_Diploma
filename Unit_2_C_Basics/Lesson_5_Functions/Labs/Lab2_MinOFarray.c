//AOS
//Functions
//Lab2_MinOFarray
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcMin(int v[],int x);

int main() {
	int xv[10]={35,67,27,54,76,44,59,32,43,25};
	int yv[5] ={28,71,67,83,62};
	int zv[13]={87,21,74,36,27,64,87,63,27,86,48,32,76};

	printf("The minimum value of x , y , z is ( %d , %d , %d )",calcMin(xv,10),calcMin(yv,5),calcMin(zv,13));
}

int calcMin(int v[],int x){
	int i , min=v[0] ;
	for(i=0;i<x;i++){
	if (v[i]<min) min=v[i];
	}
	return min;
}
