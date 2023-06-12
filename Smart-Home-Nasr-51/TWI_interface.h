/*
 * TWI_interface.h
 *
 * Created: 5/13/2023 8:59:20 AM
 *  Author: AMIT
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_


void TWI_initMaster           (void);
void TWI_sendStartCondition   (void);
void TWI_sendRepStartCondition(void);
void TWI_sendStopCondition    (void);
void TWI_sendSlaveAddWithWrite(u8 slaveAdd);
void TWI_sendSlaveAddWithRead (u8 slaveAdd);
void TWI_sendMasterDataByte   (u8 data);
u8   TWI_recieveMasterDataByte(void);


#endif /* TWI_INTERFACE_H_ */