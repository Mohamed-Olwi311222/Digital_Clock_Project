/*
 * main.c
 *
 * Created: 2/2/2025 8:15:36 AM
 *  Author: Mohamed olwi
 */ 
#define __AVR_ATmega328P__
#define F_CPU		16000000UL		//MCU Clock
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB =  0x20;
	PORTB = 0x00;
	
    while(1)
    {
		PORTB = 0x20;
		_delay_ms(50);
		PORTB = 0x00;
		_delay_ms(50);

    }

}