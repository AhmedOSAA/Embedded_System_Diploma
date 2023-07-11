/* Drivers.c
 * Created: 6/29/2023 5:55:31 PM
 * Author : ENG.Ahmed Osamaa
 */ 

// SLAVE

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
	config.MODE = SPI_Mode_Slave ;
	config.DataORD = SPI_DataORD_MSB ;
	config.Data_Mode = SPI_DataMode_Leading_RisingSample ;
	config.Interrupt_EN = SPI_Interrupt_Disable ;
	config.Clock_Rate = SPI_Clock_Divide_16 ;
	SPI_Init(SPI , &config);
}


int main(void)
{
	unsigned char i ;
	DDRA = 0xFF ;
	
	SPIinit();
	
	for(i = 255 ; i>0 ; i--)
	{
		PORTA = SPI_ReveiveData(SPI , i );
	}
}
