/*  LCD_Keypad_Drivers.c
 *  Author: ENG.Ahmed Osamaa
 */

#include "LCD_driver/lcd.h"
#include "Keypad_driver/keypad.h"

int main(void) 
{
	int count = 0 ;
	char temp ;
	LCD_init();
	keypad_init();
    /* Replace with your application code */
	//LCD_Write_CHAR('A');
	//LCD_Write_STRING("Ahmed");
	//LCD_dis_realNUM (652.48145);
    while (1) 
    {
		temp = getkey();
		if(temp == '!'){
			LCD_Write_command(0x01);
			LCD_GoToXY(0,0);
			count = 0;
		}
		else if(temp == 'E')continue;
		else
		{
			count++;
			next_line(&count);
			LCD_Write_CHAR(temp);
		}
    }
}

