/*
 * MotorDriver.c
 *
 * Created: 10/02/2013 18:12:07
 *  Author: hslovett
 */ 
#include <asf.h>
#include "CustomDevices/CustomDevices.h"
#include <delay.h>



static void local_start_highfreq_clock(void)
{
  const scif_pll_opt_t opt = {
            .osc = SCIF_OSC0,     // Sel Osc0/PLL0 or Osc1/PLL1
            .lockcount = 16,      // lockcount in main clock for the PLL wait lock
            .div = 1,             // DIV=1 in the formula
            .mul = 6,             // MUL=7 in the formula
            .pll_div2 = 1,        // pll_div2 Divide the PLL output frequency by 2 (this settings does not change the FVCO value)
            .pll_wbwdisable = 0,  // pll_wbwdisable 1 Disable the Wide-Bandith Mode (Wide-Bandwith mode allow a faster startup time and out-of-lock time). 0 to enable the Wide-Bandith Mode.
            .pll_freq = 1,        // Set to 1 for VCO frequency range 80-180MHz, set to 0 for VCO frequency range 160-240Mhz.
  };
  // Switch main clock to Osc0.
//  pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);

  /* Setup PLL0 on Osc0, mul=7 ,no divisor, lockcount=16, ie. (16Mhzx7)/(div2) = 56MHz output */
  scif_pll_setup(SCIF_PLL0, &opt); // lockcount in main clock for the PLL wait lock

  /* Enable PLL0 */
  scif_pll_enable(SCIF_PLL0);

  /* Wait for PLL0 locked */
  scif_wait_for_pll_locked(SCIF_PLL0) ;
}
static void pwm_start_gc(void)
{
  scif_gc_setup(AVR32_SCIF_GCLK_PWM,
                SCIF_GCCTRL_PLL0,
                AVR32_SCIF_GC_NO_DIV_CLOCK,
                0);
  scif_gc_enable(AVR32_SCIF_GCLK_PWM);
}
void Analogue_Comparator_Init()
{
	static const gpio_map_t ACIFA_GPIO_MAP =
	{
	{POT0_AC1AP1_PIN, POT0_AC1AP1_FUNCTION},
	{POT1_AC1BP1_PIN, POT1_AC1BP1_FUNCTION},
	{SENSE0_AC1AN1_PIN, SENSE0_AC1AN1_FUNCTION},
	{SENSE1_AC1BN1_PIN, SENSE1_AC1BN1_FUNCTION},
	};
	
	gpio_enable_module(ACIFA_GPIO_MAP, sizeof(ACIFA_GPIO_MAP) / sizeof(ACIFA_GPIO_MAP[0]));
	//Make it an interrupt
	Disable_global_interrupt();
	
	acifa_configure_hysteresis(&AVR32_ACIFA1, ACIFA_COMP_SELA, 2);
	acifa_configure(&AVR32_ACIFA1,
	ACIFA_COMP_SELA,
	POT0_AC1AP1_INPUT,
	SENSE0_AC1AN1_INPUT,
	FOSC0);
	
	acifa_configure_hysteresis(&AVR32_ACIFA1, ACIFA_COMP_SELB, 2);
	acifa_configure(&AVR32_ACIFA1,
	ACIFA_COMP_SELB,
	POT1_AC1BP1_INPUT,
	SENSE1_AC1BN1_INPUT,
	FOSC0);
	
	// 	acifa_enable_interrupt(&AVR32_ACIFA1, (1 << AVR32_ACIFA_ACBINT )| (1 << AVR32_ACIFA_ACAINT));//Enable ACBINT and ACAINT
	// 	AVR32_ACIFA1.ier = 3; //enable interrupts
	// 	acifa_enable_interrupt_toggle(&AVR32_ACIFA1, ACIFA_COMP_SELA);
	// 	acifa_enable_interrupt_toggle(&AVR32_ACIFA1, ACIFA_COMP_SELB);
	// 	acifa_enable_interrupt_inp_lower(&AVR32_ACIFA1, ACIFA_COMP_SELA);
	// 	acifa_enable_interrupt_inp_lower(&AVR32_ACIFA1, ACIFA_COMP_SELB);
	acifa_start(&AVR32_ACIFA1, (ACIFA_COMP_SELA|ACIFA_COMP_SELB));
	
	//	INTC_register_interrupt(&ACInterruptHandler,AVR32_ACIFA1_IRQ ,AVR32_INTC_INT0);
	
	Enable_global_interrupt();
}
void Motor_Init()
{
	//Turn boths motors off
	ML_STANDBY;
	MR_STANDBY;
	
	ML_IN1_CLR;
	ML_IN2_CLR;
	
	MR_IN1_CLR;
	MR_IN2_CLR;
	
	Motor_Control.Left_Count = 0;
	Motor_Control.Right_Count = 0;
	Motor_Control.Left_State = STOP;
	Motor_Control.Right_State = STOP;

	avr32_pwm_channel_t pwm_channel = {	{0}, // cmr
										{0}, // cdty
										{0}, // cdtyupd
										{0}, // cprd
										{0}, // cprdupd
										{0}, // ccnt
										{0}, // dt
										{0}};// dtupd  ;  One channel config.
/*	unsigned int channel_id;*/

	// Start PLL for PWM
	local_start_highfreq_clock();
	// Start Enable Generic Clock with PLL as source clock
	pwm_start_gc();
	gpio_enable_module_pin(ML_PWM_H_PIN, ML_PWM_H_FUNCTION);
	gpio_enable_module_pin(MR_PWM_H_PIN, MR_PWM_H_FUNCTION); 
	// PWM controller configuration.
	pwm_opt.diva = AVR32_PWM_DIVA_CLK_OFF;
	pwm_opt.divb = AVR32_PWM_DIVB_CLK_OFF;
	pwm_opt.prea = AVR32_PWM_PREA_CCK;
	pwm_opt.preb = AVR32_PWM_PREB_CCK;
	pwm_opt.fault_detection_activated = false;
	pwm_opt.sync_channel_activated    = true;
	pwm_opt.sync_update_channel_mode  = PWM_SYNC_UPDATE_MANUAL_WRITE_MANUAL_UPDATE;
	pwm_opt.sync_channel_select[0]    = false;
	pwm_opt.sync_channel_select[1]    = false;
	pwm_opt.sync_channel_select[2]    = false;
	pwm_opt.sync_channel_select[3]    = false;
	pwm_opt.cksel                     = PWM_CKSEL_GCLK;
	pwm_init(&pwm_opt);
	// Update the period
	pwm_update_period_value(10);
	// Channel configuration
	pwm_channel.CMR.dte   = 0;							// Enable Deadtime for complementary Mode
	pwm_channel.CMR.dthi  = 0;							// Deadtime Inverted on PWMH
	pwm_channel.CMR.dtli  = 0;							// Deadtime Not Inverted on PWML
	pwm_channel.CMR.ces   = 0;							// 0/1 Channel Event at the End of PWM Period
	pwm_channel.CMR.calg  = PWM_MODE_LEFT_ALIGNED;      // Channel mode.
	pwm_channel.CMR.cpol  = PWM_POLARITY_HIGH;          // Channel polarity.
	pwm_channel.CMR.cpre  = AVR32_PWM_CPRE_CCK;         // Channel prescaler.
	pwm_channel.cdty      = 50;							// Channel duty cycle, should be < CPRD.
	pwm_channel.cprd      = 200;						// Channel period.
	
	pwm_channel_init(ML_PWM_CHANNEL_ID, &pwm_channel); // Set channel configuration to channel 0
	pwm_channel_init(MR_PWM_CHANNEL_ID, &pwm_channel); // Set channel configuration to channel 0
	Analogue_Comparator_Init();
}

