/*
 * motor.c
 *
 * Created: 15/12/2012 15:05:43
 *  Author: hslovett
 */ 

#include "Motor.h"

void PWM_Init( void )
{
	//Set clear on Compare, 10 bit PWM
	TCCR1A = (0 << WGM11) | (1 << WGM10) | (1 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0);
	TCCR1B = (0 << WGM13) | (1 << WGM12) | (1 << CS12) | (0 << CS11) | (1 << CS10);
	OCR1A = TopSpeed;
}
void ADC_Init(void)
{
	ADMUX = (0 << REFS1) | (1 << REFS0) ;
	ADCSRA = (1 << ADEN) | (0 << ADIE) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
uint8_t ADC_Read(void)
{
	ADCSRA |= (1 << ADSC);
	while ((ADCSRA & (1 << ADIF)) == 0) //wait for the interrupt flag to be high
	;
	
	return (uint8_t)(ADC >> 2);
}
ISR(ADC_vect)
{
	ADC_Value = (ADC >> 2);
	ADCSRA |= (1 << ADSC);//continually read ADC
}

void AComp_Init(void)
{
	ACSR = (1 << ACIE) | (1 << ACIS1);//enable interrupt on falling edge
	DIDR1 = 0x03;
}
ISR(ANALOG_COMP_vect)
{
// 	if ( ACSR & (1<<ACO))
// 		PORTB |= (1<<PB4);
// 	else
// 		PORTB &= ~(1 << PB4);
	Counter++;
	ACSR &= ~(1 << ACIE); //turn interrupt off. To stop edge bounce. Reenabled at timer overflow
	Comparator_Sleep = 10;
}
void Motor_Init()
{
	MOTOR_DDR |= (1 << IN1) | (1 << IN2);
	MOTOR_PORT &= ~((1 << IN1) | (1 << IN2));
	
	//ADC_Value = 0;
	Counter = 0;
	//Motor_Threshold = 180;
	TopSpeed = 128;
	Comparator_Sleep = 0;
	PWM_Init();
	//ADC_Init();
	AComp_Init();
	
}
void Motor_Go(uint8_t Direction)
{
	switch (Direction)
	{
		case STOP:
			MOTOR_PORT &= ~((1 << IN1) | (1 << IN2));
			break;
			
		case FORWARD:
			MOTOR_PORT &= ~(1 << IN2);
			MOTOR_PORT |= (1 << IN1);
			break;
			
		case REVERSE:
			MOTOR_PORT &= ~(1 << IN1);
			MOTOR_PORT |= (1 << IN2);
			break;
			
		case BREAK:
			MOTOR_PORT |= ((1 << IN1) | (1 << IN2));
			break;
	}
}
void Motor_Execute()
{
	if (Counter >= Counter_Max)
		Motor_Go(STOP);
	//printf("Motor: Counter = %d\n", Counter);
}
void Test_Motor()
{
	Counter = 0;
	Counter_Max = 10;
	Motor_Go(FORWARD);
}