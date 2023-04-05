//AOS
//EX7_Sum_NUM  //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int sum(int n1,int n2);
int main(){
	int n1,n2;
	printf("Enter the two numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&n1 ,&n2);
	printf("The sum of numbers from %d to %d = %d",n1,n2,sum(n1,n2));
	return 0;
}
int sum(int n1,int n2){
	if(n1<=n2)
		return n1+sum(n1+1,n2);
	else
		return 0;
}
