//AOS  //Pointers //Lab3_pointerTOpointer
#include "stdio.h"
#include "string.h"

int main(){
	int x = 5 , y=9;
	int* px =&x;
	int** ppx =&px;

	printf ("x = %d , y = %d\r\n",x,y);

	**ppx=7;
	printf ("x = %d , y = %d\r\n",x,y);

	*ppx=&y;

	*px = 11;
	printf ("x = %d , y = %d\r\n",x,y);
	return 0;
}

