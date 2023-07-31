/* STM32_F103C6_SPI_Driver.c
 * Author: ENG. Ahmed Osamaa
 */


//=======================================================
//*********************  Includes  **********************
//=======================================================

#include "STM32_F103C6_SPI_Driver.h"

//=======================================================
//*****************  Generic Variable  ******************
//=======================================================

SPI_Config* Global_SPI_Config[2] = {NULL , NULL};

//=======================================================
//*****************  Generic Function  ******************
//=======================================================

//=======================================================
//*****************  Generic Macros  ******************
//=======================================================

#define SPI1_index				0
#define SPI2_index				1

#define SPI_SR_TXE				((uint8_t)0x02)				// Transmit Buffer is Empty
#define SPI_SR_RXNE				((uint8_t)0x01)				// Receive Buffer is not Empty

//=======================================================
//***************  APIs Impelementation  ****************
//=======================================================


/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_SPI_Init
 * @brief						- Initialization SPI according to the specific parameter.
 * @param[in]					- SPIx: where x can be (1..3 depending on device used).
 * @param[in]					- SPI_Config : ALL SPI Configuration
 * @retval						- NONE
 * Note							- Support For SPI Full Duplex Master/Slave only & NSS HW/SW
 * 								- In case of master you have to configure SS pin and drive it.
 * */

void MCAL_SPI_Init(SPI_typedef* SPIx, SPI_Config* SPI_Config)
{
	// Safty for register
	uint16_t tmpreg_CR1 = 0 ;
	uint16_t tmpreg_CR2 = 0 ;


	//SPI1
	if (SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_index] = SPI_Config ;
		RCC_SPI1_CLK_EN();

	}else if(SPIx == SPI2) // SPI2
	{
		Global_SPI_Config[SPI2_index] = SPI_Config ;
		RCC_SPI2_CLK_EN();
	}

	// Enable SPI	CR1. Bit 6 SPE : SPI Enable

	tmpreg_CR1 = (0x1U<<6) ;

	// Master or Slave
	tmpreg_CR1 |= SPI_Config->Device_Mode ;

	// SPI Communication Mode
	tmpreg_CR1 |= SPI_Config->Communication_Mode ;

	// SPI Frame Format
	tmpreg_CR1 |= SPI_Config->Frame_Format ;

	// SPI Data Size
	tmpreg_CR1 |= SPI_Config->DataSize ;

	// SPI Clock Polarity
	tmpreg_CR1 |= SPI_Config->CLKPolarity ;

	// SPI Clock Phase
	tmpreg_CR1 |= SPI_Config->CLKPhase ;

	//====================   NSS   =====================

	if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_Enable)
	{
		tmpreg_CR2 |= SPI_Config->NSS ;
	}else if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_Disable)
	{
		tmpreg_CR2 &= ~ SPI_NSS_Hard_Master_SS_output_Enable ;
	}else
	{
		tmpreg_CR1 |= SPI_Config->NSS ;
	}

	//======================================================

	// SPI Baud Rate PS
	tmpreg_CR1 |= SPI_Config->BaudRatePS ;

	//Interrupt Enable

	if (SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		tmpreg_CR2 |= SPI_Config->IRQ_Enable ;

		if (SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable;

		}else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable;
		}
	}

	SPIx->CR1 = tmpreg_CR1 ;
	SPIx->CR2 = tmpreg_CR2 ;

}



/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_SPI_DeInit
 * @brief						- DeInitialization and Reset SPI and its Register.
 * @param[in]					- SPIx: where x can be (1..3 depending on device used).
 * @retval						- NONE
 * Note							- NONE
 * */


void MCAL_SPI_DeInit(SPI_typedef* SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_CLK_RESET();

	}else if (SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_CLK_RESET();
	}
}


/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_SPI_GPIO_Set_Pins
 * @brief						- Initialization GPIO pins for spacific SPI.
 * @param[in]					- SPIx: where x can be (1..3 depending on device used).
 * @retval						- NONE
 * Note							- NONE
 * */


