/*
 * lifo.c
 * Author: ENG.Ahmed Osamaa
 */
#include "lifo.h"

LIFO_status LIFO_Add_item (LIFO_Buf_t* lifo_buf , unsigned int item)
{
	//check lifo is valid
	if( !lifo_buf->base || !lifo_buf->head )
		return LIFO_Null ;
	// check is not full
	if (lifo_buf->count > lifo_buf->length )
		return LIFO_full ;

	*(lifo_buf->head) = item ;
	lifo_buf->head++ ;
	lifo_buf->count++ ;

	return LIFO_no_error ;

}
LIFO_status LIFO_get_item (LIFO_Buf_t* lifo_buf , int* item)
{
	//check lifo is valid
	if( !lifo_buf->base || !lifo_buf->head )
		return LIFO_Null ;
	// check is not empty
	if (lifo_buf->count == 0 )
		return LIFO_empty ;

	lifo_buf->head--;
	*item = *(lifo_buf->head) ;
	lifo_buf->count -- ;

	return LIFO_no_error ;

}
LIFO_status LIFO_init (LIFO_Buf_t* lifo_buf , unsigned int* bufs , unsigned int length)
{
	if ( bufs == NULL )
		return LIFO_Null ;


	lifo_buf->base = bufs ;
	lifo_buf->head = bufs ;
	lifo_buf->length = length;
	lifo_buf->count = 0 ;

	return LIFO_no_error ;
}
