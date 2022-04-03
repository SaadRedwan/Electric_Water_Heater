/*
 * File: Eeprom24C16.h
 * Author: Eng_Saad_Redwan
 */


#ifndef EEPROM_H_
#define EEPROM_H_

#include "Std_Types.h"
#include "I2C.h"
#include <util/delay.h>

void EEPROM24C16_Init(void);
void EEPROM24C16_Write_Byte(u16 Address , u8 Data);
u8 EEPROM24C16_Read_Byte(u16 Address);


#endif
