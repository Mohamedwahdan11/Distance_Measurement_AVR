/*
 * mini_project_4.c
 *
 *  Created on: May 29, 2022
 *      Author: DELL
 */

#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */

uint16 Ultrasonic_readDistance(void);

int main()
{
	uint16 distance = 0;

	/* Initialize both the LCD and Ultrasonic driver */
		LCD_init();
		Ultrasonic_init();


	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	LCD_displayString("Distance = ");

	while(1)
	{


			/* function to get the distance */
			distance=Ultrasonic_readDistance();
			LCD_moveCursor(0, 11);
			/* display the distance on LCD screen */
			LCD_intgerToString(distance);
			LCD_displayString(" m");
		}

}