void MCAL_SPI_GPIO_Set_Pins (SPI_typedef* SPIx)
{
	GPIO_PinConfig_t PINCfg ;

	if(SPIx == SPI1)
	{
		//	PA4 : SPI1_NSS
		//	PA5 : SPI1_SCK
		//	PA6 : SPI1_MISO
		//	PA7 : SPI1_MOSI

		if(Global_SPI_Config[SPI1_index]->Device_Mode == SPI_Device_Mode_Master)
		{
			//	PA4 : SPI1_NSS
			switch (Global_SPI_Config[SPI1_index]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_Disable :
				// HW Master/slave Input floating
				PINCfg.GPIO_PinNumber = GPIO_PIN_4 ;
				PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_init(GPIOA , &PINCfg);
				break;

			case SPI_NSS_Hard_Master_SS_output_Enable :
				//HW Master output enable alternate function push-pull
				PINCfg.GPIO_PinNumber = GPIO_PIN_4 ;
				PINCfg.GPIO_MODE = GPIO_MODE_AF_PP ;
				PINCfg.GPIO_output_speed = GPIO_SPEED_10M ;
				MCAL_GPIO_init(GPIOA, &PINCfg) ;
				break;
			}

			//	PA5 : SPI1_SCK
			// Master Alternative function push-pull
			PINCfg.GPIO_PinNumber = GPIO_PIN_5 ;
			PINCfg.GPIO_MODE = GPIO_MODE_AF_PP ;
			PINCfg.GPIO_output_speed = GPIO_SPEED_10M ;
			MCAL_GPIO_init(GPIOA, &PINCfg) ;

			//	PA6 : SPI1_MISO
			// Full Duplex master | input floating
			PINCfg.GPIO_PinNumber = GPIO_PIN_6 ;
			PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_init(GPIOA, &PINCfg) ;

			//	PA7 : SPI1_MOSI
			//  Full Duplex master | Alternative function push-pull
			PINCfg.GPIO_PinNumber = GPIO_PIN_7 ;
			PINCfg.GPIO_MODE = GPIO_MODE_AF_PP ;
			PINCfg.GPIO_output_speed = GPIO_SPEED_10M ;
			MCAL_GPIO_init(GPIOA, &PINCfg) ;

		}else
		{
			//	PA4 : SPI1_NSS
			if (Global_SPI_Config[SPI1_index]->NSS == SPI_NSS_Hard_Slave)
			{
				// HW Master/slave Input floating
				PINCfg.GPIO_PinNumber = GPIO_PIN_4 ;
				PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_init(GPIOA , &PINCfg);

			}

			//	PA5 : SPI1_SCK
			// Slave Input floating
			PINCfg.GPIO_PinNumber = GPIO_PIN_5 ;
			PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_init(GPIOA , &PINCfg);

			//	PA6 : SPI1_MISO
			// Full Duplex  slave (point to point) | Alternate function push-pull
			PINCfg.GPIO_PinNumber = GPIO_PIN_6 ;
			PINCfg.GPIO_MODE = GPIO_MODE_AF_PP ;
			PINCfg.GPIO_output_speed = GPIO_SPEED_10M ;
			MCAL_GPIO_init(GPIOA, &PINCfg) ;

			//	PA7 : SPI1_MOSI
			//  Full Duplex master | Alternative function push-pull
			// Slave Input floating
			PINCfg.GPIO_PinNumber = GPIO_PIN_7 ;
			PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_init(GPIOA , &PINCfg);

		}

	}else if (SPIx == SPI2)
	{
		//	PB12 : SPI2_NSS
		//	PB13 : SPI2_SCK
		//	PB14 : SPI2_MISO
		//	PB15 : SPI2_MOSI

		if(Global_SPI_Config[SPI2_index]->Device_Mode == SPI_Device_Mode_Master)
		{
			//	PB12 : SPI2_NSS
			switch (Global_SPI_Config[SPI2_index]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_Disable :
				// HW Master/slave Input floating
				PINCfg.GPIO_PinNumber = GPIO_PIN_12 ;
				PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_init(GPIOB , &PINCfg);
				break;

			case SPI_NSS_Hard_Master_SS_output_Enable :
				//HW Master output enable alternate function push-pull
				PINCfg.GPIO_PinNumber = GPIO_PIN_12 ;
				PINCfg.GPIO_MODE = GPIO_MODE_AF_PP ;
				PINCfg.GPIO_output_speed = GPIO_SPEED_10M ;
				MCAL_GPIO_init(GPIOB, &PINCfg) ;
				break;
			}

			//	PB13 : SPI2_SCK
			// Master Alternative function push-pull
			PINCfg.GPIO_PinNumber = GPIO_PIN_13 ;
			PINCfg.GPIO_MODE = GPIO_MODE_AF_PP ;
			PINCfg.GPIO_output_speed = GPIO_SPEED_10M ;
			MCAL_GPIO_init(GPIOB, &PINCfg) ;

			//	PB14 : SPI2_MISO
			// Full Duplex master | input floating
			PINCfg.GPIO_PinNumber = GPIO_PIN_14 ;
			PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_init(GPIOB, &PINCfg) ;

			//	PB15 : SPI1_MOSI
			//  Full Duplex master | Alternative function push-pull
			PINCfg.GPIO_PinNumber = GPIO_PIN_15 ;
			PINCfg.GPIO_MODE = GPIO_MODE_AF_PP ;
			PINCfg.GPIO_output_speed = GPIO_SPEED_10M ;
			MCAL_GPIO_init(GPIOB, &PINCfg) ;

		}else
		{
			//	PB12 : SPI2_NSS
			if (Global_SPI_Config[SPI2_index]->NSS == SPI_NSS_Hard_Slave)
			{
				// HW Master/slave Input floating
				PINCfg.GPIO_PinNumber = GPIO_PIN_12 ;
				PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_init(GPIOB , &PINCfg);

			}

			//	PB13 : SPI2_SCK
			// Slave Input floating
			PINCfg.GPIO_PinNumber = GPIO_PIN_13 ;
			PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_init(GPIOB , &PINCfg);

			//	PB14 : SPI2_MISO
			// Full Duplex  slave (point to point) | Alternate function push-pull
			PINCfg.GPIO_PinNumber = GPIO_PIN_14 ;
			PINCfg.GPIO_MODE = GPIO_MODE_AF_PP ;
			PINCfg.GPIO_output_speed = GPIO_SPEED_10M ;
			MCAL_GPIO_init(GPIOB, &PINCfg) ;

			//	PB15 : SPI2_MOSI
			//  Full Duplex master | Alternative function push-pull
			// Slave Input floating
			PINCfg.GPIO_PinNumber = GPIO_PIN_15 ;
			PINCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_init(GPIOB , &PINCfg);

		}
	}
}

