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
//Camera
#include "CustomDevices/OV7670.h"
//I2C Mux
#include "CustomDevices/PCA9542A.h"
//MotorDriver
#include "CustomDevices/MotorDriver.h"
//SDCard
#include "CustomDevices/SD_Card.h"
#include "conf_sd_mmc_spi.h"
#include "fat.h"
#include "file.h"
#include "navigation.h"

#define TWIM               (&AVR32_TWIM0)  //! TWIM Module Used

#define TARGET_ADDRESS     0x0            //! Target's TWI address
#define TARGET_ADDR_LGT    3               //! Internal Address length
#define VIRTUALMEM_ADDR    0x123456        //! Internal Address
#define TWIM_MASTER_SPEED  50000           //! Speed of TWI
static void twim_init (void)
{
	int8_t status;
	/**
	* \internal
	* PIN 2 & 3 in Header J24 can be used in EVK1104
	* PIN 1 & 2 in Header J44 can be used in UC3C_EK
	* \endinternal
	*/
	const gpio_map_t TWIM_GPIO_MAP = {
	{AVR32_TWIMS0_TWCK_0_0_PIN, AVR32_TWIMS0_TWCK_0_0_FUNCTION},
	{AVR32_TWIMS0_TWD_0_0_PIN, AVR32_TWIMS0_TWD_0_0_FUNCTION}
	};

	// Set TWIM options
	const twi_options_t TWIM_OPTIONS = {
		.pba_hz = FOSC0,
		.speed = TWIM_MASTER_SPEED,
		.chip = TARGET_ADDRESS,
		.smbus = false,
	};
	// TWIM gpio pins configuration
	gpio_enable_module (TWIM_GPIO_MAP,
			sizeof (TWIM_GPIO_MAP) / sizeof (TWIM_GPIO_MAP[0]));
	
	// Initialize as master.
	status = twim_master_init (TWIM, &TWIM_OPTIONS);

}

#define LOG_FILE "log.txt"


void LED_Flash()
{
	LED2_SET;
	delay_s(1);
	LED2_CLR;
	delay_s(1);
}

#define TOGGLE LED_Flash

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
	nav_reset();
	// Use the last drive available as default.
	nav_drive_set(nav_drive_nb() - 1);
	// Mount it.
	nav_partition_mount();
	nav_filelist_reset();
	if(nav_filelist_findname((FS_STRING)LOG_FILE, false))
	{
		print_dbg("\n\rLog File Already Exists\n\rAttempting to delete...");	
		nav_setcwd((FS_STRING)LOG_FILE, true, false);
		nav_file_del(false);
		
		if(nav_filelist_findname((FS_STRING)LOG_FILE, false))
			print_dbg("\n\rLog File Still Exists...");
		else
			print_dbg("\n\rLog File Deleted!");
	}
	
	
	print_dbg("\n\rCreating Log File.");
	//char buff[20] = "log.txt";
	if(nav_file_create((FS_STRING)LOG_FILE) == true)
		print_dbg("\n\rSuccess!");
	else
		print_dbg("\n\rNot worked...");
	
	
	Log_Write("Columbus Tester:\n\r", -1);

	

	print_dbg("Resetting Motors.");
	
	Motors_Reset();
	while(Motors_Moving() == true)
		;

	FIFO_Reset(CAMERA_LEFT | CAMERA_RIGHT);
	print_dbg("\n\rTaking Photos");
	TakePhoto(CAMERA_LEFT | CAMERA_RIGHT);
	while(Photos_Ready() == false)
		;

	if(Store_Both_Images() == true)
		print_dbg("\n\rImages Stored Successfully!");
		
	print_dbg("\n\rTest Complete!");
	// Insert application code here, after the board has been initialized.
	while(1)
	{
		TOGGLE();

	}
}
