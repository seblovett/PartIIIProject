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
#include <conf_board.h>
//#include "SD_Card.h"
#include "CustomDevices/SD_Card.h"
#include "conf_sd_mmc_spi.h"


// Software wait



int main (void)
{
	unsigned long sdram_size, progress_inc, i, j, tmp, noErrors = 0;
	volatile unsigned long *sdram = SDRAM;
	uint32_t VarTemp;
	board_init();
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
	init_dbg_rs232(FOSC0);
	print_dbg("\x0C");
	print_dbg("Columbus Board Tester\n\n\r");
	print_dbg("LED Test:\n\rAll LEDS on;");
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
	
	print_dbg("\n\n\rSDRAM Test:");
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
	print_dbg("\rSDRAM filled with test pattern       \r\n");
	// Recover the test pattern from the SDRAM and verify it.
	for (i = 0, j = 0; i < sdram_size; i++)
	{
		
		if (i == j * progress_inc)
		{
			print_dbg("\rRecovering test pattern from SDRAM: ");
			print_dbg_ulong(j++);
			print_dbg_char('%');
		}
		tmp = sdram[i];
		if (tmp != i)//failed
		{
			noErrors++;
		}

	}
	print_dbg("\rSDRAM tested: ");
	print_dbg_ulong(noErrors);
	print_dbg(" corrupted word(s)       \r\n");
	if (noErrors)
	{
			LED3_SET;
	}
	else
	{
			LED2_SET;
	}
	
	
	for(i = 0; i < 10; i++)
	{
		sdram[i] = i;
		print_dbg("\n\rWritten data: ");
		print_dbg_ulong(i);
		print_dbg("\n\rRead data: ");
		print_dbg_ulong(sdram[i]);
	}

	sd_mmc_resources_init();
	//sd_mmc_resources_init();
	print_dbg("\n\n\rSD Card Memory Test:\n\r");
	// Test if the memory is ready - using the control access memory abstraction layer (/SERVICES/MEMORY/CTRL_ACCESS/)
	if (mem_test_unit_ready(LUN_ID_SD_MMC_SPI_MEM) == CTRL_GOOD)
	{
		// Get and display the capacity
		mem_read_capacity(LUN_ID_SD_MMC_SPI_MEM, &VarTemp);
		print_dbg("OK:\t");
		print_dbg_ulong((VarTemp + 1) >> (20 - FS_SHIFT_B_TO_SECTOR));
		print_dbg("MB\r\n");
		print_dbg("SD Card Okay.\n\r");
	}
	else
	{
		// Display an error message
		print_dbg("Not initialized: Check if memory is ready...\r\n");
	}






	print_dbg("\n\rTest Complete!");
	// Insert application code here, after the board has been initialized.
	while(1)
	{
		
		
	}
}
