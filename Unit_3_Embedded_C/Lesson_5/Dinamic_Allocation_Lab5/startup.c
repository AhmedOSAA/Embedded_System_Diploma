/* write startup.c cortexM3 
 * ENG.Ahmed Osamaa
 */

#include <stdint.h>

extern int main(void);

void Reset_Handler (void);
void NMI_Handler () __attribute__((weak,alias("Defoult_Handler")));;
void H_Fault_Handler () __attribute__((weak,alias("Defoult_Handler")));;
void MM_Fault_Handler () __attribute__((weak,alias("Defoult_Handler")));;
void Bus_Fault () __attribute__((weak,alias("Defoult_Handler")));;
void Usage_Fault_Handler () __attribute__((weak,alias("Defoult_Handler")));;

extern unsigned int _stack_top ;

uint32_t vectors[] __attribute__((section(".vectors"))) = {
	
	(uint32_t) &_stack_top ,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_Fault_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bus_Fault,
	(uint32_t) &Usage_Fault_Handler
};

extern unsigned int _E_text ;
extern unsigned int _s_data ;
extern unsigned int _E_data ;
extern unsigned int _s_bss ;
extern unsigned int _e_bss ;

void Reset_Handler (void){
	int i;
	// copy .data from flash to sram
	unsigned int datasize = (unsigned char*)&_E_data - (unsigned char*)&_s_data ;
	unsigned char *p_src = (unsigned char*)&_E_text ;
	unsigned char *p_dis = (unsigned char*)&_s_data ;
	for(i=0;i<datasize;i++){
		*((unsigned char*)p_dis++) = *((unsigned char*)p_src++);
	}
	// init the .bss with zeros at sram
	p_dis = (unsigned char*)&_s_bss ;
	unsigned int bss_size = (unsigned char*)&_e_bss - (unsigned char*)&_s_bss ;
	for(i=0;i<bss_size;i++){
		*((unsigned char*)p_dis++) = (unsigned char)0;		
	}
	// call main
	main();
}

void Defoult_Handler (void){
	Reset_Handler();
}