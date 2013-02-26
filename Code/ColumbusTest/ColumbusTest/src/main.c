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
#include <stdio_usb.h>

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
	unsigned long sdram_size, progress_inc, i, j, tmp, noErrors = 0;
	volatile unsigned long *sdram = SDRAM;
	uint32_t VarTemp;
	board_init();
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
	
	// Initialize interrupt vector table support.
	irq_initialize_vectors();

	// Enable interrupts
	sd_mmc_resources_init();
	INTC_init_interrupts();
	stdio_usb_init();
	twim_init();
	PCA9542A_Init();
	sdramc_init(FOSC0);
	OV7670_Init();
	Motor_Init();
	Enable_global_interrupt();
	/* Call a local utility routine to initialize C-Library Standard I/O over
	 * a USB CDC protocol. Tunable parameters in a conf_usb.h file must be
	 * supplied to configure the USB device correctly.
	 */
	//stdio_usb_init();
	uint8_t ch;
	
	while (true) {

		scanf("%c",&ch); // get one input character

		if (ch) {
			printf("%c",ch); // echo to output
		}
		if(ch == 13)
			break;
	}
	//init_dbg_rs232(FOSC0);
	printf("\xC");
	printf("Columbus Board Tester\n\n\r");
// 	sd_mmc_resources_init();
// 	INTC_init_interrupts();
// 	
	
	printf("\n\n\rSD Card Memory Test:\n\r");
	// Test if the memory is ready - using the control access memory abstraction layer (/SERVICES/MEMORY/CTRL_ACCESS/)
	if (mem_test_unit_ready(LUN_ID_SD_MMC_SPI_MEM) == CTRL_GOOD)
	{
		// Get and display the capacity
		mem_read_capacity(LUN_ID_SD_MMC_SPI_MEM, &VarTemp);
		printf("OK:\t");
		//printf_ulong((VarTemp + 1) >> (20 - FS_SHIFT_B_TO_SECTOR));
		i = ((VarTemp + 1) >> (20 - FS_SHIFT_B_TO_SECTOR));
		printf("%dMB\r\n", i);
		printf("SD Card Okay.\n\r");
	}
	else
	{
		// Display an error message
		printf("Not initialized: Check if memory is ready...\r\n");
	}
	nav_reset();
	// Use the last drive available as default.
	nav_drive_set(nav_drive_nb() - 1);
	// Mount it.
	nav_partition_mount();
	nav_filelist_reset();
	if(nav_filelist_findname((FS_STRING)LOG_FILE, false))
	{
		printf("\n\rLog File Already Exists\n\rAttempting to delete...");	
		nav_setcwd((FS_STRING)LOG_FILE, true, false);
		nav_file_del(false);
		
		if(nav_filelist_findname((FS_STRING)LOG_FILE, false))
			printf("\n\rLog File Still Exists...");
		else
			printf("\n\rLog File Deleted!");
	}
	
	
	printf("\n\rCreating Log File.");
	//char buff[20] = "log.txt";
	if(nav_file_create((FS_STRING)LOG_FILE) == true)
		printf("\n\rSuccess!");
	else
		printf("\n\rNot worked...");
	
	printf("\n\rWriting to log file.");
	
	Log_Write("Columbus Tester:\n\r", -1);


	printf("\n\rLED Test:\n\rAll LEDS on;");
	LEDMOTOR_SET;
	LED2_SET;
	LED3_SET;
	LED4_SET;
	LED5_SET;
	LED6_SET;
	delay_s(1);
	printf("\n\rAll LEDS off;");
	LEDMOTOR_CLR;
	LED2_CLR;
	LED3_CLR;
	LED4_CLR;
	LED5_CLR;
	LED6_CLR;
	delay_s(1);
	
	printf("\n\n\rSDRAM Test:");
	sdram_size = SDRAM_SIZE >> 2;
	printf("\n\rSDRAM size: %d", SDRAM_SIZE >> 20);
//	printflong(SDRAM_SIZE >> 20);
	printf(" MB\r\n");
