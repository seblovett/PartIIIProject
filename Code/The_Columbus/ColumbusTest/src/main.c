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
#define DSP16_FORMAT 10
#define COMMAND_BUFFER_SIZE		128
#include <asf.h>
#include <conf_board.h>
#include "CustomDevices/CustomDevices.h"
#include "conf_sd_mmc_spi.h"
#include "fat.h"
#include "file.h"
#include "navigation.h"
#include "fastmath.h"
#include "delay.h"
#include "stdio.h"



void Get_Line( char * CommandBuffer );
int Auto_Run();
void Debug_Mode();
void System_Error();


int main (void)
{
	Columbus_Status.SD_Card = &SD_Status;
	Columbus_Status.Cameras = &OV7670_Status;
	Columbus_Status.I2CMux = &PCA9542A;
	Columbus_Status.SD_Card = &SD_Status;
	Columbus_Status.Motors = &Motor_Control;
	board_init();
	print_dbg("\n\r");
	print_dbg(THE);
	print_dbg(COLUMBUS);
	print_dbg(ASCII_SHIP);
	System_Test();
	
	if(Columbus_Status.Status != STATUS_OK)
	{
		System_Error();
	}
	print_dbg("\n\rColumbus Ready!");
	
	//Enter into Auto Run if not in debug mode
	if(gpio_get_pin_value(DEBUG_PIN))
	{	
		print_dbg("\n\rEntering Auto Run");
		if(1 == Auto_Run(0)) //if 
			System_Error(); //use the system error loop to stop operation
	}	
	print_dbg("\n\rEntering Debug Mode...");
	Debug_Mode();
	
}
void Get_Line( char * CommandBuffer )
{
	int c = 0;
	
	while(c != 13)
	{
		c = usart_getchar(DBG_USART);
		if(c == '\b')
		{
			CommandBuffer--;
			*(CommandBuffer) = 0;
		}
		else
		{
			*(CommandBuffer) = c;
			CommandBuffer++;
		}
		print_dbg_char(c);
	}
	usart_putchar(DBG_USART, 6);
}
void PrintStatus()
{
	print_dbg("\n\n\rColumbus Status:\t0x");
	print_dbg_hex(Columbus_Status.Status);
	print_dbg("\n\rSD Card:\n\rStatus:\t\t\t0x");
	print_dbg_hex(Columbus_Status.SD_Card->Status);
	print_dbg("\n\rMemory Size :\t\t0x");
	print_dbg_hex(Columbus_Status.SD_Card->Memory_size);
	print_dbg("\n\rMotors:");
	print_dbg("\n\rLeft State :\t\t0x");
	print_dbg_hex(Columbus_Status.Motors->Left_State);
	print_dbg("\n\rLeft Count :\t\t0x");
	print_dbg_hex(Columbus_Status.Motors->Left_Count);
	print_dbg("\n\rRight State :\t\t0x");
	print_dbg_hex(Columbus_Status.Motors->Right_State);
	print_dbg("\n\rRight Count :\t\t0x");
	print_dbg_hex(Columbus_Status.Motors->Right_Count);
	print_dbg("\n\rCameras:");
	print_dbg("\n\rStatus :\t\t0x");
	print_dbg_hex(Columbus_Status.Cameras->Status);
	print_dbg("\n\rVSYNC0 State :\t\t0x");
	print_dbg_hex(Columbus_Status.Cameras->VSYNC0_State);
	print_dbg("\n\rVSYNC1 State :\t\t0x");
	print_dbg_hex(Columbus_Status.Cameras->VSYNC1_State);
	print_dbg("\n\rI2C Mux:");
	print_dbg("\n\rStatus :\t\t0x");
	print_dbg_hex(Columbus_Status.I2CMux->Status);
	print_dbg("\n\rChannel Selected :\t0x");
	print_dbg_hex(Columbus_Status.I2CMux->ChannelSelected);
}
void System_Error()
{
	while(1)
	{
		LED2_SET;
		if(Columbus_Status.Status & SD_ERR)
			LED3_SET;
		if(Columbus_Status.Status & CAM_ERR)
			LED4_SET;
		delay_ms(500);
		
		LED2_CLR;
		if(Columbus_Status.Status & SD_ERR)
			LED3_CLR;
		if(Columbus_Status.Status & CAM_ERR)
			LED4_CLR;
		delay_ms(500);
		PrintStatus();
	}
}

