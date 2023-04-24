#include "uart.h"

unsigned char string_buffer[100] = "learn-in-depth: Ahmed Osamaa";


void main(void)
{
	Uart_Send_string(string_buffer);
}