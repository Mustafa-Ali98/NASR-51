/*
 * KPD_programe.c
 *
 * Created: 4/7/2023 2:18:06 PM
 *  Author: AMIT
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "KPD_interface.h"
#include "KPD_config.h"


void KPD_init(void)
{
	//coloumns pins >> output
	DIO_setPinDeriction(KPD_COLS_PORT, KPD_COL0_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDeriction(KPD_COLS_PORT, KPD_COL1_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDeriction(KPD_COLS_PORT, KPD_COL2_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDeriction(KPD_COLS_PORT, KPD_COL3_PIN, DIO_PIN_OUTPUT);
	
	//rows pins >> input
	DIO_setPinDeriction(KPD_ROWS_PORT, KPD_ROW0_PIN, DIO_PIN_INPUT);
	DIO_setPinDeriction(KPD_ROWS_PORT, KPD_ROW1_PIN, DIO_PIN_INPUT);
	DIO_setPinDeriction(KPD_ROWS_PORT, KPD_ROW2_PIN, DIO_PIN_INPUT);
	DIO_setPinDeriction(KPD_ROWS_PORT, KPD_ROW3_PIN, DIO_PIN_INPUT);
	
	//active internal pull up for rows pins
	DIO_activePinInPullUpResistance(KPD_ROWS_PORT, KPD_ROW0_PIN);
	DIO_activePinInPullUpResistance(KPD_ROWS_PORT, KPD_ROW1_PIN);
	DIO_activePinInPullUpResistance(KPD_ROWS_PORT, KPD_ROW2_PIN);
	DIO_activePinInPullUpResistance(KPD_ROWS_PORT, KPD_ROW3_PIN);
}


void KPD_getValue(u8* returnedValue)
{
	u8 colsCounter,rowsCounter,pinValue;
	u8 flag = 0;
	u8 coloumnsPins[4] = {KPD_COL0_PIN,KPD_COL1_PIN,KPD_COL2_PIN,KPD_COL3_PIN};
	u8 rowsPins[4]     = {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};
	u8 KPD_Chars[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
	
	for(colsCounter=0;colsCounter<4;colsCounter++)
	{
		// Activate Each cols
		DIO_setPinValue(KPD_COLS_PORT, coloumnsPins[colsCounter], DIO_PIN_LOW);
		
		// Loop TO Check Rows Values
		for(rowsCounter=0;rowsCounter<4;rowsCounter++)
		{
			DIO_getPinValue(KPD_ROWS_PORT, rowsPins[rowsCounter], &pinValue);
			
			if(pinValue == 0)
			{
				*returnedValue = KPD_Chars[rowsCounter][colsCounter];
				while(pinValue == 0)
				{
					DIO_getPinValue(KPD_ROWS_PORT, rowsPins[rowsCounter], &pinValue);
				}
				flag =1;
				break;
			}
		}
		
		if(flag == 1)
		{
			break;
		}
		
		// deactivate current coloumn
		DIO_setPinValue(KPD_COLS_PORT, coloumnsPins[colsCounter], DIO_PIN_HIGH);	
	}
}
