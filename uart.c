//
//  uart.c
//  
//
//  Created by Виталий Рамазанов on 05.12.2019.
//

#include "uart.h"
#include <avr/io.h>

void USART_init(unsigned int ubrr) {
    //Настройка скорости
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    // 8 бит данных, 1 стоповый бит, без контроля четности
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
    UCSRB = (1 << TXEN);
}

void USART_transmit(char data) {
    while (!(UCSRA & (1 << UDRE))); //Ждём опустошения буффера
    UDR = data;
}

void UART_print(char* str) {
    int i = 0;
    while (str[i] != 0x00) {
        USART_transmit(str[i++]);
    }
}

void UART_println(char* str) {
    UART_print(str);
    UART_print("\r\n");
}
