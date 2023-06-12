/*
 * ADC_interface.h
 *
 * Created: 4/14/2023 3:16:20 PM
 *  Author: Eng.Mostafa Ali
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define	ADC_CHANNEL0	0
#define	ADC_CHANNEL1	1
#define	ADC_CHANNEL2	2
#define	ADC_CHANNEL3	3
#define	ADC_CHANNEL4	4
#define	ADC_CHANNEL5	5
#define	ADC_CHANNEL6	6
#define	ADC_CHANNEL7	7

void ADC_init(void);
void ADC_getDigital(u8 ChannelNum, u16* DigitalValue);


#endif /* ADC_INTERFACE_H_ */