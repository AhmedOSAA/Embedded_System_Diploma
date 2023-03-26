//another way for this code
// using line condition
// AOS

#include <stdio.h>
#include <stdlib.h>

int main() {
	int num1 , num2 , num3 , result;
	printf("Enter three values : ");
	fflush(stdout); fflush(stdin);
	scanf("%d %d %d", &num1 ,&num2 ,&num3);
	result = (num1>num2)? num1:num2 ;		//line condition
	result = (result>num3)? result:num3 ;	//line condition
	printf("The largest value is : %d ",result);

}
