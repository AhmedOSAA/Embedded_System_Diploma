/* Drivers.c
 * Created: 6/29/2023 5:55:31 PM
 * Author : ENG.Ahmed Osamaa
 */ 

// MASTER

#include "MemoryMap.h"
#include "lcd.h"
#include "USART.h"
#include "SPI.h"
#include <avr/interrupt.h>
#include <util/delay.h>


// Generic Functions

void SPIinit (void)
{
	SPI_Config config ;
	config.SPI_EN = SPI_Enable ;
	config.MODE = SPI_Mode_Master ;
	config.DataORD = SPI_DataORD_MSB ;
	config.Data_Mode = SPI_DataMode_Leading_RisingSample ;
	config.Interrupt_EN = SPI_Interrupt_Disable ;
	config.Clock_Rate = SPI_Clock_Divide_16 ;
	SPI_Init(SPI , &config);
}


void execute (uint8_t cmd , uint8_t data)
{
	PORTB &= ~(1<<SS);
	SPI->SPDR_ = cmd ;
	while (!(SPI->SPSR_ & (1<<7)));
	SPI->SPDR_ = data;
	while (!(SPI->SPSR_ & (1<<7)));
	PORTB |= (1<<SS);
	
}


int main(void)
{
	
	/* ***(LAB2)*** */
	uint8_t counter =  0;
	uint8_t index_display ;
	SPIinit();
	
	execute(0x09, 0xFF);
	execute(0x0A, 0xFF);
	execute(0x0B, 0xF7);
	execute(0x0C, 0x01);
	while(1)
	{
		for (index_display = 1 ; index_display < 9 ; index_display++)
		{
			execute(index_display , counter++);
		}
		_delay_ms(1000);
	}
	
// 	/* ***(LAB1)*** */
// 	unsigned char data ;
// 	DDRA = 0xFF ;
// 	
// 	SPIinit();
// 	for(data = 0 ; data <= 255 ; data++ ) 
// 	{
// 		_delay_ms(1000);
// 		PORTA = SPI_SendData(SPI , data );
// 	}

}
