/*
 * File: SSD.c
 * Author: Eng_Saad_Redwan
 */

#include "SSD_Interface.h"

void SSD_Init(void)
{
	/*	Configure Digit1 Enable Pin as Output	*/
	Dio_ConfigChannel(SSD_DIGIT1_EN_PORT,SSD_DIGIT1_EN_CHANNEL,OUTPUT);
	/*	Configure Digit2 Enable Pin as Output	*/
	Dio_ConfigChannel(SSD_DIGIT2_EN_PORT,SSD_DIGIT2_EN_CHANNEL,OUTPUT);
	/*	Configure 4-bit data Pins as Output	*/
	Dio_ConfigChannels(SSD_DATA_PORT, SSD_MASK, OUTPUT);
}
void SSD_Display(u8 num)
{
	u8 digit1=num%10<<4;
	u8 digit2=num/10<<4;
	/* Enable Digit One	*/
	Dio_WriteChannel(SSD_DIGIT1_EN_PORT, SSD_DIGIT1_EN_CHANNEL,STD_HIGH);
	/* Disable Digit Two*/
	Dio_WriteChannel(SSD_DIGIT2_EN_PORT, SSD_DIGIT2_EN_CHANNEL,STD_LOW);
	/*	Write Digit one value to SSD Data Lines	*/
	Dio_WriteChannels(SSD_DATA_PORT, digit1, SSD_MASK);
	_delay_ms(1);
 	/* Disable Digit One	*/
	Dio_WriteChannel(SSD_DIGIT1_EN_PORT, SSD_DIGIT1_EN_CHANNEL,STD_LOW);
	/* Enable Digit Two	*/
	Dio_WriteChannel(SSD_DIGIT2_EN_PORT, SSD_DIGIT2_EN_CHANNEL,STD_HIGH);
	/*	Write Digit Two value to SSD Data Lines	*/
	Dio_WriteChannels(SSD_DATA_PORT, digit2, SSD_MASK);
	_delay_ms(1);
	/* Disable Digit One	*/
	Dio_WriteChannel(SSD_DIGIT1_EN_PORT, SSD_DIGIT1_EN_CHANNEL,STD_LOW);
	/* Disable Digit Two	*/
	Dio_WriteChannel(SSD_DIGIT2_EN_PORT, SSD_DIGIT2_EN_CHANNEL,STD_LOW);
}
void SSD_DelayWithDisaplayMS(u8 num,u16 delay)
{
	u16 count=0;
	for (count=0;count<delay;count+=3)
	{
		SSD_Display(num);
		_delay_ms(1);
	}
}
