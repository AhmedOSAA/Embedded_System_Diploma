/* main.h
 * Author: ENG. Ahmed Osamaa
 */

/*  •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 *  ••• @file	:	main.c
 *  ••• @author :	ENG.Ahmed Osamaa
 *  ••• @brief  :	Learn_IN_Depth
 *  ••• @LAB    :	LAP 1
 *  ••• @Topic  :	Unit 8 Lesson 5 (SPI Full Duplex Driver for "BLUEPILL" STM32 )
 *  •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 *  @TASK  :  1- Terminal <----> USART1 : MCU1
 *  		  2- MCU1 : (SPI1 Master) --->(SPI2 Slave) : MCU2
 *  		  3- MCU2 : USART2 ---> Terminal2
 */


//=======================================
//*************** Macros  ****************
//=======================================

//#define MCU_Act_AS_Master
#define MCU_Act_AS_Slave

//=======================================
//********* Generic Variable  ***********
//=======================================

unsigned char ch ;

//=======================================
//************  INcludes  ***************
//=======================================

#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_EXTI_Driver.h"
#include "STM32_F103C6_RCC_Driver.h"
#include "STM32_F103C6_USART_Driver.h"
#include "STM32_F103C6_SPI_Driver.h"
#include "STM32_F103C6_I2C_Driver.h"
#include "I2C_Slave_EEPROM.h"

//delay
void delay (int x){
	int i , j ;
	for (i=0 ; i<x ; i++)
		for (j=0 ; j<50 ; j++);
}

void Clock_init (void)
{
	// Enable clock for GPIOA
	RCC_GPIOA_CLK_EN();
	// Enable clock for GPIOB
	RCC_GPIOB_CLK_EN();
	// Enable clock for AFIO
	RCC_AFIO_CLK_EN();
}


//Main Program
int main(void)
{
	Clock_init();

	// Test Case 1
	unsigned char ch1[] = {0x1 , 0x2 , 0x3 , 0x4 , 0x5 , 0x6 , 0x7} ;
	unsigned char ch2[7] = {0} ;

	eeprom_init();
	eeprom_write_Nbytes(0xAF, ch1, 7);
	eeprom_read_Nbytes(0xAF, ch2, 7);


	// Test Case 2

	ch1[0] = 0xA ;
	ch1[1] = 0xB ;
	ch1[2] = 0xC ;
	ch1[3] = 0xD ;

	eeprom_write_Nbytes(0xFFF, ch1, 4);
	eeprom_read_Nbytes(0xFFF, ch2, 4);

	while (1)
	{

	}
	return 0;
}
