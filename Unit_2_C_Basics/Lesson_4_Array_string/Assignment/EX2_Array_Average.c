//AOS
//EX2_Array_Average
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n,i;
	float a[100],ave;
	printf("Enter the number of data :");
	fflush(stdin);   fflush(stdout);
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("Enter number :");
		fflush(stdin);   fflush(stdout);
		scanf("%f",&a[i]);
	}
	for(i=0,ave=0;i<n;i++){
		ave = ave+a[i];
	}
printf("Average = %.2f",ave/n);
}
