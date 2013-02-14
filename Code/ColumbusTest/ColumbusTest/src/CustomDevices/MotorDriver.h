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
#define MOTOR0			M0_PWM_CHANNEL_ID
#define MOTOR1			M1_PWM_CHANNEL_ID

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
void Analogue_Comparator_Init();
/*static void ACInterruptHandler(void);*/
#endif /* MOTORDRIVER_H_ */
