/*
 * MotorDriver.c
 *
 * Created: 12/12/2012 12:58:27
 *  Author: hslovett
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 12000000UL
#include "Usart.h"
#include "Motor.h"
#include <util/delay.h>
static FILE mystdout = FDEV_SETUP_STREAM(Usart_printf, NULL, _FDEV_SETUP_WRITE);

void Timer_Init()
{
	TCCR0B = (1 << CS02)|(1 << CS00);
	TIMSK0 = (1 << TOIE0);
	
}
ISR(TIMER0_OVF_vect)
{
	
	Motor_Execute();
	
}
int main(void)
{
	stdout = &mystdout;
	USART0_Init();
	printf("Hello\n\n");
	DDRB = 0x03;
	DDRC = 0x01;
	DDRD = 0xFF;
	Motor_Init();
	Timer_Init();
	sei();
	char buff[20];
	//Motor_Move(1000);
    while(1)
    {
		
    }
}