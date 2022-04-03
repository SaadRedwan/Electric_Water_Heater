/*
 * File: Eeprom_Interface.h
 * Author: Eng_Saad_Redwan
 */

#ifndef EEPROM_H
#define EEPROM_H


#include "Std_Types.h"
#include "Eeprom_Private.h"


void EEPROM_Write(u16 address,u8 data);
u8 EEPROM_Read(u16 address);



#endif  /* EEPROM_H */
