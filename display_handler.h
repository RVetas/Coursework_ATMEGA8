#include <avr/io.h>
#include <util/delay.h>
#ifndef DISPLAY_HANDLER
#define DISPLAY_HANDLER

unsigned int char_to_code(char symbol);
void send_digit_to_display(unsigned int number, char digit);
void printDisplay();
extern char display[];
#endif