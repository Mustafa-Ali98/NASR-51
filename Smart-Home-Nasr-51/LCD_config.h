/*
 * LCD_config.h
 *
 * Created: 4/1/2023 3:26:44 PM
 *  Author: AMIT
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/* Macros For Rs configuration */	
#define LCD_RS_PORT         DIO_PORTB
#define LCD_RS_PIN          DIO_PIN1

/* Macros For Rw configuration */
#define LCD_RW_PORT         DIO_PORTB
#define LCD_RW_PIN          DIO_PIN2

/* Macros For En configuration */
#define LCD_EN_PORT         DIO_PORTB
#define LCD_EN_PIN          DIO_PIN3

/* 4 Bit Mode Data Pins Configurtion */
#define LCD_DATA_PORT       DIO_PORTB
#define LCD_D4_PIN          DIO_PIN4
#define LCD_D5_PIN          DIO_PIN5
#define LCD_D6_PIN          DIO_PIN6
#define LCD_D7_PIN          DIO_PIN7


#endif /* LCD_CONFIG_H_ */