/* fifo.c
 * Author: ENG.Ahmed Osamaa
 */

#include "fifo.h"

FIFO_stat fifo_create  (FIFO_Buf_T* fifo ,element_type* buf ,unsigned int lenght )
{
	// check validation of buffer
	if (buf == NULL)
		return fifo_null ;

	fifo->base = buf ;
	fifo->head = buf ;
	fifo->tail = buf ;
	fifo->length = lenght ;
	fifo->count = 0 ;

	return fifo_no_error ;
}
FIFO_stat fifo_enqueue (FIFO_Buf_T* fifo ,element_type item )
{
	// check validation of fifo
	if(!fifo->base || !fifo->head || !fifo->tail)
		return fifo_null;
	// check fifo is full
	if (fifo_is_full (fifo) == fifo_full )
		return fifo_full ;

	*(fifo->head) = item ;
	if (fifo->head == fifo->base + ((fifo->length-1)*sizeof(element_type)))
		fifo->head = fifo->base ;
	else fifo->head++;

	fifo->count++;

	return fifo_no_error ;
}	// to circular enqueue fifo

FIFO_stat fifo_dequeue (FIFO_Buf_T* fifo ,element_type* item )
{
	// check validation of fifo
	if(!fifo->base || !fifo->head || !fifo->tail)
		return fifo_null;
	// check fifo is empty
	if (fifo->count == 0 ){
		printf("FIFO is empty .");
		return fifo_empty ;}

	*item = *(fifo->tail);

	// to circular dequeue fifo
	if(fifo->tail == fifo->base + (fifo->length*sizeof(element_type)))
		fifo->tail = fifo->base ;
	else fifo->tail++;

	fifo->count--;

	return fifo_no_error ;
}
FIFO_stat fifo_is_full (FIFO_Buf_T* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
			return fifo_null;
	if(fifo->count == fifo->length){
		printf("FIFO is full .");
		return fifo_full ;}
	return fifo_no_error ;
}
void print_fifo (FIFO_Buf_T* fifo)
{
	printf("\t=====Print FIFO===== \n\n");
	element_type* temp ;
	temp = fifo->tail;
	for(int i = 0 ; i < fifo->count ;i++)
	{
		if (temp == fifo->base + (fifo->length*sizeof(element_type)))
			temp =fifo->base;
		printf ("\t value = %x\n",*temp);
		temp++;
	}
	printf("\n");

}
