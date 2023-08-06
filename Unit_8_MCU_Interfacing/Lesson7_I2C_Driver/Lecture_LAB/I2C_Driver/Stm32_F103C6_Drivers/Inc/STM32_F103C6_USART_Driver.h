/* STM32_F103C6_USART_Driver.h
 * Author: ENG. Ahmed Osamaa
 */

#ifndef STM32_F103C6_USART_DRIVER_H_
#define STM32_F103C6_USART_DRIVER_H_

// includes

#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_RCC_Driver.h"

//=======================================
// Configuration structure
//=======================================

typedef struct
{
	uint8_t		USART_Mode ;		// Specify TX/RX Enable/Disable.
									// This parametar must be set based on @ref UART_Mode_define.
	uint32_t	BaudRate ;			// Specify BaudRate.
									// This parametar must be set based on @ref UART_BaudRate_define.
	uint8_t		Payload ;			// Specify the number of data bits transmitted or received in a frame.
									// This parametar must be set based on @ref UART_Payload_length_define.
	uint32_t	Parity ;			// Specify the Parity mode.
									// This parametar must be set based on @ref UART_Parity_define.
	uint8_t		StopBits ;			// Specify the number of stop bits.
									// This parametar must be set based on @ref UART_StopBits_define.
	uint8_t		HWFlowCtl ;			// Specify the Hardware flow control mode is Enble or Disable.
									// This parametar must be set based on @ref UART_HWFlowCtl_define.
	uint8_t		IRQ_Enable ;		// Enable or Disable UART IRQ TX/RX.
									// @ref UART_IRQ_Enable_define , you can select two or three parameters EX: UART_IRQ_Enable_TXE  | UART_IRQ_Enable_TC .

	void (*P_IRQ_CallBack)(void);	// Set the C Function() which be called once the IRQ Happen
}UART_Config;


//=======================================
//Macros configuration reference
//=======================================

// @ref UART_Mode_define

#define UART_Mode_RX			(uint32_t)(1<<2)
#define UART_Mode_TX			(uint32_t)(1<<3)
#define UART_Mode_TX_RX			((uint32_t)(1<<2 | 1<<3))

// @ref UART_BaudRate_define

#define UART_BaudRate_2400			2400
#define UART_BaudRate_9600			9600
#define UART_BaudRate_19200			19200
#define UART_BaudRate_57600			57600
#define UART_BaudRate_115200		115200
#define UART_BaudRate_230400		230400
#define UART_BaudRate_460800		430800
#define UART_BaudRate_921600		921600
#define UART_BaudRate_2250000		2250000
#define UART_BaudRate_4500000		4500000

// @ref UART_Payload_length_define

#define UART_Payload_length_8BIT	(uint32_t)(0)
#define UART_Payload_length_9BIT	(uint32_t)(1<<12)

// @ref UART_Parity_define

#define UART_Parity_NONE			(uint32_t)(0)
#define UART_Parity_EVEN			(uint32_t)(1<<10)
#define UART_Parity_ODD				(uint32_t)(1<<9 | 1<<10)

// @ref UART_StopBits_define.

#define UART_StopBits_half			(uint32_t)(1<<12)
#define UART_StopBits_1				(uint32_t)(0)
#define UART_StopBits_1_half		(uint32_t)(3<<12)
#define UART_StopBits_2				(uint32_t)(2<<12)

// @ref UART_HWFlowCtl_define

#define UART_HWFlowCtl_NONE			(uint32_t)(0)
#define UART_HWFlowCtl_RTS			(uint32_t)(1<<8)
#define UART_HWFlowCtl_CTS			(uint32_t)(1<<9)
#define UART_HWFlowCtl_RTS_CTS		(uint32_t)(3<<8)

// @ref UART_IRQ_Enable_define

#define UART_IRQ_Enable_NONE		(uint32_t)(0)
#define UART_IRQ_Enable_TXE			(uint32_t)(1<<7)		// Transmission data register Empty
#define UART_IRQ_Enable_TC			(uint32_t)(1<<6)		// Transmission Complete
#define UART_IRQ_Enable_RXNEIE		(uint32_t)(1<<5)		// Received data readyto be read & Overrun Error detected
#define UART_IRQ_Enable_PE			(uint32_t)(1<<8)		// Parity Error


//=======================================
//***************  APIs  ****************
//=======================================

enum Polling_mechanism
{
	PO_Enable,
	PO_Disable
};


/*•*•*• BaudRate Calculation *•*•*•*•*/

// USARTDIV = fclk / (16* Baudrate)
// USARTDIV_MUL100 = 25*fclk / (4* Baudrate)
// DIV_Mantissa_MUL100 = Integar Part of (USARTDIV) * 100
// DIV_Mantissa = Integar Part of (USARTDIV)
// DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) * 16 ) / 100

#define USARTDIV(_PCLK_,_BAUD_)						(uint32_t)(_PCLK_/(16 * _BAUD_))
#define USARTDIV_MUL100(_PCLK_,_BAUD_)				(uint32_t)((25 * _PCLK_)/(4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_,_BAUD_)				(uint32_t)(USARTDIV(_PCLK_,_BAUD_)*100)
#define Mantissa(_PCLK_,_BAUD_)						(uint32_t)(USARTDIV(_PCLK_,_BAUD_))
#define DIV_Fraction(_PCLK_,_BAUD_)					(uint32_t)(((USARTDIV_MUL100(_PCLK_,_BAUD_) - Mantissa_MUL100(_PCLK_,_BAUD_)) * 16)/100)
#define UART_BRR_Register(_PCLK_,_BAUD_)			((Mantissa(_PCLK_,_BAUD_) << 4) | (DIV_Fraction(_PCLK_,_BAUD_) & 0xf))



/* Initialization / DeInitialization Functions */

void MCAL_UART_Init (USART_typedef * USARTx , UART_Config * UART_Config);
void MCAL_UART_DeInit (USART_typedef* USARTx);

void MCAL_UART_GPIO_Set_Pins (USART_typedef * USARTx);

void MCAL_UART_SendData (USART_typedef* USARTx , uint16_t* ptxBuffer , enum Polling_mechanism PollingEN);
void MCAL_UART_ReceiveData (USART_typedef* USARTx , uint16_t* ptxBuffer , enum Polling_mechanism PollingEN);

void MCAL_UART_WAIT_TC (USART_typedef * USARTx);

//todo	MCAL_USART_LIN_Init ()			// LIN
//todo	MCAL_USART_Init ()				// Synchronous
//todo	MCAL_USART_DMA_Init ()			// Multibuffer Communication

#endif /* STM32_F103C6_USART_DRIVER_H_ */
