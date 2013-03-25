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

//REF : http://www.chris.com/ASCII/index.php?art=transportation/nautical 
#define ASCII_SHIP "\t\t\t             |    |    | \n\r\t\t\t            )_)  )_)  )_) \n\r\t\t\t           )___))___))___)\\  \n\r\t\t\t           )____)____)_____)\\\\ \n\r\t\t\t         _____|____|____|____\\\\\\__ \n\r\t\t\t---------\\                   /--------- \n\r\t\t\t  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^ \n\r\t\t\t    ^^^^      ^^^^     ^^^    ^^\n\r\t\t\t         ^^^^      ^^^\n\r"
#define COLUMBUS " _______  _______  _                 _______  ______            _______ \n\r(  ____ \\(  ___  )( \\      |\\     /|(       )(  ___ \\ |\\     /|(  ____ \\\n\r| (    \\/| (   ) || (      | )   ( || () () || (   ) )| )   ( || (    \\/\n\r| |      | |   | || |      | |   | || || || || (__/ / | |   | || (_____ \n\r| |      | |   | || |      | |   | || |(_)| ||  __ (  | |   | |(_____  )\n\r| |      | |   | || |      | |   | || |   | || (  \\ \\ | |   | |      ) |\n\r| (____/\\| (___) || (____/\\| (___) || )   ( || )___) )| (___) |/\\____) |\n\r(_______/(_______)(_______/(_______)|/     \\||______/ (_______)\\_______)\n\n\r"
#define THE "\t\t\t_________          _______ \n\r \t\t\t\\__   __/|\\     /|(  ____ \\ \n\r \t\t\t   ) (   | )   ( || (    \\/\n\r\t\t\t   | |   | (___) || (__    \n\r \t\t\t   | |   |  ___  ||  __)   \n\r \t\t\t   | |   | (   ) || (      \n\r \t\t\t   | |   | )   ( || (____/\\\n\r \t\t\t   )_(   |/     \\|(_______/\n\r"
#define PROMPT "\n\r$>"

#define HELP	"\n\rColumbus Prompt Help:\n\r\
				? : Shows this prompt\n\r \
				c : converts the working buffer from integer to fixed point\n\r\
				D : Frees the Memory pointed to by the Working Buffer \n\r \
				r : displays the contents of the working buffer\n\r\
				R : Reads contents of signal.bin, representing 1D Signal. Integers, Big Endian\n\r\
				T : Reads contents of signal2d.bin, representing 2D Signal. \n\r \
				s : saves the working buffer\n\r\
				P : Takes and stores Stereo Photos \n\r \
				1 : computes the One Dimensional FFT of the working buffer. Returns magnitude.\n\r\
				2 : Computes the Two Dimensional FFT of the Working Buffer. \n\r \
				"

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

#define COMMAND_BUFFER_SIZE		128
int main (void)
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
		while(1)
		{	
			LED2_SET;
			LED3_SET;
			LED4_SET;
			LED5_SET;
			LED6_SET;
			delay_ms(500);
			LED2_CLR;
			LED3_CLR;
			LED4_CLR;
			LED5_CLR;
			LED6_CLR;
			delay_ms(500);
		}//inifinte loop
	}


	print_dbg("\n\rColumbus Ready!");
	// Insert application code here, after the board has been initialized.
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

			case '1'://1d FFT (w/ memallocs)
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
					
			case 'I':
				print_dbg("\rInverse Fourier Transform;");
				IFFT2D(ComplexBuffer);
				break;
				
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
					case 'l':
						Motor_Stop(MOTOR_L);
						break;
					case 'L':
						Columbus_Status.Motors->Left_Count = INTERRUPTS_PER_REVOLUTION + 1;
						Columbus_Status.Motors->Left_State = FORWARD;
						Motor_Start(MOTOR_L);
						Motors_Execute();
						break;
					case 'r':
						Motor_Stop(MOTOR_R);
						break;
					case 'R':
						Columbus_Status.Motors->Right_Count = INTERRUPTS_PER_REVOLUTION + 1;
						Columbus_Status.Motors->Right_State = FORWARD;
						Motor_Start(MOTOR_R);
						Motors_Execute();
						break;
					default:
						print_dbg("\rCommand Not Recognised");
						break;
				}
				
				break;
				
			case 'p':
				print_dbg("\rPreparing Image;");
				PrepareImage(&image);
				print_dbg("\rImage Prepared!");
				break;
				
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
// 					print_dbg_ulong(Working_Buffer[i]);
// 					print_dbg(", ");
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
				print_dbg("\rColumbus Status:");
				print_dbg("\n\rSD Card:\n\rStatus: ");
				print_dbg_ulong(Columbus_Status.SD_Card->Status);
				print_dbg("\n\rMemory Size : ");
				print_dbg_ulong(Columbus_Status.SD_Card->Memory_size);
				print_dbg("\n\rMotors:");
				print_dbg("\n\rLeft State : ");
				print_dbg_ulong(Columbus_Status.Motors->Left_State);
				print_dbg("\n\rLeft Count : ");
				print_dbg_ulong(Columbus_Status.Motors->Left_Count);
				print_dbg("\n\rRight State : ");
				print_dbg_ulong(Columbus_Status.Motors->Right_State);
				print_dbg("\n\rRight Count : ");
				print_dbg_ulong(Columbus_Status.Motors->Right_Count);
				print_dbg("\n\rCameras:");
				print_dbg("\n\rStatus : ");
				print_dbg_ulong(Columbus_Status.Cameras->Status);
				print_dbg("\n\rVSYNC0 State : ");
				print_dbg_ulong(Columbus_Status.Cameras->VSYNC0_State);
				print_dbg("\n\rVSYNC1 State : ");
				print_dbg_ulong(Columbus_Status.Cameras->VSYNC1_State);
				print_dbg("\n\rI2C Mux:");
				print_dbg("\n\rStatus : ");
				print_dbg_ulong(Columbus_Status.I2CMux->Status);
				print_dbg("\n\rChannel Selected : ");
				print_dbg_ulong(Columbus_Status.I2CMux->ChannelSelected);
				break;
			case 'o':
				print_dbg("\r1 in Fixed point = ");
				i = DSP16_Q(1);
				print_dbg_ulong(i);
				break;
// 			case 'o'://testing storing a complex
// 				print_dbg("\rFreeing Complex Buffer");
// 				mspace_free(sdram_msp, ComplexBuffer);
// 				print_dbg("\n\rAssiging Space to the Complex Buffer;");
// 				SizeOfComplex_Buffer = 10;
// 				ComplexBuffer = mspace_malloc(sdram_msp, 10*sizeof(ComplexBuffer));
// 				if(ComplexBuffer == NULL)
// 				{
// 					print_dbg("\n\rAssign Failed;");
// 					break;
// 				}
// 				for(i = 0; i < SizeOfComplex_Buffer; i++)
// 				{
// 					ComplexBuffer[i].imag = i;
// 					ComplexBuffer[i].real = i;
// 				}
// 				for(i = 0; i < SizeOfComplex_Buffer; i ++)
// 				{
// 					print_dbg("\n\r");
// 					print_dbg_ulong(ComplexBuffer[i].real);
// 					print_dbg(" + j");
// 					print_dbg_ulong(ComplexBuffer[i].imag);
// 				}
// 				print_dbg("\n\rFreeing Complex Buffer");
// 				mspace_free(sdram_msp, ComplexBuffer);
// 				SizeOfComplex_Buffer = 0;
// 				break;
	
			default:
				print_dbg("\rCommand Not Recognised;");
				break;
		}
	}
}
