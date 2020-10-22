MEMORY {
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    sram (!rx) : ORIGIN = 0x20000000, LENGTH = 8K
}

ENTRY(_start)

SECTIONS {
    .text :
    {
        lib/crt0.o(.text)
        *(.text)
    } >sram

    .rodata :
    {
        *(.rodata*);
    } >sram

    .data :
    {
        _data = . ;
        *(.data);
        _edata = . ;
    } >sram

    .bss :
    {
        _bstart = . ;
        *(.bss) *(*COM*);
        _bend = . ;
    } >sram
}

_stack = ORIGIN(sram) + LENGTH(sram);
