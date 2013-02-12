/*
 * MotorDriver.c
 *
 * Created: 10/02/2013 18:12:07
 *  Author: hslovett
 */ 
#include <asf.h>
#include "CustomDevices/MotorDriver.h"



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
  pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);

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
// 	scif_gc_setup(	AVR32_SCIF_GCLK_PWM,
// 					PCL_OSC0,
// 					AVR32_SCIF_GC_NO_DIV_CLOCK,
// 					0);
  // Now enable the generic clock
  scif_gc_enable(AVR32_SCIF_GCLK_PWM);
}
#  define EXAMPLE_PWM_L_PIN             AVR32_PWM_PWML_0_1_PIN
#  define EXAMPLE_PWM_L_FUNCTION        AVR32_PWM_PWML_0_1_FUNCTION
#  define EXAMPLE_PWM_H_PIN             AVR32_PWM_PWMH_0_1_PIN
#  define EXAMPLE_PWM_H_FUNCTION        AVR32_PWM_PWMH_0_1_FUNCTION
#  define EXAMPLE_PWM_CHANNEL_ID        0
void Motor_Init()
{
	//Turn boths motors off
// 	M0_STANDBY;
// 	M1_STANDBY;
	
	M0_IN1_CLR;
	M0_IN2_CLR;
	
	M1_IN1_CLR;
	M1_IN2_CLR;
	
	//initialise PWM
// 	scif_gc_setup(AVR32_SCIF_GCLK_PWM, SCIF_GCCTRL_OSC0, AVR32_SCIF_GC_NO_DIV_CLOCK, 0);
// 	// Now enable the generic clock
// 	scif_gc_enable(AVR32_SCIF_GCLK_PWM);

	avr32_pwm_channel_t pwm_channel = {{0}, // cmr
											{0}, // cdty
											{0}, // cdtyupd
											{0}, // cprd
											{0}, // cprdupd
											{0}, // ccnt
											{0}, // dt
											{0}};// dtupd  ;  One channel config.
		unsigned int channel_id;
	
		// Start Main Clock On external 16MHz Oscillator
		// Start PLL for PWM
		local_start_highfreq_clock();
		// Start Enable Generic Clock with PLL as source clock
		pwm_start_gc();
	
		channel_id = EXAMPLE_PWM_CHANNEL_ID;
		gpio_enable_module_pin(EXAMPLE_PWM_L_PIN, EXAMPLE_PWM_L_FUNCTION);
		gpio_enable_module_pin(EXAMPLE_PWM_H_PIN, EXAMPLE_PWM_H_FUNCTION);
		// PWM controller configuration.
		pwm_opt.diva = AVR32_PWM_DIVA_CLK_OFF;
		pwm_opt.divb = AVR32_PWM_DIVB_CLK_OFF;
		pwm_opt.prea = AVR32_PWM_PREA_CCK;
		pwm_opt.preb = AVR32_PWM_PREB_CCK;
	
		pwm_opt.fault_detection_activated = false;
		pwm_opt.sync_channel_activated    = true;
		pwm_opt.sync_update_channel_mode  = PWM_SYNC_UPDATE_MANUAL_WRITE_MANUAL_UPDATE;
		pwm_opt.sync_channel_select[0]    = true;
		pwm_opt.sync_channel_select[1]    = true;
		pwm_opt.sync_channel_select[2]    = false;
		pwm_opt.sync_channel_select[3]    = false;
		pwm_opt.cksel                     = PWM_CKSEL_GCLK;
		pwm_init(&pwm_opt);
	
		// Update the period
		pwm_update_period_value(10);
	
		// Channel configuration
		pwm_channel.CMR.dte   = 0;        // Enable Deadtime for complementary Mode
		pwm_channel.CMR.dthi  = 0;        // Deadtime Inverted on PWMH
		pwm_channel.CMR.dtli  = 0;        // Deadtime Not Inverted on PWML
		pwm_channel.CMR.ces   = 0;        // 0/1 Channel Event at the End of PWM Period
		pwm_channel.CMR.calg  = PWM_MODE_LEFT_ALIGNED;       // Channel mode.
		pwm_channel.CMR.cpol  = PWM_POLARITY_LOW;            // Channel polarity.
		pwm_channel.CMR.cpre  = AVR32_PWM_CPRE_CCK;           // Channel prescaler.
		pwm_channel.cdty      = 100;       // Channel duty cycle, should be < CPRD.
		pwm_channel.cprd      = 200;       // Channel period.
	
		// With these settings, the output waveform period will be :
		// (56MHz)/20 == 2.8MHz == (MCK/prescaler)/period, with MCK == 56MHz,
		// prescaler == 1, period == 20.

	pwm_channel_init(channel_id, &pwm_channel); // Set channel configuration to channel 0
	pwm_start_channels((1 << channel_id));  // Start channel 0 & 1.
}

void Motor_Go(int Direction)
{
	switch(Direction)
	{
		case STOP: //Stop Movement
			M0_STANDBY;
			M1_STANDBY;
			M0_IN1_CLR;
			M0_IN2_CLR;
			M1_IN1_CLR;
			M1_IN2_CLR;
			break;
			
		case FORWARD://Drive Both Motors Forward
			M0_IN1_SET;
			M1_IN1_SET;
			M0_IN2_CLR;
			M1_IN2_CLR;
// 			M0_PWM_HIGH;
// 			M1_PWM_HIGH;
			M0_GO;
			M1_GO;
			break;
			
		case BACKWARD:
			M0_IN1_CLR;
			M1_IN1_CLR;
			M0_IN2_SET;
			M1_IN2_SET;
			M0_GO;
			M1_GO;
			break;
			
		
		default://Something is wrong.
			return;
	}
	
}