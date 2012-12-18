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

//Pin and Port Definitions
#define MOTOR_DDR	DDRB
#define MOTOR_PORT	PORTB
#define IN1 PB0
#define IN2 PB1

//Motor States
#define STOP 0
#define FORWARD 1
#define REVERSE 2
#define BREAK 3

//Characteristics 
#define INTS_PER_REV	1		//number of counts per full revolution
#define CIRCUMFERENCE	118		//Length of Circumference in mm
#define MINSPEED		80
#define MAXSPEED		150
//Globals
uint8_t Comparator_Sleep;
uint8_t ADC_Value;
uint8_t Counter;
uint8_t Counter_Target;
uint8_t TopSpeed;
uint8_t Motor_State;
//Methods
void Motor_Init();
void Motor_Execute();
//void Motor_State_Change();
void Test_Motor();
int Motor_Move(int Distance_mm);
#endif /* MOTOR_H_ */