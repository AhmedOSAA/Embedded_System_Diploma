/* main.h
 * Author: ENG. Ahmed Osamaa
 */


#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "lcd.h"
#include "keypad.h"
#include "7SEG.h"

uint8_t SEG[] = {ZERO ,ONE ,TWO ,THREE ,FOUR ,FIVE ,SIX ,SEVEN ,EIGHT ,NINE ,ZERO } ;
unsigned char SEG_to_LCD[] = {'0' ,'1' ,'2' ,'3' ,'4' ,'5' ,'6' ,'7' ,'8' ,'9' ,'0'} ;

char APP_Keypad();
void APP_GPIO_TEST ();
void APP_SEG7(char temp);

void Clock_init ()
{
	// Enable clock GPIOA & GPIOB
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
}

void HAL_init(){
	LCD_init () ;
	keypad_init();
	SEG7_init();
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
	for (i=0 ; i<x ; i++)
		for (j=0 ; j<50 ; j++);
}

void Booting_Program(){
	int i ;
	Clock_init ();
	HAL_init();

	// Test LCD_driver at STM32
	LCD_Write_STRING(">>> Program is  Booting");
	delay(20);
	LCD_Write_command(LCD_CLEAR_SCREEN);
	for(i=0;i<(sizeof(SEG)/sizeof(uint8_t));i++){
		LCD_Write_CHAR(SEG_to_LCD[i]);
		SEG7_display_NUM(SEG[i]);
		LCD_Write_command(LCD_CLEAR_SCREEN);
	}
	SEG7_display_NUM(SEG[8]);
	LCD_Write_STRING("Hey There !");
	delay(20);
	LCD_Write_command(LCD_CLEAR_SCREEN);
	LCD_Write_STRING(">Booting Success");
	delay(20);
	LCD_Write_command(LCD_CLEAR_SCREEN);
	LCD_Write_STRING(" Learn IN Depth");
	LCD_Write_command(0xc0);
	LCD_Write_STRING("ENG.Ahmed Osamaa");
	delay(200);
	LCD_Write_command(LCD_CLEAR_SCREEN);
	LCD_Write_STRING(">>>Start Now");
	delay(20);
	LCD_Write_command(LCD_CLEAR_SCREEN);
	LCD_Write_command(0x80);
	SEG7_display_NUM(SEG[0]);
}



//Main Program
int main(void)
{
	char temp ;
	Booting_Program();

	while (1){
	temp = APP_Keypad();
	APP_SEG7(temp);
	}
	return 0;
}


char APP_Keypad(){
	// Test Keypad_driver at STM32
	int count = 0 ;
	char temp ;
	temp = getkey();
	if(temp == '!'){
		LCD_Write_command(0x01);
		LCD_GoToXY(0,0);
		count = 0;
	}
	else if(temp == 'E');
	else
	{
		count++;
		next_line(&count);
		LCD_Write_CHAR(temp);
	}
	return temp ;
}

void APP_SEG7(char temp){
	if(temp == '!' || temp == '+' ||temp == 'x' || temp == '/' || temp == '=' || temp == '-' );
		else if(temp == 'E');
		else if(temp == '0')SEG7_display_NUM(ZERO);
		else if(temp == '1')SEG7_display_NUM(ONE);
		else if(temp == '2')SEG7_display_NUM(TWO);
		else if(temp == '3')SEG7_display_NUM(THREE);
		else if(temp == '4')SEG7_display_NUM(FOUR);
		else if(temp == '5')SEG7_display_NUM(FIVE);
		else if(temp == '6')SEG7_display_NUM(SIX);
		else if(temp == '7')SEG7_display_NUM(SEVEN);
		else if(temp == '8')SEG7_display_NUM(EIGHT);
		else if(temp == '9')SEG7_display_NUM(NINE);
}

void APP_GPIO_TEST (){
	/* LAP_GPIO_Driver
	 * // single press
				MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
				while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0);
			}
			// Multiple press
			if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == 1)
			{
				MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
			}
			delay(100);*/
}
