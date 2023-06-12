/*
 * TIMER1_Program.c
 *
 * Created: 4/29/2023 3:36:48 PM
 *  Author: Mostafa Sabry
 */ 

/* UTILES */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "TIMER1_Interface.h"
#include "TIMER1_Config.h"

void TIMER1_init(void)
{
	// Choose Mode 14
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	
	// Selecting Non Inverting Mode
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
	
	// Set pin OC1A as Output Pin
	SET_BIT(DDRD,5);	
	
	// ICR1 --> Period time = 20ms --> Freq. = 50HZ ("TIMER1_Config.h")
ICR1_u16 = ICR11_u16;
}

void TIMER1_start(void)
{
	// Select Pre-scaler Value = 64
	SET_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
	
}

void TIMER1_setCompareMatchValueA(u16 Value)
{
	// Init TIMER1 With Compare Value
	OCR1A_u16 = Value;
}

void TIMER1_setCompareMatchValueB(u16 Value)
{
	// Init TIMER1 With Compare Value
	OCR1B_u16 = Value;
}
