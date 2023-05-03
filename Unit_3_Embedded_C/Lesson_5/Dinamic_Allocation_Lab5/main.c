#include <stdio.h>
#include <stdlib.h>
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

unsigned char g_var[3] = {1,2,3};
unsigned char const const_var[3] = {1,2,3};
unsigned char bss_var[3] ;

void* _sbrk (int incr)
{
	static unsigned char* heap_ptr = NULL ;
	unsigned char* prev_heap_ptr = NULL ;
	extern unsigned int _e_bss ; //sympol
	extern unsigned int _heap_end ; //sympol

	if (heap_ptr == NULL)
		heap_ptr = (unsigned char*)&_e_bss;

	prev_heap_ptr = heap_ptr ;

	// protiction from overwrite
		if((heap_ptr + incr) > ( (unsigned char*)&_heap_end ))
		return (void*) NULL ; 

	// book size 
	heap_ptr += incr;

	return (void*) prev_heap_ptr ;
}

int main(void)
{
	int* p = (int*)malloc(4);
	free (p);
	int i ;
	RCC_APB2ENR |= 1<<2;
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;

	while (1)
	{
		R_ODR->pin.p_13 = 0;
		for(i=0; i<5000 ; i++);
		R_ODR->pin.p_13 = 1;
		for(i=0; i<5000 ; i++);
	}
	return 0;
}

