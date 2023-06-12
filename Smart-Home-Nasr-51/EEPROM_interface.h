/*
 * EEPROM_interface.h
 *
 * Created: 5/13/2023 11:28:36 AM
 *  Author: AMIT
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


#define EEPROM_FIXED_ADDRESS          0x50


void EEPROM_init     (void);
void EEPROM_writeByte(u16 byteAddress, u8 data);
u8   EEPROM_readByte (u16 byteAddress);


#endif /* EEPROM_INTERFACE_H_ */