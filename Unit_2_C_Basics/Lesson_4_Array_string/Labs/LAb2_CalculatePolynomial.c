//AOS
//LAb2_CalculatePolynomial
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i;
	float y ;
	float x[5]={5,16,22,3.5,15};
	for(i=0;i<5;i++){
		y=5*x[i]*x[i]+3*x[i]+2;
		printf("y(%.2f) = %.2f\n",x[i],y);
	}

}

