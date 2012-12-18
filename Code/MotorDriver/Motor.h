/*
 * Motor.h
 *
 * Created: 15/12/2012 15:06:08
 *  Author: hslovett
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#define MOTOR_DDR	DDRB
#define MOTOR_PORT	PORTB
#define IN1 PB0
#define IN2 PB1

#define STOP 0
#define FORWARD 1
#define REVERSE 2
#define BREAK 3

uint8_t Comparator_Sleep;
uint8_t ADC_Value;
//uint8_t Motor_Threshold;
uint8_t Counter;
uint8_t Counter_Max;
uint8_t TopSpeed;
void Motor_Init();

void Motor_Execute();
void Motor_Go(uint8_t Direction);
void Test_Motor();
#endif /* MOTOR_H_ */