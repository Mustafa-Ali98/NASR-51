/*
 * LCD_Interface.h
 *
 * Created: 4/30/2023 11:22:02 PM
 *  Author: Group 1
 */ 
#include "LED_Config.h"

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LED_on(u8 RegisterId, u8 PinId);
void LED_off(u8 RegisterId, u8 PinId);
// void LED_toggle(u8 RegisterId, u8 PinId);
// void LED_flash(u8 RegisterId, u8 PinId, u32 FlashTime);

#endif /* LCD_INTERFACE_H_ */