// __attribute__((__interrupt__)) static void ACInterruptHandler(void)
// {
// 	
// }

void Motor_Start(int Motors)
{
	if(Motors & MOTOR_L)
	{
		if(Motor_Control.Left_State == FORWARD)
		{
			ML_IN1_SET;
			ML_IN2_CLR;
		}
		else if (Motor_Control.Left_State == BACKWARD)
		{
			ML_IN1_CLR;
			ML_IN2_SET;
		}
		else //Somethings gone wrong
		{
			ML_IN1_CLR;
			ML_IN2_CLR;
			return;//don't start any pwm channel
		}
		ML_GO;
		pwm_start_channels((1 << MOTOR_L)); //Start PWM Channel on M0 line
	}
	
	if(Motors & MOTOR_R)
	{
		if(Motor_Control.Right_State == FORWARD)
		{
			MR_IN1_SET;
			MR_IN2_CLR;
		}
		else if (Motor_Control.Right_State == BACKWARD)
		{
			MR_IN1_CLR;
			MR_IN2_SET;
		}
		else //Somethings gone wrong
		{
			MR_IN1_CLR;
			MR_IN2_CLR;
			return;//don't start any pwm channel
		}
		MR_GO;
		pwm_start_channels((1 << MOTOR_R));
	}	
}

