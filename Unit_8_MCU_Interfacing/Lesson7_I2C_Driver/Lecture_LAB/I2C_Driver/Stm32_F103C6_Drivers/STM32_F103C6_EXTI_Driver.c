/* STM32_F103C6_EXTI_DRIVER.c
 * Author: ENG. Ahmed Osamaa
 */

#include "STM32_F103C6_EXTI_Driver.h"


/*
 * ============================================================================
 * 								Generic Variables
 * ============================================================================
 */

	void (*GP_IRQ_CallBack[16])(void);

/*
 * ============================================================================
 * 								Generic Macros
 * ============================================================================
 */

#define AFIO_SXTI_GPIO_Mapping(x)		   ((x==GPIOA)?0:\
											(x==GPIOB)?1:\
											(x==GPIOC)?2:\
											(x==GPIOD)?3:0)
/*
 * ============================================================================
 * 								Generic Functions
 * ============================================================================
 */

	void Enable_NVIC (uint16_t IRQ)
	{
		switch(IRQ)
		{
		case 0 :
			NVIC_IRQ6_EXTI0_Enable;
			break;
		case 1 :
			NVIC_IRQ7_EXTI1_Enable;
			break;
		case 2 :
			NVIC_IRQ8_EXTI2_Enable;
			break;
		case 3 :
			NVIC_IRQ9_EXTI3_Enable;
			break;
		case 4 :
			NVIC_IRQ10_EXTI4_Enable;
			break;
		case 5 :
		case 6 :
		case 7 :
		case 8 :
		case 9 :
			NVIC_IRQ23_EXTI5_9_Enable;
			break;
		case 10 :
		case 11 :
		case 12 :
		case 13 :
		case 14 :
		case 15 :
			NVIC_IRQ40_EXTI10_15_Enable;
			break;
		}
	}
	void Disable_NVIC (uint16_t IRQ)
	{
		switch(IRQ)
		{
		case 0 :
			NVIC_IRQ6_EXTI0_Disable;
			break;
		case 1 :
			NVIC_IRQ7_EXTI1_Disable;
			break;
		case 2 :
			NVIC_IRQ8_EXTI2_Disable;
			break;
		case 3 :
			NVIC_IRQ9_EXTI3_Disable;
			break;
		case 4 :
			NVIC_IRQ10_EXTI4_Disable;
			break;
		case 5 :
		case 6 :
		case 7 :
		case 8 :
		case 9 :
			NVIC_IRQ23_EXTI5_9_Disable;
			break;
		case 10 :
		case 11 :
		case 12 :
		case 13 :
		case 14 :
		case 15 :
			NVIC_IRQ40_EXTI10_15_Disable;
			break;
		}
	}

