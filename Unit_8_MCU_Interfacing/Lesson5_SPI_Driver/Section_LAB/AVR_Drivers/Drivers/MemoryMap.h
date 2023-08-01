/* MemoryMap.h
 * Created: 6/29/2023 6:22:36 PM
 * Author : ENG.Ahmed Osamaa
 */ 


#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

//-----------------------------
// Includes
//-----------------------------

#include <stdlib.h>
#include <stdint.h>

#define F_CPU 8000000UL

//--------------------------------
// Base addresses for Memories
//--------------------------------

#define Flash				0x00
#define SRAM				0x60

#define Peripherals_Base	0x20


//--------------------------------
// Peripherals addresses for Memories
//--------------------------------

// The AVR Status Register
#define SREG	*((volatile unsigned char*)0x5F)

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

//SPI

#define SPI_Base			(0x0D + Peripherals_Base)

//=========================================================================
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral registers
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//•••••••••••••••••••••••••
// Peripheral registers : SPI
//•••••••••••••••••••••••••

typedef struct {
	volatile uint8_t SPCR_ ;
	volatile uint8_t SPSR_ ;
	volatile uint8_t SPDR_ ;				
}SPI_typedef;


//=========================================================================
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral Instants
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define SPI			((SPI_typedef *)(SPI_Base))


//=========================================================================
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Macros 
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// Enable Global Interrupt
// Enable Bit 7 – I: Global Interrupt Enable
#define  Global_interrupt_Enable()			SREG |= (1<<7)
#define  Global_interrupt_Disable()			SREG &= ~(1<<7)

#endif /* MEMORYMAP_H_ */