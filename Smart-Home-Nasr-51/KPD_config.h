/*
 * KPD_config.h
 *
 * Created: 4/7/2023 2:18:25 PM
 *  Author: AMIT
 */ 


#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_


                      /* MACROS FOR KPD COLUMNS PORTS & PINS CONFIGURATION */

//output				  
#define KPD_COLS_PORT          DIO_PORTA
#define KPD_COL0_PIN           DIO_PIN4
#define KPD_COL1_PIN           DIO_PIN5
#define KPD_COL2_PIN           DIO_PIN6
#define KPD_COL3_PIN           DIO_PIN7

                      /* MACROS FOR KPD ROWS PORTS & PINS CONFIGURATION */
					  
//input
#define KPD_ROWS_PORT          DIO_PORTC
#define KPD_ROW0_PIN           DIO_PIN3
#define KPD_ROW1_PIN           DIO_PIN4
#define KPD_ROW2_PIN           DIO_PIN5
#define KPD_ROW3_PIN           DIO_PIN6       


#endif /* KPD_CONFIG_H_ */