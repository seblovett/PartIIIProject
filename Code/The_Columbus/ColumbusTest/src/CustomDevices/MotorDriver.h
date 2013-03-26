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
#define SPOT_PIVOT		6
#define STOP			7


#define ENABLE_ACA_INTERRUPT		//{AVR32_ACIFA1.ier = 1;}
#define DISABLE_ACA_INTERRUPT		//{AVR32_ACIFA1.idr = 1;}
#define ENABLE_ACB_INTERRUPT		//{AVR32_ACIFA1.ier = 2;}
#define DISABLE_ACB_INTERRUPT		//{AVR32_ACIFA1.idr = 2;}
#define GAMMA	10	//Interrupts caused per full rotation of a wheel
#define CIRCUMFERENCE_WHEEL_MM		116 //in millimeters
//#define CIRCUMFERENCE_WHEEL_CM		12 //in centimeters
#define MIN_DISTANCE_RESOLUTION		CIRCUMFERENCE_WHEEL_MM / GAMMA
#define MIN_ROTATION_RESOLUTION		(CIRCUMFERENCE_WHEEL_MM*360)/(GAMMA * C_b)
#define C_b							282
#define ROTATION_CONST				(GAMMA * C_b) / (CIRCUMFERENCE_WHEEL_MM * 360)
//Type Defs
typedef struct {
	int Left_State;
	int Right_State;
	int Left_Count;
	int Right_Count;
	} Motor_Control_t;

//Globals
pwm_opt_t pwm_opt;                // PWM option config.
avr32_pwm_channel_t pwm_channel;
Motor_Control_t Motor_Control;

void Motor_Init();
void Motor_Go();
void Analogue_Comparator_Init();
void Motor_Start(int Motors);
void Motors_Reset(void);
void Motor_Stop(int Motors);
bool Motors_Moving();
void Motors_Move(int centimetres_fwd)/*Move this amount forward in centimeters */;
void Motors_Execute();
void Motors_Rotate(int angle_degs);
/*static void ACInterruptHandler(void);*/
#endif /* MOTORDRIVER_H_ */
