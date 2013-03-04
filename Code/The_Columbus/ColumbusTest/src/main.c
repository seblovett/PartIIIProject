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
#include "CustomDevices/CustomDevices.h"
#include "conf_sd_mmc_spi.h"
#include "fat.h"
#include "file.h"
#include "navigation.h"
#include "fastmath.h"

//#define DSP32_FORMAT 4
//REF : http://www.chris.com/ASCII/index.php?art=transportation/nautical 
#define ASCII_SHIP "              |    |    | \n\r \
            )_)  )_)  )_) \n\r \
           )___))___))___)\\  \n\r\
           )____)____)_____)\\\\ \n\r \
         _____|____|____|____\\\\\\__ \n\r \
---------\\                   /--------- \n\r \
  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^ \n\r \
    ^^^^      ^^^^     ^^^    ^^\n\r \
         ^^^^      ^^^\n\r"
#define PROMPT "\n\r$>"
#define SIGNAL_FILE "signal.bin"

#define FFT_SIZE	16
#define FFT_LOG2	4
void Get_Line( char * WorkingBuffer ) 
{
	int c = 0;
	
	while(c != 13)
	{
		c = usart_getchar(DBG_USART);
		*(WorkingBuffer) = c; 
		WorkingBuffer++;
		print_dbg_char(c);
	}
	usart_putchar(DBG_USART, 0x10);
}

int ReadSignal( int * WorkingBuffer ) 
{
	bool status_b;
	int Status;
	char c = 0;
	if(Columbus_Status.SD_Card->Status != STATUS_OK)
		return ERR_IO_ERROR;
	nav_filelist_reset();
	nav_setcwd((FS_STRING)SIGNAL_FILE, false, false);
	status_b = file_open(FOPEN_MODE_R);
	if(status_b == false)
	{
		print_dbg("File Open Error");
		return ERR_IO_ERROR;
	}
	
	
	//Status = file_read_buf(WorkingBuffer, 16);
	for(Status = 0; Status < FFT_SIZE; Status++)
	{
		print_dbg("\n\r Read from file: ");
		c = file_getc();
		print_dbg_char(c);
		
		WorkingBuffer[Status] = c;
		print_dbg("  Working Buff = ");
		print_dbg_char(WorkingBuffer[Status]);
	}
	file_close();
	return STATUS_OK;
}

void FFT( int * WorkingBuffer ) 
{
	int i =0;
	double a;
	A_ALIGNED dsp32_complex_t vect1[FFT_SIZE];
	A_ALIGNED dsp32_t vect2[FFT_SIZE];
	for(i = 0; i < FFT_SIZE; i++)
	{
		vect2[i] = WorkingBuffer[i];
	}
	dsp32_trans_realcomplexfft(vect1, vect2, FFT_LOG2);
	dsp32_vect_complex_abs(vect2, vect1, FFT_SIZE);
	for(i = 0; i < FFT_SIZE; i++)
	{
		WorkingBuffer[i] = vect2[i];
	}
	
}
#define BUFFER_FILENAME		"Buffer.bin"
void SaveBuff( int * WorkingBuffer ) 
{
	//If the file exists, delete it
	if(nav_filelist_findname((FS_STRING)BUFFER_FILENAME, false))
	{
		nav_setcwd((FS_STRING)BUFFER_FILENAME, false, false);
		nav_file_del(false);
	}
	nav_file_create((FS_STRING)BUFFER_FILENAME);
	nav_setcwd((FS_STRING)BUFFER_FILENAME, false, true);
	file_open(FOPEN_MODE_APPEND);
	file_write_buf(WorkingBuffer, sizeof(WorkingBuffer));
	file_close();
}

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
	char CommandBuffer[16];
	int *WorkingBuffer;
	Columbus_Status.SD_Card = &SD_Status;
	Columbus_Status.Cameras = &OV7670_Status;
	Columbus_Status.I2CMux = &PCA9542A;
	Columbus_Status.SD_Card = &SD_Status;
	board_init();
	print_dbg("\n\r");
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
		print_dbg("\n\r$");
		//print_dbg(WorkingBuffer);
		switch(CommandBuffer[0])
		{
			case 'F':
				switch(CommandBuffer[1])
				{
					case 'F':
						switch(CommandBuffer[2])
						{
							case 'T':
								print_dbg("= Fast Fourier Transform...");
								FFT(WorkingBuffer);
								break;
								
							default:
								print_dbg("= Command Not Recognised");
								break;
						}
						break;
					
					default:
						print_dbg("= Command Not Recognised");
						break;
				}
				break;
				
			case 'R':
				WorkingBuffer = mspace_malloc(sdram_msp, FFT_SIZE);
				print_dbg("Reading in signal.bin");
				ReadSignal(WorkingBuffer);
				break;
			case 'r':
				
				print_dbg("Working Buffer:\n\r");
				for(i = 0; i < FFT_SIZE; i++)
				{
					print_dbg_ulong(WorkingBuffer[i]);
					print_dbg("\n\r");
				}				
				break; 
			case 'P'://take a photo
					FIFO_Reset(CAMERA_LEFT | CAMERA_RIGHT);
					print_dbg("\n\rTaking Photos");
					TakePhoto(CAMERA_LEFT | CAMERA_RIGHT);
					while(Photos_Ready() == false)
						;

					if(Store_Both_Images() == true)
						print_dbg("\n\rImages Stored Successfully!");
					break;
			case '1':
				i = DSP32_Q(1.0);
				print_dbg_ulong(i);
				break;
			
			case 'c':
				for(i = 0; i < FFT_SIZE; i++)
				{
					WorkingBuffer[i] = DSP32_Q (WorkingBuffer[i]);
				}
				break;
			case 's'://save the working buffer
				SaveBuff(WorkingBuffer);
				break;
// 			case 't':
// 				WorkingBuffer = mspace_malloc(sdram_msp, 16);
// 				for(i = 0; i < 16; i++)
// 				{
// 					WorkingBuffer[i] = ('A' + i);
// 					print_dbg_char(WorkingBuffer[i]);
// 				}
// 				mspace_free(sdram_msp, WorkingBuffer);
// 				break;
			default:
				print_dbg("= Command Not Recognised");
		}
	}
}
