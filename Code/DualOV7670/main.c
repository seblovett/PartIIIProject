/*
 * DualOV7670.c
 *
 * Created: 09/11/2012 11:43:13
 *  Author: hl13g10
 */ 
#include "Config.h"



static FILE mystdout = FDEV_SETUP_STREAM(Usart_printf, NULL, _FDEV_SETUP_WRITE);
//FatFS Variables
FILINFO Finfo;
FATFS Fatfs[_VOLUMES];		/* File system object for each logical drive */
//FIL Files[2];				/* File object */

// char Line[100];				/* Console input buffer */
char Buff[100];			/* Working buffer */

ISR(TIMER0_COMPA_vect)
{
	disk_timerproc();	/* Drive timer procedure of low level disk I/O module */
}
int main(void)
{
	unsigned long int a = 0;
	uint8_t b = 0;
	FRESULT fr;
	
	USART0_Init();
	sei();
	stdout = &mystdout;
	b = MCUSR;
	MCUSR = 0;
	printf("\n\nIl Matto Dual Camera\nMCUSR = %x\n", b);
	printf("Initialising IO\n");
	IO_Init();
	printf("Initialising TWI\n");
	TWI_Master_Initialise();
	printf("Disk Initialise : %d\n", f_mount(0, &Fatfs[0]));
	//sprintf(&Buff, "image.bmp");
	fr = f_open(&Files[0], "/log.txt", FA_WRITE | FA_CREATE_ALWAYS);
	printf("Open File : %d\n", fr);
	if (fr != FR_OK)
		return 0;
	f_write(&Files[0], "System Startup Complete.\n", 16, &a);
	f_close(&Files[0]);
	printf("Starting Camera Initialise...\n");
	FIFO_init();
	b = OV7670_init();
	
	printf( "OV7670_0 initialised with exit code %d\n", b);
	//f_write(&Files[0], &Buff, sizeof(Buff), &a);
	
	
	
	printf("Image file opening.\n");
	//f_write(&File[0], &Buff, sizeof(Buff), &a);
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
	LoadImageToBuffer();
	while(0 != GetImageIfAvailiable(DIBHEADERSIZE + BMPHEADERSIZE)) 
		;
	printf("Photo Taken\n");
// 	printf("Closing File 1: %d\n", f_close(&File[1]));
// 	printf("Closing File 0: %d\n", f_close(&File[0]));
	
    while(1)
    {
	 
    }
}