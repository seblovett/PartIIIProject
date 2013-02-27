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
// Camera
// #include "CustomDevices/OV7670.h"
// I2C Mux
// #include "CustomDevices/PCA9542A.h"
// MotorDriver
// #include "CustomDevices/MotorDriver.h"
// SDCard
// #include "CustomDevices/SD_Card.h"
#include "CustomDevices/CustomDevices.h"
#include "conf_sd_mmc_spi.h"
#include "fat.h"
#include "file.h"
#include "navigation.h"


#define LOG_FILE "log.txt"

typedef struct {
		SD_Status_t *SD_Card;
		Motor_Control_t *Motors;
		OV7670_t *Cameras;
		PCA9542A_t *I2CMux;
	} Columbus_Status_t;
	
Columbus_Status_t Columbus_Status;

void Log_Write(char *buff, int length) 
{
	nav_setcwd((FS_STRING)LOG_FILE, true, false);
	file_open(FOPEN_MODE_APPEND);
	if(length == -1)
		length = sizeof(buff);
	file_write_buf(buff, length);
	file_close();
}
void Log_Write_ulong(unsigned long n)
{
	char tmp[11];
	int i = sizeof(tmp) - 1;

	// Convert the given number to an ASCII decimal representation.
	tmp[i] = '\0';
	do
	{
	tmp[--i] = '0' + n % 10;
	n /= 10;
	} while (n);

	// Transmit the resulting string with the given USART.
	Log_Write(tmp + i, -1);
}
int main (void)
{
	unsigned long i, j, tmp = 0;
	volatile unsigned long *sdram = SDRAM;
	uint32_t VarTemp;
	Columbus_Status.SD_Card = &SD_Status;
	Columbus_Status.Cameras = &OV7670_Status;
	Columbus_Status.I2CMux = &PCA9542A_Status;
	Columbus_Status.SD_Card = &SD_Status;
	board_init();
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
	init_dbg_rs232(FOSC0);
	
	print_dbg("\x0C");
	print_dbg("Columbus Board Tester\n\n\r");
	sdramc_init(FOSC0);
	sd_mmc_resources_init();
	INTC_init_interrupts();
	twim_init();
	
	Motor_Init();
	OV7670_Init();
	Enable_global_interrupt();
// 	
	print_dbg("\n\n\rSD Card Memory Test:\n\r");
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
			SD_Status.Status = ERROR + 1;//print_dbg("\n\rNot worked...");
	
		Log_Write("Columbus Tester:\n\r", -1);
		}
	else
	{
		SD_Status.Status = ERROR;
	}
	
	print_dbg("\n\rResetting Motors.");
	
	Motors_Reset();
	while(Motors_Moving() == true)
		;

// 	FIFO_Reset(CAMERA_LEFT | CAMERA_RIGHT);
// 	print_dbg("\n\rTaking Photos");
// 	TakePhoto(CAMERA_LEFT | CAMERA_RIGHT);
// 	while(Photos_Ready() == false)
// 		;
// 
// 	if(Store_Both_Images() == true)
// 		print_dbg("\n\rImages Stored Successfully!");
		
	print_dbg("\n\rColumbus Ready!");
	// Insert application code here, after the board has been initialized.
	while(1)
	{


	}
}
