//AOS
//EX3_Prime_NUM //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void prime(int n1,int n2);
int main(){
	int n1,n2;
	printf("Enter the two numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&n1 ,&n2);
	prime(n1,n2);
	return 0;
}
void prime(int n1,int n2){
	int flag;
	for(int i=n1;i<=n2;++i){       // loop to move between numbers
		for(int j=2;j<=i/2;++j){  // loop to check this number is prime or not
			if(i%j==0){
				flag =0;
				break;}
			else flag =1 ;
		}
		if(flag == 1 || i == 1 || i == 2 || i == 3)printf("%d\t",i);
	}
}
