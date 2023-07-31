/* STM32_F103C6_SPI_Driver.h
 * Author: ENG. Ahmed Osamaa
 */


#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_

// includes

#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"

// Generic Variable

struct S_IRQ_SRC
{
	uint8_t TXE:1 ;			// TX buffer is empty interrupt
	uint8_t RXNE:1 ;		// RX buffer is not empty interrupt
	uint8_t ERRI:1 ;		// Error interrupt
	uint8_t Reserved:5 ;
};


//=======================================
// Configuration structure
//=======================================

typedef struct
{
	uint16_t Device_Mode;			// Specify Master/Slave Mode.
									// This parametar must be set based on @ref SPI_Device_Mode_define .

	uint16_t Communication_Mode;	// Specify Communication Mode will be Semplex or Half duplex or full duplex.
									// This parametar must be set based on @ref SPI_Communication_Mode_define .

	uint16_t Frame_Format;			// Specify data transmitte by LSB or MSB.
									// This parametar must be set based on @ref SPI_Frame_Format_define .

	uint16_t DataSize;				// Specify transmitted Data Size will be 8bit or 16bit.
									// This parametar must be set based on @ref SPI_DataSize_define .

	uint16_t CLKPolarity;			// Specify polarity of clock is by default High or Low .
									// This parametar must be set based on @ref SPI_CLKPolarity_define .

	uint16_t CLKPhase;				// Specify the phase of clock start sampling from (first edge) or (second edge).
									// This parametar must be set based on @ref SPI_CLKPhase_define .

	uint16_t NSS	;				// Specify wether the NSS signal is managed by (Hardware) NSS bin or (Software) using the SSI bitenable.
									// This parametar must be set based on @ref SPI_NSS_define .

	uint16_t BaudRatePS;			// Specify the baud rate prescaler value which will be used to configure the transmit and receive SCK Clock.
									// This parametar must be set based on @ref SPI_BaudRatePS_define .
									// @NOTE : The clock is derived from master, take care you have to configure RCC to enter the correct clock to (APB2 >> SPI1) or (APB1 >> SPI2)

	uint16_t IRQ_Enable;			// This parametar must be set based on @ref SPI_IRQ_Enable_define .


	void (*P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);		// Set the C Function() which be called once the IRQ Happen

}SPI_Config;


//=======================================
//Macros configuration reference
//=======================================

// @ref SPI_Device_Mode_define

#define SPI_Device_Mode_Slave			(0x00000000U)
#define SPI_Device_Mode_Master			(0x1U << 2)    // CR1.MSTR = 1 : Master configuration

// @ref SPI_Communication_Mode_define

#define SPI_Communication_Direction_2Line			(0x00000000U)
#define SPI_Communication_Direction_2Line_RXonly	(0x1U<<10)		//CR1. Bit 10 RXONLY : Receive only
#define SPI_Communication_Direction_1Line_RXonly	(0x1U << 15)	//CR1. Bit 15  BIDIMODE : Bidirectional data mode enable
#define SPI_Communication_Direction_1Line_TXonly	((0x1U<<15) | (0x1U<<14))		//CR1. Bit 15  BIDIMODE : Bidirectional data mode enable & CR1. Bit 14 BIDIOE : Ouput enable in bidirectional mode

// @ref SPI_Frame_Format_define

#define SPI_Frame_Format_MSB_Transmitted_First			(0x00000000U)
#define SPI_Frame_Format_LSB_Transmitted_First				(0x1U<<7)				//CR1. Bit 7 LSBFIRST : Data frame format

// @ref SPI_DataSize_define

#define SPI_DataSize_8BIT				(0x00000000U)
#define SPI_DataSize_16BIT				(0x1U<<11)				//CR1. Bit 11 DFF: Data Size

// @ref SPI_CLKPolarity_define

#define SPI_CLKPolarity_Low_when_IDLE		(0x00000000U)
#define SPI_CLKPolarity_High_when_IDLE		(0x1U<<1)			//CR1. Bit 1 CPOL : Clock Polarity

// @ref SPI_CLKPhase_define

#define SPI_CLKPhase_1EDGE_first_data_capture_edge			(0x00000000U)
#define SPI_CLKPhase_2EDGE_first_data_capture_edge			(0x1U<<0)		// CR1. Bit 0 CPHA : Clock phase
//========================================================
/* @ref SPI_NSS SPI Slave Select Managment
 *
 * Hardware Or Software
 */
// HardWare
#define SPI_NSS_Hard_Slave							(0x00000000U)
#define SPI_NSS_Hard_Master_SS_output_Enable		(0x1U<<2)				//CR2. Bit 2 SSOE = 1 : SS output Enable
#define SPI_NSS_Hard_Master_SS_output_Disable		(0x00000000U)				//CR2. Bit 2 SSOE = 0 : SS output Disable


//NSS is deriven by Software (Master or Slave)

#define SPI_NSS_SW_NSSInternalSoft_Reset	(0x1U<<9)							//CR2. Bit 9 SSM : SW SS Enable
#define SPI_NSS_SW_NSSInternalSoft_set		((0x1U<<9) | (0x1U<<8))				//CR2. Bit 9 SSM : SW SS Enable & CR2. Bit 8 SSI : internal SS (1) is set (0) is Reset

//========================================================

//@ref SPI_BaudRatePS_define

#define SPI_BaudRatePS_2					(0x00000000U)
#define SPI_BaudRatePS_4					(0b001U << 3)
#define SPI_BaudRatePS_8					(0b010U << 3)
#define SPI_BaudRatePS_16					(0b011U << 3)
#define SPI_BaudRatePS_32					(0b100U << 3)
#define SPI_BaudRatePS_64					(0b101U << 3)
#define SPI_BaudRatePS_128					(0b110U << 3)
#define SPI_BaudRatePS_256					(0b111U << 3)

//@ref SPI_IRQ_Enable_define

#define SPI_IRQ_Enable_NONE					(0x00000000U)
#define SPI_IRQ_Enable_TXEIE				(uint32_t)(1<<7)
#define SPI_IRQ_Enable_RXNEIE				(uint32_t)(1<<6)
#define SPI_IRQ_Enable_ERRIE				(uint32_t)(1<<5)


enum Pollingmechanism
{
	POLLingEnable,
	POLLingDisable
};



//=======================================
//***************  APIs  ****************
//=======================================


void MCAL_SPI_Init(SPI_typedef* SPIx, SPI_Config* SPI_Config);
void MCAL_SPI_DeInit(SPI_typedef* SPIx);

void MCAL_SPI_GPIO_Set_Pins (SPI_typedef* SPIx);

void MCAL_SPI_SendData (SPI_typedef* SPIx , uint16_t* pTXBuffer, enum Pollingmechanism PollingEn);
void MCAL_SPI_ReceiveData (SPI_typedef* SPIx, uint16_t* pRXBuffer , enum Pollingmechanism PollingEn);
void MCAL_SPI_TX_RX (SPI_typedef* SPIx, uint16_t* pTRXBuffer , enum Pollingmechanism PollingEn);




#endif /* INC_STM32_F103C6_SPI_DRIVER_H_ */
