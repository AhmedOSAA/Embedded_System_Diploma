/*
 * Drivers.c
 *
 * Created: 6/29/2023 5:55:31 PM
 * Author : midom
 */ 

#include "MemoryMap.h"
#include "lcd.h"
#include "USART.h"
#include <avr/interrupt.h>
// Generic Variables

char num[] = {'0','1','2','3','4','5','6','7','8','9'};

int main(void)
{
   	LCD_init();
	   
 	LCD_Write_STRING("Learn IN Depth");
	LCD_Write_command(LCD_CLEAR_SCREEN);

	UART_init();
	UART_interrupt_TX_EN();
	UART_interrupt_RX_EN();
	SREG |= 1<<7 ;   // Enable Bit 7 – I: Global Interrupt Enable
	

	UART_SendString_Asynch("Hello Ahmed");

    while (1) 
    {
		
		for (int i=0 ; i<10 ; i++)
		{
			LCD_GoToXY(1,0);
			LCD_Write_CHAR(num[i]);
			_delay_ms(1000);
		}
	
    }
}

ISR(USART_TXC_vect)
{
	extern char* str ;
	extern uint8_t flag_tx	;
	str++;
	if (*str)
	{
		UDR_R = *str ;
	}else{
		// Done
		flag_tx = 0 ;
	}
}

ISR(USART_RXC_vect)
{
	static char * Ptr = CH ;
	*Ptr = UDR_R ;
	if(*Ptr == Default_stop)
	{
		*Ptr = 0 ;
		LCD_GoToXY(0,0);
		LCD_Write_STRING(CH);
		for(int i=0 ; i<100 ; i++)
		{
			if (CH[i] == 0) break;
			CH[i] = 0 ;
		}
		Ptr = CH;
	}else
	{
		Ptr++ ;
	}
	
}