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
	TCCR0B = (1 << CS00);
	TIMSK0 = (1 << TOIE0);
	
}
ISR(TIMER0_OVF_vect)
{
	Motor_Execute();
	printf("Counter = %d\n", Counter);
}
int main(void)
{
	stdout = &mystdout;
	USART0_Init();
	printf("Hello\n\n");
	DDRD = 0xFF;
	Motor_Init();
	Timer_Init();
	sei();
	char buff[20];
    while(1)
    {
// 		Motor_Execute();
// 		printf("Counter = %d\n", Counter);
// 		_delay_ms(50);
		Usart_get_line(&buff, 20);
		switch(buff[0])
		{
			case 'F':
				printf("Forward\n");
				Motor_Go(FORWARD);
				break;
				
			case 'R':
				printf("Reverse\n");
				Motor_Go(REVERSE);
				break;
			
			case 'B':
				printf("Break\n");
				Motor_Go(BREAK);
				break;
			
			case 'S':
				printf("Stop\n");
				Motor_Go(STOP);
				break;
		}			
    }
}