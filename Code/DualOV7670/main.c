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
#define STATUS_SDOkay		0x02
#define STATUS_CAM0Okay		0x04
#define STATUS_CAM1Okay		0x08
#define STATUS_READY		0x10
#define STATUS_CAPTURING	0x20
#define STATUS_Exit_Bad		0x80

#define Button_Capture		0
#define Button_Exit			3
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
	_delay_us(250);
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
	PCA9542A_Init();

	StatusReg = STATUS_OKAY;
	UI_LEDs(StatusReg);
	_delay_ms(10);
	UI_Buttons();

	fr = f_mount(0, &Fatfs[0]);
	if(fr != FR_OK)
	{
		StatusReg |= (STATUS_Exit_Bad);
		StatusReg &= ~(STATUS_OKAY);
		UI_LEDs(StatusReg);
		return 0;
	}
	else
		StatusReg |= STATUS_SDOkay;
	UI_LEDs(StatusReg);
	
	fr = f_open(&Files[0], "/log.txt", FA_WRITE|FA_CREATE_ALWAYS);
	if(fr != FR_OK)
	{
		StatusReg |= (STATUS_Exit_Bad);
		StatusReg &= ~(1<<STATUS_SDOkay) | (1<<STATUS_OKAY);
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

	/*f_write(&Files[0], "System Startup Complete.\n", 26, &a);*/
	
	PCA9542A_SetChannel(CH1);
	b = OV7670_init();
	if(b == 0)
		StatusReg |= STATUS_CAM1Okay;
	PCA9542A_SetChannel(NO_SELECT);
	UI_LEDs(StatusReg);
	sprintf(Buff, "OV7670_1 Initialise result : %d\n", b);
	f_write(&Files[0], &Buff, 33, &a);
	
	PCA9542A_SetChannel(CH0);
	b = OV7670_init();
	if(b == 0)
		StatusReg |= STATUS_CAM0Okay;
	UI_LEDs(StatusReg);
	PCA9542A_SetChannel(NO_SELECT);
	sprintf(Buff, "OV7670_0 Initialise result : %d\n", b);
	f_write(&Files[0], &Buff, 33, &a);
	FIFO_init();

	//f_close(&Files[0]);
	StatusReg |= STATUS_READY;
	UI_LEDs(StatusReg);
	_delay_ms(250);
	uint8_t Input;
	
    while(1)
    {
		Input = (~UI_Buttons() & 0x0F);//Data is received negative
		if(Input)//if a button has been pressed
		{
			_delay_ms(250);
			sprintf(Buff, "Button Received : %d\n", Input);
			f_write(&Files[0], Buff, 21, &a);
			
			StatusReg&= ~(STATUS_READY);//no longer ready
			
			switch(Input)
			{
				case (1<<Button_Capture):
					StatusReg |= STATUS_CAPTURING;
					UI_LEDs(StatusReg);
					//Reset both buffers
					FIFO_Reset(0);
					FIFO_Reset(1);
					f_write(&Files[0], "Capturing Images...\n", 20, &a);
					LoadImagesToBuffer();//Load both images
					
					//Create Bitmap for image 0
					f_open(&Files[1], "/image0.bmp", FA_CREATE_ALWAYS | FA_WRITE);
					f_write(&Files[0], "Created image0 file.\n", 22, &a);
					f_lseek(&Files[1], BMPFileSize);
					f_lseek(&Files[1], 0);
					f_close(&Files[1]);
					f_write(&Files[0], "Extended image0 file.\n", 22, &a);
					
					//Create Bitmap for image 1
					f_open(&Files[1], "/image1.bmp", FA_CREATE_ALWAYS | FA_WRITE);
					f_write(&Files[0], "Created image1 file.\n", 22, &a);
					f_lseek(&Files[1], BMPFileSize);
					f_lseek(&Files[1], 0);
					f_close(&Files[1]);
					f_write(&Files[0], "Extended image1 file.\n", 22, &a);
					//Get image 0
					f_open(&Files[1], "/image0.bmp", FA_WRITE);
					while (2 == GetImageIfAvailiable(&Files[1], 0))	;
					f_close(&Files[1]);
					f_write(&Files[0], "Captured image0.\n", 17, &a);
					//get image 1
					f_open(&Files[1], "/image1.bmp", FA_WRITE);
					while (2 == GetImageIfAvailiable(&Files[1], 1))	;
					f_close(&Files[1]);
					f_write(&Files[0], "Captured image1.\n", 17, &a);
					StatusReg |= STATUS_READY;
					StatusReg &= ~STATUS_CAPTURING;
					UI_LEDs(StatusReg);
					break;//break case(1<<ButtonCapture)
					
				case (1<<Button_Exit):
					f_write(&Files[0], "\nSystem Exiting...\n",19 ,&a);
					f_close(&Files[0]);//close log file
					
					StatusReg = 0x41;
					UI_LEDs(StatusReg);
					return 0;//Q
			}//End switch
		}//End if(Input)
		else
		{
			StatusReg |= STATUS_READY;
			UI_LEDs(StatusReg);
			_delay_ms(250);//wait
		}//end else(Input)					
    }//End while(1)
}//End Main