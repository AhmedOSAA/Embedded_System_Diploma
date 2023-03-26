//Calculate the Summation of values between 1 and 99

#include <stdio.h>
#include <stdlib.h>

int main() {
	int i, sum = 0;
	for(i=1;i<=99;i++){
		sum += i;  //sum = sum + i
	}
	printf(" Calculate the Summation of values between 1 and 99 is : %d\n",sum);
}
