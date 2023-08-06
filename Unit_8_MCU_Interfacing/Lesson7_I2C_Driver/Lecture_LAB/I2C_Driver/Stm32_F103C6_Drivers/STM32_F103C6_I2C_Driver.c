/* STM32_F103C6_I2C_Driver.c
 * Author: ENG. Ahmed Osamaa
 */


//=======================================================
//*********************  Includes  **********************
//=======================================================

#include "STM32_F103C6_I2C_Driver.h"


//=======================================================
//*****************  Generic Macros  ******************
//=======================================================

#define I2C1_INDEX					0
#define I2C2_INDEX					1


//=======================================================
//*****************  Generic Variable  ******************
//=======================================================

I2C_Config Global_I2C_Config[2] = {0} ;

//=======================================================
//*****************  Generic Function  ******************
//=======================================================

void I2C_GenerateSTART (I2C_typedef* I2Cx , FunctionalState NewState , Repeated_Start Start)
{
	if(Start != REPEATED_START)
	{
		// Check if the bus is idle
		while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	}
	/*
	 * I2C_CR1 >> Bit 8 START: Start generation
		This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
		In Master Mode:
		0: No Start generation
		1: Repeated start generation
		In Slave mode:
		0: No Start generation
		1: Start generation when the bus is free
	 */
	if(NewState != DISABLE)
	{
		I2Cx->CR1 |= I2C_CR1_START ;
	}else
	{
		I2Cx->CR1 &= ~(I2C_CR1_START) ;
	}

}

/* •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• */

FlagStatus I2C_GetFlagStatus (I2C_typedef* I2Cx , Status Flag)
{
	FlagStatus bitstatus = RESET ;
	uint32_t flag1 = 0 , flag2 = 0 , lastevent=0 ;
	switch (Flag)
	{
	case I2C_FLAG_BUSY:
		/*I2C_SR2 >> Bit 1 BUSY: Bus busy
			0: No communication on the bus
			1: Communication ongoing on the bus
			– Set by hardware on detection of SDA or SCL low
			– cleared by hardware on detection of a Stop condition*/
		if(I2Cx->SR2 & I2C_SR2_BUSY)
			bitstatus = SET ;
		else
			bitstatus = RESET ;
		break ;
	case EV5:
		// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
		/*  Bit 0 SB: Start bit (Master mode)
			0: No Start condition
			1: Start condition generated.
			– Set when a Start condition generated.
			– Cleared by software by reading the SR1 register followed by writing the DR register, or by
			hardware when PE=0
		 */
		if(I2Cx->SR1 & I2C_SR1_SB)
			bitstatus = SET ;
		else
			bitstatus = RESET ;
		break ;
	case EV6:
		// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
		/*Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
			This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
			when PE=0.
			Address matched (Slave)
			0: Address mismatched or not received.
			1: Received address matched.*/
		if(I2Cx->SR1 & I2C_SR1_ADDR)
			bitstatus = SET ;
		else
			bitstatus = RESET ;
		break ;
	case EV8_1:
	case EV8:
		// EV8: TxE=1, shift register not empty, d. ata register empty, cleared by writing DR registe
		if(I2Cx->SR1 & I2C_SR1_TXE)
			bitstatus = SET ;
		else
			bitstatus = RESET ;
		break ;
	case EV7 :
		// RxNE=1 Cleared by reading DR register
		if(I2Cx->SR1 & I2C_SR1_RXNE)
			bitstatus = SET ;
		else
			bitstatus = RESET ;
		break ;
	case MASTER_BYTE_TRANSMITTING :
		// Checking on " TRA , BUSY , MSL , TXE flags "
		flag1 = I2Cx->SR1 ;
		flag2 = I2Cx->SR2 ;
		flag2 = flag2 << 16 ;
		lastevent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);

		if ((lastevent & Flag ) == Flag)
			bitstatus = SET ;
		else
			bitstatus = RESET ;
		break ;

	}
	return bitstatus ;
}

/* •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• */

void I2C_SendAddress (I2C_typedef* I2Cx , uint8_t Address ,  I2C_Direction Direction )
{
	uint8_t index = I2Cx == I2C1 ? I2C1_INDEX :  I2C2_INDEX ;

	if ((Global_I2C_Config[index].I2C_Slave_Device_Address.I2C_Addressing_Slave_Mode) == I2C_Addressing_Slave_Mode_7BIT)
	{
		Address = Address << 1 ;

		if(Direction != I2C_Direction_Transmitter)
		{
			Address |= 1<<0 ;
		}else{
			Address &= ~(1<<0) ;
		}

		I2Cx->DR = Address ;

	}else{
		// not supported
	}
}

