//AOS
//EX2_Square_root  //Mid term
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double sq_rt(double n);

int main(){
	double n;
	printf("Enter the number: ");
	fflush(stdin); fflush(stdout);
	scanf("%lf",&n);
	printf("Square root of %.2lf = %.3lf\n",n,sq_rt(n));
	return 0;
}
double sq_rt(double n){
	double i,f;
	for(i=0.0,f=0.0;i<n;i=i+0.00001){    //find the square root
		if((i*i) >= n){
			f=i;
			break;}
	}
	return f;
}
