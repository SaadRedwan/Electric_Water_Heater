/*
 * File: Button.c
 * Author: Eng_Saad_Redwan
 */

#include "Dio_Interface.h"
#include "Button_Interface.h"

void Button_Init(void)
{
	Dio_ConfigChannel(BUTTON0_PORT, BUTTON0_CHANNEL, INPUT);
	Dio_ConfigChannel(BUTTON1_PORT, BUTTON1_CHANNEL, INPUT);
	Dio_ConfigChannel(BUTTON2_PORT, BUTTON2_CHANNEL, INPUT);
}
boolean Button_Pressed(Button_ID button)
{
	boolean loc_ButtonPressed=FALSE;
	switch (button)
	{
	case BUTTON0:
#if (BUTTON0_CONNECTION == PULL_DOWN)
		if (Dio_ReadChannel(BUTTON0_PORT, BUTTON0_CHANNEL) == STD_HIGH)
		{
			loc_ButtonPressed = TRUE;
		}
#elif (BUTTON0_CONNECTION == PULL_UP)
		if (Dio_ReadChannel(BUTTON0_PORT, BUTTON0_CHANNEL) == STD_LOW)
		{
			loc_ButtonPressed = TRUE;
		}
#endif
		break;
	case BUTTON1:
#if (BUTTON1_CONNECTION == PULL_DOWN)
		if (Dio_ReadChannel(BUTTON1_PORT, BUTTON1_CHANNEL) == STD_HIGH)
		{
			loc_ButtonPressed = TRUE;
		}
#elif (BUTTON1_CONNECTION == PULL_UP)
		if (Dio_ReadChannel(BUTTON1_PORT, BUTTON1_CHANNEL) == STD_LOW)
		{
			loc_ButtonPressed = TRUE;
		}
#endif
		break;
	case BUTTON2:
#if (BUTTON2_CONNECTION == PULL_DOWN)
		if (Dio_ReadChannel(BUTTON2_PORT, BUTTON2_CHANNEL) == STD_HIGH)
		{
			loc_ButtonPressed = TRUE;
		}
#elif (BUTTON2_CONNECTION == PULL_UP)
		if (Dio_ReadChannel(BUTTON2_PORT, BUTTON2_CHANNEL) == STD_LOW)
		{
			loc_ButtonPressed = TRUE;
		}
#endif
		break;
	}
	return loc_ButtonPressed;
}
