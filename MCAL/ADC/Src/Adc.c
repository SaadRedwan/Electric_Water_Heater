/*
 * File: Adc.c
 * Author: Eng_Saad_Redwan
 */
#include "Adc_Interface.h"

void adcInit(void)
{
	ADC_ADMUX_REG|=(AVCC5V_REF<<6);
	ADC_ADCSRA_REG=(ADC_ENABLE)|(ADCPS_128);
}
u16 adcRead(adc_ChannelID chnlNo)
{
    u16 result;
    ADC_ADMUX_REG = (ADC_ADMUX_REG & 0xF8)|(chnlNo);
    //SET_BIT(ADC_ADCSRA_REG,ADSC_BIT_NO);
    ADC_ADCSRA_REG|=(ADC_START_CONVERSION);

 	while(!(CHECK_BIT(ADC_ADCSRA_REG,ADIF_BIT_NO)))
 		  {
 		  	  /*	Do Nothing	*/
 		  	  	  ;
 		  }
 	SET_BIT(ADC_ADCSRA_REG,ADIF_BIT_NO);

 	result=(ADC_ADCL_REG|(ADC_ADCH_REG<<8));
 	return result;
}
