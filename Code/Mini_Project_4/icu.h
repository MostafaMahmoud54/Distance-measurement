/************************************************************************************
 * Module: ICU
 *
 * Filename: icu.h
 *
 * Description: Header file for the icu driver
 *
 * Created on: Oct 9, 2021
 *
 * Author: Mostafa Mahmoud
 ************************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"
/************************************************************************************
 * 								Types Declarations
 ************************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock;
typedef enum
{
	FALLING,RISING
}Icu_EdgeType;
typedef struct
{
	Icu_Clock clock;
	Icu_EdgeType edge;
}Icu_ConfigType;
/************************************************************************************
 * 								Function Prototypes
 ************************************************************************************/
/*
 * Description:Initialize the ICU driver
 * 1-set the required clock
 * 2-set the required edge detection
 * 3-enable the input capture interrupt
 * 4-initialize timer1 registers
 */
void ICU_init(const Icu_ConfigType* config_ptr);

/*
 * Description: function to set the call back
 */
void ICU_setCallBack(void(*a_ptr)(void));
/*
 * Description:
 * function to set the edge detection type
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType a_edgetype);
/*
 * Description:
 * function to get the value stored at the ICR1 register when the input is captured
 */
uint16 ICU_getInputCaptureValue();
/*
 * Description :
 * function to start count from 0
 */
void ICU_clearTimerValue();
/*Description:
 *function to stop the icu
 */
void ICU_deInit();
#endif /* ICU_H_ */
