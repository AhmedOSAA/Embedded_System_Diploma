//AOS
//EX1_primeNUM   //Functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_prime(int n);
int main() {
	int n1,n2,flag,i;
	printf("Enter two number(intervals): ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&n1,&n2);

	for(i=n1;i<=n2;i++){
		flag=check_prime(i);
		if (flag==0) printf("%d ",i);
	}
}
int check_prime(int n){
	int i,flag=0;
	for(i=2;i<=n/2;i++){
		if(n%i==0){
			flag=1;
			break;}
	}
	return flag;
}