/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_SPI_SendData
 * @brief						- Transmit data with or without polling mechanism.
 * @param[in]					- SPIx: where x can be (1..3 depending on device used).
 * @param[in]					- pTXBuffer: Pointer to the data is wanted to be sent .
 * @param[in]					- PollingEn: Specify using polling mecanism or not .
 * @retval						- NONE
 * Note							- NONE
 * */

void MCAL_SPI_SendData (SPI_typedef* SPIx , uint16_t* pTXBuffer, enum Pollingmechanism PollingEn)
{

	if(PollingEn == POLLingEnable)
		while (!(SPIx->SR & SPI_SR_TXE));


	SPIx->DR = *pTXBuffer ;


}


/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_SPI_ReceiveData
 * @brief						- Receive data with or without polling mechanism.
 * @param[in]					- SPIx: where x can be (1..3 depending on device used).
 * @param[in]					- pRXBuffer: Pointer to the data is wanted to be Received .
 * @param[in]					- PollingEn: Specify using polling mecanism or not .
 * @retval						- NONE
 * Note							- NONE
 * */


void MCAL_SPI_ReceiveData (SPI_typedef* SPIx, uint16_t* pRXBuffer , enum Pollingmechanism PollingEn)
{
	if(PollingEn == POLLingEnable)
		while (!(SPIx->SR & SPI_SR_RXNE));

	*pRXBuffer = SPIx->DR ;


}

/*••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 * @Fn							- MCAL_SPI_TX_RX
 * @brief						- Send or Receive data with or without polling mechanism.
 * @param[in]					- SPIx: where x can be (1..3 depending on device used).
 * @param[in]					- pTRXBuffer: Pointer to the data is wanted to be Sent Then Received .
 * @param[in]					- PollingEn: Specify using polling mecanism or not .
 * @retval						- NONE
 * Note							- NONE
 * */

void MCAL_SPI_TX_RX (SPI_typedef* SPIx, uint16_t* pTRXBuffer , enum Pollingmechanism PollingEn)
{
	if(PollingEn == POLLingEnable)
		while (!(SPIx->SR & SPI_SR_TXE));
	SPIx->DR = *pTRXBuffer ;

	if(PollingEn == POLLingEnable)
		while (!(SPIx->SR & SPI_SR_RXNE));
	*pTRXBuffer = SPIx->DR ;


}




//=======================================================
//*****************  		IRQ		  ******************
//=======================================================


void SPI1_IRQHandler (void)
{
	struct S_IRQ_SRC irq_src ;

	irq_src.TXE  = ((SPI1->SR & (1<<1)) >> 1);
	irq_src.RXNE = ((SPI1->SR & (1<<0)) >> 0);
	irq_src.ERRI = ((SPI1->SR & (1<<4)) >> 4);

	Global_SPI_Config[SPI1_index]->P_IRQ_CallBack(irq_src);

}


void SPI2_IRQHandler (void)
{
	struct S_IRQ_SRC irq_src ;

		irq_src.TXE  = ((SPI2->SR & (1<<1)) >> 1);
		irq_src.RXNE = ((SPI2->SR & (1<<0)) >> 0);
		irq_src.ERRI = ((SPI2->SR & (1<<4)) >> 4);

		Global_SPI_Config[SPI2_index]->P_IRQ_CallBack(irq_src);
}
