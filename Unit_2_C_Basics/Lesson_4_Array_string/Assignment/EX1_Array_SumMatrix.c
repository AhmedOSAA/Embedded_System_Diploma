//AOS
//EX1_Array_SumMatrix
#include <stdio.h>
#include <stdlib.h>

int main() {
	int r , c;
	float a[2][2],b[2][2] ;
	printf("Enter the element of 1st matrix\n");
	for(r=0;r<2;r++){
		for(c=0;c<2;c++){
			printf("Enter a%d%d :",r+1,c+1);
			fflush(stdin);   fflush(stdout);
			scanf("%f",&a[r][c]);
		}
	}
	printf("Enter the element of 2st matrix\n");
	for(r=0;r<2;r++){
		for(c=0;c<2;c++){
			printf("Enter b%d%d :",r+1,c+1);
			fflush(stdin);   fflush(stdout);
			scanf("%f",&b[r][c]);
		}
	}
	printf("Sum of Matrix :\n");
	for(r=0;r<2;r++){
		for(c=0;c<2;c++){
			printf("%.1f\t",a[r][c]+b[r][c]);
		}
		printf("\n");
	}
}
