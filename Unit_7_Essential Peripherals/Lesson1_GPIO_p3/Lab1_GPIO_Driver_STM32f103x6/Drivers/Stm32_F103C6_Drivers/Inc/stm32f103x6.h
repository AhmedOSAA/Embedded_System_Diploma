/* stm32f103x6.h
 * Author: ENG. Ahmed Osamaa
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
// Includes
//-----------------------------

#include <stdlib.h>
#include <stdint.h>

//--------------------------------
// Base addresses for Memories
//--------------------------------

#define Flash_Memory_Base						0x08000000UL   // (UL) >> unsigned long
#define System_Memory_Base						0x1FFFF000UL
#define SRAM_Memory_Base						0x20000000UL

#define Peripherals_Base						0x40000000UL
#define Cortex_M3_Internal_Peripherals_Base		0x40000000UL

//------------------------------------
// Base addresses for AHB Peripheral
//------------------------------------

//>RCC
#define RCC_BASE		0x40021000UL


//------------------------------------
// Base addresses for APB2 Peripheral
//------------------------------------

//>GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE		0x40010800UL
#define GPIOB_BASE		0x40010C00UL
//C,D Partial included in LQFP48 Package
#define GPIOC_BASE		0x40011000UL
#define GPIOD_BASE		0x40011400UL
//E , F , G are not included in LQFP48 Package
#define GPIOE_BASE		0x40011800UL
//>EXTI
#define EXTI_BASE		0x40010400UL

//>AFIO
#define AFIO_BASE		0x40010000UL

//------------------------------------
// Base addresses for APB1 Peripheral
//------------------------------------

//=========================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral registers
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


//•••••••••••••••••••••••••
// Peripheral registers : GPIO
//•••••••••••••••••••••••••

typedef struct
{
	volatile uint32_t CRL ;
	volatile uint32_t CRH ;
	volatile uint32_t IDR ;
	volatile uint32_t ODR ;
	volatile uint32_t BSRR ;
	volatile uint32_t BRR ;
	volatile uint32_t LCKR ;
}GPIO_typedef;


//•••••••••••••••••••••••••
// Peripheral registers : RCC
//•••••••••••••••••••••••••
typedef struct
{
	volatile uint32_t CR ;
	volatile uint32_t CFGR ;
	volatile uint32_t CIR ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR ;
	volatile uint32_t AHBENR ;
	volatile uint32_t APB2ENR ;
	volatile uint32_t APB1ENR ;
	volatile uint32_t BDCR ;
	volatile uint32_t CSR ;
}RCC_typedef;


//•••••••••••••••••••••••••
// Peripheral registers : EXTI
//•••••••••••••••••••••••••
typedef struct
{
	volatile uint32_t IMR ;
	volatile uint32_t EMR ;
	volatile uint32_t RTSR ;
	volatile uint32_t FTSR ;
	volatile uint32_t SWIER ;
	volatile uint32_t PR ;
}EXTI_typedef;

//•••••••••••••••••••••••••
// Peripheral registers : AFIO
//•••••••••••••••••••••••••
typedef struct
{
	volatile uint32_t EVCR ;
	volatile uint32_t MAPR ;
	volatile uint32_t EXTICR1 ;
	volatile uint32_t EXTICR2 ;
	volatile uint32_t EXTICR3 ;
	volatile uint32_t EXTICR4 ;
	volatile uint32_t APB1ENR ;   // 0x14
	volatile uint32_t RESERVED0 ; // 0x18
	volatile uint32_t MAPR2 ;     // 0x1C
}AFIO_typedef;


//===========================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral Instants
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA			((GPIO_typedef *)GPIOA_BASE)
#define GPIOB			((GPIO_typedef *)GPIOB_BASE)
#define GPIOC			((GPIO_typedef *)GPIOC_BASE)
#define GPIOD			((GPIO_typedef *)GPIOD_BASE)
#define GPIOE			((GPIO_typedef *)GPIOE_BASE)

#define EXTI			((EXTI_typedef *)EXTI_BASE)

#define RCC				((RCC_typedef *)RCC_BASE)

#define AFIO			((AFIO_typedef *)AFIO_BASE)

//===========================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Clock Enable Macros
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()			(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()			(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()			(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()			(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()			(RCC->APB2ENR |= 1<<6)

#define RCC_AFIO_CLK_EN()			(RCC->APB2ENR |= 1<<0)

#endif /* INC_STM32F103X6_H_ */
