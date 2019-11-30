#include "display_handler.h"
#include "ds1621.h"
#include "button_handler.h"
#include "i2c_routines.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

//Настройка портов
void set_up_ports(void) {
  //Эти пины настроены на вывод. Вывод идет на A,B,C,D,E,F 7-сегментного индикатора
	DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<< PB3) | (1<<PB4) | (1<<PB5);
  //Этот пин служит для вывода G на 7-сегментный индикатор
  DDRD |= (1<<PD3);
  //Эти пины служат для выбора одного из четырех 7-сегментных индикаторов
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);

  // Перевод PD5,6,7 на чтение для последующей обработки кнопок
  // DDRD &= ~((1 << PD5)| (1 << PD6) | (1 << PD7)); 
  // DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
  // PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);

  // Настройка i2c. PC4,5 на вывод.
  DDRC |= (1 << PC4) | (1 << PC5);
} 

//Обработчик прерывания переполнения таймера
ISR(TIMER0_OVF_vect) {
	printDisplay(display);
}

ISR(INT0_vect) {
  unsigned char button_number = number_key_pressed();
  handle_buttons(button_number);
}

void handle_buttons(unsigned char button_number) {
  // unsigned char button_number = number_key_pressed();

  switch (button_number) {
    case 0:
    strcpy(display, "0000");
    break;

    case 1:
    strcpy(display, "1111");
    break;

    case 2:
    strcpy(display, "2222");
    break;

    default:
    break;
  };
}

//Инициализация таймера
void timer_init() {
	TIMSK |= (1 << TOIE0);
	TCCR0 = (1 << CS02);
}

void init() {
  // cli();
  set_up_ports();
  timer_init();

  GICR |= (1 << INT0);
  MCUCR |= (1 << ISC00) | (1 << ISC01);
  sei();
  // cli();
}

int main(void) {
  init();
  ds1621_init();
  DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
  PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
	while(1) {
    // handle_buttons();
    signed char temp = getTemperature();
		_delay_ms(1);
	}
	return 0;
}
