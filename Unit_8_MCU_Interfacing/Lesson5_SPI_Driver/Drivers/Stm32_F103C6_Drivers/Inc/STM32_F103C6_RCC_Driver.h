/* STM32_F103C6_RCC_Driver.h
 * Author: ENG. Ahmed Osamaa
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_

// Includes

#include "stm32f103x6.h"

// Clock SW Mode

#define HSI_RCC_CLK			8000000UL
#define HSE_CLK				0


//APIs

uint32_t MCAL_RCC_Get_SYSCLK_Freq(void);
uint32_t MCAL_RCC_Get_HCLK_Freq(void);
uint32_t MCAL_RCC_Get_PCLK1_Freq(void);
uint32_t MCAL_RCC_Get_PCLK2_Freq(void);



#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
