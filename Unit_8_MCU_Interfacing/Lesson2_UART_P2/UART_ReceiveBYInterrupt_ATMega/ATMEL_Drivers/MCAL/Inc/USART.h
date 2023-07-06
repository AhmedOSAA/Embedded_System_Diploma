/*
 * USART.h
 *
 * Created: 6/29/2023 6:07:36 PM
 *  Author: midom
 */ 


#ifndef USART_H_
#define USART_H_

#define Default_stop '\r'

// Generic Variable 

char CH[100];


// Registers

#define  UDR_R			*(volatile uint8_t *)(0x2C)
#define  UCSRA_R		*(volatile uint8_t *)(0x2B)
#define  UCSRB_R		*(volatile uint8_t *)(0x2A)
#define  UCSRC_R		*(volatile uint8_t *)(0x40)
#define  UBRRL_R		*(volatile uint8_t *)(0x29)
#define  UBBRH_R		*(volatile uint8_t *)(0x40)

// Macros 

#define UART_interrupt_RX_EN()			UCSRB_R |= (1<<7)
#define UART_interrupt_RX_DI()			UCSRB_R &= ~(1<<7)
#define UART_interrupt_TX_EN()			UCSRB_R |= (1<<6)
#define UART_interrupt_TX_DI()			UCSRB_R &= ~(1<<6)

// APIs

void UART_init (void);


void UART_Send (int8_t data);


int8_t UART_Receive (void);

void UART_Send_String (char* p);
void UART_Receive_String (void);
void UART_SendString_Asynch (char* strr);

#endif /* USART_H_ */