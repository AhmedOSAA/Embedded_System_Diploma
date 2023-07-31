/* STM32_F103C6_USART_Driver.c
 * Author: ENG. Ahmed Osamaa
 */

//Includes
#include "STM32_F103C6_USART_Driver.h"

//=======================================================
//*****************  Generic Variable  ******************
//=======================================================

UART_Config* Global_UART_Config = NULL ;

UART_Config* Global_UART1_Config = NULL ;
UART_Config* Global_UART2_Config = NULL ;
UART_Config* Global_UART3_Config = NULL ;

//=======================================================
//*****************  Generic Function  ******************
//=======================================================



//=======================================================
//***************  APIs Impelementation  ****************
//=======================================================


/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_UART_Init
 * @brief						- Initialization UART (Supported feature Asynch. Only).
 * @param[in]					- USARTx: where x can be (1..3 depending on device used).
 * @param[in]					- UART_Config : ALL UART Configuration
 * @retval						- NONE
 * Note							- Support For now Asunch mode & Clock 8 MHz
 * */

void MCAL_UART_Init (USART_typedef * USARTx , UART_Config * UART_Config)
{
	Global_UART_Config = UART_Config ;
	uint32_t PCLK , BRR ;

	//1- Enable the clock gor given USART peripheral
	if (USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
		Global_UART1_Config = UART_Config ;
	}
	else if (USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
		Global_UART2_Config = UART_Config ;
	}
	else if (USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
		Global_UART3_Config = UART_Config ;
	}

	//2- UART Enable Module
	// Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13 ;

	//3- Enable TX / RX according to the USART_MODE configuration item
	//USART1_CR1 >> Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= UART_Config->USART_Mode ;

	//4- Payload length 8 or 9 bit
	//USART1_CR1 >> Bit 12 M: Word length
	USARTx->CR1 |= UART_Config->Payload ;

	//4- configure of parity control bit field
	//USART1_CR1 >> Bit 10 PCE: Parity control enable & Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->Parity ;

	//5- USART Hardware Flow Control
	//USART_CR3 >> Bit 8 RTSE: RTS enable & Bit 9 CTSE: CTS enable
	USARTx->CR3 |= UART_Config->HWFlowCtl ;

	// 6- Configuration BoadRate
	// PCLK1 for USART2 , 3
	// PCLK2 for USART1
	if (USARTx == USART1)
	{
		PCLK = MCAL_RCC_Get_PCLK2_Freq();
	}
	else
	{
		PCLK = MCAL_RCC_Get_PCLK1_Freq();
	}

	BRR = UART_BRR_Register(PCLK,UART_Config->BaudRate);
	USARTx->BRR = BRR ;

	// 7- Enable Interrupt
	// USART_CR1
	if(UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= UART_Config->IRQ_Enable ;
		//Enable E=interrupt on NVIC
		if (USARTx == USART1)
			NVIC_IRQ37_USART1_Enable ;
		else if (USARTx == USART2)
			NVIC_IRQ38_USART2_Enable ;
		else if (USARTx == USART3)
			NVIC_IRQ39_USART3_Enable ;
	}

}

/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_UART_DeInit
 * @brief						- DeInitialization UART (Supported feature Asynch. Only).
 * @param[in]					- USARTx: where x can be (1..3 depending on device used).
 * @retval						- NONE
 * Note							- Reset the model by RCC
 * */

void MCAL_UART_DeInit (USART_typedef* USARTx)
{
	if (USARTx == USART1)
	{
		RCC_USART1_CLK_RESET() ;
		NVIC_IRQ37_USART1_Disable ;
	}

	else if (USARTx == USART2)
	{
		RCC_USART2_CLK_RESET() ;
		NVIC_IRQ38_USART2_Disable ;
	}

	else if (USARTx == USART3)
	{
		RCC_USART3_CLK_RESET() ;
		NVIC_IRQ39_USART3_Disable ;
	}

}


