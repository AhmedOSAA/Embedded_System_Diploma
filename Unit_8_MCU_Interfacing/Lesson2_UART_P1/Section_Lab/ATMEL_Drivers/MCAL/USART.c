/*
 * CFile1.c
 *
 * Created: 6/29/2023 6:07:03 PM
 *  Author: midom
 */ 

#include "MemoryMap.h"

#include "USART.h"


// APIs

void UART_init (void)
{
	// BoadRate
	UBRRL_R = 51 ;
	
	UCSRA_R &= ~(1<<1);
	
	//Frame
	
	//no parity
	// 8-bit data
	
	// Enable
	
	UCSRB_R |= (0b11<<3);
	
}

void UART_Send (int8_t data)
{
	while( !((UCSRA_R >> 5) & 1) );
	UDR_R = data ;
}

int8_t UART_Receive (void)
{
	while( !((UCSRA_R >> 7) & 1) );
	return UDR_R ;
}

void UART_Send_String (char* p)
{
	while(*p){
		UART_Send(*p);
		p++;
	}
}

void UART_Receive_String (void)
{
	for(int i=0 ; i<100 ; i++)
	{
		if (CH[i] == 0) break;
		CH[i] = 0 ;
	}
	int8_t* PCH = CH ;
	while (1)
	{
	*PCH = UART_Receive();
	if(*PCH == '!' )
	{
		*PCH = 0 ;
		 break;
	}
	PCH++ ;
	}
}
