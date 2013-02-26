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
#define MOTOR_L			ML_PWM_CHANNEL_ID
#define MOTOR_R		MR_PWM_CHANNEL_ID

#define FORWARD			2
#define BACKWARD		3
#define LEFT_SPOT		4
#define RIGHT_SPOT		5
#define STOP			6



#define LEFT_INTERRUPTS_PER_REVOLUTION		1
#define RIGHT_INTERRUPTS_PER_REVOLUTION		1
#define CIRCUMFERENCE_WHEEL		118 //in milimeters
//Type Defs
typedef struct {
	int Left_State;
	int Right_State;
	int Left_Count;
	int Right_Count;
	} Motor_Control;

//Globals
pwm_opt_t pwm_opt;                // PWM option config.
avr32_pwm_channel_t pwm_channel;
Motor_Control Motor_Cntrl;

void Motor_Init();
void Motor_Go();
void Analogue_Comparator_Init();
void Motor_Start(int Motors);
void Motors_Reset(void);
void Motor_Stop(int Motors);
bool Motors_Moving();
/*static void ACInterruptHandler(void);*/
#endif /* MOTORDRIVER_H_ */
