/* 
 *  lcd.h
 *  Author: ENG.Ahmed Osamaa
 */


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define R_LCD PINA
#define LCD_PORT PORTA
#define DDRLCD  DDRA

#define LCD_CTRL PORTB
#define DDR_CTRL  DDRB

#define RS 1
#define RW 2
#define Enable 3

#define EIGHT_BIT_MODE
//#define FOUR_BIT_MODE

#ifdef EIGHT_BIT_MODE 
#define DATA_shift 0
#endif

#ifdef FOUR_BIT_MODE
#define DATA_shift 4
#endif

#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)


void LCD_init(void);
void LCD_Write_command(unsigned char command);
void LCD_Write_CHAR(unsigned char data);
void LCD_Write_STRING(char* data);
void LCD_isBUSY(void);
void LCD_GoToXY(unsigned char line , unsigned char position);
void LCD_dis_NUM(int num);
void LCD_dis_realNUM (float num);
void next_line (int *count);


#endif /* LCD_H_ */