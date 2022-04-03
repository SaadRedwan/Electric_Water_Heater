/*
 * File: Timer1_Private.h
 * Author: Eng_Saad_Redwan
 */

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#include "Std_Types.h"

#define TIMER1_TCCR1A_REG			(*(volatile u8*)0x4F)
#define TIMER1_TCCR1B_REG			(*(volatile u8*)0x4E)
#define TIMER1_TCNT1_REG			(*(volatile u16*)0x4C)
//#define TIMER1_TCNT1H_REG			(*(volatile u8*)0x4D)
//#define TIMER1_TCNT1L_REG			(*(volatile u8*)0x4C)
#define TIMER1_TIMSK_REG			(*(volatile u8*)0x59)


#define TIMER1_MODE_NONE            		(0)
#define TIMER1_MODE_INTERVAL             	(1)

#endif  /* TIMER1_PRIVATE_H_ */
