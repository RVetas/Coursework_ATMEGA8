#include <avr/io.h>

#ifndef BUTTON_HANDLER
#define BUTTON_HANDLER

void button_matrix_init();
unsigned char which_key_pressed();

#endif