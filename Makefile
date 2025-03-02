TARGET = DemOS
PREF_SRC = ./src/
CSRC := $(shell find ./ -name "*.c")
COBJ = $(patsubst %.c, %.o, $(CSRC))
COBJ := kernel_entry.o $(COBJ)

CC = i386-elf-gcc
LD = i386-elf-ld
AC = nasm

run: $(TARGET)
	qemu-system-i386 $(TARGET).iso

$(TARGET): clear everything.bin zeroes.bin
	cat "everything.bin" "zeroes.bin" > "$(TARGET).iso"
	find . -name "*.o" -type f -delete
	find . -name "*.bin" -type f -delete
%.o: $(PREF_SRC)%c
	$(CC) -ffreestanding -m32 -g -c $< -o $@
kernel_entry.o:
	$(AC) "kernel/kernel_entry.asm" -f elf -o "kernel_entry.o"
full_kernel.bin: $(COBJ)
	$(LD) -o "full_kernel.bin" -Tkernel/kernel.ld $(COBJ) --oformat binary
	wc -c < full_kernel.bin
boot.bin:
	$(AC) -f bin "boot/boot.asm" -o "boot.bin"
everything.bin: boot.bin full_kernel.bin
	cat "boot.bin" "full_kernel.bin" >"everything.bin"
zeroes.bin:
	$(AC) -f bin "boot/zeroes.asm" -o "zeroes.bin"
clear:
	echo sources = $(CSRC)
	echo objects = $(COBJ)
	find . -name "*.o" -type f -delete
	find . -name "*.bin" -type f -delete