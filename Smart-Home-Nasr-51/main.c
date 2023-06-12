/*
 * SmartHome.c
 *
 * Created: 5/24/2023 1:44:58 AM
 * Author : Eng.Mostafa Ali
 */ 

#include "STD_TYPES.h"
#include "ATMEGA32_REG.h"
#include "BIT_MATH.h"
#include "KPD_interface.h"
#include "KPD_config.h"
#include "LCD_interface.h"
#include "LCD_interface.h"
#include "TWI_interface.h"
#include "EEPROM_interface.h"
#include "DIO_interface.h"
#include "MainConfig.h"
#include "LED_Interface.h"
#include "LED_Config.h"
#include "ADC_interface.h"

#define F_CPU 1000000UL			/* Define frequency here its 8MHz */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "UART_interface.h"

#define SELECT_LAMP1            '1'
#define SELECT_LAMP2            '2'
#define SELECT_LAMP3            '3'
#define SELECT_MOREOP           '4'
#define SELECT_LAMP4            '5'
#define SELECT_LAMP5            '6'
#define SELECT_TV               '8'
#define SELECT_AIR_CONDITIONING '7'

#define SELECT_LAMP_ON      '*'
#define SELECT_LAMP_OFF		'0'




void AdminDisplay(void);
u8 start_messsage=0;
u8 valu = 0;
u8 Value;
u8 pass_size=4;
u8 Guestcounter=0;
u8 loginMode=0;
u8 ui8ComparePass(const u8* pass1,const u8* pass2,const u8 size);
u8 NumOfTrail;
u8 SetValue[2];
u16 DigitalValue;
u8 analoge;
u8 temp;
u8 temp_2;
u8 temp_sensor_reading;
 u8 temprature;

