/*
 * DualOV7670.c
 *
 * Created: 09/11/2012 11:43:13
 *  Author: hl13g10
 */ 
#include "Config.h"



//static FILE mystdout = FDEV_SETUP_STREAM(File_Write_Printf, NULL, _FDEV_SETUP_WRITE);
//FatFS Variables
FILINFO Finfo;
FATFS Fatfs[_VOLUMES];		/* File system object for each logical drive */
FIL Files[2];				/* File object */

// char Line[100];				/* Console input buffer */
//char Buff[100];			/* Working buffer */

ISR(TIMER0_COMPA_vect)
{
	disk_timerproc();	/* Drive timer procedure of low level disk I/O module */
}
#define STATUS_OKAY		0x01
#define STATUS_SDErr	0x02
#define STATUS_CAM0Err	0x04
#define STATUS_CAM1Err	0x08
#define STATUS_Exit		0x80
unsigned char UI_LEDs(uint8_t LED)
{
	unsigned char mesbuf[TWI_BUFFER_SIZE];
	mesbuf[0] = (0x15 << TWI_ADR_BITS) | (FALSE << TWI_READ_BIT);
	mesbuf[1] = 0x10;
	mesbuf[2] = LED;
	TWI_Start_Transceiver_With_Data(mesbuf, 3);
	while(TWI_Transceiver_Busy())	;
	return TWI_statusReg.lastTransOK;
}
int main(void)
{
	unsigned long int a = 0;
	uint8_t b = 0;
	FRESULT fr;
<<<<<<< HEAD
	char c = 0;
	USART0_Init();
=======
	
	//USART0_Init();
	
>>>>>>> Stereovision
	sei();
	TWI_Master_Initialise();
	
	UI_LEDs(STATUS_OKAY);
	
	fr = f_mount(0, &Fatfs[0]);
	if(fr != FR_OK)
	{
		UI_LEDs(STATUS_SDErr|STATUS_Exit);
		return 0;
	}
	fr = f_open(&Files[0], "/log.txt", FA_WRITE|FA_CREATE_ALWAYS);
	if(fr != FR_OK)
	{
		UI_LEDs(STATUS_SDErr|STATUS_Exit);
		return 0;
	}		
// 	f_lseek(&Files[0], 100);
// 	f_lseek(&Files[0], 0);
	f_close(&Files[0]);
	f_open(&Files[0], "/log.txt", FA_WRITE);
	//stdout = &mystdout;
	b = MCUSR;
	MCUSR = 0;
	f_write(&Files[0],"Il Matto Dual Camera\n", sizeof("Il Matto Dual Camera\n"), &a);
	f_close(&Files[0]);
	
	//printf("Initialising IO\n");
	IO_Init();
	//printf("Initialising TWI\n");
	
	//printf("Disk Initialise : %d\n", f_mount(0, &Fatfs[0]));
	f_mount(0, &Fatfs[0]);
	fr = f_open(&Files[0], "/log.txt", FA_WRITE | FA_CREATE_ALWAYS);
	//printf("Open File : %d\n", fr);
	if (fr != FR_OK)
		return 0;
<<<<<<< HEAD
	f_write(&Files[0], "System Startup Complete.\n", 16, &a);
	f_close(&Files[0]);
	printf("Starting Camera Initialise...\n");
	FIFO_init();
	b = OV7670_init();
	
	printf( "OV7670_0 initialised with exit code %d\n", b);

    while(1)
    {
		c = Usart_Receive();
		
		switch(c)
		{
			case 'a':
				fr =f_open(&Files[0], "image1.bmp", FA_CREATE_ALWAYS | FA_WRITE);
				printf("File Opened : %d\n", fr);
				f_lseek(&Files[0], 155000);
				printf("File Size exercised.\n");
				f_lseek(&Files[0], 0);
				printf("Closing File 1: %d\n", f_close(&Files[0]));
				fr =f_open(&Files[0], "image1.bmp", FA_WRITE);
				printf("File Opened : %d\n", fr);
				printf("Write BMP Header.\n");
				WriteBMPHeader(&Files[0]);
				printf("Write DIB Header.\n");
				WriteDIBHeader(&Files[0]);
				printf("Loading Image to FIFO Buffer.\n");
				LoadImageToBuffer();
				printf("Getting Image.\n");
				while(0 != GetImageIfAvailiable(&Files[0], DIBHEADERSIZE + BMPHEADERSIZE)) ;
				printf("Photo Taken");
				break;
				
				default:
				
				break;
			
		}					
	 
=======
	f_write(&Files[0], "System Startup Complete.\n", 26, &a);
	

	b = OV7670_init();
	//printf("OV7670_1 Initialise result : %d\n", b);
	sprintf(Buff, "OV7670_1 Initialise result : %d\n", b);
	f_write(&Files[0], &Buff, sizeof(Buff), &a);
	InitSCCB();
	b = OV7670_SCCB_init();
	printf("OV7670_0 Initialise result : %d\n", b);
	sprintf(Buff, "OV7670_0 Initialise result : %d\n", b);
	f_write(&Files[0], &Buff, sizeof(Buff), &a);
	FIFO_init();
	f_close(&Files[0]);
// 	f_open(&Files[0], "/image0.bmp", FA_CREATE_ALWAYS | FA_WRITE);
// 	printf("Made File\n");
// 	f_lseek(&Files[0], 155000);
// 	f_lseek(&Files[0], 0);
// 	f_close(&Files[0]);
// 	printf("Closed File\n");
// 	f_open(&Files[0], "/image0.bmp", FA_WRITE);
// 	printf("Opened File\n");
// 	LoadImagesToBuffer();
// 	printf("Loaded Images\n");
// 	while (2 == GetImageIfAvailiable(&Files[0], 0)) ;
// 	printf("Image 0 Taken Successfully!\n");
// 	
// 	
// 	f_open(&Files[0], "/image1.bmp", FA_CREATE_ALWAYS | FA_WRITE);
// 	printf("Made File\n");
// 	f_lseek(&Files[0], 155000);
// 	f_lseek(&Files[0], 0);
// 	f_close(&Files[0]);
// 	printf("Closed File\n");
// 	f_open(&Files[0], "/image1.bmp", FA_WRITE);
// 	printf("Opened File\n");
// 	LoadImagesToBuffer();
// 	printf("Loaded Images\n");
// 	while (2 == GetImageIfAvailiable(&Files[0], 1)) ;
// 	printf("Image 1 Taken Successfully!\n");
// 	while(1);
	
    while(1)
    {
		switch(Usart_Receive())
		{
			case '0':
				f_open(&Files[0], "/image0.bmp", FA_CREATE_ALWAYS | FA_WRITE);
				printf("Made File\n");
				f_lseek(&Files[0], BMPFileSize);
				f_lseek(&Files[0], 0);
				f_close(&Files[0]);
				printf("Closed File\n");
				f_open(&Files[0], "/image0.bmp", FA_WRITE);
				printf("Opened File\n");
				LoadImagesToBuffer();
				printf("Loaded Images\n");
				while (2 == GetImageIfAvailiable(&Files[0], 0)) ;
				printf("Image 0 Taken Successfully!\n");
				break;
				
			case '1':
				f_open(&Files[0], "/image1.bmp", FA_CREATE_ALWAYS | FA_WRITE);
				printf("Made File\n");
				f_lseek(&Files[0], BMPFileSize);
				f_lseek(&Files[0], 0);
				f_close(&Files[0]);
				printf("Closed File\n");
				f_open(&Files[0], "/image1.bmp", FA_WRITE);
				printf("Opened File\n");
				LoadImagesToBuffer();
				printf("Loaded Images\n");
				while (2 == GetImageIfAvailiable(&Files[0], 1)) ;
				printf("Image 1 Taken Successfully!\n");
				break;
			
			case 'P':
				LoadImagesToBuffer();
				while (2 == GetImageIfAvailiable(&Files[0], 1)) ;
				break;

			
		}			
>>>>>>> Stereovision
    }
}