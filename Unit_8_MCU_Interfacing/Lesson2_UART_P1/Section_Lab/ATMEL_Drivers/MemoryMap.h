/*
 * MemoryMap.h
 *
 * Created: 6/29/2023 6:22:36 PM
 *  Author: midom
 */ 


#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

//-----------------------------
// Includes
//-----------------------------

#include <stdlib.h>
#include <stdint.h>

//--------------------------------
// Base addresses for Memories
//--------------------------------

#define Flash				0x00
#define SRAM				0x60

#define Peripherals_Base	0x20

//--------------------------------
// Peripherals addresses for Memories
//--------------------------------


//GPIO Registers
#define DDRA	*((volatile unsigned char*)0x3A)
#define PORTA	*((volatile unsigned char*)0x3B)
#define PINA	*((volatile unsigned char*)0x39)

#define DDRB	*((volatile unsigned char*)0x37)
#define PORTB	*((volatile unsigned char*)0x38)
#define PINB	*((volatile unsigned char*)0x36)

#define DDRC	*((volatile unsigned char*)0x34)
#define PORTC	*((volatile unsigned char*)0x35)
#define PINC	*((volatile unsigned char*)0x33)

#define DDRD	*((volatile unsigned char*)0x31)
#define PORTD	*((volatile unsigned char*)0x32)
#define PIND	*((volatile unsigned char*)0x30)

// USART




#endif /* MEMORYMAP_H_ */