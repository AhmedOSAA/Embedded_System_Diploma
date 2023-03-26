//AOS
//LAb3_Transpose_Matrix        //AOS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int r, c;
	float x[3][3] , t[3][3];
	for(r=0;r<3;r++){            // Row for          //1) get matrix value from user.
		for(c=0;c<3;c++){       // colum for
			printf("Enter the item(%d ,%d):",r,c);
			fflush(stdin);    fflush(stdout);
			scanf("%f",&x[r][c]);
		}
	}
	printf("\nThe matrix is :\n");
	for(r=0;r<3;r++){            // Row for          //2) Print x Matrix.
		for(c=0;c<3;c++){       // colum for
			printf("%f\t",x[r][c]);
		}
		printf("\n");
	}
	printf("\nThe transpose matrix is :\n");
	for(r=0;r<3;r++){            // Row for          //3) transpose x matrix
		for(c=0;c<3;c++){       // colum for
			t[r][c]=x[c][r];                         // transpose exp. : t[r][c]=x[c][r];
		}
	}
	for(r=0;r<3;r++){            // Row for           //4) print transposed x matrix.
		for(c=0;c<3;c++){       // colum for
			printf("%f\t",t[r][c]);	}
		printf("\n");}}

