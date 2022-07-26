/************************************************************************************
 * Module: ICU
 *
 * Filename: icu.c
 *
 * Description: source file for the icu driver
 *
 * Created on: Oct 9, 2021
 *
 * Author: Mostafa Mahmoud
 ************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "icu.h"
#include "common_macros.h"
#include "std_types.h"
/*******************************************************************************
 *                      Global Variables	                                   *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void)= NULL_PTR;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description:Initialize the ICU driver
 * 1-set the required clock
 * 2-set the required edge detection
 * 3-enable the input capture interrupt
 * 4-initialize timer1 registers
 */
void ICU_init(const Icu_ConfigType* config_ptr)
{
	DDRD &=~(1<<PD6);
	TCCR1A=(1<<FOC1A)|(1<<FOC1B); /*normal mode*/
	/*insert the required clock value in the first three bits (CS10, CS11 and CS12)*/
	TCCR1B=(TCCR1B & 0xF8)|(config_ptr->clock);
	/*insert the required edge detection in the ICES1 bit */
	TCCR1B=(TCCR1B & 0xBF)|(config_ptr->edge<<6);
	TCNT1=0;	/*initialize value for timer1*/
	ICR1 = 0;	/*initialize value for the icu register*/
	TIMSK|=(1<<TICIE1);/*enable icu interrupt*/
}
/*
 * Description: function to set the call back
 */
void ICU_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr=a_ptr;
}
/*
 * Description:
 * function to set the edge detection type
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType a_edgetype)
{
	/*insert the required edge detection in the ICES1 bit */
	TCCR1B=(TCCR1B & 0xBF)|(a_edgetype<<6);
}
/*
 * Description:
 * function to get the value stored at the ICR1 register when the input is captured
 */
uint16 ICU_getInputCaptureValue()
{
	return ICR1;
}

/*
 * Description :
 * function to start count from 0
 */
void ICU_clearTimerValue()
{
	TCNT1=0;
}
/*Description:
 *function to stop the icu
 */
void ICU_deInit()
{
	/*clear all timer registers*/
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}
/*******************************************************************************
 *                      	Interrupt Service Routines                         *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/*call the call back function when the edge is detected*/
		(*g_callBackPtr)();
	}
}
