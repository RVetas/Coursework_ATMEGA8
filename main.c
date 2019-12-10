#include "display_handler.h"
#include "ds1621.h"
#include "button_handler.h"
#include "i2c_routines.h"
#include "24c64.h"
#include "uart.h"

// Подключение стандартных библиотек
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

enum State {
  Register = 0, Transmit = 1, TURBO = 2
};
enum State state = Register;

int timer1_divider = 0; //timer1 divider
unsigned int address = 0; // eeprom write address
int timer_temp_divider = 0;
int should_update_temp = 1;
signed int temp = 0;
int error;
//Настройка портов
void set_up_ports(void) {
  //Эти пины настроены на вывод. Вывод идет на A,B,C,D,E,F 7-сегментного индикатора
	DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<< PB3) | (1<<PB4) | (1<<PB5);
  //Этот пин служит для вывода G на 7-сегментный индикатор
  DDRD |= (1<<PD3);
  //Эти пины служат для выбора одного из четырех 7-сегментных индикаторов
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);
  // Настройка i2c. PC4,5 на вывод.
  DDRC |= (1 << PC4) | (1 << PC5);
} 

//Обработчик прерывания переполнения таймера
ISR(TIMER0_OVF_vect) {
	printDisplay(display);
}

ISR(TIMER1_OVF_vect) {
  if (state == Register) {
    //Если значение timer1_divider меньше 56, то 15 минут еще не прошло
    if (timer1_divider < 56) {
      timer1_divider++;
    } else {
      //Значение timer1_divider достигло 56 => настало время записать данные в EEPROM
      signed char temp = getTemperature();
      EEWriteByte(address, temp);
      timer1_divider = 0;
    }
  }

  if (timer_temp_divider < 3) {
    timer_temp_divider++;
  } else {
    should_update_temp = 1;
    timer_temp_divider = 0;
  }
}

void transmit_data() {
  UART_println("TRANSMITION START");
  for (unsigned int i = 0; i < address; i++) {
    signed char data = EEReadByte(i);
    char *string_to_transmit = "Data #    : temp =     ";
    sprintf(string_to_transmit, "Data #%4d: temp = %4d", i, data);
    UART_println(string_to_transmit);
  }
  UART_println("TRANSMITION END");
}

void handle_buttons(unsigned char button_number) {
  // unsigned char button_number = number_key_pressed();

  switch (button_number) {
    case 0:
    state = Register;
    break;

    case 1:
    transmit_data();
    state = Register;
    break;

    case 2:
    state = TURBO;
    break;

    default:
    break;
  };
}

ISR(INT0_vect) {
  unsigned char button_number = number_key_pressed();
  handle_buttons(button_number);
}

//Инициализация таймера
void timer_init() {
	TIMSK |= (1 << TOIE0) | (1 << TOIE1) | (1 << TOIE2);
	TCCR0 = (1 << CS02);
  TCCR1B = (1 << CS12) | (1 << CS10);
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
  EEOpen();
  USART_init(UBRR);
  DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
  PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
	while(1) {
    if (should_update_temp) {
      temp = getTemperature();
      sprintf(display, "%4d", temp);
      should_update_temp = 0;
    }

    if (state == TURBO) {
      temp = getTemperature();
      if ((error = EEWriteByte(address, temp)) == 0 ) {
        strcpy(display, "0001");
      }

      address++;
      sprintf(display, "%4d", temp);
      char str[30];
      sprintf(str, "current temperature: %4d", temp);
      UART_println(str);
    }
    _delay_ms(1);
	}
	return 0;
}
