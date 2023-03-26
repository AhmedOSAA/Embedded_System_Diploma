//AOS
//EX3_Array_Transpose
#include <stdio.h>
#include <stdlib.h>

int main() {
	int a[10][10], t[10][10],r,c,i,j;
	printf("Enter rows and column of matrix :");  //take number of rows & columns
	fflush(stdin);   fflush(stdout);
	scanf("%d %d",&r,&c);
	printf("Enter element of matrix :\n");
	for(i=0;i<r;i++){ 					//take element of a matrix
		for(j=0;j<c;j++){
			printf("Enter element a%d%d:",i+1,j+1);
			fflush(stdin);   fflush(stdout);
			scanf("%d",&a[i][j]);
		}
	}
	printf("Entered Matrix :\n");
	for(i=0;i<r;i++){					// print a matrix
		for(j=0;j<c;j++){
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<r;i++){         			//transpose the matrix
		for(j=0;j<c;j++){				// standard to transpose t[j][i]=a[i][j];
			t[j][i]=a[i][j];
		}
	}
	printf("Transpose of Matrix :\n");
	for(i=0;i<c;i++){					// print transpose a matrix
		for(j=0;j<r;j++){				// to print transpose matrix swipe r & c in for loops
			printf("%d\t",t[i][j]);
		}
		printf("\n");
	}
}
