//
//  uart.h
//  
//
//  Created by Виталий Рамазанов on 05.12.2019.
//

#ifndef uart_h
#define uart_h

#define BAUD 9600
#define FOSC 4000000UL
#define UBRR FOSC/16/BAUD - 1

void UART_println(char*);
void USART_init(unsigned int);
void USART_transmit(char);
void UART_print(char*);

#endif /* uart_h */
