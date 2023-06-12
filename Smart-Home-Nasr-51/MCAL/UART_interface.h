/*
 * UART_interface.h
 *
 * Created: 5/5/2023 5:09:03 PM
 *  Author: Eng.Mostafa Ali
 */ 

#include "STD_TYPES.h"
#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#define F_CPU 8000000UL	

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_init(long USART_BAUDRATE);
unsigned char UART_RxChar();
void UART_TxChar(char ch);
void UART_SendString(char *str);



#endif /* UART_INTERFACE_H_ */