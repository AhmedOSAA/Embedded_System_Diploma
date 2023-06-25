/* main.h
 * Author: ENG. Ahmed Osamaa
 */


#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_EXTI_Driver.h"
#include "lcd.h"

unsigned int IRQ_FLAG = 0 ;

//delay
void delay (int x){
	int i , j ;
	for (i=0 ; i<x ; i++)
		for (j=0 ; j<50 ; j++);
}

//CAllBack Function for EXTI9

void EXTI9_Callback (void)
{
	IRQ_FLAG = 1 ;
	LCD_Write_STRING("IRQ EXTI9 is happen _|- ");
	delay(200);
}

//Main Program
int main(void)
{
	//Enable Clock for Port B
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();
	//init LCD
	LCD_init();
	LCD_Write_command(LCD_CLEAR_SCREEN);
	// EXTI PIN Configure
	EXTI_PinConfig_t EXTI_CFG ;
	EXTI_CFG.EXTI_PIN = EXTI9PB9 ;
	EXTI_CFG.Trigger_Case = EXTI_Trigger_RISING ;
	EXTI_CFG.P_IRQ_CallBack = EXTI9_Callback ;
	EXTI_CFG.IRQ_EN = EXTI_IRQ_Enable ;
	MCAL_EXTI_GPIO_init(&EXTI_CFG);

	IRQ_FLAG = 1 ;

	while (1)
	{
		if(IRQ_FLAG)
		{
			LCD_Write_command(LCD_CLEAR_SCREEN);
			IRQ_FLAG = 0 ;
		}
	}
	return 0;
}