/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_UART_GPIO_Set_Pins
 * @brief						- Initialization GPIO Pins for UART (Supported feature Asynch. Only).
 * @param[in]					- USARTx: where x can be (1..3 depending on device used).
 * @retval						- NONE
 * Note							- Sould Enable the corresponding AFIO & GPIO in RCC clock also called after MCAL_UART_Init()
 * */
void MCAL_UART_GPIO_Set_Pins (USART_typedef * USARTx)
{
	GPIO_PinConfig_t PINCFG ;

	if(USARTx == USART1)
	{
		//PA9  >>	TX
		//PA10 >>	RX
		//PA11 >>	CTS
		//PA12 >>	RTS

		//PA9  >>	TX
		PINCFG.GPIO_PinNumber = GPIO_PIN_9 ;
		PINCFG.GPIO_MODE =	GPIO_MODE_AF_PP ;
		PINCFG.GPIO_output_speed = GPIO_SPEED_10M ;
		MCAL_GPIO_init(GPIOA, &PINCFG);

		//PA10 >>	RX
		PINCFG.GPIO_PinNumber = GPIO_PIN_10 ;
		PINCFG.GPIO_MODE =	GPIO_MODE_AF_INPUT ;
		MCAL_GPIO_init(GPIOA, &PINCFG);

		//PA11 >>	CTS
		if(Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_CTS || Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS)
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_11 ;
			PINCFG.GPIO_MODE =	GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_init(GPIOA, &PINCFG);

		}

		//PA12 >>	RTS
		if (Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_CTS || Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS)
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_12 ;
			PINCFG.GPIO_MODE =	GPIO_MODE_AF_PP ;
			PINCFG.GPIO_output_speed = GPIO_SPEED_10M ;
			MCAL_GPIO_init(GPIOA, &PINCFG);
		}
	}
	else if(USARTx == USART2)
	{
		//PA2 >>	TX
		//PA3 >>	RX
		//PA0 >>	CTS
		//PA1 >>	RTS

		//PA2 >>	TX
		PINCFG.GPIO_PinNumber = GPIO_PIN_2 ;
		PINCFG.GPIO_MODE =	GPIO_MODE_AF_PP ;
		PINCFG.GPIO_output_speed = GPIO_SPEED_10M ;
		MCAL_GPIO_init(GPIOA, &PINCFG);

		//PA3 >>	RX
		PINCFG.GPIO_PinNumber = GPIO_PIN_3 ;
		PINCFG.GPIO_MODE =	GPIO_MODE_AF_INPUT ;
		MCAL_GPIO_init(GPIOA, &PINCFG);

		//PA0 >>	CTS
		if(Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_CTS || Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS)
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_0 ;
			PINCFG.GPIO_MODE =	GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_init(GPIOA, &PINCFG);

		}

		//PA1 >>	RTS
		if (Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_CTS || Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS)
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_1 ;
			PINCFG.GPIO_MODE =	GPIO_MODE_AF_PP ;
			PINCFG.GPIO_output_speed = GPIO_SPEED_10M ;
			MCAL_GPIO_init(GPIOA, &PINCFG);
		}
	}
	else if(USARTx == USART3)
	{
		//PB10  >>	TX
		//PB11 >>	RX
		//PB13 >>	CTS
		//PB14 >>	RTS

		//PB10  >>	TX
		PINCFG.GPIO_PinNumber = GPIO_PIN_10 ;
		PINCFG.GPIO_MODE =	GPIO_MODE_AF_PP ;
		PINCFG.GPIO_output_speed = GPIO_SPEED_10M ;
		MCAL_GPIO_init(GPIOB, &PINCFG);

		//PB11 >>	RX
		PINCFG.GPIO_PinNumber = GPIO_PIN_11 ;
		PINCFG.GPIO_MODE =	GPIO_MODE_AF_INPUT ;
		MCAL_GPIO_init(GPIOB, &PINCFG);

		//PB13 >>	CTS
		if(Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_CTS || Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS)
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_13 ;
			PINCFG.GPIO_MODE =	GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_init(GPIOB, &PINCFG);

		}

		//PB14 >>	RTS
		if (Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_RTS || Global_UART_Config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS)
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_14 ;
			PINCFG.GPIO_MODE =	GPIO_MODE_AF_PP ;
			PINCFG.GPIO_output_speed = GPIO_SPEED_10M ;
			MCAL_GPIO_init(GPIOB, &PINCFG);
		}
	}

}

