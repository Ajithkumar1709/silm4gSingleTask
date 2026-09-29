
INCLUDE inc.ld
MEMORY
{
	ROM (rx)     : ORIGIN = __APP_ROM_ADDR, LENGTH = 0x7D000
	SRAM (rwx)     : ORIGIN = __APP_RAM_ADDR, LENGTH = 0x7D000
}
SECTIONS
{
    . = __APP_ROM_ADDR;
    .INIT : ALIGN(4)
	{ 
		KEEP (*(.INIT))
	}>ROM
	.text : ALIGN(4)
	{
        PROVIDE_HIDDEN (__text_load = LOADADDR(.text));
        PROVIDE_HIDDEN (__text_start = .);
		
	    *(.text)
        *(.text*)
        PROVIDE_HIDDEN (_etext = .);
	}>ROM
	.rodata : ALIGN(4)
	{
	    *(.rodata)
	    *(.rodata*)
	}>ROM
	
	. = __APP_RAM_ADDR;
	.data : ALIGN(4)
	{
		PROVIDE_HIDDEN (__data_load = LOADADDR(.data));
		PROVIDE_HIDDEN (__data_start = .);
		*(table_stub)
		
		LONG(0x41505031)
		*(table_stub_c)
        *(table_stub_c*)
		LONG(0x41505032)
		
		*(.data)
        *(.data*)
		PROVIDE_HIDDEN (_edata = .);
	}>SRAM AT>ROM
	.ARM.exidx : ALIGN(4)
	{ 
		PROVIDE_HIDDEN (__exidx_start = .);
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		PROVIDE_HIDDEN (__exidx_end = .);
	}>SRAM AT>ROM
	.bss : ALIGN(4)
	{
        PROVIDE_HIDDEN (__bss_load = LOADADDR(.bss));
		PROVIDE_HIDDEN (__bss_start = .);
		*(.bss)
        *(.bss*)
		PROVIDE_HIDDEN (__bss_end = .);
	}>SRAM AT>ROM
    __init_length = SIZEOF(.INIT);
    __ro_length = SIZEOF(.text) + SIZEOF(.rodata);
    __rw_length = SIZEOF(.data) + SIZEOF(.ARM.exidx);
    __zi_length = SIZEOF(.bss);
	end = .;
}