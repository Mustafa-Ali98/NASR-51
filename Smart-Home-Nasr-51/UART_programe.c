/*
 * UART_programe.c
 *
 * Created: 5/5/2023 5:08:46 PM
 *  Author: Eng.Mostafa Ali
 */ 

#include "STD_TYPES.h"
#include "ATMEGA32_REG.h"
#include <avr/io.h>
#include "BIT_MATH.h"
#include "UART_interface.h"
//#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)



void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);/* Turn on transmission and reception */
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit character sizes */
	UBRRL = BAUD_PRESCALE;		/* Load lower 8-bits of the baud rate value */
	UBRRH = (BAUD_PRESCALE >> 8);	/* Load upper 8-bits*/
}

unsigned char UART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0);/* Wait till data is received */
	return(UDR);			/* Return the byte*/
}

void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
	UDR = ch ;
}

void UART_SendString(char *str)
{
	unsigned char j=0;

	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);
		j++;
	}
}
