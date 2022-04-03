/*
 * File: Eeprom24C16.c
 * Author: Eng_Saad_Redwan
 */



#include "Eeprom24C16.h"
#include "Led_Interface.h"

void EEPROM24C16_Init(void){
	I2C_InitMaster();
}

/*	byte num from 0----2047	*/
void EEPROM24C16_Write_Byte(u16 Address , u8 Data){
//	Led_Toggle(LED2);
	I2C_ERROR_STATUS State = NOK;
	u8 pageNum = Address/256;
	u8 byteNum = Address%256;
	State = I2C_StartCondition();
	if(State == OK){
		State = I2C_Master_Send_Slave_Address_With_Write(0x50 | (pageNum));
		if(State == OK){
			State = I2C_Maste_Write_Byte_To_Slave((u8)byteNum);
			if(State == OK){
				State = I2C_Maste_Write_Byte_To_Slave(Data);
				if(State == OK){
					I2C_StopCondition();
				}
			}
		}
	}
	_delay_ms(5);	/*	Time For A Byte To Be Physically Written	*/
//	Led_Toggle(LED2);
}

/*	byte num from 0----2047	*/
u8 EEPROM24C16_Read_Byte(u16 Address){
//	Led_Toggle(LED2);
	u8 LOC_u8Data;
	u8 pageNum = Address/256;
	u8 byteNum = Address%256;
	I2C_ERROR_STATUS State = NOK;
	State = I2C_StartCondition();
	if(State == OK){
		State = I2C_Master_Send_Slave_Address_With_Write(0x50 | (pageNum));
		if(State == OK){
			State = I2C_Maste_Write_Byte_To_Slave((u8)byteNum);
			if(State == OK){
				State = I2C_RepeatedStart();
				if(State == OK){
					State = I2C_Master_Send_Slave_Address_With_Read(0x50 | (pageNum));
					if( State == OK ){
						State = I2C_Master_Read_Byte_From_Slave_NACK(&LOC_u8Data);
						if(State == OK){
							I2C_StopCondition();
						}
					}
				}
			}
		}
	}
//	Led_Toggle(LED2);
	return LOC_u8Data;
}
