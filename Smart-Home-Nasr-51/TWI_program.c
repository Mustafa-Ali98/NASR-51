/*
 * TWI_program.c
 *
 * Created: 5/13/2023 8:59:10 AM
 *  Author: AMIT
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "TWI_interface.h"


void TWI_initMaster(void)
{
	// Set Prescaller = 1 >> Set Freq. = 400KHZ
	TWBR = 12;
	CLR_BIT(TWSR,0);
	CLR_BIT(TWSR,1);
	
	// Enable ACK
	SET_BIT(TWCR,6);
	
	// Enable TWI
	SET_BIT(TWCR,2);
}


void TWI_sendStartCondition(void)
{
	// Send Start Condition
	SET_BIT(TWCR,5);

    // Clear flag to start current job
	SET_BIT(TWCR,7);
	
	// Wait for the flag
	while( 0 == GET_BIT(TWCR,7));
	
	// Check ACK = SC ACK
	while((TWSR & 0xF8) != 0x08);
}


void TWI_sendRepStartCondition(void)
{
	// Send Start Condition
	SET_BIT(TWCR,5);

    // Clear flag to start current job
	SET_BIT(TWCR,7);
	
	// Wait for the flag
	while( 0 == GET_BIT(TWCR,7));
	
	// Check ACK = Repeated SC ACK
	while((TWSR & 0xF8) != 0x10);
}


void TWI_sendStopCondition(void)
{
	// Send Stop Condition
	SET_BIT(TWCR,4);
	
	// Clear flag to start current job
	SET_BIT(TWCR,7);
}


void TWI_sendSlaveAddWithWrite(u8 slaveAdd)
{
	// Send slave address
	TWDR = slaveAdd<<1;
	
	// Select write operation
	CLR_BIT(TWDR,0);
	
	// Clear SC bit
	CLR_BIT(TWCR,5);
	
	// Clear flag to start current job
	SET_BIT(TWCR,7);
	
	// Wait for the flag
	while(0 == GET_BIT(TWCR,7));
	
    // Check ACK = Master transmit ( slave address + Write request ) ACK
	while((TWSR & 0xF8) != 0x18);
}


void TWI_sendSlaveAddWithRead(u8 slaveAdd)
{
	// Send slave address
	TWDR = slaveAdd<<1;
	
	// Select read operation
	SET_BIT(TWDR,0);
	
	// Clear SC bit
	CLR_BIT(TWCR,5);
	
	// Clear flag to start current job
	SET_BIT(TWCR,7);
	
	// Wait for the flag
	while(0 == GET_BIT(TWCR,7));
	
   	// Check ACK = Master transmit ( slave address + Read request ) ACK
	while((TWSR & 0xF8) != 0x40);
}


void TWI_sendMasterDataByte(u8 data)
{
	// Write Data into data register
	TWDR = data;
	
	// Clear flag to start current job
	SET_BIT(TWCR,7);
	
	// Wait for the flag
	while(0 == GET_BIT(TWCR,7));
	
	// Check ACK = Master transmit data ACK
	while((TWSR & 0xF8) != 0x28);
}


u8 TWI_recieveMasterDataByte(void)
{
	// Clear flag to start current job
	SET_BIT(TWCR,7);
	
	// Wait for the flag
	while(0 == GET_BIT(TWCR,7));
	
	// Check ACK = Master received data with ACK
	while((TWSR & 0xF8) != 0x50);
	
	// Read Data from data register
	return TWDR;
}