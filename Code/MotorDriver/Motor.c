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
	
	//Proportional Controller
	uint8_t TempSpeed;
	TempSpeed = TopSpeed - ((TopSpeed * Counter) / Counter_Target);
	if (TempSpeed < MINSPEED) //min speed in place so that the wheel doesn't slow down to a speed that can't move.
		OCR1A = MINSPEED;
	else
		OCR1A = TempSpeed;
}
void Motor_Init()
{
	MOTOR_DDR |= (1 << IN1) | (1 << IN2);
	MOTOR_PORT &= ~((1 << IN1) | (1 << IN2));
	
	//ADC_Value = 0;
	Counter = 0;
	//Motor_Threshold = 180;
	TopSpeed = MAXSPEED;
	Comparator_Sleep = 0;
	PWM_Init();
	//ADC_Init();
	AComp_Init();
	
}
void Motor_State_Change()
{
	switch (Motor_State)
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
void Motor_Execute() //method to run everytime the counter overflows
{
	switch(Motor_State)//state machine
	{
		case FORWARD:
		case REVERSE:
			if (Counter >= Counter_Target)
			{
				Motor_State = BREAK;	
			}
			
			break;
			
		case BREAK:
			Motor_State = STOP;
			break;
			
		default:
			Motor_State = STOP;
			
	}
	Motor_State_Change();//update driving pins
	
	//sleep of comparator
	if(Comparator_Sleep == 0)
		ACSR |= (1 << ACIE);//re enable interrupt
	else
		Comparator_Sleep--;
	//printf("Motor: Counter = %d\n", Counter);
}
void Test_Motor()
{
	Counter = 0;
	Counter_Target = 10;
	Motor_State = FORWARD;
}
int Motor_Move(int Distance_mm)
{
	Counter_Target = (Distance_mm * INTS_PER_REV) / CIRCUMFERENCE; 
	Counter = 0;
	if (Distance_mm > 0)
		Motor_State = FORWARD;
	else 
		Motor_State = REVERSE;
		
	return (Counter_Target * CIRCUMFERENCE)/INTS_PER_REV; //return actual distance to move
}