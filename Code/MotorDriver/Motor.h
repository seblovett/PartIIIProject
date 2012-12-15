/*
 * Motor.h
 *
 * Created: 15/12/2012 15:06:08
 *  Author: hslovett
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#include <avr/io.h>

#define MOTOR_DDR	DDRA
#define MOTOR_PORT	PORTA
#define IN1 PA1
#define IN2 PA2

#define STOP 0
#define FORWARD 1
#define REVERSE 2
#define BREAK 3


uint8_t ADC_Value;
uint8_t Motor_Threshold;
uint8_t Counter;
uint8_t TopSpeed;
void Motor_Init();

void Motor_Execute();
void Motor_Go(uint8_t Direction);
#endif /* MOTOR_H_ */