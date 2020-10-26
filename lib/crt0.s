.thumb
.syntax unified
.cpu cortex-m0
.global _start

.thumb_func
_start:
    @ load initial sp
    ldr r0, =_stack
    mov sp, r0

    @ zero bss out
    bl init_bss

    @ copy data from flash to ram
    bl copy_data

    @ call main
    bl main

_exit:
    @ endless loop
    b _exit
