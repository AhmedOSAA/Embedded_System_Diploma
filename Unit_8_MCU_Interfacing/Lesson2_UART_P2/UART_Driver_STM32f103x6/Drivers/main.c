/* main.h
 * Author: ENG. Ahmed Osamaa
 */


#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_EXTI_Driver.h"
#include "STM32_F103C6_RCC_Driver.h"
#include "STM32_F103C6_USART_Driver.h"
#include "lcd.h"

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


unsigned char CH ;

// UART Reseiver IRQ
void UART_IRQ_Receiver (void)
{
	MCAL_UART_ReceiveData(USART1, (uint16_t*)&CH , PO_Disable) ;

	MCAL_UART_SendData(USART1,(uint16_t*)&CH, PO_Enable) ;
}


//Main Program
int main(void)
{
	Clock_init();
	UART_Config UART1_CFG ;

	UART1_CFG.BaudRate = UART_BaudRate_115200 ;
	UART1_CFG.HWFlowCtl = UART_HWFlowCtl_NONE ;
	UART1_CFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE ;
	UART1_CFG.P_IRQ_CallBack = UART_IRQ_Receiver ;
	UART1_CFG.Parity = UART_Parity_NONE ;
	UART1_CFG.Payload = UART_Payload_length_8BIT ;
	UART1_CFG.StopBits = UART_StopBits_1 ;
	UART1_CFG.USART_Mode = UART_Mode_TX_RX ;

	MCAL_UART_Init(USART1, &UART1_CFG ) ;
	MCAL_UART_GPIO_Set_Pins(USART1) ;

	while (1)
	{
		//Using Polling Mechanesim
		//MCAL_UART_ReceiveData(USART1, (uint16_t*)&CH , PO_Enable) ;

		//MCAL_UART_SendData(USART1,(uint16_t*)&CH, PO_Enable) ;
	}
	return 0;
}
