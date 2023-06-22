#include <stdio.h>
#include <stdint.h>

//register address
//RCC
#define RCC_BASE  0x40021000
#define RCC_APB2ENR *((volatile uint32_t *)(RCC_BASE+0x18))

void clock_init ()
{
	// Enable clock GPIO
	RCC_APB2ENR |= 1<<2;
	// Enable clock AFIO
	RCC_APB2ENR |= 1<<0 ;
}

// GPIO
#define GPIO_BASE 0x40010800
#define GPIOA_CRH   *((volatile uint32_t *)(GPIO_BASE+0x04))
#define GPIOA_CRL   *((volatile uint32_t *)(GPIO_BASE+0x00))
#define GPIOA_ODR   *((volatile uint32_t *)(GPIO_BASE+0x0c))
void GPIP_init ()
{
	//pin 13 port A output
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;
	// Pin A 0 input floating
	GPIOA_CRL |= 1<<2 ;

}

// EXTI

#define EXTI_Base 0x40010400
#define EXTI_IMR *(volatile uint32_t *)(EXTI_Base + 0x00)
#define EXTI_RTSR *(volatile uint32_t *)(EXTI_Base + 0x08)
#define EXTI_PR *(volatile uint32_t *)(EXTI_Base + 0x14)

// AFIO
#define AFIO_Base 0x40010000
#define AFIO_EXTICR1 *(volatile uint32_t *)(AFIO_Base + 0x08)

// NVIC cortexM3
#define NVIC_EXTIE0 *(volatile uint32_t *)(0xE000E100)

int main(void)
{
	clock_init ();
	GPIP_init () ;
	// EXTI0 Configuration to PortA0
	AFIO_EXTICR1 = 0 ;
	// Enable EXTI line 0 (Mask = 1)
	EXTI_IMR |= 1<<0 ;
	// Enable rising trigger
	EXTI_RTSR |= 1<<0 ;
	// Enable NVIC Irq6
	NVIC_EXTIE0 |= 1<<6 ;

	while (1);
	return 0;
}


void EXTI0_IRQHandler ()
{
	// IRQ is happen EXTI0 >> Port pin 0 -- rising edge
	// toggle pin A 13
	GPIOA_ODR ^= (1<<13) ;

	//Clear pending Request for line 0
	EXTI_PR |= 1<<0 ;
}
