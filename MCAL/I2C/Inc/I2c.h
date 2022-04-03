 /*
 * File: I2C.h
 * Author: Eng_Saad_Redwan
 */


#ifndef I2C_H_
#define I2C_H_

#include "Std_Types.h"
#include "Bit_Math.h"
#include "I2C_Private.h"
typedef enum{

	NOK,  //NOK = 0
	OK    //OK = 1

}I2C_ERROR_STATUS;

void I2C_InitMaster(void);
void I2C_InitSlave(void);
I2C_ERROR_STATUS I2C_StartCondition(void);
I2C_ERROR_STATUS I2C_RepeatedStart(void);//New
void I2C_StopCondition(void);
I2C_ERROR_STATUS I2C_Master_Send_Slave_Address_With_Write(u8 Address);
I2C_ERROR_STATUS I2C_Master_Send_Slave_Address_With_Read(u8 Address);
I2C_ERROR_STATUS I2C_Maste_Write_Byte_To_Slave(u8 Data);
I2C_ERROR_STATUS I2C_Master_Read_Byte_From_Slave_NACK(u8 * ptr);//New
I2C_ERROR_STATUS I2C_Slave_Check_About_His_Addr_With_Write(void);
I2C_ERROR_STATUS I2C_Slave_Check_About_His_Addr_With_Read(void);//New
I2C_ERROR_STATUS I2C_Slave_Read_Byte_From_Master(u8 * ptr);
I2C_ERROR_STATUS I2C_Slave_Write_Byte_To_Master(u8 Data);//New


#endif /* I2C_H_ */
