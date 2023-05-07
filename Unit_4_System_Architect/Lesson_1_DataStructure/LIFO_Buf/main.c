/*
 * main.c
 * Author: ENG.Ahmed Osamaa
 */

#include "lifo.h"

/*  <<<<<<<<<<<< Static allocation >>>>>>>>>>>>>> */
unsigned int buffer1 [5];


int main ()
{
	printf("\t\t<<<<<< Static allocation  >>>>>\t\t\n\n");
	int i , temp ;
	LIFO_Buf_t Uart_lifo ;
	//Create LIFO
	LIFO_init (&Uart_lifo,buffer1,5);
	//Adding item
	for(i = 0 ; i<7 ; i++)
	{
		if ( LIFO_Add_item(&Uart_lifo,i) == LIFO_no_error )
			printf("LIFO_Add : %d\n", i);
	}

	printf("\n\n");
	// Get item & print it
	for(i = 0 ; i<7 ; i++)
	{
		if (LIFO_get_item(&Uart_lifo,&temp) == LIFO_no_error )
			printf("LIFO_get : %d\n", temp);
	}

	printf("\n\n\n\n");
	printf("\t\t<<<<<< Dynamic allocation  >>>>>\t\t\n\n");
	/* <<<<<< Dynamic allocation  >>>>> */
	int length ;
	LIFO_Buf_t I2C_lifo ;

	printf("Put the size of Stack (LIFO) : ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &length);    // get from user

	unsigned int* buffer2 = (unsigned int* )malloc(length*sizeof(unsigned int)) ;

	//Create LIFO
	LIFO_init (&I2C_lifo,buffer2,length);
	//Adding item
	for(i = 0 ; i<length ; i++)
	{
		if ( LIFO_Add_item(&I2C_lifo,i) == LIFO_no_error )
			printf("LIFO_Add : %d\n", i);
		fflush(stdout); fflush(stdin);   // to make sure display will be done
	}
	/* reallocation for dynamic location
	 * by take new length from user */
	printf("Put the NEW size of Stack (LIFO) : ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &length);   // get from user

	/* First argument in realloc(*, ) is an address of pointer of buf 2 */
	realloc( &buffer2 , length);
	I2C_lifo.length = length ;  // update the length of I2C LIFO

	for(i = I2C_lifo.count ; i<length ; i++)
	{
		if ( LIFO_Add_item(&I2C_lifo,i) == LIFO_no_error )
			printf("LIFO_Add : %d\n", i);
		fflush(stdout); fflush(stdin);    // to make sure display will be done

	}

	printf("\n\n");

	// Get item & print it
	for(i = 0 ; i<length ; i++)
	{
		if (LIFO_get_item(&I2C_lifo,&temp) == LIFO_no_error )
			printf("LIFO_get : %d\n", temp);
		fflush(stdout); fflush(stdin);   // to make sure display will be done
	}
	return 0 ;
}