#define HYST_MAX	10
#define SAMPLE_TIME	10
void Motors_Execute()
{
	LEDMOTOR_SET;
	int Left_State = acifa_is_acb_inp_higher(&AVR32_ACIFA1);
	int Right_State = acifa_is_aca_inp_higher(&AVR32_ACIFA1);
	int Left_Hyst = 0;
	int Right_Hyst = 0;
	bool Left_OnTab = false;
	bool Right_OnTab = false;
	
	while(Motors_Moving())
	{
		///////////////////////////////////////////////////////
		// LEFT MOTOR /////////////////////////////////////////
		///////////////////////////////////////////////////////
		Left_OnTab = acifa_is_acb_inp_higher(&AVR32_ACIFA1); //Read the status of the comparator
		
		if(Left_State == 0) //State Not on Tab
		{
			LED5_CLR;
			if(Left_OnTab == true)
			{
				Left_Hyst++;
				if(Left_Hyst == HYST_MAX)//reached threshold, change state
				{
					Left_State = 1;
					Motor_Control.Left_Count--; //Decrement the global counter
					Left_Hyst = 0;
					print_dbg("\n\rLeft Count Decrement");
				}
			}
			else //Reset counter
			{
				Left_Hyst = 0;
			}
		}
		else //State On Tab
		{
			LED5_SET;
			if(Left_OnTab == true)//still on a tab
			{
				Left_Hyst = 0;//Reset counter
			}
			else
			{
				Left_Hyst ++;
				if(Left_Hyst == HYST_MAX)//Reached Threshold. Change state
				{
					Left_State = 0;
					Left_Hyst = 0;
				}
			}
		}			
		///////////////////////////////////////////////////////
		// RIGHT MOTOR ////////////////////////////////////////
		///////////////////////////////////////////////////////	
		Right_OnTab = acifa_is_aca_inp_higher(&AVR32_ACIFA1); //Read the status of the comparator
		
		if(Right_State == 0) //State Not on Tab
		{
			LED6_CLR;
			if(Right_OnTab == true)
			{
				Right_Hyst++;
				if(Right_Hyst == HYST_MAX)//reached threshold, change state
				{
					Right_State = 1;
					Motor_Control.Right_Count--; //Decrement the global counter
					Right_Hyst = 0;
					print_dbg("\n\rRight Count Decrement");
				}
			}
			else //Reset counter
			{
				Right_Hyst = 0;
			}
		}
		else //State On Tab
		{
			LED6_SET;
			if(Right_OnTab == true)//still on a tab
			{
				Right_Hyst = 0;//Reset counter
			}
			else
			{
				Right_Hyst ++;
				if(Right_Hyst == HYST_MAX)//Reached Threshold. Change state
				{
					Right_State = 0;
					Right_Hyst = 0;
				}
			}
		}
		int temp = 0;
		if(Motor_Control.Left_Count <= 0) //if we have reached the end of the movement on left wheel
			temp |= MOTOR_L;
		
		if(Motor_Control.Right_Count <= 0)
			temp |= MOTOR_R;
		if(temp != 0)
			Motor_Stop(temp); //Stop the Motor
		
		//Delay to keep a low sample time
		delay_ms(SAMPLE_TIME);
	}
	LEDMOTOR_CLR;
}
void Motor_Stop(int Motors)
{
	if(Motors & MOTOR_L)
	{
		ML_STANDBY;
		Motor_Control.Left_State = STOP;
		pwm_stop_channels((1 << MOTOR_L)); //Start PWM Channel on M0 line
	}
	
	if(Motors & MOTOR_R)
	{
		MR_STANDBY;
		Motor_Control.Right_State = STOP;
		pwm_stop_channels((1 << MOTOR_R));
	}
}
int Motors_Move(int millimetres_fwd)//Move this amount forward in centimeters
{
	//Calculate number of interrupts of each wheel
	int number_interrupts; 
	int distance_moved; 
	if(millimetres_fwd > 0)
	{
		Motor_Control.Left_State = FORWARD;
		Motor_Control.Right_State = FORWARD;
	}
	else 
	{
		millimetres_fwd = Abs(millimetres_fwd);
		Motor_Control.Left_State = BACKWARD;
		Motor_Control.Right_State = BACKWARD;
	}
	number_interrupts = (millimetres_fwd * (int)GAMMA) / (int)CIRCUMFERENCE_WHEEL_MM; 
	distance_moved = number_interrupts * MIN_DISTANCE_RESOLUTION;
	print_dbg("\n\rNumber of interrupts to move = ");
	print_dbg_ulong(number_interrupts);
	
	Motor_Control.Left_Count = number_interrupts;
	Motor_Control.Right_Count = number_interrupts;
	Motor_Start(MOTOR_L | MOTOR_R);
	Motors_Execute();
	return distance_moved;
}