#define AutoRun_Commands_FileName	"AutoRun.txt"
const AutoCommand_t DefaultCommands[13] = {
	{'F', 10},
	{'P', 0},
	{'R', 90},
	{'F', 10},
	{'P', 0},
	{'R', 90},
	{'F', 10},
	{'P', 0},
	{'R', -90},
	{'F', 10},
	{'P', 0},
	{'R', -90},
	{ 'q', 0}
};
AutoCommand_t *AutoCommands = DefaultCommands;//Use the default by default.
#define ReadBuffSize 256
void LoadCommands()
{
	int i = 1;
	int j, k;
	char c = 0;
	char buff[ReadBuffSize];
	nav_filelist_reset();
	if(nav_filelist_findname((FS_STRING)AutoRun_Commands_FileName, false))
	{ //If the file exists, load it
		print_dbg("\n\rAuto Run File Found");
		nav_setcwd((FS_STRING)AutoRun_Commands_FileName, false, false);
		file_open(FOPEN_MODE_R);
		while(!file_eof())//count how many commands there are
		{
			c = file_getc();
			if(c == 0xD)//if a carriage return if found
				i++;

		}
		sprintf(buff, "\n\r%d commands found\n\r", i);
		print_dbg(buff);
		
		AutoCommands = malloc(i*sizeof(AutoCommand_t));//Initalise the array
		
		file_seek(0, FS_SEEK_SET);
		i = 0;//command counter
		c = 0;
		while(!file_eof())
		{
			k = file_read_buf(buff, ReadBuffSize);//read a chunk of the files
			if(k > ReadBuffSize)
				k = ReadBuffSize;
			//parse it
			for(j = 0; j < k; )
			{
				while(buff[j] == ' ') //find next non-whitespace
					j++;
				AutoCommands[i].Command = buff[j++];
				while(buff[j] == ' ') //find next non-whitespace
					j++;
				if((AutoCommands[i].Command == 'F') || (AutoCommands[i].Command == 'B') || AutoCommands[i].Command == 'R' || AutoCommands[i].Command == 'J')
					AutoCommands[i].Arg = atoi(buff+j);
				else
					AutoCommands[i].Arg = 0;
				i++;
				while((buff[j++] != 0xA) && (j < k));//find the next line char
				
			}
		}
		file_close();
	}
	else
	{	//Load default commands
		print_dbg("\n\rAuto Run File Not Found, Using Default Commands:");
	}		
}

int Auto_Run(int Debug)//Debug = 1, don't run commands
{
	int PC = 0;
	
	LoadCommands();
	while(1)
	{
		switch(AutoCommands[PC].Command)
		{
			case 'F'://Move Forward
				print_dbg("\n\rMove Forward ");
				LED4_SET;
				print_dbg_ulong(AutoCommands[PC].Arg);
				if(!Debug){
				Motors_Move(AutoCommands[PC].Arg);
				}
				LED4_CLR;
				break;
				
			case 'B'://Move Backward
				print_dbg("\n\rMove Backward ");
				LED4_SET;
				print_dbg_ulong(AutoCommands[PC].Arg);
				if(!Debug){
				Motors_Move(-AutoCommands[PC].Arg);
				}
				LED4_CLR;
				break;
			
			case 'R'://Rotate
				print_dbg("\n\rRotate ");
				LED3_SET;
				print_dbg_ulong(AutoCommands[PC].Arg);
				if(!Debug){
				Motors_Rotate(AutoCommands[PC].Arg);
				}
				LED3_CLR;
				break;
			
			case 'P'://Take Photo
				print_dbg("\n\rTaking Photos");
				LED2_SET;
				if(!Debug){				
				FIFO_Reset(CAMERA_LEFT | CAMERA_RIGHT);
				if(TakePhoto(CAMERA_LEFT | CAMERA_RIGHT) == CAMERAS_BUSY){
					print_dbg("\n\rCameras Busy");
					break;
				}
				while(Photos_Ready() == false)
				;

				if(Store_Both_Images() == true)
				print_dbg("\n\rImages Stored Successfully!");
				}
				LED2_CLR;
				break;
				
			case 'J': //Jump
				print_dbg("\n\rProgram Jump to ");
				print_dbg_ulong(AutoCommands[PC].Arg);
				if(!Debug){
				PC = AutoCommands[PC].Arg;
				}
				break;
				
			case 'q': //End and enter debug
				print_dbg("\n\rQuit to Debug");
				return 0;
				
			default: //System Error
				if(!Debug){//Inevitable in Debug mode
				Columbus_Status.Status |= AutoRunCMD_ERR;
				print_dbg("\n\rSystem Error");
				}		
				return 1;
		}
		PC++;
	}
}



