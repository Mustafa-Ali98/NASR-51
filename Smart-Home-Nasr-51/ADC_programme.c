/*
 * ADC_programme.c
 *
 * Created: 4/14/2023 3:16:02 PM
 *  Author: Eng.Mostafa Ali
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"
#include "ADC_interface.h"
void ADC_init(void)
{
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
	CLR_BIT(ADMUX,5);
	SET_BIT(ADCSRA,7);
	CLR_BIT(ADCSRA,5);
	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
}

void ADC_getDigital(u8 ChannelNum, u16* DigitalValue)
{
	ADMUX &= 0b11100000;//clear five bits
	ADMUX |= ChannelNum;
	SET_BIT(ADCSRA,6);
	while(0==GET_BIT(ADCSRA,4));
	
	SET_BIT(ADCSRA,6);
	* DigitalValue=ADC_u16 ;
}