
INCLUDE inc.ld

SECTIONS
{
    . = __APP_ROM_ADDR;
    .INIT : ALIGN(4)
	{ 
		KEEP (*(.INIT))
	}
	.text __APP_RAM_ADDR : AT(__APP_ROM_ADDR + SIZEOF(.INIT)) ALIGN(4)
	{
        PROVIDE_HIDDEN (__text_load = LOADADDR(.text));
        PROVIDE_HIDDEN (__text_start = .);
		*(table_stub)
		
		LONG(0x41505031)
		*(table_stub_c)
        *(table_stub_c*)
		LONG(0x41505032)
		
	    *(.text)
        *(.text*)
        PROVIDE_HIDDEN (_etext = .);
	}
	.rodata : ALIGN(4)
	{
	    *(.rodata)
	    *(.rodata*)
	}
	.data : ALIGN(4)
	{
		PROVIDE_HIDDEN (__data_load = LOADADDR(.data));
		PROVIDE_HIDDEN (__data_start = .);
		*(.data)
        *(.data*)
		PROVIDE_HIDDEN (_edata = .);
	}
	.ARM.exidx : ALIGN(4)
	{ 
		PROVIDE_HIDDEN (__exidx_start = .);
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		PROVIDE_HIDDEN (__exidx_end = .);
	}
	.bss : ALIGN(4)
	{
        PROVIDE_HIDDEN (__bss_load = LOADADDR(.bss));
		PROVIDE_HIDDEN (__bss_start = .);
		*(.bss)
        *(.bss*)
		PROVIDE_HIDDEN (__bss_end = .);
	}
    __init_length = SIZEOF(.INIT);
    __ro_length = SIZEOF(.text) + SIZEOF(.rodata);
    __rw_length = SIZEOF(.data) + SIZEOF(.ARM.exidx);
    __zi_length = SIZEOF(.bss);
	end = .;
}