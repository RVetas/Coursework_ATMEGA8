#include "display_handler.h"

char display[] = "    ";

unsigned int char_to_code(char symbol) {
    unsigned int code;
    switch (symbol) {
        case '-':
            code = 0b10111111;
            break;
        case '_':
            code = 0b11110111;
            break;
        case '0':
            code = 0b11000000;
            break;
        case '1':
            code = 0b11111001;
            break;
        case '2':
            code = 0b10100100;
            break;
        case '3':
            code = 0b10110000;
            break;
        case '4':
            code = 0b10011001;
            break;
        case '5':
            code = 0b10010010;
            break;
        case '6':
            code = 0b10000010;
            break;
        case '7':
            code = 0b11111000;
            break;
        case '8':
            code = 0b10000000;
            break;
        case '9':
            code = 0b10010000;
            break;
        case 'C':
            code = 0b11000110;
            break;
        case 'H':
            code = 0b10001001;
            break;
        case 'L':
            code = 0b11000111;
            break;
        case : '':
            code = 0b11111111;
            break;
        default:
            code = 0xff;
    };
    return code;
}

void send_digit_to_display(unsigned int number, char digit) {
    unsigned int displayDigit = char_to_code(digit);
    PORTB |= (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<< PB3) | (1<<PB4) | (1<<PB5);//clr data pin
    PORTD |= (1<<PD4);// clr data pin
    
    PORTC &= ~((1<<PC0) | (1<<PC1) | (1<<PC2) | (1<< PC3));// clr addr
    PORTC |= (1 << number); // set addr
    
    PORTB = displayDigit; // set data1
    PORTD &= ~((1<<PD4) & (~(displayDigit>>3))); // set data2
    _delay_ms(1);
}

void printDisplay() {
    for (short int i = 0; i < 4; ++i) {
        send_digit_to_display(i, display[i]);
    }
}
