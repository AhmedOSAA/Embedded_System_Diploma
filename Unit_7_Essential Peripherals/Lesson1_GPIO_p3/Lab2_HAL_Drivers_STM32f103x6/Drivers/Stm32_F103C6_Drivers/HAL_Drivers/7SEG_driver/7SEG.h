/*  7SEG.h
 *  Author: ENG.Ahmed Osamaa
 */


#ifndef A7SEG_DRIVER_7SEG_H_
#define A7SEG_DRIVER_7SEG_H_

#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"

//7SEG Port

#define SEG7_PORT GPIOB

//configure out number on port pin

#define P1		GPIO_PIN_9
#define P2		GPIO_PIN_10
#define P3		GPIO_PIN_11
#define P4		GPIO_PIN_12
#define P5		GPIO_PIN_13
#define P6		GPIO_PIN_14
#define P7		GPIO_PIN_15


// HEX code of 7Seg Common Anode

#define ZERO 	0x40
#define ONE 	0x79
#define TWO 	0x24
#define THREE 	0x30
#define FOUR	0x19
#define FIVE 	0x12
#define SIX 	0x02
#define SEVEN 	0x78
#define EIGHT 	0x00
#define NINE 	0x10


//APIs

void SEG7_init();
void SEG7_display_NUM(uint8_t Value);

#endif /* 7SEG_DRIVER_7SEG_H_ */
