/*
 * LCD_interface.h
 *
 * Created: 4/1/2023 3:26:23 PM
 *  Author: AMIT
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/* Macros For LCD Line Id */
#define LCD_LINE_ONE            1
#define LCD_LINE_TWO            2

/* Macros For LCD Shifting Direction */
#define LCD_SHIFT_LEFT          0
#define LCD_SHIFT_RIGHT         1


void LCD_init(void);
void LCD_sendCmnd(u8 Cmnd);
void LCD_sendChar(u8 data);
void LCD_writeHalfPort(u8 value);
void LCD_writeString(u8* String);
void LCD_writeNumber(u32 number);
void LCD_clear(void);
void LCD_shift(u8 shifttingDirection);
void LCD_goToSpecificPosition(u8 LineNumber, u8 Position);

#endif /* LCD_INTERFACE_H_ */