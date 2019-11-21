#include "display_handler.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Настройка портов
void set_up_ports(void) {
  //Эти пины настроены на вывод. Вывод идет на A,B,C,D,E,F 7-сегментного индикатора
	DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<< PB3) | (1<<PB4) | (1<<PB5);
  //Этот пин служит для вывода G на 7-сегментный индикатор
  DDRD |= (1<<PD4);
  //Эти пины служат для выбора одного из четырех 7-сегментных индикаторов
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);
} 

//Обработчик прерывания переполнения таймера
ISR(TIMER0_OVF_vect) {
	printDisplay(display);
}

ISR(INT0_vect) {
  unsigned char button_number = which_key_pressed();

  switch (button_number) {
    case 0:
    *display = "0000";
    break;

    case 1:
    *display = "0001";
    break;

    case 2:
    *display = "0002";
    break;

    default:
    *display = "5051";
    break;
  }
}

//Инициализация таймера
void timer_init() {
	TIMSK |= (1 << TOIE0);
	TCCR0 = (1 << CS01);
}

int main(void) {
	set_up_ports();
    timer_init();
    GICR |= (1 << INT0); //Разрешаем прерывание INT0
    MCUCR |= (1 << ISC00) | (1 << ISC01); //Генерация сигнала по возрастающему фронту
	sei(); //Глобальное разрешение прерываний

	while(1) {
		_delay_ms(1000);
	}
	return 0;
}
