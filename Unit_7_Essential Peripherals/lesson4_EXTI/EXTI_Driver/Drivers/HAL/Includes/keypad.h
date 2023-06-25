/*
 *  keypad.h
 *  Author: ENG.Ahmed Osamaa
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include <stdio.h>


// keypad Port D

#define keyPORT GPIOB

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8

// DRIVE FUNCTION

void keypad_init ();
char getkey() ;



#endif /* KEYPAD_H_ */
