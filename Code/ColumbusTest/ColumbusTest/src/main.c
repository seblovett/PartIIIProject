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

int main (void)
{
	unsigned long sdram_size, progress_inc, i, j, tmp, noErrors = 0;
  volatile unsigned long *sdram = SDRAM;
	board_init();
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
	init_dbg_rs232(FOSC0);
	print_dbg("\x0C Columbus Board Tester");
	print_dbg("\n\rAll LEDS on;");
	LEDMOTOR_SET;
	LED2_SET;
	LED3_SET;
	LED4_SET;
	LED5_SET;
	LED6_SET;
	delay_s(1);
	print_dbg("\n\rAll LEDS off;");
	LEDMOTOR_CLR;
	LED2_CLR;
	LED3_CLR;
	LED4_CLR;
	LED5_CLR;
	LED6_CLR;
	delay_s(1);
	
	
	sdram_size = SDRAM_SIZE >> 2;
	print_dbg("\n\rSDRAM size: ");
	print_dbg_ulong(SDRAM_SIZE >> 20);
	print_dbg(" MB\r\n");
	sdramc_init(FOSC0);
	print_dbg("SDRAM initialized\r\n");
	// Determine the increment of SDRAM word address requiring an update of the
	// printed progression status.
	progress_inc = (sdram_size + 50) / 100;
	// Fill the SDRAM with the test pattern.
	for (i = 0, j = 0; i < sdram_size; i++)
	{
		if (i == j * progress_inc)
		{
			//LED_Toggle(LED_SDRAM_WRITE);
			print_dbg("\rFilling SDRAM with test pattern: ");
			print_dbg_ulong(j++);
			print_dbg_char('%');
		}
		sdram[i] = i;
		
	}
	//LED_Off(LED_SDRAM_WRITE);
	print_dbg("\rSDRAM filled with test pattern       \r\n");
	
	// Recover the test pattern from the SDRAM and verify it.
	for (i = 0, j = 0; i < sdram_size; i++)
	{
		
		if (i == j * progress_inc)
		{
			//LED_Toggle(LED_SDRAM_READ);
			print_dbg("\rRecovering test pattern from SDRAM: ");
			print_dbg_ulong(j++);
			print_dbg_char('%');
		}
		tmp = sdram[i];
		if (tmp != i)//failed
		{
// 			print_dbg("\n\rError occurred at address: ");
// 			print_dbg_ulong(i);
// 			print_dbg("Data returned: ");
// 			print_dbg_ulong(tmp);
			noErrors++;
		}

	}
	//LED_Off(LED_SDRAM_READ);
	print_dbg("\rSDRAM tested: ");
	print_dbg_ulong(noErrors);
	print_dbg(" corrupted word(s)       \r\n");
	if (noErrors)
	{
		//LED_Off(LED_SDRAM_ERRORS);

			//LED_Toggle(LED_SDRAM_ERRORS);
			LED3_SET;
			cpu_delay_ms(200, FOSC0);   // Fast blink means errors.

	}
	else
	{
		//LED_Off(LED_SDRAM_OK);

			//LED_Toggle(LED_SDRAM_OK);
			LED2_SET;
			cpu_delay_ms(1000, FOSC0);  // Slow blink means OK.

	}
	
// 	for(i = 1; i < sdram_size; i <<= 1)
// 	{
// 		print_dbg("\n\rWriting to address ");
// 		print_dbg_ulong(i);
// 		print_dbg(" value ");
// 		j = 0xFFFFFFFF;
// 		print_dbg_ulong(j);
// 		sdram[i] = j;
// 		print_dbg("\n\rReturned: ");
// 		print_dbg_ulong(sdram[i]);
// 		
// 		print_dbg("\n\rWriting to address ");
// 		print_dbg_ulong(i);
// 		print_dbg(" value ");
// 		j = 0;
// 		print_dbg_ulong(j);
// 		sdram[i] = j;
// 		print_dbg("\n\rReturned: ");
// 		print_dbg_ulong(sdram[i]);
// 	}
	
	for(i = 0; i < 10; i++)
	{
		sdram[i] = i;
		print_dbg("\n\rWritten data: ");
		print_dbg_ulong(i);
		print_dbg("\n\rRead data: ");
		print_dbg_ulong(sdram[i]);
	}
// 	for(i = 0; i < sdram_size; i ++)
// 	{
// 		sdram[i] = i;
// 		if(i == sdram[i])
// 			print_dbg("Pass!");
// 		else
// 			print_dbg("Fail.");
// 	}
	print_dbg("\n\rTest Complete!");
	// Insert application code here, after the board has been initialized.
	while(1)
	{
		
		
	}
}