//	printf_ulong(sdram_size);
	//sdramc_init(FOSC0);
	printf("\n\rSDRAM initialized\r\n");
	

	// Determine the increment of SDRAM word address requiring an update of the
	// printed progression status.
	progress_inc = (sdram_size + 50) / 100;
	// Fill the SDRAM with the test pattern.
	for (i = 0, j = 0; i < sdram_size; i++)
	{
		if (i == j * progress_inc)
		{
			//LED_Toggle(LED_SDRAM_WRITE);
			printf("\rFilling SDRAM with test pattern: %d\%", j++);
			//printf_ulong(j++);
			//printf_char('%');
		}
		sdram[i] = i;
		
	}
	printf("\rSDRAM filled with test pattern       \r\n");
	// Recover the test pattern from the SDRAM and verify it.
	
	for (i = 0, j = 0; i < sdram_size; i++)
	{
		
		if (i == j * progress_inc)
		{
			printf("\rRecovering test pattern from SDRAM: %d\%", j++);
// 			print_dbg_ulong(j++);
// 			print_dbg_char('%');
		}
		tmp = sdram[i];
		if (tmp != i)//failed
		{
			noErrors++;
		}
	}
	printf("\rSDRAM tested: ");
	print_dbg_ulong(noErrors);
	printf(" corrupted word(s)       \r\n");
	if (noErrors)
	{
			LED3_SET;
	}
	else
	{
			LED2_SET;
	}

 	printf("\n\n\rTWI Test:\n\r");
	Log_Write("\n\n\rTWI Test:\n\r", 14);
//  	twim_init();
// 	printf("\n\rInitialising the I2C Mux");
// 	PCA9542A_Init();
	
	printf("Scanning all Channels\n\r");
	printf("h 0 1 2 3 4 5 6 7 8 9 A B C D E F\n\r");
	tmp = 0;
	for(i = 0; i < 8; i++)
	{
		printf("%d ", i);
		//printf_char(' ');
		for(j = 0; j < 16; j++)
		{
			int status = twim_probe(TWIM, tmp++);
			if(status == STATUS_OK)
			{
				printf("A");
			}
			else
			{
				printf("-");
			}
			printf(" ");
		}
		printf("\n\r");
	}
	
	
	//Channel 0
	PCA9542A_Chan_Sel(I2C_CHANNEL_0);
	printf("\n\rScanning Channel 0\n\r");
	printf("h 0 1 2 3 4 5 6 7 8 9 A B C D E F\n\r");
	tmp = 0;
	for(i = 0; i < 8; i++)
	{
		printf("%d ", i);
		//printf_char(' ');
		for(j = 0; j < 16; j++)
		{
			int status = twim_probe(TWIM, tmp++);
			if(status == STATUS_OK)
			{
				printf("A");
			}
			else
			{
				printf("-");
			}
			printf(" ");
		}
		printf("\n\r");
	}
		
	//Channel 1
	PCA9542A_Chan_Sel(I2C_CHANNEL_1);
	printf("\n\rScanning Channel 1\n\r");
	printf("h 0 1 2 3 4 5 6 7 8 9 A B C D E F\n\r");
	tmp = 0;
	for(i = 0; i < 8; i++)
	{
		printf("%d ", i);
		//printf_char(' ');
		for(j = 0; j < 16; j++)
		{
			int status = twim_probe(TWIM, tmp++);
			if(status == STATUS_OK)
			{
				printf("A");
			}
			else
			{
				printf("-");
			}
			printf(" ");
		}
		printf("\n\r");
	}

	printf("\n\rInitialising Cameras");
	OV7670_Init();
	FIFO_Reset(CAMERA_LEFT | CAMERA_RIGHT);
	if(STATUS_OK == OV7670_Status.Error)
	{
		printf("\n\rCamera Initialise Okay!");
	}
	else
		printf("\n\rCamara Initialise Fail.");
		
	printf("\n\rTaking Photos");

	TakePhoto(CAMERA_LEFT | CAMERA_RIGHT);
	while(Photos_Ready() == false)
		;

	if(Store_Both_Images() == true)
		printf("\n\rImages Stored Successfully!");
		
	printf("\n\rMotor Testing:\n\rMotor Initialised");
 	Motor_Init();
	Motors_Reset();//reset the motors to test them
	while(Motors_Moving() == true)
		;//wait for the motors to finish moving
		
	printf("\n\rTest Complete!");
	// Insert application code here, after the board has been initialized.
	while(1)
	{
		TOGGLE();

	}
}
