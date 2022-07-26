/************************************************************************************
 * Device: Ultrasonic
 *
 * Filename: us.c
 *
 * Description: Source file for the ultrasonic driver
 *
 * Created on: Oct 17, 2021
 *
 * Author: Mostafa Mahmoud
 ************************************************************************************/
#include"icu.h"
#include"gpio.h"
#include"us.h"
#include <avr/delay.h>
#include <avr/io.h>
uint16 time=0;
uint8 g_EdgeDetected=0;
void Ultrasonic_init(void)
{
	Icu_ConfigType config={F_CPU_8,RISING};
	ICU_init(&config);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	return time/58.8;
}
void Ultrasonic_edgeProcessing(void)
{
	g_EdgeDetected++;
	if(g_EdgeDetected==1)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_EdgeDetected==2)
	{
		time=ICU_getInputCaptureValue();
		g_EdgeDetected=0;
		ICU_setEdgeDetectionType(RISING);

	}

}


