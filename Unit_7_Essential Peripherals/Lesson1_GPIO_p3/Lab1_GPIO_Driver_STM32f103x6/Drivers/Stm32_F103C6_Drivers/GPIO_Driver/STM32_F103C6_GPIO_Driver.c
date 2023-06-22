/* STM32_F103C6_GPIO_DRIVER.c
 * Author: ENG. Ahmed Osamaa
 */

#include "STM32_F103C6_GPIO_Driver.h"

uint8_t Get_CRLH_Position (uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0 :
		return 0 ;
		break;
	case GPIO_PIN_1 :
		return 4 ;
		break;
	case GPIO_PIN_2 :
		return 8 ;
		break;
	case GPIO_PIN_3 :
		return 12 ;
		break;
	case GPIO_PIN_4 :
		return 16 ;
		break;
	case GPIO_PIN_5 :
		return 20 ;
		break;
	case GPIO_PIN_6 :
		return 24 ;
		break;
	case GPIO_PIN_7 :
		return 28 ;
		break;
	case GPIO_PIN_8 :
		return 0 ;
		break;
	case GPIO_PIN_9 :
		return 4 ;
		break;
	case GPIO_PIN_10 :
		return 8 ;
		break;
	case GPIO_PIN_11 :
		return 12 ;
		break;
	case GPIO_PIN_12 :
		return 16 ;
		break;
	case GPIO_PIN_13 :
		return 20 ;
		break;
	case GPIO_PIN_14 :
		return 24 ;
		break;
	case GPIO_PIN_15 :
		return 28 ;
		break;
	}
	return 0 ;
}


/*=====================================================================
 * @Fun			- MCAL_GPIO_init
 * @brief		- Initializes the GPIOx PINy according to the specified parameter in the PinConfig
 * @param [in] 	- GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in]	- PinConfig is a pointer to a GPIO_PinConfig_t structure that contain
 * 					the configuration information for the specified GPIO PIN.
 * @retval		- none
 * Note			- Stm32f103C6 MCU has GPIO A,B,C,D,E Modules
 * 					but LQFP48 PPackage has only GPIO A,B, Partial of C/D exported as external PINS from the MCU
 */


void MCAL_GPIO_init(GPIO_typedef* GPIOx , GPIO_PinConfig_t* PinConfig)
{
	// Port configuration register low (GPIOx_CRL) Configure PINs from 0 >>> 7
	// Port configuration register High (GPIOx_CRH) Configure PINs from 8 >>> 15
	volatile uint32_t* configregister = NULL ;
	uint8_t pin_config = 0 ;

	configregister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH ;
	//Clear CNFx[0:1] & MODEx [0:1]
	(*configregister) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));;
	//if pin is output
	if((PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD) ||(PinConfig->GPIO_MODE == GPIO_MODE_AF_PP)||(PinConfig->GPIO_MODE == GPIO_MODE_AF_OD))
	{
		//Set CNFx[0:1] & MODEx [0:1]
		pin_config = ((((PinConfig->GPIO_MODE - 4)<<2) | PinConfig->GPIO_output_speed ) & 0x0f );
	}
	else
	{
		if((PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO)||(PinConfig->GPIO_MODE == GPIO_MODE_Analog))
		{
			//Set CNFx[0:1] & MODEx [0:1]
			pin_config = ((((PinConfig->GPIO_MODE)<<2) | 0x00 ) & 0x0f );
		}
		else if ((PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT)) // consider it as input floating
		{
			//Set CNFx[0:1] & MODEx [0:1]
			pin_config = ((((GPIO_MODE_INPUT_FLO)<<2) | 0x00 ) & 0x0f );
		}
		else // Pull-UP / Pull-Down input
		{
			//Set CNFx[0:1] & MODEx [0:1]
			pin_config = ((((GPIO_MODE_INPUT_PU)<<2) | 0x00 ) & 0x0f );
			if((PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU))
				GPIOx->ODR |= (PinConfig->GPIO_PinNumber);
			else GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
		}

	}
	//Write on CRL or CRH
	*configregister |= (pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
}

/*=====================================================================
 * @Fun			- MCAL_GPIO_Deinit
 * @brief		- Reset the GPIOx PINy according to the specified parameter in the PinConfig
 * @param [in] 	- GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval		- none
 * Note			- none
 */
void MCAL_GPIO_Deinit(GPIO_typedef* GPIOx)
{
	//APB2 peripheral reset register (RCC_APB2RSTR)
	//Set and Cleared by software
	if(GPIOx == GPIOA){
		RCC->APB2RSTR |= (1<<2) ;		//Bit 2 IOPARST: IO port A reset
		RCC->APB2RSTR &= ~(1<<2) ;
	}else if(GPIOx == GPIOB){
		RCC->APB2RSTR |= (1<<3) ;		//Bit 3 IOPARST: IO port B reset
		RCC->APB2RSTR &= ~(1<<3) ;
	}else if(GPIOx == GPIOC){
		RCC->APB2RSTR |= (1<<4) ;		//Bit 4 IOPARST: IO port C reset
		RCC->APB2RSTR &= ~(1<<4) ;
	}else if(GPIOx == GPIOD){
		RCC->APB2RSTR |= (1<<5) ;		//Bit 5 IOPARST: IO port D reset
		RCC->APB2RSTR &= ~(1<<5) ;
	}else if(GPIOx == GPIOE){
		RCC->APB2RSTR |= (1<<6) ;		//Bit 6 IOPARST: IO port E reset
		RCC->APB2RSTR &= ~(1<<6) ;
	}
}

