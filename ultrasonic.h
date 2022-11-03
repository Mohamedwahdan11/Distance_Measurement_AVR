/*
 * ultrasonic.h
 *
 *  Created on: May 29, 2022
 *      Author: DELL
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


/*Function to initialize the ultrasonic driver*/
void Ultrasonic_init();


/*function to trigger the trigger pin*/
void Ultrasonic_Trigger(void);





/*function to get the time period "the high time period on the echo pin"*/
void Ultrasonic_edgeProcessing(void);



#endif /* ULTRASONIC_H_ */
