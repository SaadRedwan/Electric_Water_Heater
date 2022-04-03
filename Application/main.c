/*****************************************
 *  File: main.c
 *  Author: Eng_Saad_Redwan
 ****************************************/

#include "avr/io.h"
#include <avr/interrupt.h>
#include "Dio_Interface.h"
#include "Adc_Interface.h"
#include "GlblInterrupt_Interface.h"
#include "Timer0.h"
#include "Timer1.h"
#include "Eeprom_Interface.h"
#include "Button_Interface.h"
#include "Led_Interface.h"
#include "SSD_Interface.h"
#include "Eeprom24C16.h"
#include "Configs.h"




#define INIT_TEMP                 60        //Initial temperature
#define TIMER1_PRELOAD            49911     //for 1 second at 16 MHz
#define TIMER0_PRELOAD            88        //for 100ms every 98 overflows
#define NUM_OF_SENSING_TEMP      10         //number of sensing temperatures

/*volatile because it changed by Interrupts*/
volatile boolean ON_OFF_STATE=FALSE;            //show status of Electric Water Heater ON or OFF
volatile boolean SETTING_MODE_STATE=FALSE;      //show status of Sitting mode  ON or OFF
volatile boolean HEATING_ELEMENT_STATE=FALSE;   //show status of Heating element  ON or OFF
volatile boolean COOLING_ELEMENT_STATE=FALSE;   //show status of cooling element  ON or OFF

/*volatile because it changed by Interrupts*/
volatile u8 AVG_TEMP_SENSING=0;
volatile f64 SENSING_TEMP_LAST10[NUM_OF_SENSING_TEMP]={0};

/*using in loop of sensing temperature as index*/
u8 ind=0;
/*variable for setting temperature*/
u8 SITTING_TEMP=INIT_TEMP;


/*counter of overflows to achieve time of 5 second*/
volatile u8 TIME_5S_COUNTER=0;
/*counter of overflows to achieve time of 100ms*/
volatile u8 TIME_100mS_COUNTER=0;

/*interrupt occur every 1 second*/
ISR(TIMER1_OVF_vect)
{
	DisableAllInterrupts();
	/*for blinking SSD with setting temperature by 1 second if the Electric Water Heater is on the setting mode*/
	if(SETTING_MODE_STATE==TRUE)
	{
		SSD_DelayWithDisaplayMS(SITTING_TEMP,100);
	}
	TIME_5S_COUNTER++;
	if(TIME_5S_COUNTER==5)
	{
		/*save the last setting temperature*/
		EEPROM24C16_Write_Byte(0,SITTING_TEMP);
//		EEPROM_Write(0,SITTING_TEMP);
		/*put the Electric Water Heater out of setting mode*/
		SETTING_MODE_STATE=FALSE;
		/*makes value of counter for 5 second interrupt equals zero*/
		TIME_5S_COUNTER=0;
	}
	/*set preload of timer1 with TIMER1_PRELOAD to make timer1 interrupt occur every 1 second*/
	TCNT1 = TIMER1_PRELOAD;
	EnableAllInterrupts();
}

ISR(TIMER0_OVF_vect)
{
	DisableAllInterrupts();
	TIME_100mS_COUNTER++;
	/*every 100ms senses water temperature and update average sensed temperature*/
	if(TIME_100mS_COUNTER==98)
	{
		u16 adcResult;
		double temp;
		adcResult=adcRead(ADC_CHANNEL1);
		temp=4.8*adcResult;
		temp=temp/10;
		for(ind=0;ind<NUM_OF_SENSING_TEMP-1;ind++)
		{
			/*update the array of last 10 readings*/
			SENSING_TEMP_LAST10[ind]=SENSING_TEMP_LAST10[ind+1];
			AVG_TEMP_SENSING+=SENSING_TEMP_LAST10[ind];
		}
		/*update the array of last 10 readings with the last sensed temperature*/
		SENSING_TEMP_LAST10[ind]=temp;
		AVG_TEMP_SENSING+=SENSING_TEMP_LAST10[ind];
		/*Calculate average*/
		AVG_TEMP_SENSING=AVG_TEMP_SENSING/NUM_OF_SENSING_TEMP;

		/*makes value of counter for 100ms interrupt equals zero to start count again*/
		TIME_100mS_COUNTER=0;

		/*set preload of timer0 with TIMER0_PRELOAD to make timer0 interrupt occur almost every 1ms second*/
		TCNT0 = TIMER0_PRELOAD;
	}
	EnableAllInterrupts();
}



