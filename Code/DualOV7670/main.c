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
//FIL Files[2];				/* File object */
uint8_t StatusReg;
// char Line[100];				/* Console input buffer */
//char Buff[100];			/* Working buffer */

#define STATUS_OKAY			0x01
#define STATUS_SDErr		0x02
#define STATUS_CAM0Err		0x04
#define STATUS_CAM1Err		0x08
#define STATUS_EXIT_Good	0x40
#define STATUS_Exit_Bad		0x80
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
unsigned char UI_Buttons()
{
	unsigned char messageBuf[TWI_BUFFER_SIZE]; //Initialise a buffer
	messageBuf[0] = (0x15<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
	messageBuf[1] = 0x20;             // The first byte is used for the command
	TWI_Start_Transceiver_With_Data( messageBuf, 2 );
	//_delay_us(500);
	// Request/collect the data from the Slave
	messageBuf[0] = (0x15<<TWI_ADR_BITS) | (TRUE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
	TWI_Start_Transceiver_With_Data( messageBuf, 2 );
	
	// Get the received data from the transceiver buffer
	TWI_Get_Data_From_Transceiver( messageBuf, 2 );
	return messageBuf[1];
}
ISR(TIMER0_COMPA_vect)
{
	disk_timerproc();	/* Drive timer procedure of low level disk I/O module */
// 	if(!TWI_statusReg.lastTransOK) //if the last TWI transmission failed, reset the protocol
// 		TWI_Start_Transceiver();
// 	if(!TWI_Transceiver_Busy())
// 		UI_LEDs(StatusReg);
}
int main(void)
{
	unsigned long int a = 0;
	uint8_t b = 0;
	FRESULT fr;
	TWI_Master_Initialise();
	IO_Init();
	sei();
	
	
	StatusReg = STATUS_OKAY;
	UI_LEDs(StatusReg);
	_delay_ms(10);
	UI_Buttons();
	
	while(1);
	fr = f_mount(0, &Fatfs[0]);
	if(fr != FR_OK)
	{
		StatusReg |= (STATUS_SDErr|STATUS_Exit_Bad);
		StatusReg &= ~(STATUS_OKAY);
		UI_LEDs(StatusReg);
		return 0;
	}
	
	fr = f_open(&Files[0], "/log.txt", FA_WRITE|FA_CREATE_ALWAYS);
	if(fr != FR_OK)
	{
		StatusReg |= (STATUS_SDErr|STATUS_Exit_Bad);
		StatusReg &= ~(1<<STATUS_OKAY);
		UI_LEDs(StatusReg);
		return 0;
	}		
	UI_LEDs(StatusReg);
	f_close(&Files[0]);
	f_open(&Files[0], "/log.txt", FA_WRITE);
	//stdout = &mystdout;
	b = MCUSR;
	MCUSR = 0;
	f_write(&Files[0],"Il Matto Dual Camera\n", sizeof("Il Matto Dual Camera\n"), &a);
	
	
	//printf("Initialising IO\n");
	
	//printf("Initialising TWI\n");
	
	//printf("Disk Initialise : %d\n", f_mount(0, &Fatfs[0]));

	//fr = f_open(&Files[0], "/log.txt", FA_WRITE | FA_CREATE_ALWAYS);
	//printf("Open File : %d\n", fr);
// 	if (fr != FR_OK)
// 		return 0;
	f_write(&Files[0], "System Startup Complete.\n", 26, &a);
	

	b = OV7670_init();
	if(b == 0)
		StatusReg |= STATUS_CAM1Err;
		
		
	UI_LEDs(StatusReg);
	//printf("OV7670_1 Initialise result : %d\n", b);
	sprintf(Buff, "OV7670_1 Initialise result : %d\n", b);
	f_write(&Files[0], &Buff, 33, &a);
	InitSCCB();
	b = OV7670_SCCB_init();
	if(b == 0)
		StatusReg |= STATUS_CAM0Err;
	UI_LEDs(StatusReg);
	//printf("OV7670_0 Initialise result : %d\n", b);
	sprintf(Buff, "OV7670_0 Initialise result : %d\n", b);
	f_write(&Files[0], &Buff, 33, &a);
	FIFO_init();
	f_close(&Files[0]);
	StatusReg |= STATUS_EXIT_Good;
	UI_LEDs(StatusReg);
	_delay_ms(1);
	UI_Buttons();
	while(1)	;
    while(0)
    {
		switch(0)
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
    }
}