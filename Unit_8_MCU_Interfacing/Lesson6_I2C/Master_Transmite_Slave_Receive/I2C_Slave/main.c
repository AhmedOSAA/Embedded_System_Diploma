/* Drivers.c
 * Created: 6/29/2023 5:55:31 PM
 * Author : ENG.Ahmed Osamaa
 */ 

// Slave

#include "MemoryMap.h"
#include "lcd.h"
#include "USART.h"
#include "SPI.h"
#include "I2C.h"
#include <avr/interrupt.h>
#include <util/delay.h>


// Generic Functions

void I2Cinit (void)
{
	I2C_Config config ;

	config.I2C_EN = I2C_Enable ;
	config.MODE = I2C_Slave ;
	config.AD = 0xf0 ;
	I2C_init(&config);
}

//I2C_Write = 0,
// 	I2C_Read = 1,
int main(void)
{
	I2Cinit();
	DDRA = 0xFF ;
	while(1)
	{
		PORTA = I2C_Slave_Read();
	}
}