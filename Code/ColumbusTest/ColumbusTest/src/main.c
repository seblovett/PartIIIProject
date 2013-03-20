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

void LED_Flash()
{
	LED2_SET;
	delay_s(1);
	LED2_CLR;
	delay_s(1);
}

#define TOGGLE LED_Flash
#define LOG_FILE "log.txt"
void Log_Write(char *buff, int length) 
{
	nav_setcwd((FS_STRING)LOG_FILE, true, false);
	file_open(FOPEN_MODE_APPEND);
	
	
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
	unsigned long sdram_size, progress_inc, i, j, k, tmp, noErrors = 0;
	volatile unsigned long *sdram = SDRAM;
	uint32_t VarTemp;
	char Buffer[16];
	board_init();
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
	
	// Initialize interrupt vector table support.
	irq_initialize_vectors();

	// Enable interrupts
	sd_mmc_resources_init();
	INTC_init_interrupts();
	twim_init();
	PCA9542A_Init();
	sdramc_init(FOSC0);
	OV7670_Init();
	Motor_Init();
	init_dbg_rs232(FOSC0);
	Enable_global_interrupt();
	//////////////////////////////////////////////////
	// UART Test /////////////////////////////////////
	//////////////////////////////////////////////////
	uint8_t ch;
	while (true) {
		ch = usart_getchar(DBG_USART); // get one input character
		if (ch) {
			print_dbg(ch); // echo to output
		}
		if(ch == 13)
			break;
	}
	print_dbg("\xC");
	print_dbg("Columbus Board Tester\n\n\r");	
	//////////////////////////////////////////////////
	// SD Card Test //////////////////////////////////
	//////////////////////////////////////////////////
	print_dbg("\n\n\rSD Card Memory Test:\n\r");
	// Test if the memory is ready - using the control access memory abstraction layer (/SERVICES/MEMORY/CTRL_ACCESS/)
	if (mem_test_unit_ready(LUN_ID_SD_MMC_SPI_MEM) == CTRL_GOOD)
	{
		// Get and display the capacity
		mem_read_capacity(LUN_ID_SD_MMC_SPI_MEM, &VarTemp);
		print_dbg("OK:\t");
		//printf_ulong((VarTemp + 1) >> (20 - FS_SHIFT_B_TO_SECTOR));
		i = ((VarTemp + 1) >> (20 - FS_SHIFT_B_TO_SECTOR));
		print_dbg_ulong(i);
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
	
	if(nav_file_create((FS_STRING)LOG_FILE) == true)
		print_dbg("\n\rSuccess!");
	else
		print_dbg("\n\rNot worked...");
	print_dbg("\n\rWriting to log file.");
	Log_Write("Columbus Tester:\n\r", 18);
	nav_filelist_reset();
	nav_setcwd((FS_STRING)LOG_FILE, true, false);
	file_open(FOPEN_MODE_R);//Open File
	file_read_buf(Buffer, 8);
	noErrors = 0;
	if(Buffer[0] != 'C')
		noErrors++;
	if(Buffer[1] != 'o')
		noErrors++;
	if(Buffer[2] != 'l')
		noErrors++;
	if(Buffer[3] != 'u')
		noErrors++;
	if(Buffer[4] != 'm')
		noErrors++;
	if(Buffer[5] != 'b')
		noErrors++;
	if(Buffer[6] != 'u')
		noErrors++;
	if(Buffer[7] != 's')
		noErrors++;
	file_close();
	if(noErrors == 0)
		print_dbg("\n\rSD Card Read Successful\n\r");
	else
		print_dbg("\n\rSD Card Read Fail\n\r");
	noErrors = 0;
	//////////////////////////////////////////////////
	// LED Test //////////////////////////////////////
	//////////////////////////////////////////////////
	print_dbg("\n\rLED Test:\n\rAll LEDS on;");
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
	
	//////////////////////////////////////////////////
	// SDRAM Test ////////////////////////////////////
	//////////////////////////////////////////////////
	print_dbg("\n\n\rSDRAM Test:");
	sdram_size = SDRAM_SIZE >> 2;
	print_dbg("\n\rSDRAM size: ");
	print_dbg_ulong(SDRAM_SIZE >> 20);
	print_dbg(" MB\r\n");
	// Determine the increment of SDRAM word address requiring an update of the
	// printed progression status.
	progress_inc = (sdram_size + 50) / 100;
	// Fill the SDRAM with the test pattern.
	for (i = 0, j = 0; i < sdram_size; i++)
	{
		if (i == j * progress_inc)
		{
			print_dbg("\rFilling SDRAM with test pattern:");
			print_dbg_ulong(j++);
			print_dbg("%");
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
			print_dbg("%");
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
	
	//////////////////////////////////////////////////
	// TWI Test //////////////////////////////////////
	//////////////////////////////////////////////////
 	print_dbg("\n\n\rTWI Test:\n\r");
	Log_Write("\n\n\rTWI Test:\n\r", 14);
	for(k = 0; tkmp < 3; k++)
	{
		if(k == 0){
			print_dbg("Scanning all Channels\n\r");
		}
		else if (k == 1){
			//Channel 0
			PCA9542A_Chan_Sel(I2C_CHANNEL_0);
			print_dbg("\n\rScanning Channel 0\n\r");
		}
		else {
			//Channel 1
			PCA9542A_Chan_Sel(I2C_CHANNEL_1);
			print_dbg("\n\rScanning Channel 1\n\r");
		}
		
		print_dbg("h 0 1 2 3 4 5 6 7 8 9 A B C D E F\n\r");
		tmp = 0;
		for(i = 0; i < 8; i++)
		{
			print_dbg_ulong(i);
			print_dbg(" ");
			for(j = 0; j < 16; j++){
				int status = twim_probe(TWIM, tmp++);
				if(status == STATUS_OK){
					print_dbg("A");
				}
				else{
					print_dbg("-");
				}
				print_dbg(" ");
			}
			print_dbg("\n\r");
		}
	}	
	noErrors = 0;
	//Check cameras exist
	PCA9542A_Chan_Sel(I2C_CHANNEL_0);
	if(twim_probe(TWIM, 0x21) != STATUS_OK)
		print_dbg("\n\rCamera 0 Not Found;");
	PCA9542A_Chan_Sel(I2C_CHANNEL_1);
	if(twim_probe(TWIM, 0x21) != STATUS_OK)
		print_dbg("\n\rCamera 1 Not Found;");
	//////////////////////////////////////////////////
	// Camera Test ///////////////////////////////////
	//////////////////////////////////////////////////
	print_dbg("\n\rInitialising Cameras");
	OV7670_Init();
	FIFO_Reset(CAMERA_LEFT | CAMERA_RIGHT);
	if(STATUS_OK == OV7670_Status.Error)
	{
		print_dbg("\n\rCamera Initialise Okay!");
	}
	else
		print_dbg("\n\rCamara Initialise Fail.");
		
	print_dbg("\n\rTaking Photos");

	TakePhoto(CAMERA_LEFT | CAMERA_RIGHT);
	while(Photos_Ready() == false)
		;

	if(Store_Both_Images() == true)
		print_dbg("\n\rImages Stored Successfully!");
	else
		print_dbg("\n\rImages Store Fail.");
	//////////////////////////////////////////////////
	// Motor Test ////////////////////////////////////
	//////////////////////////////////////////////////
	print_dbg("\n\rMotor Testing:\n\rMotor Initialised");
 	Motor_Init();
	Motors_Reset();//reset the motors to test them
	while(Motors_Moving() == true)
		;//wait for the motors to finish moving
		
	print_dbg("\n\rTest Complete!");
	
	while(1)
	{
		TOGGLE();

	}
}
