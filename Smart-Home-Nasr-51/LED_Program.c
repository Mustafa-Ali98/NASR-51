/*
 * LCD_Program.c
 *
 * Created: 4/30/2023 11:21:34 PM
 *  Author: Group 1
 */ 

/* UTILES */
#include "STD_TYPES.h"
#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"



/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LED_Interface.h"

void LED_on(u8 RegisterId, u8 PinId)
{
	DIO_setPinDeriction(RegisterId, PinId, DIO_PIN_OUTPUT);
	DIO_setPinValue(RegisterId, PinId, DIO_PIN_HIGH);
}

void LED_off(u8 RegisterId, u8 PinId)
{
	DIO_setPinDeriction(RegisterId, PinId, DIO_PIN_OUTPUT);
	DIO_setPinValue(RegisterId, PinId, DIO_PIN_LOW);
}

/*void LED_toggle(u8 RegisterId, u8 PinId)
{
	if (GET_BIT(RegisterId, PinId) == 1)
	{
		DIO_setPinValue(RegisterId, PinId, DIO_PIN_LOW);
	}
	else if (GET_BIT(RegisterId, PinId) == 0)
	{
		DIO_setPinValue(RegisterId, PinId, DIO_PIN_HIGH);
	}
}*/

/*void LED_flash(u8 RegisterId, u8 PinId, u32 FlashTime)
{
	DIO_setPinDirection(RegisterId, PinId, DIO_PIN_OUTPUT);
	LED_toggle(RegisterId, PinId);
	_delay_ms(FlashTime);
	LED_toggle(RegisterId, PinId);
	_delay_ms(FlashTime);
}*/