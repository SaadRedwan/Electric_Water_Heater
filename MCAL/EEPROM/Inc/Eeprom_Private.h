/*
 * File: Eeprom_Interface.h
 * Author: Eng_Saad_Redwan
 */

#ifndef EEPROM_PRIVATE_H
#define EEPROM_PRIVATE_H



#define EEPROM_ARH_REG				(*(volatile u8*)0x3F)
#define EEPROM_ARL_REG				(*(volatile u8*)0x3E)
#define EEPROM_DR_REG				(*(volatile u8*)0x3D)
#define EEPROM_CR_REG				(*(volatile u8*)0x3C)
#define EERE				(0u)
#define EEWE             	(1u)
#define EEMWE				(2u)



#endif  /* EEPROM_PRIVATE_H */
