/*
 * MotorDriver.c
 *
 * Created: 12/12/2012 12:58:27
 *  Author: hslovett
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

void PWM_Init( void )
{
	//Set clear on Compare, 10 bit PWM
	TCCR1A = (0 << WGM11) | (1 << WGM10) | (1 << COM1A1) | (0 << COM1A0) | (1 << COM1B1) | (0 << COM1B0);
	TCCR1B = (0 << WGM13) | (1 << WGM12) | (0 << CS12) | (0 << CS11) | (1 << CS10);
	OCR1A = 0x00FF;
}
void ADC_Init(void)
{
	ADMUX = (0 << REFS1) | (1 << REFS0) ;
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADSC);
}
ISR(ADC_vect)
{
	OCR1A = (ADC>>2);
	OCR1B = 255 - OCR1A;
	ADCSRA |= (1 << ADSC);
}
int main(void)
{
	DDRD = 0xFF;
	PWM_Init();
	ADC_Init();
	sei();
    while(1)
    {
        ;//TODO:: Please write your application code 
    }
}