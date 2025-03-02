#include "VGA_Text.h"
#include "port_io.h"
char* VRAM = (char*)0xb8000;
int print_ttyraw(uint8_t c, uint8_t color, int8_t pos){
    *(VRAM + pos * 2) = c;
    *(VRAM + pos * 2 + 1) = color;
    return 0;
}
int print_tty(uint8_t c, uint8_t color, int8_t x, int8_t y){
    *(VRAM + (y*SCREEN_WIDTH + x) * 2) = c;
    *(VRAM + (y*SCREEN_WIDTH + x) * 2 + 1) = color;
    return 0;
}
int printf_str(const char* str, int8_t x, int8_t y){
    int cursor_pos = x;
    for(int i = 0; str[i] != 0; i++){
        print_tty(str[i], BACKGROUND_BLACK | WHITE, cursor_pos, y);
        cursor_pos++;
    }
    return cursor_pos - y * SCREEN_WIDTH + x;
}
int printf_dec(int dec, int8_t x, int8_t y){
    int cursor_pos = x;
    if(dec == 0){
        print_tty(dec + 48, BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, y);
        return 0;
    }
    long mult = 1000000;
    for(;mult != 0; mult /= 10){
        if(((dec / mult) % 10) != 0) break;
    }
    for(;mult != 0; mult /= 10){
        print_tty((dec / mult) % 10 + 48, BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, y);
        cursor_pos++;
    }
    return cursor_pos;
}
int printf_bin(int dec, int8_t x, int8_t y){
    int cursor_pos = x;
    if(dec == 0){
        print_tty(dec + 48, BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, y);
        return 0;
    }
    long mult = 2*2*2*2*2*2*2*2;
    //for(;(dec / mult) % 2 == 0 ; mult /= 2);
    for(;mult != 0; mult /= 2){
        print_tty((dec / mult) % 2 + 48, BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, y);
        cursor_pos++;
    }
    return 0;
}
void printf_time(){
    int cursor_pos = 79-20;
    char time;
    //year
    print_tty('2', BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
    print_tty('0', BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos+1, 24);
    cursor_pos += 2;
    outb(0x70, 0x09);
    printf_dec(inb(0x71), cursor_pos, 24);
    cursor_pos += 2;
    print_tty(45, BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
    cursor_pos += 1;
    //month
    outb(0x70, 0x08);
    time = inb(0x71);
    if(time < 10){
        print_tty('0', BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
        printf_dec(time, cursor_pos+1, 24);
    }
    else{
        printf_dec(time, cursor_pos, 24);
    }
    cursor_pos += 2;
    print_tty(45, BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
    cursor_pos += 1;
    //day
    outb(0x70, 0x07);
    time = inb(0x71);
    if(time < 10){
        print_tty('0', BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
        printf_dec(time, cursor_pos+1, 24);
    }
    else{
        printf_dec(time, cursor_pos, 24);
    }
    cursor_pos += 2;
    print_tty(45, BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
    cursor_pos += 1;
    //hour
    outb(0x70, 0x04);
    time = inb(0x71);
    if(time < 10){
        print_tty('0', BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
        printf_dec(time, cursor_pos+1, 24);
    }
    else{
        printf_dec(time, cursor_pos, 24);
    }
    cursor_pos += 2;
    print_tty(45, BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
    cursor_pos += 1;
    //minute
    outb(0x70, 0x02);
    time = inb(0x71);
    if(time < 10){
        print_tty('0', BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
        printf_dec(time, cursor_pos+1, 24);
    }
    else{
        printf_dec(time, cursor_pos, 24);
    }
    cursor_pos += 2;
    print_tty(45, BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
    cursor_pos += 1;
    //second
    outb(0x70, 0x00);
    time = inb(0x71);
    if(time < 10){
        print_tty('0', BACKGROUND_BLACK|LIGHT_GREEN, cursor_pos, 24);
        printf_dec(time, cursor_pos+1, 24);
    }
    else{
        printf_dec(time, cursor_pos, 24);
    }
    return;
}