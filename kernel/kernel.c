#include "../drivers/VGA_Text.h"
#include "../drivers/port_io.h"
#include "../drivers/interrupts.h"
char getch();
void main(){    
    outb(0x70, 0x0b);
    outb(0x71, 0b00000110);

    long time = 0;
    printf_str("------Hello world!------", 0, 0);
    int j = 240;
    for(long i = 0;;i++){
        if(i % 3000 == 0){
            printf_str("hours: ", 0, 5);
            outb(0x70, 0x04);
            printf_bin(inb(0x71), 7, 5);
            print_tty(getch(), BACKGROUND_BLACK|LIGHT_MAGENTA, 79, 24);
            printf_time();
            j++;
        }

    }
    return;
}
char getch(){
    char code = inb(0x60);
    code = code & 0b01111111;
    switch (code)
    {
    case 0x02:
        return '1';
        break;
    case 0x03:
        return '2';
        break;
    case 0x04:
        return '3';
        break;
    case 0x05:
        return '4';
        break;
    case 0x06:
        return '5';
        break;
    case 0x07:
        return '6';
        break;
    case 0x08:
        return '7';
        break;
    case 0x09:
        return '8';
        break;
    case 0x0a:
        return '9';
        break;
    case 0x0b:
        return '0';
        break;
    case 0x0c:
        return '-';
        break;
    case 0x0d:
        return '=';
        break;
    case 0x10:
        return 'Q';
        break;
    case 0x11:
        return 'W';
        break;
    case 0x12:
        return 'E';
        break;
    case 0x13:
        return 'R';
        break;
    case 0x14:
        return 'T';
        break;
    case 0x15:
        return 'Y';
        break;
    case 0x16:
        return 'U';
        break;
    case 0x17:
        return 'I';
        break;
    case 0x18:
        return 'O';
        break;
    case 0x19:
        return 'P';
        break;
    case 0x1a:
        return '[';
        break;
    case 0x1b:
        return ']';
        break;
    case 0x1e:
        return 'A';
        break;
    case 0x1f:
        return 'S';
        break;
    case 0x20:
        return 'D';
        break;
    case 0x21:
        return 'F';
        break;
    case 0x22:
        return 'G';
        break;
    case 0x23:
        return 'H';
        break;
    case 0x24:
        return 'J';
        break;
    case 0x25:
        return 'K';
        break;
    case 0x26:
        return 'L';
        break;
    case 0x27:
        return ';';
        break;
    case 0x28:
        return '\'';
        break;
    case 0x2b:
        return '\\';
        break;
    case 0x2c:
        return 'Z';
        break;
    case 0x2d:
        return 'X';
        break;
    case 0x2e:
        return 'C';
        break;
    case 0x2f:
        return 'V';
        break;
    case 0x30:
        return 'B';
        break;
    case 0x31:
        return 'N';
        break;
    case 0x32:
        return 'M';
        break;
    case 0x33:
        return ',';
        break;
    case 0x34:
        return '.';
        break;
    default:
        return '\0';
        break;
    }
}