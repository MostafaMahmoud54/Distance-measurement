/************************************************************************************
 * Device: Ultrasonic
 *
 * Filename: us.c
 *
 * Description: Header file for the ultrasonic driver
 *
 * Created on: Oct 17, 2021
 *
 * Author: Mostafa Mahmoud
 ************************************************************************************/

#ifndef US_H_
#define US_H_

#include "std_types.h"


void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);

#endif /* US_H_ */