/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_UART_SendData
 * @brief						- Send Buffer on UART .
 * @param[in]					- USARTx: where x can be (1..3 depending on device used).
 * @param[in]					- ptxBuffer: The Buffer of data .
 * @param[in]					- PollingEN : Enable Polling or Disable
 * @retval						- NONE
 *
 * @Note					Should initialize UART First
 *							When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
 * 							the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
 * 							because it is replaced by the parity.
 * 							When receiving with the parity enabled, the value read in the MSB bit is the received parity
 *							bit.
 * */

void MCAL_UART_SendData (USART_typedef* USARTx , uint16_t* ptxBuffer , enum Polling_mechanism PollingEN)
{
	// @ Enable Polling
	// Wait until TXE flag is set in the >> USAERx_SR
	//if this bit-7 is 1 that's mean the register is empty & can to send data.
	if (PollingEN == PO_Enable)
		while (! ((USARTx->SR) & 1<<7) );


	//Check the USART_Wordlength item for 9BIT or 8BIT in a frame
	if (Global_UART_Config->Payload == UART_Payload_length_9BIT)
	{
		USARTx->DR = (*ptxBuffer & (uint16_t) 0x01FF);
	}else
	{
		// this is 8bit data transfer
		USARTx->DR = (*ptxBuffer & (uint8_t) 0xFF);
	}

}

/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_UART_ReceiveData
 * @brief						- Receiving Data.
 * @param[in]					- USARTx: where x can be (1..3 depending on device used).
 * @param[in]					- ptxBuffer: The Buffer of data .
 * @param[in]					- PollingEN : Enable Polling or Disable
 * @retval						- NONE
 * Note							-
 * */
void MCAL_UART_ReceiveData (USART_typedef* USARTx , uint16_t* ptxBuffer , enum Polling_mechanism PollingEN)
{
	// Wait until Bit-5 RXNE flag is set in the >> USAERx_SR
	if (PollingEN == PO_Enable)
		while (! ((USARTx->SR) & 1<<5) );

	// Check the USART_Wordlength item for 9BIT or 8BIT in a frame

	if (Global_UART_Config->Payload == UART_Payload_length_9BIT)
	{
		if(Global_UART_Config->Parity == UART_Parity_NONE)
		{
			// no parity so all 9bit are considered data
			*((uint16_t*)ptxBuffer) = USARTx->DR ;
		}else{
			// Parity is used, So, 8bits will be of user data and 1 bit is parity
			*((uint16_t*)ptxBuffer) = (USARTx->DR & (uint8_t)0xFF) ;
		}

	}else
	{
		if(Global_UART_Config->Parity == UART_Parity_NONE)
		{
			// no parity so all 8bit are considered data
			*((uint16_t*)ptxBuffer) = (USARTx->DR & (uint8_t)0xFF) ;
		}else{
			// Parity is used, So, 7bits will be of user data and 1 bit is parity
			*((uint16_t*)ptxBuffer) = (USARTx->DR & (uint8_t)0x7F) ;
		}

	}

}

/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_UART_WAIT_TC
 * @brief						- Waiting until all data is transfered & TC bit is set >> USARTX_SR .
 * @param[in]					- USARTx: where x can be (1..3 depending on device used).
 * @retval						- NONE
 * Note							- NONE
 * */

void MCAL_UART_WAIT_TC (USART_typedef * USARTx)
{
	// Waiting until TC flag is set in the SR
	while (!( USARTx->SR & 1<<6 ));
}


//=======================================================
//*****************  IRQ Functions  ******************
//=======================================================


void USART1_IRQHandler (void)
{
	Global_UART1_Config->P_IRQ_CallBack();
}
void USART2_IRQHandler (void)
{
	Global_UART2_Config->P_IRQ_CallBack();
}
void USART3_IRQHandler (void)
{
	Global_UART3_Config->P_IRQ_CallBack();
}
