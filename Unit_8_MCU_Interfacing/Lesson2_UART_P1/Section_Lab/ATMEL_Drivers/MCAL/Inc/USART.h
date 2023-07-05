/*
 * USART.h
 *
 * Created: 6/29/2023 6:07:36 PM
 *  Author: midom
 */ 


#ifndef USART_H_
#define USART_H_

// Generic Variable 

char CH[100];

// Registers

#define  UDR_R			*(volatile uint8_t *)(0x2C)
#define  UCSRA_R		*(volatile uint8_t *)(0x2B)
#define  UCSRB_R		*(volatile uint8_t *)(0x2A)
#define  UCSRC_R		*(volatile uint8_t *)(0x40)
#define  UBRRL_R		*(volatile uint8_t *)(0x29)
#define  UBBRH_R		*(volatile uint8_t *)(0x40)


// APIs

void UART_init (void);


void UART_Send (int8_t data);


int8_t UART_Receive (void);

void UART_Send_String (char* p);
void UART_Receive_String (void);


#endif /* USART_H_ */