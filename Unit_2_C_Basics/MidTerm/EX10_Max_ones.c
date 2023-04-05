//AOS
//EX10_Max_ones  //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void max_ones(int n);
int main(){
	int n;
	printf("Enter the number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	max_ones(n);
	return 0;
}
void max_ones(int n){
	int count=0,s=0,sn=0;
	for(int i=0; i<sizeof(n)*8; i++) // size of integer =4  * 8 number of (bits in one byte)
	{	if(n & 1){     // If LSB is set then increment ones
			++count;
			sn=count;  //store number of series of one
		}
		else{count=0;} //reset count
		if(sn>s)s=sn; // compare stored counter with new one
		n >>= 1;      //Right shift bits of number to one position
	}
	printf("Number Of max ones between two zeros = %d",s);
}
