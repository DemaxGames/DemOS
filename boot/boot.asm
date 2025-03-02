[bits 16]
[org 0x7c00]
CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start
KERNEL_LOCATION equ 0x7e00
mov [diskNum], dl

mov ah, 0x00
mov al, 0x03
int 0x10

mov bx, msg
call print

mov ah, 2
mov al, 10 ;sectors count
mov ch, 0
mov cl, 2
mov dh, 0
mov dl, [diskNum]
mov bx, KERNEL_LOCATION
int 0x13

cli
lgdt [GDT_Descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

%include "boot/print.asm"


GDT_Start:
    null_descriptor:
        dd 0
        dd 0
    code_descriptor:
        dw 0xffff
        dw 0
        db 0
        db 0b10011010
        db 0b11001111
        db 0
    data_descriptor:
        dw 0xffff
        dw 0
        db 0
        db 0b10010010
        db 0b11001111
        db 0
GDT_End:

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1
    dd GDT_Start

[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp

    jmp KERNEL_LOCATION

msg: db "Loading from disk...", 0
diskNum: db 0
times 510-($-$$) db 0
db 0x55, 0xaa