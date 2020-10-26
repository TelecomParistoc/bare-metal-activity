MEMORY {
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    sram (!rx) : ORIGIN = 0x20000000, LENGTH = 8K
}

ENTRY(_start)

SECTIONS {
    .vect_table :
    {
        _irq_table = . ;
        lib/irq.o(*vectors*)
    } >flash

    .text :
    {
        lib/crt0.o(.text)
        *(.text)
    } >flash

    .rodata :
    {
        *(.rodata*);
    } >flash

    .data :
    {
        _data = . ;
        *(.data);
        _edata = . ;
    } >sram AT>flash

    .bss :
    {
        _bstart = . ;
        *(.bss) *(*COM*);
        _bend = . ;
    } >sram
}

_stack = ORIGIN(sram) + LENGTH(sram);
_data_lma = LOADADDR(.data);
_data_lma_end = LOADADDR(.data) + SIZEOF(.data);
_data_vma = ADDR(.data);
