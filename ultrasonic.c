/*
 * ultrasonic.c
 *
 *  Created on: May 29, 2022
 *      Author: DELL
 */

#include "ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include "util/delay.h"


uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;



Icu_ConfigType Icu_Config = {F_CPU_8,RISING};


/*Function to initialize the ultrasonic driver*/
void Ultrasonic_init()
{


	/* Initialize both the ICU driver */
	Icu_init(&Icu_Config);
	/* Set the Call back function pointer in the ICU driver */
	Icu_setCallBack(Ultrasonic_edgeProcessing);

	/*Set the pin direction of the trigger pin as an output */
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID,PIN_OUTPUT);

}


/*function to trigger the trigger pin*/

void Ultrasonic_Trigger(void)
{
	/*to trigger the ultrasonic senor to start reading the distance
	 * we need to send single pulse with duration 10 microseconds
	 * to start reading*/
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);

}

uint16 Ultrasonic_readDistance(void)
{
	uint16 distance=0;


	/*Trigger the the trigger pin of the sensor*/
	Ultrasonic_Trigger();

	/*clear the timer register*/
	Icu_clearTimerValue();

	/*wait for the falling edge*/
	while(g_edgeCount!=2);

	/*calculate the distance in cm*/
	distance=0.017*g_timeHigh;

	/*if condition to increase the accuracy of  the sensor*/
	if(distance>338)
		distance+=6;
	else if(distance>272)
		distance+=5;
	else if(distance>196)
		distance+=4;
	else if(distance>127)
		distance+=3;
	else if(distance>57)
			distance+=2;
	else
		distance+=1;



	/*make the edge counter equal to zero again for next reading*/
	g_edgeCount=0;

	return distance;


}







void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge again */
		Icu_setEdgeDetectionType(RISING);
	}

}
