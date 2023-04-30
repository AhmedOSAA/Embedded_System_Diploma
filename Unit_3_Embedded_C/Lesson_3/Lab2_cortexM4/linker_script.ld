/* linker script cortexM3
ENG.Ahmed Osamaa */

MEMORY
{
	flash(RX) : ORIGIN = 0x08000000 , LENGTH = 128k
	sram(RWX) : ORIGIN = 0x20000000 , LENGTH = 20k  
}

SECTIONS
{
	.text :
	{
		*(.vectors*)
		*(.text*)
		*(.rodata)
		_E_text = . ;
	}> flash
	.data :
	{
		_s_data = . ;
		*(.data*)
		_E_data = . ;
	}> sram AT> flash
	.bss :
	{
		_s_bss = . ;
		*(.bss*) *(COMMON*)
		. = ALIGN(4);
		_e_bss = . ;
		. = . + 0x1000 ;
		_stack_top = . ;
	}> sram
}