#include <stdio.h>
#include <stdint.h>

//register address
//RCC
#define RCC_BASE  0x40021000
#define RCC_APB2ENR *((volatile uint32_t *)(RCC_BASE+0x18))

void Clock_init ()
{
	// Enable clock GPIOA & GPIOB
	RCC_APB2ENR |= (0b11<<2) ;
}

//GPIOX REG
#define GPIOA_Base 0x40010800
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_Base + 0x00)  // pin 0 >> 7
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_Base + 0x04)  // pin 8 >> 15
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_Base + 0x08)  // Input data Register
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_Base + 0x0C)  // Output data Register

#define GPIOB_Base 0x40010C00
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_Base + 0x00)  // pin 0 >> 7
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_Base + 0x04)  // pin 8 >> 15
#define GPIOB_IDR *(volatile uint32_t *)(GPIOB_Base + 0x08)  // Input data Register
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_Base + 0x0C)  // Output data Register


void GPIP_init ()
{
	// config_ Port A pin 1 & 13 input floating
	//(as it already config_ed by default CNFy = 01 & MODEy = 00 )
	// config_ Port B pin 1 output with push-pull mode
	// (CNFy(6) = 00 'General purpose output push-pull' & MODEy(4) = 01 'Output mode, max speed 10 MHz.')
	GPIOB_CRL = 0x0 ;
	GPIOB_CRL |= (0b01<<4) ;
	// config_ Port B pin 13 output with push-pull mode
	// (CNFy(22) = 00 'General purpose output push-pull' & MODEy(20) = 01 'Output mode, max speed 10 MHz.')
	GPIOB_CRH = 0x0 ;
	GPIOB_CRH |= (0b01<<20) ;
}

//delay
void delay (int x){
	int i , j ;
	for (i=0 ; i<=x ; i++)
		for (j=0 ; j<=255 ; j++);
}
//Main Program
int main(void)
{
	Clock_init ();
	GPIP_init () ;

	while (1){
		// single press
		if (((GPIOA_IDR & 1<<1) >> 1) == 0){
			GPIOB_ODR ^= 1<<1 ;
			while(((GPIOA_IDR & 1<<1) >> 1) == 0);
		}
		// Multiple press
		if (((GPIOA_IDR & 1<<13) >> 13) == 1)
		{
			GPIOB_ODR ^= 1<<13 ;
			delay(100);
		}
	}
	return 0;
}

