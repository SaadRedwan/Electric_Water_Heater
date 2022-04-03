 /*
 * File: Timer1.h
 * Author: Eng_Saad_Redwan
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "Bit_Math.h"
#include "Timer1_Cfg.h"
#include "Timer1_Private.h"

/*	TIMER1 Operation Modes	*/
#define TIMER1_INTERVAL_MODE				((u8)0<<3)


/*	TIMER1 Clock Select Prescaler	*/

#define TIMER1_CS_1024_PRESCALER			((u8)5<<0)


/*	Timer1 Interrupt Enable	Bits */
#define TIMER1_INTERVAL_INT_ENABLE_BIT_NO		(1)



void TIMER1_EnableInterrupt(void);
void TIMER1_DisableInterrupt(void);

#endif  /* TIMER1_H_ */
