#include <stdio.h>
#include <stdint.h>



#define RCC_BASE 0x40021000
#define GPIO_BASE 0x40010800

#define RCC_APB2ENR *((volatile uint32_t *)(RCC_BASE+0x18))
#define GPIOA_CRH   *((volatile uint32_t *)(GPIO_BASE+0x04))
//#define GPIOA_ODR   *((volatile uint32_t *)(GPIO_BASE+0x0c))

typedef union {
	volatile uint32_t ALL_Port;
	struct {
		volatile uint32_t  reserved:13;
		volatile uint32_t  p_13:1;
	}pin;

}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t *)(GPIO_BASE+0x0c);

int main(void)
{
	RCC_APB2ENR |= 1<<2;
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;

	while (1)
	{
		R_ODR->pin.p_13 = 0;
		for(int i=0; i<5000 ; i++);
		R_ODR->pin.p_13 = 1;
		for(int i=0; i<5000 ; i++);
	}
	return 0;
}
