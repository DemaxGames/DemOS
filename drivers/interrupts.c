#include "interrupts.h"

void cli(){
    asm volatile("cli");
    return;
}
void sti(){
    asm volatile("sti");
    return;
}