/* •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• */


void I2C_GenerateStop (I2C_typedef* I2Cx , FunctionalState NewState)
{
	if (NewState != DISABLE)
		I2Cx->CR1 |= I2C_CR1_STOP;
	else
		I2Cx->CR1 &= ~(I2C_CR1_STOP) ;
}

/* •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• */


void I2C_AcknowledgeConfig(I2C_typedef* I2Cx , FunctionalState NewState)
{
	if (NewState != DISABLE)
		I2Cx->CR1 |= I2C_CR1_ACK;
	else
		I2Cx->CR1 &= ~(I2C_CR1_ACK) ;
}



//=======================================================
//***************  APIs Impelementation  ****************
//=======================================================


/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_I2C_Init
 * @brief						- Initialization I2C according to the specific parameter.
 * @param[in]					- I2Cx: where x can be (1..3 depending on device used).
 * @param[in]					- I2C_CONGIG : ALL I2C Configuration
 * @retval						- NONE
 * Note							- Support only I2C Standard Mode Master Polling mechanism
 *
 * */


void MCAL_I2C_Init(I2C_typedef* I2Cx , I2C_Config * I2C_CONFIG)
{
	uint16_t tmpreg = 0 , freqrange = 0 , result = 0 ;
	uint32_t PCLK1 = 8000000 ;
	// Enable RCC Clock
	if (I2Cx == I2C1)
	{
		Global_I2C_Config[I2C1_INDEX] = *I2C_CONFIG ;
		RCC_I2C1_CLK_EN() ;

	}else if (I2Cx == I2C2)
	{
		Global_I2C_Config[I2C2_INDEX] = *I2C_CONFIG ;
		RCC_I2C2_CLK_EN() ;
	}

	// Check Mode
	if(I2C_CONFIG->Mode == I2C_Mode_I2C)
	{
		/* *************** *************** INIT Timing **************** ***************** */
		//• I2C_CR2 FREQ[5:0]: Peripheral clock frequency
		// Get the I2Cx CR2 Value
		tmpreg = I2Cx->CR2 ;
		// Clear FREQ[5:0] bits
		tmpreg &= ~(I2C_CR2_FREQ) ;
		// Get PCLK1 Freq
		PCLK1 = MCAL_RCC_Get_PCLK1_Freq();
		freqrange = (uint16_t) ((PCLK1)/1000000) ;

		tmpreg |= freqrange ;
		// Write to I2Cx_CR2
		I2Cx->CR2 = tmpreg ;

		// Configure the clock control register (I2C_CCR)
		I2Cx->CR1 &= ~(I2C_CR1_PE) ;

		tmpreg = 0 ;

		// SM

		if (I2C_CONFIG->ClockSpeed == I2C_SCLK_SM_50K || I2C_CONFIG->ClockSpeed == I2C_SCLK_SM_100K )
		{
			// Standard Mode Calculation

			/* Th 	  = CCR * Tpclk1
			 * Tclk/2 = CCR * Tpclk1
			 * CCR    = Tclk   /(2*Tpclk1)
			 * CCR    = Fpclk1 /(2*Fclk)   */

			result = (uint16_t)( PCLK1 / (I2C_CONFIG->ClockSpeed << 1 ) ) ;

			tmpreg |= result ;
			// Write to I2Cx_CCR
			I2Cx->CCR = tmpreg ;

			/* *************** *************** RISE Timing **************** ***************** */

			I2Cx->TRISE = freqrange + 1 ;

		}else{

			// Fast Mode not supported yet
		}

		/* *************** *************** CR1 **************** ***************** */

		tmpreg = I2Cx->CR1 ;

		tmpreg |= (uint16_t)(I2C_CONFIG->ACK_Control) | (I2C_CONFIG->Mode) | (I2C_CONFIG->StretchMode) ;
		// Write to I2Cx_CR1
		I2Cx->CR1 = tmpreg ;

		/* *************** *************** OAR1 & OAR2 **************** ***************** */

		tmpreg = 0 ;

		if (I2C_CONFIG->I2C_Slave_Device_Address.Duel_ADD == 1)
		{
			tmpreg = I2C_OAR2_ENDUAL ;
			tmpreg |= (I2C_CONFIG->I2C_Slave_Device_Address.Secondary_slave_address << I2C_OAR2_ADD2_Pos);
			I2Cx->OAR2 = tmpreg ;
		}

		tmpreg = 0 ;
		tmpreg |= (I2C_CONFIG->I2C_Slave_Device_Address.Primary_slave_address << 1) ;
		tmpreg |= (I2C_CONFIG->I2C_Slave_Device_Address.I2C_Addressing_Slave_Mode) ;
		I2Cx->OAR1 = tmpreg ;


	}else{
		// SMBus Not Supported
	}

	// Interrupt slave mode // Check callback interrupt pointer function != NULL
	if(I2C_CONFIG->P_Slave_Event_CallBack != NULL)
	{
		// Enable interrupt
		I2Cx->CR2 |= I2C_CR2_ITBUFEN ;
		I2Cx->CR2 |= I2C_CR2_ITERREN ;
		I2Cx->CR2 |= I2C_CR2_ITEVTEN ;
		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable ;
			NVIC_IRQ32_I2C1_ER_Enable ;
		}else if (I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable ;
			NVIC_IRQ34_I2C2_ER_Enable ;
		}

		I2Cx->SR1 = 0 ;
		I2Cx->SR2 = 0 ;

	}

	/* Enable the selected I2C Peripheral */
	I2Cx->CR1 |= I2C_CR1_PE ;
}



