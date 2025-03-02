print:
    mov ah, 0x0e
    jmp print_loop
print_loop:
    mov al, [bx]
    cmp al, 0
    je print_end
    int 0x10
    inc bx
    jmp print_loop
print_end:
    ret