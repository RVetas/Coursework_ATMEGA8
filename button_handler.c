#include "button_handler.h"
unsigned char number_key_pressed(void) {
  unsigned char isButton2 = ((PIND >> (8 - 1)) & 1);
  unsigned char isButton1 = ((PIND >> (7 - 1)) & 1);
  unsigned char isButton0 = ((PIND >> (6 - 1)) & 1);

  if (!isButton0) {
    return 0;
  }

  if (!isButton1) {
    return 1;
  }

  if (!isButton2) {
    return 2;
  }
  return 42;
}
