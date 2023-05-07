/* main.c
 * Author: ENG.Ahmed Osamaa
 */

#include "fifo.h"


int main ()
{
	element_type i;
	// initialization fifo
	FIFO_Buf_T UART_FIFO ;
	if( fifo_create( &UART_FIFO ,uart_buffer,wedth1) == fifo_no_error)
		printf("FIFO Create =====> DONE \n\n");

	// enqueue fifo
	for(i=0;i<7;i++)
	{
		if (fifo_enqueue(&UART_FIFO , i)== fifo_no_error )
			printf("FIFO Enqueue (%x) =====> DONE \n",i);
		else
			printf("FIFO Enqueue (%x) =====> failed \n",i);
	}

	printf("\n");

	// print
	print_fifo(&UART_FIFO);
	// dequeue fifo
	fifo_dequeue(&UART_FIFO , &i );
	printf("FIFO denqueue (%x) =====> DONE \n",i);
	fifo_dequeue(&UART_FIFO , &i );
	printf("FIFO denqueue (%x) =====> DONE \n\n",i);

	// enqueue fifo
	for(i=5;i<7;i++)
	{
		if (fifo_enqueue(&UART_FIFO , i)== fifo_no_error )
			printf("FIFO Enqueue (%x) =====> DONE \n",i);
		else
			printf("FIFO Enqueue (%x) =====> failed \n",i);
	}
	printf("\n");

	// print
	print_fifo(&UART_FIFO);

	return 0 ;
}


