/*
 * File: Button_Interface.h
 * Author: Eng_Saad_Redwan
 */

#ifndef HAL_BUTTON_INC_BUTTON_INTERFACE_H_
#define HAL_BUTTON_INC_BUTTON_INTERFACE_H_
#include "Std_Types.h"
#include "Button_Types.h"
#include "Button_Cfg.h"

void Button_Init(void);
boolean Button_Pressed(Button_ID button);

#endif /* HAL_BUTTON_INC_BUTTON_INTERFACE_H_ */
