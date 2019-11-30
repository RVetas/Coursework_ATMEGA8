#include "button_handler.h"
unsigned char number_key_pressed(void) {
  PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
  PORTD |= (1 << PD5);
  if (PIND & (1 << PD2)) {
    PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
    return 0;
  }
  PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
  PORTD |= (1 << PD6);
  if (PIND & (1 << PD2)) {
    PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
    return 1;
  }
  PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
  PORTD |= (1 << PD7);
  if (PIND & (1 << PD2)) {
    PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
    return 2;
  }

  // unsigned char isButton2 = ((PIND >> (8 - 1)) & 1);
  // unsigned char isButton1 = ((PIND >> (7 - 1)) & 1);
  // unsigned char isButton0 = ((PIND >> (6 - 1)) & 1);

  // if (!isButton0) {
  //   return 0;
  // }

  // if (!isButton1) {
  //   return 1;
  // }

  // if (!isButton2) {
  //   return 2;
  // }
  return 42;
}