/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_I2C_DeInit
 * @brief						- DeInitialization I2C according to the specific parameter.
 * @param[in]					- I2Cx: where x can be (1..3 depending on device used).
 * @retval						- NONE
 * Note							- NONE
 *
 * */


void MCAL_I2C_DeInit(I2C_typedef* I2Cx)
{
	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable ;
		NVIC_IRQ32_I2C1_ER_Disable ;
		RCC_I2C1_CLK_RESET() ;
	}else if (I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_Disable ;
		NVIC_IRQ34_I2C2_ER_Disable ;
		RCC_I2C2_CLK_RESET() ;
	}
}


/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_I2C_GPIO_Set_Pins
 * @brief						- set_I2C_GPIO_Pins configuration.
 * @param[in]					- I2Cx: where x can be (1..3 depending on device used).
 * @retval						- NONE
 * Note							- NONE
 *
 * */


void MCAL_I2C_GPIO_Set_Pins (I2C_typedef* I2Cx)
{
	GPIO_PinConfig_t PINCNF ;
	if(I2Cx == I2C1)
	{
		// PB6 : I2C1_SCL
		// PB7 : I2C1_SDA

		// PB6 : I2C1_SCL
		PINCNF.GPIO_PinNumber 	 = GPIO_PIN_6 ;
		PINCNF.GPIO_MODE 		 = GPIO_MODE_AF_OD ;
		PINCNF.GPIO_output_speed = GPIO_SPEED_10M ;
		MCAL_GPIO_init(GPIOB, &PINCNF) ;


		// PB7 : I2C1_SDA
		PINCNF.GPIO_PinNumber 	 = GPIO_PIN_7 ;
		PINCNF.GPIO_MODE 		 = GPIO_MODE_AF_OD ;
		PINCNF.GPIO_output_speed = GPIO_SPEED_10M ;
		MCAL_GPIO_init(GPIOB, &PINCNF) ;

	}else if (I2Cx == I2C2)
	{
		// PB10 : I2C2_SCL
		// PB11 : I2C2_SDA

		// PB10 : I2C2_SCL
		PINCNF.GPIO_PinNumber 	 = GPIO_PIN_10 ;
		PINCNF.GPIO_MODE 		 = GPIO_MODE_AF_OD ;
		PINCNF.GPIO_output_speed = GPIO_SPEED_10M ;
		MCAL_GPIO_init(GPIOB, &PINCNF) ;


		// PB11 : I2C2_SDA
		PINCNF.GPIO_PinNumber 	 = GPIO_PIN_11 ;
		PINCNF.GPIO_MODE 		 = GPIO_MODE_AF_OD ;
		PINCNF.GPIO_output_speed = GPIO_SPEED_10M ;
		MCAL_GPIO_init(GPIOB, &PINCNF) ;
	}

}