void Motors_Reset(void)
{
	Motor_Control.Left_State = FORWARD;
	Motor_Control.Left_Count = 1;
	Motor_Control.Right_State = FORWARD;
	Motor_Control.Right_Count = 1;
	Motor_Start(MOTOR_L | MOTOR_R);
	Motors_Execute();
}

bool Motors_Moving()
{
// 	if(Motor_Control.Left_State != STOP)
// 	{
// 		if(Motor_Control.Right_State != STOP)
// 		{
// 			return true;
// 		}
// 		else
// 			return false;
// 	}
// 	else
// 	{
// 		return false;
// 	}
	if(Motor_Control.Left_State != STOP) //Left is moving
	{
		return true;
	}
	else if (Motor_Control.Right_State != STOP) //Right is moving
	{
		return true;
	}
	else
	{
		return false;
	}
}


int Motors_Rotate(int angle_degs)
{
	int interrupts_to_move = 0; 
	int angle_rotated;
	//calculate interrupts to move
	interrupts_to_move = angle_degs * ROTATION_CONST;
	angle_rotated = interrupts_to_move * ROTATION_CONST_INV;
// 	if(Pivot_Type == LEFT_SPOT)
// 	{
// 		//Right wheel moves
// 		Motor_Control.Left_Count = 0;
// 		Motor_Control.Left_State = STOP;
// 		if(interrupts_to_move > 0)
// 		{
// 			Motor_Control.Right_State = FORWARD;
// 		}
// 		else
// 		{
// 			Motor_Control.Right_State = BACKWARD;
// 		}
// 		Motor_Control.Right_Count = Abs(interrupts_to_move);
// 	}
// 	else if (Pivot_Type == RIGHT_SPOT)
// 	{
// 		//Left Wheel Moves
// 		Motor_Control.Right_Count = 0;
// 		Motor_Control.Right_State = STOP;
// 		if(interrupts_to_move > 0)
// 		{
// 			Motor_Control.Left_State = FORWARD;
// 		}
// 		else
// 		{
// 			Motor_Control.Left_State = BACKWARD;
// 		}
// 		Motor_Control.Left_Count = Abs(interrupts_to_move);
// 	}
// 	else if (Pivot_Type == SPOT_PIVOT)
// 	{
		//Both Wheels Move
		if(interrupts_to_move > 0)
		{
			Motor_Control.Left_State = FORWARD;
			Motor_Control.Right_State = BACKWARD;
		}
		else
		{
			Motor_Control.Right_State = FORWARD;
			Motor_Control.Left_State = BACKWARD;
		}
		Motor_Control.Left_Count = Abs(interrupts_to_move);
		Motor_Control.Right_Count = Abs(interrupts_to_move);
		Motor_Start(MOTOR_L | MOTOR_R);
		Motors_Execute();
		return angle_rotated;
	//}
}