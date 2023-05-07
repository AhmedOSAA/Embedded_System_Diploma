/* fifo.h
 * Author: ENG.Ahmed Osamaa
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//USER Configuration
// select the element type (uint8_t ,uint16_t ,uint32_t ,uint64_t ,... )
#define element_type uint8_t
// create buffer 1
#define wedth1 5
element_type uart_buffer[wedth1] ;

// FIFO Data type

typedef struct {
	unsigned int length;
	unsigned int count ;
	element_type* base ;
	element_type* head ;
	element_type* tail ;
}FIFO_Buf_T;

// status

typedef enum {
	fifo_no_error,
	fifo_full,
	fifo_empty,
	fifo_null
}FIFO_stat;

// APIs

FIFO_stat fifo_create  (FIFO_Buf_T* fifo ,element_type* buf ,unsigned int lenght ) ;
FIFO_stat fifo_enqueue (FIFO_Buf_T* fifo ,element_type item ) ;
FIFO_stat fifo_dequeue (FIFO_Buf_T* fifo ,element_type* item ) ;
FIFO_stat fifo_is_full (FIFO_Buf_T* fifo) ;
void print_fifo (FIFO_Buf_T* fifo) ;



#endif /* FIFO_H_ */



