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


//•••••••••••••••••••••••••
// Peripheral registers : I2C
//•••••••••••••••••••••••••

#define I2CBR	*(uint8_t*)(0x20)
#define I2CSR	*(uint8_t*)(0x21)
#define I2CAR	*(uint8_t*)(0x22)
#define I2CDR	*(uint8_t*)(0x23)
// TWI Control Register and its bits
#define I2CCR	*(uint8_t*)(0x56)

	#define I2CINT	7		// TWI Interrupt Flag , it must set high with each transition
	#define I2CEA	6		// TWI Enable Acknowledge
	#define I2CSTA	5		// TWI START Condition
	#define I2CSTO	4		// TWI STOP Condition
	#define I2CWC	3		// TWI Write Collision Flag
	#define I2CEN	2		// I2C Enable
	#define I2CIE	0		// TWI Interrupt Enable


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