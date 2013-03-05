/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>
#include "CustomDevices/CustomDevices.h"

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	//Initialise Clocks
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
	//initialise Debug USART
	init_dbg_rs232(FOSC0);
	//Throw some text out.
	print_dbg("\x0C");
	print_dbg("The Columbus\n\n\r");
	sdramc_init(FOSC0);//SDRAM initialise
	sd_mmc_resources_init();//SD Card Init
	INTC_init_interrupts();
	twim_init();
	Motor_Init();
	OV7670_Init();
	
	//Allocate Memory Space
	sdram_msp = create_mspace_with_base((void*) SDRAM_START_ADDRESS, MEM_SPACE_SIZE, 0);
	
	Enable_global_interrupt();
}
void SD_Card_Test()
{
	uint32_t VarTemp;
	//print_dbg("\n\n\rSD Card Memory Test:\n\r");
	// Test if the memory is ready - using the control access memory abstraction layer (/SERVICES/MEMORY/CTRL_ACCESS/)
	if (mem_test_unit_ready(LUN_ID_SD_MMC_SPI_MEM) == CTRL_GOOD)
	{
		SD_Status.Status = STATUS_OK;
		// Get and display the capacity
		mem_read_capacity(LUN_ID_SD_MMC_SPI_MEM, &VarTemp);
		/*		print_dbg("OK:\t");*/
		SD_Status.Memory_size = (VarTemp + 1) >> (20 - FS_SHIFT_B_TO_SECTOR);
		// 		print_dbg_ulong(Columbus_Status.SD_Card->Memory_size);
		// 		print_dbg("MB\r\n");
		// 		print_dbg("SD Card Okay.\n\r");
		nav_reset();
		// Use the last drive available as default.
		nav_drive_set(nav_drive_nb() - 1);
		// Mount it.
		nav_partition_mount();
		nav_filelist_reset();
		if(nav_filelist_findname((FS_STRING)LOG_FILE, false))
		{
			//print_dbg("\n\rLog File Already Exists\n\rAttempting to delete...");	
			nav_setcwd((FS_STRING)LOG_FILE, true, false);
			nav_file_del(false);
		}

		if(nav_file_create((FS_STRING)LOG_FILE) == false)
			SD_Status.Status = ERR_IO_ERROR;//print_dbg("\n\rNot worked...");
	
		nav_setcwd((FS_STRING)LOG_FILE, true, false);
		file_open(FOPEN_MODE_APPEND);
		file_write_buf("SD Card Test\n\r", 14);
		file_close();
	}
	else
	{
		SD_Status.Status = ERR_IO_ERROR;
	}
}

void System_Test()
{
	SD_Card_Test();
	if(SD_Status.Status != STATUS_OK)
	{
		Columbus_Status.Status |= SD_ERR;
		print_dbg("\n\rSD Card Error!");
	}	
	if(OV7670_Status.Status != STATUS_OK)
	{
		Columbus_Status.Status |= CAM_ERR;
		print_dbg("\n\rCamera Error(s): ");
		print_dbg_ulong(OV7670_Status.Status);
	}	
	if(PCA9542A.Status != STATUS_OK)
	{
		Columbus_Status.Status |= I2CMux_ERR;
		print_dbg("\n\rI2C Mux Error!");
	}		
	
	if(Columbus_Status.Status == STATUS_OK)
		print_dbg("\n\rSystem Check: PASS;");
	else
		print_dbg("\n\rSystem Check: FAIL;");
}
