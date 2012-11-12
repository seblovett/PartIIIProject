/*
 * Config.c
 * 
 * Contains Global Methods and initialisations
 * 
 * Created: 25/10/2012 21:59:06
 *  Author: hslovett
 */ 

#include "Config.h"
#include <avr/io.h>
void IO_Init(void)
{
	//initialise timer 0 to interrupt every 10 ms
	TIMSK0 |= (1 << OCIE0A);
	TCCR0A |= (1 << WGM01);
	OCR0A = 117; //10ms interrupt at 12MHz
	TCCR0B |= (1 << CS02) | (1 << CS00);
	
	
	DDRA = 0x00;
	//PORTB = 0xBF;
	DDRC = 0xFC;
	DDRD = 0xF2;
	
	
	
	//set int0 and int1 to trigger on falling edge
	EIMSK = (1 << INT0) | (1 << INT1);				//Enable INT0 and INT1
	EICRA = (1 << ISC01) | (1 << ISC11);			//Trigger INT0 and INT1 on the falling edge
}