/*put the Electric Water Heater in the sitting mode operation*/
void setting_mode()
{
	/*once it enter the sitting mode it will not out unless no button up or down pressed for 5 second*/
	while (1)
	{
		/*must be still in setting mode*/
		if(Button_Pressed(UP_BUTTON)&&SETTING_MODE_STATE==TRUE)
		{
			while(Button_Pressed(UP_BUTTON));
			/*The maximum possible set temperature is 75 degrees*/
			if(SITTING_TEMP<75)
			{
				/*if button up pressed setting temperature increase by 5 degrees*/
				SITTING_TEMP+=5;
				/*
				 * makes value of counter for 5 second interrupt equals zero
				 * so the electric water heater doesn't out from setting mode
				 */
				TIME_5S_COUNTER=0;
				/*update SSD with the updated setting temperature*/
				SSD_DelayWithDisaplayMS(SITTING_TEMP,100);
				/*save the last updated temperature*/
				EEPROM24C16_Write_Byte(0,SITTING_TEMP);
//				EEPROM_Write(0,SITTING_TEMP);
			}
			/*
			 * if the current water temperature is less than the set temperature by 5 degrees
			 * heating element should be ON
			 * cooling element should be OFF
			 * */
			if(AVG_TEMP_SENSING==(SITTING_TEMP-5))
			{
				Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_HIGH);
				Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_LOW);
				HEATING_ELEMENT_STATE=TRUE;
				COOLING_ELEMENT_STATE=FALSE;
			}
			/*
			 * if the current water temperature is grater than the set temperature by 5 degrees
			 * heating element should be OFF
			 * cooling element should be ON
			 * */
			else if((AVG_TEMP_SENSING-5)==SITTING_TEMP)
			{
				Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_LOW);
				Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_HIGH);
				HEATING_ELEMENT_STATE=FALSE;
				COOLING_ELEMENT_STATE=TRUE;
			}
		}
		else if(Button_Pressed(DOWN_BUTTON)&&SETTING_MODE_STATE==TRUE)
		{
			while(Button_Pressed(DOWN_BUTTON));
			if(SITTING_TEMP>35)
			{
				/*if button down pressed setting temperature decrease by 5 degrees*/
				SITTING_TEMP-=5;
				TIME_5S_COUNTER=0;
				/*update SSD with the updated setting temperature*/
				SSD_DelayWithDisaplayMS(SITTING_TEMP,100);
				/*save the last updated temperature*/
				EEPROM24C16_Write_Byte(0,SITTING_TEMP);
//				EEPROM_Write(0,SITTING_TEMP);
			}
			/*
			 * if the current water temperature is less than the set temperature by 5 degrees
			 * heating element should be ON
			 * cooling element should be OFF
			 * */
			if(AVG_TEMP_SENSING==(SITTING_TEMP-5))
			{
				Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_HIGH);
				Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_LOW);
				HEATING_ELEMENT_STATE=TRUE;
				COOLING_ELEMENT_STATE=FALSE;
			}
			/*
			 * if the current water temperature is grater than the set temperature by 5 degrees
			 * heating element should be OFF
			 * cooling element should be ON
			 * */
			else if((AVG_TEMP_SENSING-5)==SITTING_TEMP)
			{
				Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_LOW);
				Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_HIGH);
				HEATING_ELEMENT_STATE=FALSE;
				COOLING_ELEMENT_STATE=TRUE;
			}
		}
		else if(SETTING_MODE_STATE==FALSE)
		{
			/*
			 * if the current water temperature is less than the set temperature by 5 degrees
			 * heating element should be ON
			 * cooling element should be OFF
			 * */
			if(AVG_TEMP_SENSING==(SITTING_TEMP-5))
			{
				Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_HIGH);
				Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_LOW);
				HEATING_ELEMENT_STATE=TRUE;
				COOLING_ELEMENT_STATE=FALSE;
			}
			/*
			 * if the current water temperature is grater than the set temperature by 5 degrees
			 * heating element should be OFF
			 * cooling element should be ON
			 * */
			else if((AVG_TEMP_SENSING-5)==SITTING_TEMP)
			{
				Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_LOW);
				Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_HIGH);
				HEATING_ELEMENT_STATE=FALSE;
				COOLING_ELEMENT_STATE=TRUE;
			}
			/*update SSD with the updated setting temperature*/
			SSD_DelayWithDisaplayMS(AVG_TEMP_SENSING,100);
			/*save the last updated temperature*/
			EEPROM24C16_Write_Byte(0,SITTING_TEMP);
//			EEPROM_Write(0,SITTING_TEMP);
			return;
		}
	}

}






int main(void)
{

	/*Initiation of BUTTONs, LED and External EEPROM  peripherals*/
	Button_Init();
	Led_Init();
	SSD_Init();
//	EEPROM24C16_Init();

	/*configure pins of heating and cooling elements*/
	Dio_ConfigChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,OUTPUT);
	Dio_ConfigChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,OUTPUT);

	/*heating and cooling elements are in OFF state at by default */
	Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_LOW);
	Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_LOW);

	/*put heating and cooling LEDs in OFF state*/
	Led_OFF(COOLING_ELEMENT_LED);
	Led_OFF(HEATING_ELEMENT_LED);

	/*Save the initial setting temperature in external EEPROM*/