/*=====================================================================
 * @Fun			- MCAL_GPIO_ReadPin
 * @brief		- Read specific input pin
 * @param [in] 	- GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- PinNumber: Set Pin Number according @ref GPIO_Pin_define
 * @retval		- the input pin value (two value based on @ref GPIO_PIN_STATE)
 * Note			- none
 */

uint8_t MCAL_GPIO_ReadPin (GPIO_typedef* GPIOx, uint16_t PinNumber)
{
	uint8_t bitstatus ;
	if ((GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_SET ;
	}
	else{
		bitstatus = GPIO_PIN_RESET ;
	}
	return bitstatus ;
}

/*=====================================================================
 * @Fun			- MCAL_GPIO_ReadPort
 * @brief		- Read the input port value
 * @param [in] 	- GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval		- the input port value
 * Note			- none
 */

uint16_t MCAL_GPIO_ReadPort (GPIO_typedef* GPIOx)
{
	uint16_t portvalue ;
	portvalue = (uint16_t)GPIOx->IDR ;
	return portvalue ;
}


/*=====================================================================
 * @Fun			- MCAL_GPIO_WritePin
 * @brief		- write on specific output pin
 * @param [in] 	- GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- PinNumber: Set Pin Number according @ref GPIO_Pin_define
 * @param [in] 	- Value: Pin value (two value based on @ref GPIO_PIN_STATE)
 * @retval		- none
 * Note			- none
 */


void MCAL_GPIO_WritePin (GPIO_typedef* GPIOx , uint16_t PinNumber , uint8_t Value){
	if (Value != GPIO_PIN_RESET)
	{
		//GPIOx->ODR |= PinNumber ;
		// or
		GPIOx->BSRR = (uint32_t)PinNumber ;
	}
	else{
		GPIOx->BRR = (uint32_t)PinNumber ;
	}
}


/*=====================================================================
 * @Fun			- MCAL_GPIO_WritePort
 * @brief		- Write on the output port
 * @param [in] 	- GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- Value: Port value
 * @retval		- none
 * Note			- none
 */


void MCAL_GPIO_WritePort (GPIO_typedef* GPIOx , uint16_t Value){

	GPIOx->ODR = (uint32_t)Value ;

}


/*=====================================================================
 * @Fun			- MCAL_GPIO_TogglePin
 * @brief		- Toggle specific pin
 * @param [in] 	- GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- PinNumber: Set Pin Number according @ref GPIO_Pin_define
 * @retval		- none
 * Note			- none
 */

void MCAL_GPIO_TogglePin (GPIO_typedef* GPIOx , uint16_t PinNumber){

	GPIOx->ODR ^= (PinNumber) ;

}

/*=====================================================================
 * @Fun			- MCAL_GPIO_LockPin
 * @brief		- The locking mechanism allows the IO configuration to be frozen
 * @param [in] 	- GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 	- PinNumber: Set Pin Number according @ref GPIO_Pin_define
 * @retval		- OK if config is locked or ERROR if pin failed to be locked (@ref GPIO_RETURN_LOCK)
 * Note			- none
 */

uint8_t MCAL_GPIO_LockPin (GPIO_typedef* GPIOx , uint16_t PinNumber)
{
	/*Bit 16 LCKK[16]: Lock key
This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
0: Port configuration lock key not active
1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
• LOCK key writing sequence:
	>>Write 1
	>>Write 0
	>>Write 1
	>>Read 0
	>>Read 1 (this read is optional but confirms that the lock is active)
Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
Any error in the lock sequence will abort the lock.
Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
These bits are read write but can only be written when the LCKK bit is 0.
0: Port configuration not locked
1: Port configuration locked.*/
	// LAB Impelement
	//Set LCKK[16]
	volatile uint32_t temp = 1<<16 ;
	//Set the LCKy
	temp |= (uint32_t)PinNumber ;
	// Write 1
	GPIOx->LCKR = temp ;
	// Write 0
	GPIOx->LCKR = (uint32_t)PinNumber;
	// Write 1
	GPIOx->LCKR = temp ;
	//Read 0
	temp = GPIOx->LCKR ;
	// Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & 1<<16)){
		return GPIO_RETURN_LOCK_Enabled ;
	}else{
		return GPIO_RETURN_LOCK_ERROR ;
	}


	/* My implement
	uint8_t temp ;
	//Set the LCKy
	GPIOx->LCKR |= (uint32_t)PinNumber ;
	// Write 1
	GPIOx->LCKR |= (1<<16) ;
	// Write 0
	GPIOx->LCKR &= ~(1<<16) ;
	// Write 1
	GPIOx->LCKR |= (1<<16) ;
	// Read 0
	temp = ((GPIOx->LCKR >> 16) & 1);
	// Read 1 (this read is optional but confirms that the lock is active)
	temp = ((GPIOx->LCKR >> 16) & 1);

	if(temp == 1){
		return GPIO_RETURN_LOCK_Enabled ;
	}else{
		return GPIO_RETURN_LOCK_ERROR ;
	}
	 */
}
