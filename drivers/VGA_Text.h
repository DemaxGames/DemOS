#pragma once
#include "typedef.h"
#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80
int print_ttyraw(uint8_t c, uint8_t color, int8_t pos);
int print_tty(uint8_t c, uint8_t color, int8_t x, int8_t y);
int printf_str(const char* str, int8_t x, int8_t y);
int printf_dec(int dec, int8_t x, int8_t y);
int printf_bin(int dec, int8_t x, int8_t y);
void printf_time();
