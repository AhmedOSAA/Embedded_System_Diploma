/*
 *  lcd.c
 *  Author: ENG.Ahmed Osamaa
 */ 

#include "lcd.h"


// Enable Pulse
void LCD_KICK(){
	LCD_CTRL |= (1<<Enable);
	_delay_ms(10);
	LCD_CTRL &= ~(1<<Enable);
	_delay_ms(10);
}



/* NOTE : 
*			For 4-bit interface data, only four bus lines (DB4 to DB7) are used for transfer. Bus lines DB0 to DB3
*				are disabled. The data transfer between the HD44780U and the MPU is completed after the 4-bit data
*				has been transferred twice. As for the order of data transfer, the four high order bits (for 8-bit operation,
*				DB4 to DB7) are transferred before the four low order bits (for 8-bit operation, DB0 to DB3).
*		? >>>	The busy flag must be checked (one instruction) after the 4-bit data has been transferred twice. <<< ?
*				Two more 4-bit operations then transfer the busy flag and address counter data.
*
*/

void LCD_isBUSY(void)
{
	//make LCD port input to read flag
	DDRLCD &= ~(0xFF << DATA_shift);
	LCD_CTRL |= (1<<RW); //read mood
	LCD_CTRL &= ~(1<<RS); 
	LCD_KICK();
	//while((LCD_PORT>>7)&1){
		//_delay_ms(30);
	//}
	DDRLCD |= (0xFF << DATA_shift);
	LCD_CTRL &= ~(1<<RW); //Write mood
}
 
void LCD_init(void)
{
	DDRLCD = 0xff;
	DDR_CTRL |= ((1<<Enable) | (1<<RW) | (1<<RS));
	LCD_isBUSY();
	
	// 8-bit
	#ifdef EIGHT_BIT_MODE
	_delay_ms(35);
	LCD_Write_command(LCD_FUNCTION_8BIT_2LINES);
	#endif
	// 4-bit
	#ifdef FOUR_BIT_MODE
	_delay_ms(35);
	LCD_Write_command(0x02);
	LCD_Write_command(LCD_FUNCTION_4BIT_2LINES);
	#endif
	
	_delay_us(40);
	LCD_Write_command(LCD_DISP_ON_CURSOR_BLINK);
	_delay_us(1);
	LCD_Write_command(LCD_CLEAR_SCREEN);
	_delay_us(2);
	LCD_Write_command(LCD_ENTRY_MODE);
	
}
void LCD_Write_command(unsigned char command){
	LCD_isBUSY();
	// RS = 0 , RW = 0
	LCD_CTRL &= ~((1<<RW) | (1<<RS));
	#ifdef EIGHT_BIT_MODE
	//write command
	LCD_PORT = command;
	//Enable pulse
	LCD_KICK();
	#endif
	
	#ifdef FOUR_BIT_MODE
	//write half command
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);   
	//Enable pulse
	LCD_KICK();
	//write half command
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	//Enable pulse
	LCD_KICK();
	_delay_ms(1);
	LCD_isBUSY();   // Very important instruction must be execute after send 2 cycle of data or command at 4-bit LCD

	#endif
}
void LCD_Write_CHAR(unsigned char data){
	LCD_isBUSY();
	
	// RS = 1 , RW = 0
	LCD_CTRL &= ~(1<<RW);
	LCD_CTRL |= (1<<RS);
	
	#ifdef EIGHT_BIT_MODE
	LCD_isBUSY();
	//write command
	LCD_PORT = data;
	//Enable pulse
	LCD_KICK();
	_delay_ms(1);
	#endif
	
	#ifdef FOUR_BIT_MODE
	//write half command
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	//Enable pulse
	LCD_KICK();
	//write half command
	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	//Enable pulse
	LCD_KICK();
	_delay_ms(1);
	LCD_isBUSY();           // Very important instruction must be execute after send 2 cycle of data or command at 4-bit LCD
	#endif
}
void LCD_Write_STRING(char* data){
	int count = 0 ;
	while(*data > 0){
		count++;
		LCD_Write_CHAR(*data);
		data++;
		if(count == 16){
			LCD_GoToXY(1,0);
		}
		else if (count == 32 || count == 33 ){
			LCD_Write_command(LCD_CLEAR_SCREEN);
			LCD_GoToXY(0,0);
			count = 0 ;
		}
	}
}

void LCD_GoToXY(unsigned char line , unsigned char position){
	if(line == 0){
		if(position < 16 && position >= 0){
			LCD_Write_command(0x80+position);
		}
	}
	else if(line == 1){
		if(position < 16 && position >= 0){
			LCD_Write_command(0xc0+position);
		}
	}
}

void LCD_dis_NUM (int num){
	char str[10];
	sprintf(str,"%d",num);
	LCD_Write_STRING(str);	

}

void LCD_dis_realNUM (float num){
	//EX : -652.4545
	char str[16];
	char* sign = (num < 0)? "-" : "";      // check the negative sign and store it if exist
	float tmvlue = (num < 0)? -num : num ;  // convert the num to positive 652.4545 
	int tmint = tmvlue ;				   // take the real part 652
	float tmfrc = tmvlue - tmint ;		   // get on the friction part 0.4545
	int tmintfrc = tmfrc * 10000 ;		   // convert friction to real 4545
	
	// print each part to get the real num in a string  
	
	sprintf (str, "%s%d.%04d",sign,tmint,tmintfrc); 
	
	LCD_Write_STRING(str);
	
}

void next_line (int* count){
	if(*count == 16){
		LCD_GoToXY(1,0);
	}
	else if (*count == 32 || *count == 33 ){
		LCD_Write_command(LCD_CLEAR_SCREEN);
		LCD_GoToXY(0,0);
		*count = 0 ;
	}
}