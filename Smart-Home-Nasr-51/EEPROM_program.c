/*
 * EEPROM_program.c
 *
 * Created: 5/13/2023 11:28:23 AM
 *  Author: AMIT
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "TWI_interface.h"

/* HAL */
#include "EEPROM_interface.h"


void EEPROM_init(void)
{
	TWI_initMaster();
}


void EEPROM_writeByte(u16 byteAddress, u8 data)
{
	u8 address = (EEPROM_FIXED_ADDRESS | (byteAddress>>8));
	
	// Send start condition
	TWI_sendStartCondition();
	
	// Send slave address with write operation
	TWI_sendSlaveAddWithWrite(address);
	
	// Send byte address
	TWI_sendMasterDataByte((u8)byteAddress);
	
	// Send byte data
	TWI_sendMasterDataByte(data);
	
	// Send stop condition
	TWI_sendStopCondition();
	
	_delay_ms(5);
}


u8 EEPROM_readByte(u16 byteAddress)
{
	u8 returnedData;
	
	u8 address = (EEPROM_FIXED_ADDRESS | (byteAddress>>8));
	
	// Send start condition
	TWI_sendStartCondition();
	
	// Send slave address with write operation
	TWI_sendSlaveAddWithWrite(address);
	
	// Send byte address
	TWI_sendMasterDataByte((u8)byteAddress);
	
	// Send repeated start
	TWI_sendRepStartCondition();
	
	// Send slave address with read operation
	TWI_sendSlaveAddWithRead(address);
	
	// Read byte data
	returnedData = TWI_recieveMasterDataByte();
	
	// Send stop condition
	TWI_sendStopCondition();
	
	_delay_ms(5);
	
	return returnedData;
}