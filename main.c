/*
 * main.c
 *
 *  Created on: Oct 17, 2021
 *      Author: Mostafa Mahmoud
 */
#include "us.h"
#include "lcd.h"
#include <avr/io.h>
int main()
{
	SREG|=(1<<7);
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance=    cm");
	uint16 distance=0;
	while(1)
	{
		LCD_moveCursor(0,10);
		distance=Ultrasonic_readDistance();
		LCD_intgerToString(distance);
		if(distance<100)
		{
			LCD_displayCharacter(' ');
		}
	}
}