// Master Polling Mechanism

/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_I2C_Master_TX
 * @brief						- Master Transmite data to Spacific Device .
 * @param[in]					- I2Cx:	 	where x can be (1..3 depending on device used).
 * @param[in]					- dataOut: 	Pointer to array of data that will be sent.
 * @param[in]					- dataLen:	length of Array of data .
 * @param[in]					- Stop:		Choose using Stop condition or not .
 * @param[in]					- Start: 	Specify Start signal is a Start or a repeated start.
 * @retval						- NONE
 * Note							- NONE
 * */

void MCAL_I2C_Master_TX (I2C_typedef* I2Cx , uint16_t devAddr , uint8_t* dataOut , uint32_t dataLen , Stop_Condition Stop , Repeated_Start Start)
{
	uint32_t i ;
	// 1- Set the start bit  in the I2C1 register to generate Start condition
	I2C_GenerateSTART(I2Cx , ENABLE , Start );
	// 2- Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!I2C_GetFlagStatus(I2Cx, EV5));
	// 3- Send Address
	I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Transmitter) ;
	// 4- Wait for EV6
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while(!I2C_GetFlagStatus(I2Cx, EV6));
	// 5- Checking on " TRA , BUSY , MSL , TXE flags "
	while(!I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING));
	// 6- Send data
	for (i = 0 ; i < dataLen ; i++)
	{
		I2Cx->DR = dataOut[i] ;
		// Wait for EV8
		while(!I2C_GetFlagStatus(I2Cx, EV8));

	}

	// 7- Stop Condition
	if (Stop == With_Stop)
	{
		I2C_GenerateStop(I2Cx , ENABLE) ;
	}

}

/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_I2C_Master_RX
 * @brief						- Master receive data from Spacific Device .
 * @param[in]					- I2Cx: 	where x can be (1..3 depending on device used).
 * @param[in]					- dataIN: 	Pointer to array of data that will be receive.
 * @param[in]					- dataLen:  length of Array of data .
 * @param[in]					- Stop: 	Choose using Stop condition or not .
 * @param[in]					- Start:	Specify Start signal is a Start or a repeated start.
 * @retval						- NONE
 * Note							- NONE
 * */

void MCAL_I2C_Master_RX (I2C_typedef* I2Cx , uint16_t devAddr , uint8_t* dataIN , uint32_t dataLen , Stop_Condition Stop , Repeated_Start Start)
{
	uint32_t i ;
	uint8_t index = I2Cx == I2C1 ? I2C1_INDEX :  I2C2_INDEX ;
	// 1- Set the start bit  in the I2C1 register to generate Start condition
	I2C_GenerateSTART(I2Cx , ENABLE , Start );
	// 2- Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!I2C_GetFlagStatus(I2Cx, EV5));
	// 3- Send Address
	I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Receiver) ;
	// 4- Wait for EV6
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while(!I2C_GetFlagStatus(I2Cx, EV6));
	// 5- Receive

	I2C_AcknowledgeConfig(I2Cx , ENABLE);

	if(dataLen)
	{
		// Read until become zero
		for (i=dataLen ; i > 1 ; i--)
		{
			// Checking RXNE become 1
			while(!I2C_GetFlagStatus(I2Cx, EV7));
			// Read data from DR
			*dataIN = I2Cx->DR ;
			dataIN++ ;
		}

		I2C_AcknowledgeConfig(I2Cx , DISABLE);

	}
	// 6- Stop Condition
	if (Stop == With_Stop)
	{
		I2C_GenerateStop(I2Cx , ENABLE) ;
	}

	if (Global_I2C_Config[index].ACK_Control == I2C_ACK_Enable)
		I2C_AcknowledgeConfig(I2Cx, ENABLE);

}

// Slave Interrupt Mechanism


void MCAL_I2C_Slave_TX (I2C_typedef* I2Cx , uint8_t data)
{
	I2Cx->DR = data ;
}
uint8_t MCAL_I2C_Slave_RX (I2C_typedef* I2Cx)
{
	return (uint8_t) I2Cx->DR ;
}


//=======================================================
//*****************  		IRQ		  ******************
//=======================================================



void I2C1_EV_IRQHandler()
{


}
void I2C1_ER_IRQHandler()
{

}
void I2C2_EV_IRQHandler()
{


}
void I2C2_ER_IRQHandler ()
{


}



