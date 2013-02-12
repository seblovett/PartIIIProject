/*
 * MotorDriver.h
 *
 * Created: 10/02/2013 18:11:55
 *  Author: hslovett
 */ 


#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_
#include <asf.h>
//Definitions
#define MOTOR0			0
#define MOTOR1			1

#define FORWARD			2
#define BACKWARD		3
#define LEFT_SPOT		4
#define RIGHT_SPOT		5
#define STOP			6

//Globals
pwm_opt_t pwm_opt;                // PWM option config.
avr32_pwm_channel_t pwm_channel;



void Motor_Init();
void Motor_Go(int Direction);


#endif /* MOTORDRIVER_H_ */
