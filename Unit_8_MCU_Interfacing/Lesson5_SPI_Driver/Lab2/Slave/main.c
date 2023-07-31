/* main.h
 * Author: ENG. Ahmed Osamaa
 */

/*  •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 *  ••• @file	:	main.c
 *  ••• @author :	ENG.Ahmed Osamaa
 *  ••• @brief  :	Learn_IN_Depth
 *  ••• @LAB    :	LAP 1
 *  ••• @Topic  :	Unit 8 Lesson 5 (SPI Full Duplex Driver for "BLUEPILL" STM32 )
 *  •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
 *  @TASK  :  1- Terminal <----> USART1 : MCU1
 *  		  2- MCU1 : (SPI1 Master) --->(SPI2 Slave) : MCU2
 *  		  3- MCU2 : USART2 ---> Terminal2
 */


//=======================================
//*************** Macros  ****************
//=======================================

//#define MCU_Act_AS_Master
#define MCU_Act_AS_Slave

//=======================================
//********* Generic Variable  ***********
//=======================================

unsigned char ch ;

//=======================================
//************  INcludes  ***************
//=======================================

#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_EXTI_Driver.h"
#include "STM32_F103C6_RCC_Driver.h"
#include "STM32_F103C6_USART_Driver.h"
#include "STM32_F103C6_SPI_Driver.h"

//delay
void delay (int x){
	int i , j ;
	for (i=0 ; i<x ; i++)
		for (j=0 ; j<50 ; j++);
}

void Clock_init (void)
{
	// Enable clock for GPIOA
	RCC_GPIOA_CLK_EN();
	// Enable clock for GPIOB
	RCC_GPIOB_CLK_EN();
	// Enable clock for AFIO
	RCC_AFIO_CLK_EN();
}

// SPI Reseiver IRQ
void SPI1_IRQ_Receiver (struct S_IRQ_SRC irq_src )
{
#ifdef MCU_Act_AS_Slave
	if(irq_src.RXNE)
	{
		ch = 0xf ;
		MCAL_SPI_TX_RX(SPI1,  (uint16_t *)&ch, POLLingDisable) ;
		MCAL_UART_SendData(USART1,  (uint16_t *)&ch, PO_Enable) ;
	}
#endif
}

// UART Reseiver IRQ
void UART_IRQ_Receiver (void)
{
#ifdef MCU_Act_AS_Master

	MCAL_UART_ReceiveData(USART1,  (uint16_t *)&ch , PO_Disable) ;
	MCAL_UART_SendData(USART1, (uint16_t *)&ch , PO_Enable) ;

	// Send to SPI
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0) ;
	MCAL_SPI_TX_RX(SPI1	, (uint16_t *)&ch , POLLingEnable) ;
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1) ;

#endif



}


//Main Program
int main(void)
{
	Clock_init();

	// •••••••••••••••Init UART1•••••••••••••••
	UART_Config uartCFG;

	uartCFG.BaudRate = UART_BaudRate_115200 ;
	uartCFG.HWFlowCtl = UART_HWFlowCtl_NONE ;
	uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE ;
	uartCFG.P_IRQ_CallBack = UART_IRQ_Receiver ;
	uartCFG.Parity = UART_Parity_NONE ;
	uartCFG.Payload = UART_Payload_length_8BIT ;
	uartCFG.StopBits = UART_StopBits_1 ;
	uartCFG.USART_Mode = UART_Mode_TX_RX ;

	MCAL_UART_Init(USART1, &uartCFG) ;
	MCAL_UART_GPIO_Set_Pins(USART1) ;

	// •••••••••••••••Init UART1•••••••••••••••
	SPI_Config SPI1CFG ;

	//Common Configure
	SPI1CFG.CLKPhase = SPI_CLKPhase_2EDGE_first_data_capture_edge ;
	SPI1CFG.CLKPolarity = SPI_CLKPolarity_High_when_IDLE ;
	SPI1CFG.DataSize = SPI_DataSize_8BIT ;
	SPI1CFG.Frame_Format = SPI_Frame_Format_MSB_Transmitted_First ;
	// Assume bu default pclk2 = 8 MHZ
	SPI1CFG.BaudRatePS = SPI_BaudRatePS_8 ;   // Prescaler 8 "/8" mean that clk will be  MHz
	SPI1CFG.Communication_Mode = SPI_Communication_Direction_2Line ;

#ifdef MCU_Act_AS_Master
	SPI1CFG.Device_Mode = SPI_Device_Mode_Master ;
	SPI1CFG.IRQ_Enable = SPI_IRQ_Enable_NONE ;
	SPI1CFG.NSS = SPI_NSS_SW_NSSInternalSoft_set ;
	SPI1CFG.P_IRQ_CallBack = NULL ;

	// Configure SS on PortA pin 4 by GPIO
	GPIO_PinConfig_t pincfg ;

	pincfg.GPIO_PinNumber = GPIO_PIN_4 ;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg.GPIO_output_speed = GPIO_SPEED_10M ;

	MCAL_GPIO_init(GPIOA, &pincfg) ;

	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1) ;  // Force the SS (High) idle Mode

#endif

#ifdef MCU_Act_AS_Slave
	SPI1CFG.Device_Mode = SPI_Device_Mode_Slave ;
	SPI1CFG.IRQ_Enable = SPI_IRQ_Enable_RXNEIE ;
	SPI1CFG.NSS = SPI_NSS_Hard_Slave ;
	SPI1CFG.P_IRQ_CallBack = SPI1_IRQ_Receiver ;
#endif

	MCAL_SPI_Init(SPI1, &SPI1CFG);
	MCAL_SPI_GPIO_Set_Pins(SPI1);


	while (1)
	{

	}
	return 0;
}
