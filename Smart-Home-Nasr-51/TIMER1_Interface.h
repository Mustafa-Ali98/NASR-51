/*
 * TIMER1_Interface.h
 *
 * Created: 4/29/2023 3:37:08 PM
 *  Author: Mostafa Sabry
 */ 


#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

void TIMER1_init(void);
void TIMER1_start(void);
void TIMER1_setCompareMatchValueA(u16 Value);
//void TIMER1_setCompareMatchValueB(u16 Value);




#endif /* TIMER1_INTERFACE_H_ */