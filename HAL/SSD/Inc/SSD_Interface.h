/*
 * File: SSD_Interface.h
 * Author: Eng_Saad_Redwan
 */


#ifndef HAL_SSD_INC_SSD_INTERFACE_H_
#define HAL_SSD_INC_SSD_INTERFACE_H_

#include "Dio_Interface.h"
#include "SSD_Cfg.h"
#include "util/delay.h"

void SSD_Init(void);
void SSD_Display(u8 num);
void SSD_DelayWithDisaplayMS(u8 num,u16 delay);

#endif /* HAL_SSD_INC_SSD_INTERFACE_H_ */


