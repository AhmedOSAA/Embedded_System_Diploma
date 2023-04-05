//AOS
//EX5_binary_ones  //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void ch_ones(int n);
int main(){
	int n;
	printf("Enter the number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	ch_ones(n);
	return 0;
}
void ch_ones(int n){
	int ones=0;
	for(int i=0; i<sizeof(n)*8; i++) // size of integer =4  * 8 number of (bits in one byte)
	{
		// If LSB is set then increment ones
		if(n & 1) ones++;
		n >>= 1;
		//Right shift bits of number to one position
	}
	printf("Number Of ones = %d",ones);
}
