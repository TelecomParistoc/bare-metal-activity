CROSSCOMPILE = arm-none-eabi-

CC = $(CROSSCOMPILE)gcc
LD = $(CROSSCOMPILE)ld
AS = $(CROSSCOMPILE)as
DB = $(CROSSCOMPILE)gdb
CPP = $(CROSSCOMPILE)cpp
OBJCOPY = $(CROSSCOMPILE)objcopy

DIRS = src lib

DEVICE = STM32030R8

GDB_SERVER = JLinkGDBServer
ENDIAN = little

ARCH = -mcpu=cortex-m0 -mthumb
ASFLAGS = -g
CPPFLAGS = -Iinclude/ -D$(DEVICE) -DSTM32F030x8
CFLAGS = -Wall -Wextra -g -O1 -std=gnu99 $(ARCH) $(INCLUDE)
LDFLAGS = -T ld_ram.lds -nostdlib
LDLIBS =

CSRCS = $(foreach DIR, $(DIRS), $(wildcard $(DIR)/*.c))
SSRCS = $(foreach DIR, $(DIRS), $(wildcard $(DIR)/*.s))
OBJS = $(CSRCS:%.c=%.o) $(SSRCS:%.s=%.o)
DEPS = $(CSRCS:%.c=%.d)

EXE = main
ELF = $(EXE).elf
IMG = $(EXE).bin

$(IMG): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(OBJS) ld_ram.lds
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

-include $(DEPS)

%.d: %.c
	@$(CC) $(CFLAGS) -M -MF $@ -MP $< -MT $(@:%.d=%.o)

gdb_server:
	$(GDB_SERVER) -device $(DEVICE) -endian $(ENDIAN) -if SWD -speed auto -ir -LocalhostOnly

gdb:
	$(GDB) $(ELF)

clean:
	$(RM) $(OBJS) $(DEPS) $(ELF)

clean-all: clean
	$(RM) $(IMG)

re: clean-all $(IMG)

.PHONY: gdb gdb_server clean re
