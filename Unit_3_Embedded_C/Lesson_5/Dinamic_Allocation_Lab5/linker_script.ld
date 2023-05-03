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
		*(.rodata.*)
		_E_text = . ;
	}> flash
	.data :
	{
		_s_data = . ;
		*(.data)
		_E_data = . ;
	}> sram AT> flash
	.bss :
	{
		_s_bss = . ;
		*(.bss*) *(COMMON*)
		_e_bss = . ;
		. = ALIGN(4);
		. = . + 0x1000 ;
		_heap_end = . ;
		. = ALIGN(4);
		. = . + 0x1000 ;
		_stack_top = . ;
	}> sram

}	