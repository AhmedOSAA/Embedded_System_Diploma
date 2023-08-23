/* Drivers.c
 * Created: 6/29/2023 5:55:31 PM
 * Author : ENG.Ahmed Osamaa
 */ 

// MASTER

#include "MemoryMap.h"
#include "lcd.h"
#include "USART.h"
#include "SPI.h"
#include "I2C.h"
#include "ADC.h"
#include <avr/interrupt.h>
#include <util/delay.h>


#define base	5.0
char patt[8] = {
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111
	};


int main(void)
{
	int pres ;
	float Value ;
	ADC_init(VREF_AVCC, ADC_SCALER_64);
	LCD_init();
	LCD_MakePatt(patt);
	while(1)
	{
		// Read from ADC CH_3
		Value = (((uint32_t)ADC_Read(CH_3)*base)/1024);
		pres  = (Value/base) * 16;
		//Value = (uint32_t)ADC_Read(CH_3);
		// Display on LCD
		LCD_Write_command(LCD_CLEAR_SCREEN);
		LCD_GoToXY(0,0);
		LCD_Write_STRING("ADC Val:");
		LCD_dis_realNUM(Value);
		LCD_GoToXY(1,0);
		for(int i = 0 ; i<pres ; i++)
		{
			LCD_Write_CHAR(0x00);
		}
		_delay_ms(500);

 
	}

}
