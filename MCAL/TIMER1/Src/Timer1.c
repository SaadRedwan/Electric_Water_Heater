/*
 * File: Timer1.c
 * Author: Eng_Saad_Redwan
 */

#include "Timer1.h"


void TIMER1_EnableInterrupt(void)
{
	#if (TIMER1_OPERATION_MODE == TIMER1_MODE_INTERVAL)
	SET_BIT(TIMER1_TIMSK_REG,TIMER1_INTERVAL_INT_ENABLE_BIT_NO);
	#endif
}
void TIMER1_DisableInterrupt(void)
{
	#if (TIMER1_OPERATION_MODE == TIMER1_MODE_INTERVAL)
	CLEAR_BIT(TIMER1_TIMSK_REG,TIMER1_INTERVAL_INT_ENABLE_BIT_NO);
	#endif
}


