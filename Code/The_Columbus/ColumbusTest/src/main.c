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
#define DSP32_FORMAT 24
#include <asf.h>
#include <conf_board.h>
#include "CustomDevices/CustomDevices.h"
#include "conf_sd_mmc_spi.h"
#include "fat.h"
#include "file.h"
#include "navigation.h"
#include "fastmath.h"

//REF : http://www.chris.com/ASCII/index.php?art=transportation/nautical 
#define ASCII_SHIP "\t\t\t             |    |    | \n\r \
\t\t\t            )_)  )_)  )_) \n\r \
\t\t\t           )___))___))___)\\  \n\r\
\t\t\t           )____)____)_____)\\\\ \n\r \
\t\t\t         _____|____|____|____\\\\\\__ \n\r \
\t\t\t---------\\                   /--------- \n\r \
\t\t\t  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^ \n\r \
\t\t\t    ^^^^      ^^^^     ^^^    ^^\n\r \
\t\t\t         ^^^^      ^^^\n\r"

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


int main (void)
{
	unsigned long i, j, tmp = 0;
	volatile unsigned long *sdram = SDRAM;
	char CommandBuffer[16];
	int *Working_Buffer = NULL;
	int SizeOfWorking_Buffer = 0;
	Columbus_Status.SD_Card = &SD_Status;
	Columbus_Status.Cameras = &OV7670_Status;
	Columbus_Status.I2CMux = &PCA9542A;
	Columbus_Status.SD_Card = &SD_Status;
	board_init();
	print_dbg("\n\r");
	print_dbg(THE);
	print_dbg(COLUMBUS);
	print_dbg(ASCII_SHIP);
	System_Test();

	
	//print_dbg("\n\rResetting Motors.");
	
// 	Motors_Reset();
// 	while(Motors_Moving() == true)
// 		;
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
		//print_dbg("\n\r$");
		//print_dbg(WorkingBuffer);
		switch(CommandBuffer[0])
		{
			case '?':
				print_dbg(HELP);
				break;

			case '1'://1d FFT (w/ memallocs)
				print_dbg("\r1D FFT;");
				FFT1D(Working_Buffer);
				break;
			case '2':
				print_dbg("\r2D FFT;");
				FFT2D(Working_Buffer);
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
					print_dbg_ulong(Working_Buffer[i]);
					print_dbg(", ");
				}
				print_dbg("\b\b]\n\r");
				break;
			case 'R':
				Working_Buffer = mspace_malloc(sdram_msp, FFT_SIZE);
				SizeOfWorking_Buffer = FFT_SIZE;
				print_dbg("\rReading in signal.bin");
				ReadSignal(Working_Buffer);
				break;

			case 'P'://take a photo
					FIFO_Reset(CAMERA_LEFT | CAMERA_RIGHT);
					print_dbg("\rTaking Photos");
					TakePhoto(CAMERA_LEFT | CAMERA_RIGHT);
					while(Photos_Ready() == false)
						;

					if(Store_Both_Images() == true)
						print_dbg("\n\rImages Stored Successfully!");
					break;

			case 'D':
				print_dbg("\rFreeing Working Buffer");
				mspace_free(sdram_msp, Working_Buffer);
				break;
			case 'c':
				for(i = 0; i < SizeOfWorking_Buffer ; i++)
				{
					Working_Buffer[i] = DSP16_Q (Working_Buffer[i]);
				}
				break;
			
			case 's'://save the working buffer
				print_dbg("\rSaving Working Buffer;");
				SaveBuff(Working_Buffer, SizeOfWorking_Buffer);
				break;
// 			case 'l':
// 				i = atoi(CommandBuffer + 2);
// 				i = log_2(i);
// 				print_dbg("\n\r");
// 				print_dbg_ulong(i);
// 				break;

			case 'T':
				print_dbg("\rReading in 2D Signal");
				Working_Buffer = mspace_malloc(sdram_msp, FFT_SIZE * FFT_SIZE);
				SizeOfWorking_Buffer = FFT_SIZE * FFT_SIZE;
				Read2DSignal(Working_Buffer);
				break;
// 			case 't':
// 				print_dbg("\n\r[[");
// 				for(i = 0; i < FFT_SIZE ; i ++)
// 				{
// 					for (j = 0; j < FFT_SIZE; j ++)
// 					{
// 						print_dbg_ulong(Working_Buffer[i*FFT_SIZE + j]);
// 						print_dbg(" ,");
// 					}
// 					print_dbg("\b]\n\r");
// 				}
// 				print_dbg("\]\n\r");
// 				break;
			default:
				print_dbg("\rCommand Not Recognised;");
				break;
		}
	}
}