int main(void)
{
    LCD_init();
	KPD_init();
	EEPROM_init();
	DIO_setPinDeriction(DIO_PORTA,DIO_PIN1,DIO_PIN_INPUT);
	
	ADC_init();
	
	DIO_setPinDeriction(DIO_PORTC,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_setPinDeriction(DIO_PORTC,DIO_PIN2,DIO_PIN_INPUT);

	LCD_writeString("Welcome to smart");
	_delay_ms(100);
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_writeString("Home System");
	_delay_ms(100);
	LCD_clear();
	_delay_ms(100);
	LCD_writeString("1>ADMIN 2>GUEST");
	
	
/*	
					************** Let user choose Mode ************						*/
valu=0;
while(valu==0)
	{
		KPD_getValue(&valu);
	}
	
/*						************** In case of Guest Mode ************						*/

if(valu=='2'){
	
/*						************** Enter password for first time ************				*/	 
	if(EEPROM_readByte(GUEST_PASSWORD_ADDRESS)!=GUEST_PASSWORD_ADDRESS_CHECK)	
	{
		LCD_writeString("Setup");
		_delay_ms(10);
		LCD_clear();
		LCD_writeString("New Pass:");
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	
	u8 pass_counter=0;
	u8 Password[4]={(u8)0xFF,(u8)0xFF,(u8)0xFF,(u8)0xFF};
		
		while(pass_counter<4)
		{
			valu=0;
			while(valu==0)
			{
				KPD_getValue(&valu);
			}
			Password[pass_counter]=valu;
			LCD_sendChar(valu);
			_delay_ms(10);
			LCD_goToSpecificPosition(LCD_LINE_TWO,pass_counter);
			LCD_sendChar('*');
			_delay_ms(100);
			pass_counter++;
		}
		EEPROM_writeByte(GUEST_PASSWORD,Password);
		EEPROM_writeByte(GUEST_PASSWORD_ADDRESS,GUEST_PASSWORD_ADDRESS_CHECK);
		LCD_clear();
		LCD_writeString("Pass Saved");
		_delay_ms(100);
		LCD_clear();
	}
	else
	{
		u8 Blocked_Mode=EEPROM_readByte(BLOCKED_MODE_ACTIVATE);
	}
	
    while (1) 
    {
		valu =0;
		u8 SelectMenu;
		LCD_clear();
		LCD_writeString("Welcome to");
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_writeString("User Mode");
		_delay_ms(1000);
		LCD_clear();
		LCD_writeString("Write pass");
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		u8 pass_counter=0;
		u8 GUEST_Password[4]={(u8)0xFF,(u8)0xFF,(u8)0xFF,(u8)0xFF};
	

	
		while(pass_counter<4)
		{
			
			valu=0;
			while(valu==0)
			{
				KPD_getValue(&valu);
			}
			GUEST_Password[pass_counter]=valu;
			LCD_sendChar(valu);
			_delay_ms(10);
			LCD_goToSpecificPosition(LCD_LINE_TWO,pass_counter);
			LCD_sendChar('*');
			_delay_ms(100);
			pass_counter++;
		}
		EEPROM_writeByte(GUEST_PASSWORD_CHECKED,GUEST_Password);
		_delay_ms(100);
		LCD_clear();
		u8 result =ui8ComparePass(EEPROM_readByte(GUEST_PASSWORD_CHECKED),EEPROM_readByte(GUEST_PASSWORD),4);
		
		if(result==1)
		{
		LCD_writeString("Login..");
		_delay_ms(100);
		LCD_clear();
		Repeat:
		LCD_writeString("1>Lamp1 2>Lamp2");
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_writeString("3>Lamp3 4>MoreOP");
		valu=0;
		while(valu == 0){
			KPD_getValue(&valu);
			}
			
			switch(valu)
			{
				case SELECT_LAMP1:
					LCD_clear();
					LCD_writeString("ON>ON 0>OFF");
					_delay_ms(20);
					valu=0;
					while(valu == 0){
					KPD_getValue(&valu);
					};
					LCD_clear();
					if (valu == SELECT_LAMP_ON )
					{
						LED_on(LED1_REG,LED1_PIN);
						LCD_writeString("LED1 ON...");
						_delay_ms(2000);
						LCD_clear();
						goto Repeat;
					}
					else if (valu==SELECT_LAMP_OFF)
					{
						LED_off(LED1_REG,LED1_PIN);
						LCD_writeString("LED1 Off");
						_delay_ms(2000);
						LCD_clear();
						goto Repeat;
					}
				
				break;
				
				case SELECT_LAMP2:
				LCD_clear();
				LCD_writeString("ON>ON 0>OFF");
				_delay_ms(20);
				valu=0;
				while(valu == 0){
					KPD_getValue(&valu);
				};
				LCD_clear();
				if (valu == SELECT_LAMP_ON )
				{
					LED_on(LED2_REG,LED2_PIN);
					LCD_writeString("LED2 ON...");
					_delay_ms(200);
					LCD_clear();
					goto Repeat;
				}
				else if (valu==SELECT_LAMP_OFF)
				{
					LED_off(LED2_REG,LED2_PIN);
					LCD_writeString("LED2 Off");
					_delay_ms(200);
					LCD_clear();
					goto Repeat;
				}
				
				break;
				
				case SELECT_LAMP3:
				LCD_clear();
				LCD_writeString("ON>ON 0>OFF");
				_delay_ms(20);
				valu=0;
				while(valu == 0){
					KPD_getValue(&valu);
				};
				LCD_clear();
				if (valu == SELECT_LAMP_ON )
				{
					LED_on(LED3_REG,LED3_PIN);
					LCD_writeString("LED3 ON...");
					_delay_ms(200);
					LCD_clear();
					goto Repeat;
				}
				else if (valu==SELECT_LAMP_OFF)
				{
					LED_off(LED3_REG,LED3_PIN);
					LCD_writeString("LED3 Off");
					_delay_ms(200);
					LCD_clear();
					goto Repeat;
				}
				
				break;
				case SELECT_MOREOP:
				SelectMenu = 4;
				LCD_clear();
				LCD_writeString("5>Lamp4 6>Lamp5");
				LCD_goToSpecificPosition(LCD_LINE_TWO,0);
				LCD_writeString("7>AirCond ");
				break;
			}
			valu =0;
			while(valu == 0){
				KPD_getValue(&valu);
			}
			
			switch(valu)
			{
				case SELECT_LAMP4:
				LCD_clear();
				LCD_writeString("ON>ON 0>OFF");
				_delay_ms(20);
				valu=0;
				while(valu == 0){
					KPD_getValue(&valu);
				};
				LCD_clear();
				if (valu == SELECT_LAMP_ON )
				{
					LED_on(LED4_REG,LED4_PIN);
					LCD_writeString("LED4 ON...");
					_delay_ms(200);
					LCD_clear();
					goto Repeat;
				}
				else if (valu==SELECT_LAMP_OFF)
				{
					LED_off(LED4_REG,LED4_PIN);
					LCD_writeString("LED4 Off");
					_delay_ms(200);
					LCD_clear();
					goto Repeat;
				}
				
				
				
				break;
				case SELECT_AIR_CONDITIONING:
				Repeat2:
				temprature==0;
				LCD_clear();
				
				LCD_writeString("1>SET 2>ON 3>OFF");
				_delay_ms(20);
				valu=0;
				while(valu == 0){
					KPD_getValue(&valu);
				};
				
				switch(valu){
					case '1':
					
					while (temprature==0)
					{
						valu=0;
						LCD_clear();
						LCD_writeString("Set Temp:__");
						LCD_goToSpecificPosition(LCD_LINE_ONE,11);
						_delay_ms(200);
						while(valu == 0){
							KPD_getValue(&valu);
						};
						_delay_ms(200);
						LCD_sendChar(valu);
						temp=valu-'0';
						
						valu=0;
						while(valu == 0){
							KPD_getValue(&valu);
						};
						_delay_ms(200);
						LCD_sendChar(valu);
						temp_2=valu-'0';
						
						temprature=(temp*10)+temp_2;
						
						_delay_ms(2000);
						LCD_clear();
						LCD_writeString("Temp set");
						_delay_ms(2000);
						LCD_clear();
						
						goto Repeat2;
					}
					
					case '2':
					
					LCD_clear();
					ADC_getDigital(ADC_CHANNEL1,  &DigitalValue);
					analoge=((DigitalValue*5000UL)/1024);
					analoge=analoge/10;
					if(analoge>temprature)
					{
						_delay_ms(2000);
						LCD_writeString("AIR CON IS ON");
						_delay_ms(300);
						LCD_clear();
					
					_delay_ms(200);
					goto Repeat2;
					}
					
					
					else if(analoge<temprature)
					{
						LCD_writeString("AIR CON Fan Mode");
						_delay_ms(3000);
						LCD_clear();
						
						_delay_ms(200);
						goto Repeat2;
					}
					
				}
					
				
				
				
				
				
				break;
			
			}
			
			
		}
		else if(result==0)
		{
			LCD_writeString("wrong pass!");
			_delay_ms(20000);
			LCD_clear();
			LCD_writeString("Try Again!");
			static NumOfTrail;
			NumOfTrail++;
			if(NumOfTrail==3)
			{
				DIO_setPinDeriction(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT);
				DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
				
				
			}
		}
	
	}
}


else if(valu==ADMIN)
{
	LCD_clear();
	LCD_writeString("Welcome to");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_writeString("ADMIN Mode");
	char c;
	UART_init(9600);
	Repeat1:
	UART_SendString("1>LAMP1 2>LAMP2 3>LAMP3 4>MORE");
	
	while(1)
	{
		
		c=UART_RxChar();
		
		
		switch(c)
		{
			case '1':
					c=UART_RxChar();
					UART_SendString("1>ON 0>OFF");
					switch(c){
					case '1':
						LED_on(LED1_REG,LED1_PIN);
						LCD_writeString("LED1 ON...");
						_delay_ms(2000);
						LCD_clear();
						goto Repeat1;
					
					break;
					case '0':
					
						LED_off(LED1_REG,LED1_PIN);
						LCD_writeString("LED1 OFF...");
						_delay_ms(2000);
						LCD_clear();
						goto Repeat1;
					break;
					}
					
			break;
				
			break;
				
			case '2':
			c=UART_RxChar();
			UART_SendString("1>ON 0>OFF");
			switch(c){
				case '1':
				LED_on(LED2_REG,LED2_PIN);
				LCD_writeString("LED2 ON...");
				_delay_ms(2000);
				LCD_clear();
				goto Repeat1;
				
				break;
				case '0':
				
				LED_off(LED2_REG,LED2_PIN);
				LCD_writeString("LED2 OFF...");
				_delay_ms(2000);
				LCD_clear();
				goto Repeat1;
				break;
			}
			
			case '3':
			c=UART_RxChar();
			UART_SendString("1>ON 0>OFF");
			switch(c){
				case '1':
				LED_on(LED3_REG,LED3_PIN);
				LCD_writeString("LED3 ON...");
				_delay_ms(2000);
				LCD_clear();
				goto Repeat1;
				
				break;
				case '0':
				
				LED_off(LED3_REG,LED3_PIN);
				LCD_writeString("LED3 OFF...");
				_delay_ms(2000);
				LCD_clear();
				goto Repeat1;
				break;
			}
			
			case '4':
			c=UART_RxChar();
			UART_SendString("5>LAMP4 6>DOOR 7>AIRCon");
			switch(c){
				case '5':
				c=UART_RxChar();
				UART_SendString("1>ON 0>OFF");
				switch(c){
					case '1':
					LED_on(LED4_REG,LED4_PIN);
					LCD_writeString("LED4 ON...");
					_delay_ms(2000);
					LCD_clear();
					goto Repeat1;
					
					break;
					case '0':
					
					LED_off(LED4_REG,LED4_PIN);
					LCD_writeString("LED4 OFF...");
					_delay_ms(2000);
					LCD_clear();
					goto Repeat1;
					break;
				}
				break;
				
				case '6':
				c=UART_RxChar();
				UART_SendString("1>Open 0>close");
				switch(c){
					case '1':
					DOOR_Open();
					LCD_writeString("DOOR OPEN...");
					_delay_ms(2000);
					LCD_clear();
					goto Repeat1;
					
					break;
					case '0':
					LCD_writeString("DOOR CLOSE...");
					DOOR_Close();
					_delay_ms(2000);
					LCD_clear();
					goto Repeat1;
					break;
				}
				break;
				
			}
				
			}
			
			
			
			
 
	/********		*/
 }
}
}







u8 ui8ComparePass(const u8* pass1,const u8* pass2,const u8 size)
{
	u8 pin_counter=0;//the offset of the character of the pin
	u8 ret_value =1;
	while (pin_counter<size)//loop till the pin is fully entered
	{
		if (*(pass1+pin_counter)!=*(pass2+pin_counter))//if the two characters of the entered pin and the stored pin are not equal
		{
			ret_value=0;//returns false that means the two PINs are not equal
			break;//break the loop
		}
		pin_counter++;//increase thee offset by one
	}
	return ret_value;//returns false that means the two PINs are equal since all characters of the PINs are equal
}






	
	
	
	
	

	//	if(start_messsage==0)
		//{
			//LCD_writeString("Select Mode: ");
		//	LCD_clear();
		//	LCD_writeString("Guest");
		//	LCD_goToSpecificPosition(LCD_LINE_TWO ,0);
		//	while (valu==0)
		//	{
		//		KPD_getValue(&valu);
		//		Value=valu;
				
		//	}
			//LCD_sendChar(Value);
		//	start_messsage++;
	//	}
		
//	if (valu =='0')
//		{
//			LCD_clear();
//			LCD_goToSpecificPosition(LCD_LINE_ONE ,0);
	//		LCD_writeString("Enter Admin Password: ");
	//		LCD_goToSpecificPosition(LCD_LINE_TWO ,0);
			
		//	if(valu !='*')
			//{
				//KPD_getValue(valu);
				//Value= valu;
			//	GuestPassword[NumberOfDigit]=Value;
				//LCD_goToSpecificPosition(LCD_LINE_TWO,NumberOfDigit);
				//LCD_sendChar(valu);
				//NumberOfDigit++;
		//	}
			
			 
			//else
		//	{
				
			//}
		//}
		//else if (valu == '1')
		//{
		//	LCD_writeString("Enter Guest Password: ");
			//GuestDisplay();
		//}
		//else
		//{
			
	//	}
		
//    }
//}

//void AdminDisplay(void)
//{
	
	//LCD_writeString("1>Room1");
	//LCD_sendCmnd(0x88);
//	LCD_writeString("2>Room2");
	//LCD_sendCmnd(0xc0);
//	LCD_writeString("3>Room3");
//	LCD_sendCmnd(0xc8);
//	LCD_writeString("4>More");
//}

//void GuestDisplay(void)
//{
	//LCD_writeString("1>Room1");
	//LCD_sendCmnd(0x88);
//	LCD_writeString("2>Room2");
//	LCD_sendCmnd(0xc0);
//	LCD_writeString("3>Room3");
	//LCD_sendCmnd(0xc8);
	//LCD_writeString("4>More");



