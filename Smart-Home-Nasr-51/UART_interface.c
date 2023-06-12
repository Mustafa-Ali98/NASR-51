/*
 * UART_interface.c
 *
 * Created: 6/11/2023 5:31:12 PM
 *  Author: Eng.Mostafa Ali
 */ #include "STD_TYPES.h"
 #include "ATMEGA32_REG.h"
 #include <avr/io.h>
 #include "BIT_MATH.h"
#include "uart_programe.c"

void UART_init(long USART_BAUDRATE);
unsigned char UART_RxChar();
void UART_TxChar(char ch);
void UART_SendString(char *str);
