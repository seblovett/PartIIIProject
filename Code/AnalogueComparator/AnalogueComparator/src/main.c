/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include <uc3c0512c.h>
//Comparator A
#define POT0_AC1AP1_INPUT		1
#define POT0_AC1AP1_PIN			AVR32_AC1AP1_PIN
#define POT0_AC1AP1_FUNCTION	AVR32_AC1AP1_FUNCTION

#define SENSE0_AC1AN1_INPUT		1
#define SENSE0_AC1AN1_PIN		AVR32_AC1AN1_PIN
#define SENSE0_AC1AN1_FUNCTION	AVR32_AC1AN1_FUNCTION

//Comparator B
#define POT1_AC1BP1_INPUT		3
#define POT1_AC1BP1_PIN			AVR32_AC1BP1_PIN
#define POT1_AC1BP1_FUNCTION	AVR32_AC1BP1_FUNCTION

#define SENSE1_AC1BN1_INPUT		1
#define SENSE1_AC1BN1_PIN		AVR32_AC1BN1_PIN
#define SENSE1_AC1BN1_FUNCTION	AVR32_AC1BN1_FUNCTION
static void ACInterruptHandler()
{
	;
}
int main (void)
{
	board_init();
	static const gpio_map_t ACIFA_GPIO_MAP =
	{
	{POT0_AC1AP1_PIN, POT0_AC1AP1_FUNCTION},
	{POT1_AC1BP1_PIN, POT1_AC1BP1_FUNCTION},
	{SENSE0_AC1AN1_PIN, SENSE0_AC1AN1_FUNCTION},
	{SENSE1_AC1BN1_PIN, SENSE1_AC1BN1_FUNCTION},
	};
	
	gpio_enable_module(ACIFA_GPIO_MAP, sizeof(ACIFA_GPIO_MAP) / sizeof(ACIFA_GPIO_MAP[0]));
	
	
	acifa_configure(&AVR32_ACIFA1,
					ACIFA_COMP_SELA,
					POT0_AC1AP1_INPUT,
					SENSE0_AC1AN1_INPUT,
					FOSC0);
					
	acifa_configure(&AVR32_ACIFA1,
					ACIFA_COMP_SELB,
					POT1_AC1BP1_INPUT,
					SENSE1_AC1BN1_INPUT,
					FOSC0);
					
	acifa_start(&AVR32_ACIFA1, (ACIFA_COMP_SELA|ACIFA_COMP_SELB));
	
	Disable_global_interrupt();
	
	INTC_init_interrupts();
	
	INTC_register_interrupt(&ACInterruptHandler,AVR32_ACIFA1_IRQ ,AVR32_INTC_INT0)
	
	// Insert application code here, after the board has been initialized.
}
