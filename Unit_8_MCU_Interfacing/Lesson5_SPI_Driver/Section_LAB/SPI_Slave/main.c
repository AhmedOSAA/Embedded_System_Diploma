/* Drivers.c
 * Created: 6/29/2023 5:55:31 PM
 * Author : ENG.Ahmed Osamaa
 */ 

// Slave

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
	config.Data_Mode = SPI_DataMode_Leading_FallingSample ;
	config.Interrupt_EN = SPI_Interrupt_Disable ;
	config.Clock_Rate = SPI_Clock_Divide_4 ;
	SPI_Init(SPI , &config);
}


int main(void)
{
	
	uint8_t x =  0 , data = 'Z' , rece_data = 0 ;
	LCD_init();
	SPIinit();

	LCD_GoToXY(0,0);
	LCD_Write_STRING("Slave");
	LCD_GoToXY(0,9);
	LCD_dis_NUM(x);
	while(1)
	{
		rece_data = SPI_ReveiveData (SPI , data-- );
		if (data == 'A' - 1)data = 'Z' ;
		LCD_GoToXY(1,0);
		LCD_Write_CHAR(rece_data); 
		LCD_GoToXY(0,9);
		LCD_dis_NUM(x++);
		if(x==101)x=0;
		_delay_ms(200);
	}

}
