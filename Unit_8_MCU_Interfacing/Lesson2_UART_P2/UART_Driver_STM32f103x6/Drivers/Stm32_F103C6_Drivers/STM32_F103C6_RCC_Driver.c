/* STM32_F103C6_RCC_Driver.c
 * Author: ENG. Ahmed Osamaa
 */

#include "STM32_F103C6_RCC_Driver.h"

/*
 Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
Set and cleared by software to control the division factor of the APB low-speed clock
(PCLK1).
Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16
*/

const uint8_t APBPreScTable[8] = {0,0,0,0,1,2,3,4};  // Shift right

/*
Bits 7:4 HPRE: AHB prescaler
Set and cleared by software to control the division factor of the AHB clock.
0xxx: SYSCLK not divided
1000: SYSCLK divided by 2
1001: SYSCLK divided by 4
1010: SYSCLK divided by 8
1011: SYSCLK divided by 16
1100: SYSCLK divided by 64
1101: SYSCLK divided by 128
1110: SYSCLK divided by 256
1111: SYSCLK divided by 512
*/

const uint8_t AHPPreScTable[16] = {0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8};  // Shift right


uint32_t MCAL_RCC_Get_SYSCLK_Freq(void)
{
	/*
	Bits 3:2 SWS: System clock switch status
	Set and cleared by hardware to indicate which clock source is used as system clock.
	00: HSI oscillator used as system clock
	01: HSE oscillator used as system clock
	10: PLL used as system clock
	11: not applicable
	*/
	switch (((RCC->CFGR >> 2) & 0b11))
	{
		case 0 :
			return HSI_RCC_CLK ;
			break;
		case 1 :
			// HSE " High Speed External Clock User should specify it
			return HSE_CLK ;
			break;
		case 2 :
			// need to calculate it PLLCLK & PLL source MUX
			return 16000000 ;
			break;
	}
	return 0 ;
}
uint32_t MCAL_RCC_Get_HCLK_Freq(void)
{
	// Bits 7:4 HPRE: AHB prescaler
	return  MCAL_RCC_Get_SYSCLK_Freq()  >> AHPPreScTable[( (RCC->CFGR >> 4 ) & 0b1111 )] ;
}
uint32_t MCAL_RCC_Get_PCLK1_Freq(void)
{
	// Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	return  MCAL_RCC_Get_HCLK_Freq()  >> APBPreScTable[( (RCC->CFGR >> 8 ) & 0b111 )] ;
}
uint32_t MCAL_RCC_Get_PCLK2_Freq(void)
{
	// Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	return  MCAL_RCC_Get_HCLK_Freq()  >> APBPreScTable[( (RCC->CFGR >> 11 ) & 0b111 )] ;
}