//	EEPROM24C16_Write_Byte(0,SITTING_TEMP);
	/*SSD show zero when the Electric Water Heater is OFF*/




	while (1)
	{
		SSD_DelayWithDisaplayMS(AVG_TEMP_SENSING,100);
		/*
		 * when power is connected the Electric Water Heater is in OFF state
		 * must release ON_OFF_BUTTON to enter in ON state
		 * */
		/*ON_OFF_BUTTON is PULL down to take action when it release*/
		if(Button_Pressed(ON_OFF_BUTTON)&&ON_OFF_STATE==FALSE)
		{
			while(Button_Pressed(ON_OFF_BUTTON));

			Led_ON(ON_OFF_LED);

			/*retrieved the stored set temperature from the External EPPROM*/
			SITTING_TEMP=EEPROM24C16_Read_Byte(0);
//			SITTING_TEMP=EEPROM_Read(0);

			ON_OFF_STATE=TRUE;

			/*display the current water temperature*/
			SSD_DelayWithDisaplayMS(AVG_TEMP_SENSING,1000);



			/*
			 * if the current water temperature is less than the set temperature by 5 degrees
			 * heating element should be ON
			 * cooling element should be OFF
			 * */
			if(AVG_TEMP_SENSING==(SITTING_TEMP-5))
			{
				Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_HIGH);
				Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_LOW);
				HEATING_ELEMENT_STATE=TRUE;
				COOLING_ELEMENT_STATE=FALSE;
			}
			/*
			 * if the current water temperature is grater than the set temperature by 5 degrees
			 * heating element should be OFF
			 * cooling element should be ON
			 * */
			else if((AVG_TEMP_SENSING-5)==SITTING_TEMP)
			{
				Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_LOW);
				Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_HIGH);
				HEATING_ELEMENT_STATE=FALSE;
				COOLING_ELEMENT_STATE=TRUE;
			}
		}

		/*if ON_OFF_BUTTON release when the electric water heater in ON state put every thing in OFF state*/
		else if(Button_Pressed(ON_OFF_BUTTON)&&ON_OFF_STATE==TRUE)
		{
			while(Button_Pressed(ON_OFF_BUTTON));
			/*OFF the led of ON_OFF_STATE*/
			Led_OFF(ON_OFF_LED);

			/*OFF the heating element and cooling element*/
			Dio_WriteChannel(HEATING_ELEMENT_REG,HEATING_ELEMENT_PIN,STD_LOW);
			Dio_WriteChannel(COOLING_ELEMENT_REG,COOLING_ELEMENT_PIN,STD_LOW);

			/*save last updated setting temperature*/
			EEPROM24C16_Write_Byte(0,SITTING_TEMP);
//			EEPROM_Write(0,SITTING_TEMP);

			/*SSD show zero when the Electric Water Heater is OFF*/
			SSD_DelayWithDisaplayMS(0,100);
			/*update ON_OFF_STATE to be OFF*/
			ON_OFF_STATE=FALSE;
		}
		/*The first “Up” or “Down” button press, enters the temperature setting mode*/
		if((Button_Pressed(UP_BUTTON)||Button_Pressed(DOWN_BUTTON))&&ON_OFF_STATE==TRUE)
		{
			while(Button_Pressed(UP_BUTTON)||Button_Pressed(DOWN_BUTTON));

			SETTING_MODE_STATE=TRUE;
			Led_Toggle(LED1);
			/*
			 * Confider the timer0
			 * by setting preload and prescaler
			 * and enable interrupt of timer0
			 * so interrupt occurs almost every 1ms so can use it to make 100ms
			 */TIMER0_TCNT0_REG=TIMER0_PRELOAD;
			 TIMER0_TCCR0_REG=TIMER0_CS_64_PRESCALER;
			 TIMER0_EnableInterrupt();

			 /*
			  * Confider the timer1
			  * by setting preload and prescaler
			  * and enable interrupt of timer1
			  * so interrupt occurs every 1 second so can use it to make 1 second
			  */
			 TIMER1_TCNT1_REG=TIMER1_PRELOAD;
			 TIMER1_TCCR1A_REG=0x00;
			 TIMER1_TCCR1B_REG=TIMER0_CS_1024_PRESCALER;
			 TIMER1_EnableInterrupt();

			 /*Enable all interrupts so interrupt of timer0 and timer1 can occure*/
			 EnableAllInterrupts();

			 /*enter the setting mode*/
			 setting_mode();
		}

	}

	return 0;
}
