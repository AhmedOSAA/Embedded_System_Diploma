/*  LCD_Keypad_Drivers.c
 *  Author: ENG.Ahmed Osamaa
 */

#include "LCD_driver/lcd.h"
#include "Keypad_driver/keypad.h"

int main(void) 
{
	LCD_init();
	LCD_Write_STRING("Learn IN Depth");
	_delay_ms(1000);

}

