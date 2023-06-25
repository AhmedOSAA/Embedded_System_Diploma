/*
 *  lcd.c
 *  Author: ENG.Ahmed Osamaa
 */ 

#include "lcd.h"

// Enable Pulse
void LCD_KICK(){
	MCAL_GPIO_WritePin(LCD_PORT, Enable , GPIO_PIN_SET);
	delay(50);
	MCAL_GPIO_WritePin(LCD_PORT, Enable , GPIO_PIN_RESET);
	delay(50);
}


void LCD_isBUSY(void)
{/*
	//make LCD port input to read flag
	DDRLCD &= ~(0xFF << DATA_shift);
	LCD_CTRL |= (1<<RW); //read mood
	LCD_CTRL &= ~(1<<RS); 
	LCD_KICK();
	//while((LCD_PORT>>7)&1){
	//delay(30);
	//}
	DDRLCD |= (0xFF << DATA_shift);
	LCD_CTRL &= ~(1<<RW); //Write mood
 */
}

void LCD_init(void)
{
	/*DDRLCD = 0xff;
	DDR_CTRL |= (1<<Enable) | (1<<RW) | (1<<RS);
	LCD_isBUSY();

	// 8-bit
	#ifdef EIGHT_BIT_MODE
	delay(35);
	LCD_Write_command(LCD_FUNCTION_8BIT_2LINES);
	#endif
	// 4-bit
	#ifdef FOUR_BIT_MODE
	delay(35);
	LCD_Write_command(LCD_FUNCTION_4BIT_2LINES);
	#endif

	delay(40);
	LCD_Write_command(LCD_DISP_ON_CURSOR_BLINK);
	delay(1);
	LCD_Write_command(LCD_CLEAR_SCREEN);
	delay(2);
	LCD_Write_command(LCD_ENTRY_MODE);*/

	delay(35);

	// Configure control pins
	//PA8 config_ For RS
	PinCfg.GPIO_PinNumber = RS ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);
	//PA9 config_ For RW
	PinCfg.GPIO_PinNumber = RW ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);
	//PA8 config_ For RS
	PinCfg.GPIO_PinNumber = Enable ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);

	// configure data pins
	//PA0 >> PA7 Output with speed 10MHz
	PinCfg.GPIO_PinNumber = GPIO_PIN_0 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_2 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_3 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_4 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_5 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_6 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_7 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(LCD_PORT, &PinCfg);

	MCAL_GPIO_WritePin(LCD_PORT, Enable, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, RS , GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, RW , GPIO_PIN_RESET);

	// initial LCD
	delay(35);
	LCD_Write_command(LCD_FUNCTION_8BIT_2LINES);
	delay(40);
	LCD_Write_command(LCD_DISP_ON_CURSOR_BLINK);
	delay(10);
	LCD_Write_command(LCD_CLEAR_SCREEN);
	delay(20);
	LCD_Write_command(LCD_ENTRY_MODE);

}

void LCD_Write_command(unsigned char command){
	/*//LCD_isBUSY();
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
#endif
	 */
	//write command
	MCAL_GPIO_WritePort(LCD_PORT ,command);
	// RS = 0 , RW = 0
	MCAL_GPIO_WritePin(LCD_PORT, RS , GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, RW , GPIO_PIN_RESET);
	//Enable pulse
	LCD_KICK();
}
void LCD_Write_CHAR(unsigned char data){
	/*LCD_isBUSY();
	// RS = 1 , RW = 0
	LCD_CTRL &= ~(1<<RW);
	LCD_CTRL |= (1<<RS);

#ifdef EIGHT_BIT_MODE
	//write command
	LCD_PORT = data;
	//Enable pulse
	LCD_KICK();
	delay(1);
#endif
#ifdef FOUR_BIT_MODE
	//write half command
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	//Enable pulse
	LCD_KICK();
	delay(1);
	//write half command
	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	//Enable pulse
	LCD_KICK();
	delay(1);
#endif
	 */

	//write command
	MCAL_GPIO_WritePort(LCD_PORT ,(uint16_t)data);
	// RS = 1 , RW = 0
	MCAL_GPIO_WritePin(LCD_PORT, RS , GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_PORT, RW , GPIO_PIN_RESET);
	//Enable pulse
	LCD_KICK();
	delay(10);

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
