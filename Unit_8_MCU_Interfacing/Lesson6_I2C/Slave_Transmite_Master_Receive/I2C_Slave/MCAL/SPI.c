/* SPI.c
 * Created: 7/10/2023 4:09:29 PM
 * Author : ENG.Ahmed Osamaa
 */ 

#include "SPI.h"
#include <avr/io.h>

//=======================================
//***************  APIs  ****************
//=======================================

void SPI_Init (SPI_typedef* SPIx , SPI_Config* CONFIG)
{
	// IMPORTANT NOTE : we must collect all configuration bits of SPCR register in a variable and then equal SPCR with it 
	// We must configure Pins Before SPI , Before anything
	// Configure Pins
	if (CONFIG->MODE == SPI_Mode_Master)
	{
		DDRB |= ((1<<SS) | (1<<MOSI) | (1<<SCK));
		DDRB &= ~(1<<MISO);
	}else if ( CONFIG->MODE == SPI_Mode_Slave)
	{
		DDRB |= (1<<MISO);
		DDRB &= ~((1<<SS) | (1<<MOSI) | (1<<SCK));
	}
	
	uint8_t config = (uint8_t) 0 ;
	
	// Clock Rate
	if( CONFIG->Clock_Rate == SPI_Clock_Divide_DS2 || CONFIG->Clock_Rate == SPI_Clock_Divide_DS8 || CONFIG->Clock_Rate == SPI_Clock_Divide_DS32 || CONFIG->Clock_Rate == SPI_Clock_Divide_DS64 )
	{
		SPIx->SPSR_ |= (uint8_t)(1<<0) ;
		config |= (CONFIG->Clock_Rate - 4) ;
		}else{
		config |= CONFIG->Clock_Rate ;
	}
	// Enable SPI
	config |= CONFIG->SPI_EN ;
	// SPI Mode
	config |= CONFIG->MODE ;
	// Data Order
	config |= CONFIG->DataORD ;
	// Data Mode
	config |= CONFIG->Data_Mode ;
	// Interrupt Enable
	config |= CONFIG->Interrupt_EN ;
	if (CONFIG->Interrupt_EN == SPI_Interrupt_Enable)
	{
		Global_interrupt_Enable();
	}
	
	// configure the SPCR register one time

	SPIx->SPCR_ = config ;	
	
}
void SPI_DeInit (SPI_typedef* SPIx)
{
	SPIx->SPCR_ = (uint8_t) 0 ;
	SPIx->SPSR_ = (uint8_t) 0 ;	
}
unsigned char SPI_SendData (SPI_typedef* SPIx , unsigned char data)
{
	SPIx->SPDR_ = data ;
	while (!(SPIx->SPSR_ & (1<<7)));
	return SPIx->SPDR_ ;
}
uint8_t SPI_ReveiveData (SPI_typedef* SPIx ,  uint8_t dataTOsend)
{
	SPIx->SPDR_ = dataTOsend ;
	while (!(SPIx->SPSR_ & (1<<7))) ;
	return SPIx->SPDR_ ;
}


