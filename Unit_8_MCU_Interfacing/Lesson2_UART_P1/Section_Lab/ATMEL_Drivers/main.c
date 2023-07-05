/*
 * Drivers.c
 *
 * Created: 6/29/2023 5:55:31 PM
 * Author : midom
 */ 

#include "MemoryMap.h"
#include "lcd.h"
#include "USART.h"


int main(void)
{
	//int8_t x ;
    
	LCD_init();
	
	LCD_Write_STRING("UART TR");
	LCD_Write_command(0xC0);
	
	UART_init();
	UART_Send_String("Egypt");
	
    while (1) 
    {
		LCD_Write_command(0xC0);

		UART_Receive_String();
		
		LCD_Write_command(LCD_CLEAR_SCREEN);
		
		LCD_Write_STRING(CH);
		
    }
}