void Debug_Mode()
{
	Image_t image;
	unsigned long i, j, tmp = 0;
	char *Ptr;
	//	volatile unsigned long *sdram = SDRAM;
	char CommandBuffer[COMMAND_BUFFER_SIZE];
	int *Working_Buffer = NULL;
	int SizeOfWorking_Buffer = 0;
	A_ALIGNED dsp16_complex_t *ComplexBuffer;
	int SizeOfComplex_Buffer = 0;
	LED2_SET;//Set these LEDs to indicate Columbus is in debug mode;
	LED3_SET;
	LED4_SET;
	while(1)
	{
		print_dbg(PROMPT);
		Get_Line(CommandBuffer);
		Ptr = CommandBuffer;
		switch(*Ptr++)
		{
			case '?':
				print_dbg(HELP);
				break;
			case 'A':
				print_dbg("\rRunning AutoRun in Debug Mode;");
				Auto_Run(1); //Runs in debug mode
				break;
			case '1':
				print_dbg("\r1D FFT;");
				SizeOfComplex_Buffer = FFT_SIZE;
				ComplexBuffer = mspace_malloc(sdram_msp,  SizeOfComplex_Buffer * sizeof(ComplexBuffer));
				i = Get_sys_count();
				FFT1D(Working_Buffer, ComplexBuffer);
				i = Get_sys_count() - i;
				print_dbg("\n\rCycles Taken for 1D FFT = ");
				print_dbg_ulong(i);
				break;
			case '2':
				print_dbg("\r2D FFT;");
				FFT2Dabs(Working_Buffer);
				break;
			case '3':
				print_dbg("\rComplex FFT2D:");
				SizeOfComplex_Buffer = FFT_SIZE * FFT_SIZE;
				ComplexBuffer = mspace_malloc(sdram_msp,  SizeOfComplex_Buffer * sizeof(ComplexBuffer));
				i = Get_sys_count();
				FFT2DCOMPLEX(Working_Buffer, ComplexBuffer, SizeOfWorking_Buffer);
				i = Get_sys_count() - i;
				print_dbg("\n\rCycles Taken for 2D FFT = ");
				print_dbg_ulong(i);
				break;
			case 'm':
				print_dbg("\r1D FFT Magnitude");
				FFT1D_Abs(Working_Buffer);
				break;
			case 'B':
				print_dbg("\rReading Bitmap;");
				ReadBitmap("Image_R_0.bmp", &image);
				print_dbg("\n\rBitmap Data Returned:\n\rImage Height = ");
				print_dbg_ulong(image.Height);
				print_dbg("\n\rImage Width = ");
				print_dbg_ulong(image.Width);
				break;
			
			case 'c':
				print_dbg("\rConverting Working Buffer to Fixed Point");
				for(i = 0; i < SizeOfWorking_Buffer ; i++)
				{
					Working_Buffer[i] = DSP16_Q (Working_Buffer[i]);
				}
				break;
			
			case 'C':
				print_dbg("\rConverting Working Buffer back from Fixed Point");
				j = DSP16_Q(1);
				for(i = 0; i < SizeOfWorking_Buffer ; i++)
				{
					Working_Buffer[i] = Working_Buffer[i] / j;
				}
				break;
			
			case 'D':
				print_dbg("\rFreeing Working Buffer");
				mspace_free(sdram_msp, Working_Buffer);
				break;
			
			case 'i':
				print_dbg("\rImage info:");
				print_dbg("\n\rImage Pointer = ");
				print_dbg_ulong(image.ImagePtr);
				print_dbg("\n\rImage Height = ");
				print_dbg_ulong(image.Height);
				print_dbg("\n\rImage Width = ");
				print_dbg_ulong(image.Width);
				break;
			
// 			case 'I': //Not yet tested
// 				print_dbg("\rInverse Fourier Transform;");
// 				IFFT2D(ComplexBuffer);
// 				break;
			
			case 'k':
				print_dbg("\rComplex Buffer:\n\r[");
				for (i = 0; i < SizeOfComplex_Buffer; i ++)
				{
					// 					print_dbg_ulong(ComplexBuffer[i].real);
					// 					print_dbg(" + ");
					// 					print_dbg_ulong(ComplexBuffer[i].imag);
					// 					print_dbg(", ");
					if(ComplexBuffer[i].imag >= 0)
					sprintf(CommandBuffer, "%d + %dj,", ComplexBuffer[i].real, ComplexBuffer[i].imag);
					else
					sprintf(CommandBuffer, "%d %dj,", ComplexBuffer[i].real, ComplexBuffer[i].imag);
					print_dbg(CommandBuffer);
				}
				print_dbg("]\n\r");
				break;
			case 'M': //Motor Related
				while(*Ptr == ' ')
				Ptr++; //Find next non - space char
			
				switch(*(Ptr++))
				{
					case 'q': // Reset Motors
						print_dbg("\rResetting Motors");
						Motors_Reset();
						break;
				
					case 'F': //Move Forward
						while(*Ptr == ' ')
							Ptr++; //Find next non - space char
						i = atoi(Ptr);
						Motors_Move(i);
						break;
					case 'T':
						while(*Ptr == ' ')
							Ptr++; //Find next non - space char
						i = atoi(Ptr);
						Motors_Rotate(i);
						break;
					case 'L':
						Columbus_Status.Motors->Left_Count = GAMMA + 1;
						Columbus_Status.Motors->Left_State = FORWARD;
						Motor_Start(MOTOR_L);
						Motors_Execute();
						break;
					case 'R':
						Columbus_Status.Motors->Right_Count = GAMMA + 1;
						Columbus_Status.Motors->Right_State = FORWARD;
						Motor_Start(MOTOR_R);
						Motors_Execute();
						break;
					default:
						print_dbg("\rCommand Not Recognised");
						break;
				}
			
			break;
			
// 			case 'p':
// 				print_dbg("\rPreparing Image;");
// 				PrepareImage(&image);
// 				print_dbg("\rImage Prepared!");
// 				break;
			
			case 'P'://take a photo
				FIFO_Reset(CAMERA_LEFT | CAMERA_RIGHT);
				print_dbg("\rTaking Photos");
				if(TakePhoto(CAMERA_LEFT | CAMERA_RIGHT) == CAMERAS_BUSY){
					print_dbg("Cameras Busy");
					break;
				}
				while(Photos_Ready() == false)
				;

				if(Store_Both_Images() == true)
				print_dbg("\n\rImages Stored Successfully!");
				break;
			
			case 'r':
				if (Working_Buffer == 0)
				{
					print_dbg("\rWorking Buffer Not Initialised");
					break;
				}
				print_dbg("\rWorking Buffer:\n\r[");
				for(i = 0; i < SizeOfWorking_Buffer; i++)
				{
					sprintf(CommandBuffer, "%d,", (dsp16_t)Working_Buffer[i]);
					print_dbg(CommandBuffer);
				}
				print_dbg("\b\b]\n\r");
				break;
			case 'R':
				Working_Buffer = mspace_malloc(sdram_msp, FFT_SIZE);
				SizeOfWorking_Buffer = FFT_SIZE;
				print_dbg("\rReading in signal.bin");
				ReadSignal(Working_Buffer);
				break;

			case 's'://save the working buffer
				print_dbg("\rSaving Working Buffer;");
				SaveBuff(Working_Buffer, SizeOfWorking_Buffer);
				break;
			case 'd':
				print_dbg("\rSaving Working Buffer as CSV;");
				SaveBuff_CSV("Buffer_result.csv", Working_Buffer, SizeOfWorking_Buffer);
				break;
			case 'g':
				print_dbg("\rSaving Complex Buffer as CSV");
				SaveCBuff_CSV("Buffer_Complex.csv", ComplexBuffer, SizeOfComplex_Buffer);
				break;
			case 'f':
				SizeOfWorking_Buffer = FFT_SIZE*FFT_SIZE;
				Working_Buffer = mspace_malloc(sdram_msp, SizeOfWorking_Buffer);
				print_dbg("\rReading in Buffer.csv");
				Read_CSV("Buffer.csv", Working_Buffer, SizeOfWorking_Buffer);
				print_dbg("\n\rComplete!");
				break;
			
			case 'S':
				print_dbg("\rSaving Bitmap;");
				SaveBitmap(image.ImagePtr, image.Width, image.Height, "ResavedImage.bmp");
				print_dbg("\rSaved Bitmap!;");
				break;
			
			case 'T':
				print_dbg("\rReading in 2D Signal");
				Working_Buffer = mspace_malloc(sdram_msp, FFT_SIZE * FFT_SIZE);
				SizeOfWorking_Buffer = FFT_SIZE * FFT_SIZE;
				Read2DSignal(Working_Buffer);
				break;
			case 'v':
				PrintStatus();
				break;
			case 'o':
				print_dbg("\r1 in Fixed point = ");
				i = DSP16_Q(1);
				print_dbg_ulong(i);
				break;

			
			default:
				print_dbg("\rCommand Not Recognised;");
				break;
		}
	}
}