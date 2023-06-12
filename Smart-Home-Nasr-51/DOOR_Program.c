/*
 * DOOR_Program.c
 *
 * Created: 5/31/2023 9:09:32 PM
 *  Author: Group 1
 */ 

/* UTILES */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "TIMER1_Interface.h"
#include "TIMER1_Config.h"

/* HAL */
#include "DOOR_Interface.h"

void DOOR_Open(void)
{
	TIMER1_init();
	TIMER1_setCompareMatchValueA(499);
	TIMER1_start();
}

void DOOR_Close(void)
{
	TIMER1_init();
	TIMER1_setCompareMatchValueA(249);
	TIMER1_start();
}