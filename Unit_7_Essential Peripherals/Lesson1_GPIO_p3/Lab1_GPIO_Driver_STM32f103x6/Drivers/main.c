/* main.h
 * Author: ENG. Ahmed Osamaa
 */


#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"

void Clock_init ()
{
	// Enable clock GPIOA & GPIOB
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
}


void GPIP_init ()
{
	GPIO_PinConfig_t PinCfg ;

	//PA1 config_ Port A pin 1
	PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_init(GPIOA, &PinCfg);
	//PA13 config_ Port A pin 13
	PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_init(GPIOA, &PinCfg);

	//PB1 config_ Port B pin 1
	PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(GPIOB, &PinCfg);
	//PB13 config_ Port B pin 13
	PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(GPIOB, &PinCfg);

}

//delay
void delay (int x){
	int i , j ;
	for (i=0 ; i<=x ; i++)
		for (j=0 ; j<=255 ; j++);
}
//Main Program
int main(void)
{
	Clock_init ();
	GPIP_init () ;

	while (1){
		// single press
		if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0){
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0);
		}
		// Multiple press
		if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == 1)
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		}
		delay(100);
	}
	return 0;
}