void Update_EXTI(EXTI_PinConfig_t* EXTI_Config)
{
	//==================================
	//1-configure GPIO to be AF input -> Floating input
	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN ;
	PinCfg.GPIO_MODE	  = GPIO_MODE_AF_INPUT;
	MCAL_GPIO_init(EXTI_Config->EXTI_PIN.GPIO_Port, &PinCfg);

	//==================================
	//2- Update AFIO to route between EXTI Line with port A,B,C,D

	uint8_t AFIO_EXTICR_index = EXTI_Config->EXTI_PIN.EXTI_InputLineNumber / 4 ;
	uint8_t AFIO_EXTICR_Position = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber % 4)*4 ;

	// Clear the four bit in AFIO EXTICR Register
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(1<<AFIO_EXTICR_Position);

	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_SXTI_GPIO_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port) & 0xf) << AFIO_EXTICR_Position );

	//==================================
	//3-Update Rising & Falling Edge
	EXTI->RTSR &= ~(1<< EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(1<< EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	if (EXTI_Config->Trigger_Case == EXTI_Trigger_RISING)
	{
		EXTI->RTSR |= (1<< EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if (EXTI_Config->Trigger_Case == EXTI_Trigger_FALLING)
	{
		EXTI->FTSR |= (1<< EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if (EXTI_Config->Trigger_Case == EXTI_Trigger_RisingANDFalling)
	{
		EXTI->RTSR |= (1<< EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		EXTI->FTSR |= (1<< EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}

	//==================================
	//4-Update IRQ Handling CALLBACK

	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;

	//==================================
	//5- Enable/Disable IRQ
	if (EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber) ;
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}else{

		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber) ;
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
}

/*
 * ============================================================================
 * 								APIs Functions Definition
 * ============================================================================
 */


/*=====================================================================
 * @Fun			- MCAL_EXTI_GPIO_Deinit
 * @brief		- this is used to initialize EXTI from specific GPIO PIN and specfy the Mask/Trigger Condition and IRQ CallBack.
 * @param [in] 	- EXTI_Config set by @ref EXTI_define , EXTI_Trigger_define and EXTI_IRQ_define
 * @retval		- none
 * NOTE : 		- Stm32f103C6 MCU has GPIO A,B,C,D,E Modules
 * 					but LQFP48 PPackage has only GPIO A,B, Partial of C/D exported as external PINS from the MCU
 * 				- Also Mandatory to Enable RCC Clock for AFIO and the corresponding GPIO.
 */

void MCAL_EXTI_GPIO_init(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

/*=====================================================================
 * @Fun			- MCAL_EXTI_GPIO_Deinit
 * @brief		- Reset EXTI Register and NVIC corresponding IRQ mask
 * @param [in] 	- none
 * @retval		- none
 */
void MCAL_EXTI_GPIO_Deinit(void)
{

	EXTI->IMR = 0x00000000 ;
	EXTI->EMR = 0x00000000 ;

	EXTI->RTSR = 0x00000000 ;
	EXTI->FTSR = 0x00000000 ;

	EXTI->SWIER = 0x00000000 ;

	EXTI->PR = 0xFFFFFFFF ;     // W1C  "Write 1 to Clear

	//Disable EXTI IRQ  From NVIC
	NVIC_IRQ6_EXTI0_Disable		;
	NVIC_IRQ7_EXTI1_Disable		;
	NVIC_IRQ8_EXTI2_Disable		;
	NVIC_IRQ9_EXTI3_Disable		;
	NVIC_IRQ10_EXTI4_Disable	;
	NVIC_IRQ23_EXTI5_9_Disable	;
	NVIC_IRQ40_EXTI10_15_Disable;

}

/*=====================================================================
 * @Fun			- MCAL_EXTI_GPIO_Deinit
 * @brief		- this is used to Update at run time EXTI from specific GPIO PIN and specfy the Mask/Trigger Condition and IRQ CallBack.
 * @param [in] 	- EXTI_Config set by @ref EXTI_define , EXTI_Trigger_define and EXTI_IRQ_define
 * @retval		- none
 * NOTE : 		- Stm32f103C6 MCU has GPIO A,B,C,D,E Modules
 * 					but LQFP48 PPackage has only GPIO A,B, Partial of C/D exported as external PINS from the MCU
 * 				- Also Mandatory to Enable RCC Clock for AFIO and the corresponding GPIO.
 */

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}




//==================================================================
//==================================================================
//===============		   	ISR FUNCTIONS	    		============
//==================================================================
//==================================================================


void EXTI0_IRQHandler(void)
{
	// CLear by write 1 into pending register
	EXTI->PR |= 1<<0 ;
	// CALLBACK IRQ_CALL
	GP_IRQ_CallBack[0]();

}
void EXTI1_IRQHandler(void)
{
	// CLear by write 1 into pending register
	EXTI->PR |= 1<<1 ;
	// CALLBACK IRQ_CALL
	GP_IRQ_CallBack[1]();
}
void EXTI2_IRQHandler(void)
{
	// CLear by write 1 into pending register
	EXTI->PR |= 1<<2 ;
	// CALLBACK IRQ_CALL
	GP_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(void)
{
	// CLear by write 1 into pending register
	EXTI->PR |= 1<<3 ;
	// CALLBACK IRQ_CALL
	GP_IRQ_CallBack[3]();
}
void EXTI4_IRQHandler(void)
{
	// CLear by write 1 into pending register
	EXTI->PR |= 1<<4 ;
	// CALLBACK IRQ_CALL
	GP_IRQ_CallBack[4]();
}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5){EXTI->PR |= 1<<5 ; GP_IRQ_CallBack[5]();}
	if(EXTI->PR & 1<<6){EXTI->PR |= 1<<6 ; GP_IRQ_CallBack[6]();}
	if(EXTI->PR & 1<<7){EXTI->PR |= 1<<7 ; GP_IRQ_CallBack[7]();}
	if(EXTI->PR & 1<<8){EXTI->PR |= 1<<8 ; GP_IRQ_CallBack[8]();}
	if(EXTI->PR & 1<<9){EXTI->PR |= 1<<9 ; GP_IRQ_CallBack[9]();}
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1<<10){EXTI->PR |= 1<<10 ; GP_IRQ_CallBack[10]();}
	if(EXTI->PR & 1<<11){EXTI->PR |= 1<<11 ; GP_IRQ_CallBack[11]();}
	if(EXTI->PR & 1<<12){EXTI->PR |= 1<<12 ; GP_IRQ_CallBack[12]();}
	if(EXTI->PR & 1<<13){EXTI->PR |= 1<<13 ; GP_IRQ_CallBack[13]();}
	if(EXTI->PR & 1<<14){EXTI->PR |= 1<<14 ; GP_IRQ_CallBack[14]();}
	if(EXTI->PR & 1<<15){EXTI->PR |= 1<<15 ; GP_IRQ_CallBack[15]();}
}
