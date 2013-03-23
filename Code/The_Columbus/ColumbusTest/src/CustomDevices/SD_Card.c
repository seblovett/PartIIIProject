/*
 * SD_Card.c
 *
 * Created: 10/02/2013 17:11:58
 *  Author: hslovett
 */ 
//Camera
/*#include "CustomDevices/OV7670.h"*/
//I2C Mux
/*#include "CustomDevices/PCA9542A.h"*/
//MotorDriver
/*#include "CustomDevices/MotorDriver.h"*/
//SDCard
/*#include "CustomDevices/SD_Card.h"*/
#include "CustomDevices/CustomDevices.h"
#include "conf_sd_mmc_spi.h"
#include <asf.h>
#include "stdlib.h"
#include "stdio.h"
// Dummy char table
const char dummy_data[] = 
#include "dummy.h"
;


// PDCA Channel pointer
volatile avr32_pdca_channel_t* pdca_channelrx ;
volatile avr32_pdca_channel_t* pdca_channeltx ;
// Used to indicate the end of PDCA transfer
volatile bool end_of_transfer;
// Local RAM buffer for the example to store data received from the SD/MMC card
volatile char ram_buffer[1000];


void wait()
{
  volatile int i;
  for(i = 0 ; i < 5000; i++);
}
/* interrupt handler to notify if the Data reception from flash is
 * over, in this case lunch the Memory(ram_buffer) to USART transfer and
 * disable interrupt*/

static void pdca_int_handler(void)
{
  // Disable all interrupts.
  Disable_global_interrupt();

  // Disable interrupt channel.
  pdca_disable_interrupt_transfer_complete(AVR32_PDCA_CHANNEL_SPI_RX);

  sd_mmc_spi_read_close_PDCA();//unselects the SD/MMC memory.
  wait();
  // Disable unnecessary channel
  pdca_disable(AVR32_PDCA_CHANNEL_SPI_TX);
  pdca_disable(AVR32_PDCA_CHANNEL_SPI_RX);

  // Enable all interrupts.
  Enable_global_interrupt();

  end_of_transfer = true;
}

/*! \brief Initializes SD/MMC resources: GPIO, SPI and SD/MMC.
 */
void sd_mmc_resources_init(void)
{
  // GPIO pins used for SD/MMC interface
  static const gpio_map_t SD_MMC_SPI_GPIO_MAP =
  {
    {SD_MMC_SPI_SCK_PIN,  SD_MMC_SPI_SCK_FUNCTION },  // SPI Clock.
    {SD_MMC_SPI_MISO_PIN, SD_MMC_SPI_MISO_FUNCTION},  // MISO.
    {SD_MMC_SPI_MOSI_PIN, SD_MMC_SPI_MOSI_FUNCTION},  // MOSI.
    {SD_MMC_SPI_NPCS_PIN, SD_MMC_SPI_NPCS_FUNCTION}   // Chip Select NPCS.
  };

  // SPI options.
  spi_options_t spiOptions =
  {
    .reg          = SD_MMC_SPI_NPCS,
    .baudrate     = SD_MMC_SPI_MASTER_SPEED,  // Defined in conf_sd_mmc_spi.h.
    .bits         = SD_MMC_SPI_BITS,          // Defined in conf_sd_mmc_spi.h.
    .spck_delay   = 0,
    .trans_delay  = 0,
    .stay_act     = 1,
    .spi_mode     = 0,
    .modfdis      = 1
  };

  // Assign I/Os to SPI.
  gpio_enable_module(SD_MMC_SPI_GPIO_MAP,
                     sizeof(SD_MMC_SPI_GPIO_MAP) / sizeof(SD_MMC_SPI_GPIO_MAP[0]));

  // Initialize as master.
  spi_initMaster(SD_MMC_SPI, &spiOptions);

  // Set SPI selection mode: variable_ps, pcs_decode, delay.
  spi_selectionMode(SD_MMC_SPI, 0, 0, 0);

  // Enable SPI module.
  spi_enable(SD_MMC_SPI);

  // Initialize SD/MMC driver with SPI clock (PBA).
  sd_mmc_spi_init(spiOptions, PBA_HZ);
}

/*! \brief Initialize PDCA (Peripheral DMA Controller A) resources for the SPI transfer and start a dummy transfer
 */
void local_pdca_init(void)
{
  // this PDCA channel is used for data reception from the SPI
  pdca_channel_options_t pdca_options_SPI_RX ={ // pdca channel options

    .addr = ram_buffer,
    // memory address. We take here the address of the string dummy_data. This string is located in the file dummy.h

    .size = 512,                              // transfer counter: here the size of the string
    .r_addr = NULL,                           // next memory address after 1st transfer complete
    .r_size = 0,                              // next transfer counter not used here
    .pid = AVR32_PDCA_CHANNEL_USED_RX,        // select peripheral ID - data are on reception from SPI1 RX line
    .transfer_size = PDCA_TRANSFER_SIZE_BYTE  // select size of the transfer: 8,16,32 bits
  };

  // this channel is used to activate the clock of the SPI by sending a dummy variables
  pdca_channel_options_t pdca_options_SPI_TX ={ // pdca channel options

    .addr = (void *)&dummy_data,              // memory address.
                                              // We take here the address of the string dummy_data.
                                              // This string is located in the file dummy.h
    .size = 512,                              // transfer counter: here the size of the string
    .r_addr = NULL,                           // next memory address after 1st transfer complete
    .r_size = 0,                              // next transfer counter not used here
    .pid = AVR32_PDCA_CHANNEL_USED_TX,        // select peripheral ID - data are on reception from SPI1 RX line
    .transfer_size = PDCA_TRANSFER_SIZE_BYTE  // select size of the transfer: 8,16,32 bits
  };

  // Init PDCA transmission channel
  pdca_init_channel(AVR32_PDCA_CHANNEL_SPI_TX, &pdca_options_SPI_TX);

  // Init PDCA Reception channel
  pdca_init_channel(AVR32_PDCA_CHANNEL_SPI_RX, &pdca_options_SPI_RX);

  //! \brief Enable pdca transfer interrupt when completed
  INTC_register_interrupt(&pdca_int_handler, AVR32_PDCA_IRQ_0, AVR32_INTC_INT1);  // pdca_channel_spi1_RX = 0

}

#define BUFFER_FILENAME		"Buffer.bin"
#define BUFFERCSV_FILENAME		"Buffer.csv"
void SaveBuff( int * WorkingBuffer , int size) 
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
	file_write_buf(WorkingBuffer, size * sizeof(WorkingBuffer));
	file_close();
}
void SaveBuff_CSV(char *Filename, int *WorkingBuffer, int size)
{
	int i, j;
	char Buff[16];
	//If the file exists, delete it
	nav_filelist_reset();
	if(nav_filelist_findname((FS_STRING)Filename, false))
	{
		nav_setcwd((FS_STRING)Filename, false, false);
		nav_file_del(false);
	}
	nav_file_create((FS_STRING)Filename);
	nav_setcwd((FS_STRING)Filename, false, true);
	file_open(FOPEN_MODE_W);
	for(i = 0; i < size; i++)
	{
		sprintf(Buff, "%d,", WorkingBuffer[i]);
		//itoa(WorkingBuffer[i], Buff, 10);
		j = 0;
		while(Buff[j++] != 0);//count the size of data to be written
		atoi(Buff);
		file_write_buf(Buff, j-1);
		//file_write_buf(",", 1);
	}	
	
	file_close(); 
}
void SaveCBuff_CSV(char *Filename, dsp16_complex_t *ComplexBuffer, int size)
{
	int i, j;
	char Buff[16];
	//If the file exists, delete it
	nav_filelist_reset();
	if(nav_filelist_findname((FS_STRING)Filename, false))
	{
		nav_setcwd((FS_STRING)Filename, false, false);
		nav_file_del(false);
	}
	nav_file_create((FS_STRING)Filename);
	nav_setcwd((FS_STRING)Filename, false, true);
	file_open(FOPEN_MODE_W);
	for(i = 0; i < size; i++)
	{
		if(ComplexBuffer[i].imag >= 0)
			sprintf(Buff, "%d+%dj,", ComplexBuffer[i].real, ComplexBuffer[i].imag);
		else
			sprintf(Buff, "%d%dj,", ComplexBuffer[i].real, ComplexBuffer[i].imag);
		//itoa(WorkingBuffer[i], Buff, 10);
		j = 0;
		while(Buff[j++] != 0);//count the size of data to be written
		atoi(Buff);
		file_write_buf(Buff, j-1);
		//file_write_buf(",", 1);
	}
	
	file_close();
}
void Read_CSV(char *Filename, int *WorkingBuffer, int size)
{
	char Buff[32];
	int i, j;
	char c;
	nav_filelist_reset();
	if(WorkingBuffer == NULL){
		print_dbg("\n\rRead_CSV: Buffer not initialised");
		return;
	}
	//Check file Exists
	if(nav_filelist_findname((FS_STRING)Filename, false) == false){		
		print_dbg("\n\rRead_CSV : File doesn't exist;");
		return;
	}
	nav_setcwd((FS_STRING)Filename, false, true);
	file_open(FOPEN_MODE_R);
	for(i = 0; i < size; i++)
	{
		if(file_eof())
			break;
		c = 0;
		//j = 0;
		for(j = 0; j < 32; j++)
			Buff[j] = 0; //clear the buffer
		j = 0;
		while(c != ',')
		{
			if(file_eof())
				break;
			c = file_getc();
			if(c == ',')
				break;
			Buff[j++] = c; //load string into buffer
		}
		WorkingBuffer[i] = atoi(Buff); //Convert to int and put into buffer
	}
	file_close();
	return;
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

int ReadSignal( int * WorkingBuffer ) 
{
	bool status_b;
	int Status, temp;
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
//		print_dbg("\n\r Read from file: ");
		c = 0;
		temp = 0;
		temp |= file_getc() << 24;
		temp |= file_getc() << 16;
		temp |= file_getc() << 8;
		temp |= file_getc();	
		
//		print_dbg_char(c);
		
		WorkingBuffer[Status] = temp;
// 		print_dbg("  Working Buff = ");
// 		print_dbg_char(WorkingBuffer[Status]);
	}
	file_close();
	return STATUS_OK;
}

int Read2DSignal( int * WorkingBuffer )
{
	bool status_b;
	int Status, temp;
	char c = 0;
	if(Columbus_Status.SD_Card->Status != STATUS_OK)
	return ERR_IO_ERROR;
	nav_filelist_reset();
	nav_setcwd((FS_STRING)TWOD_SIGNAL_FILE, false, false);
	status_b = file_open(FOPEN_MODE_R);
	if(status_b == false)
	{
		print_dbg("File Open Error");
		return ERR_IO_ERROR;
	}
	
	
	//Status = file_read_buf(WorkingBuffer, 16);
	for(Status = 0; Status < FFT_SIZE * FFT_SIZE; Status++)
	{
		//		print_dbg("\n\r Read from file: ");
		c = 0;
		temp = 0;
		temp |= file_getc() << 24;
		temp |= file_getc() << 16;
		temp |= file_getc() << 8;
		temp |= file_getc();
		
		//		print_dbg_char(c);
		
		WorkingBuffer[Status] = temp;
		// 		print_dbg("  Working Buff = ");
		// 		print_dbg_char(WorkingBuffer[Status]);
	}
	file_close();
	return STATUS_OK;
}

void SaveBitmap(uint16_t *Image, int width, int height, char *FileName)
{
	int i, j, k;
	uint8_t *Buffer;
	
	nav_filelist_reset();
	if(nav_filelist_findname((FS_STRING)FileName, false))
	{
		nav_setcwd((FS_STRING)FileName, true, false);		
		nav_file_del(false);
	}
	nav_file_create((FS_STRING)FileName);
	file_open(FOPEN_MODE_W);
	//write a modified bitmap header 
	//Calculate which is the biggest:
	i = width * 2; 
	if(height > i)
		i = height;
	if(DIBHEADERSIZE > i)
		i = DIBHEADERSIZE;
	
	Buffer = malloc(i);
	
	for(i = 0; i < BMPHEADERSIZE; i++)//copy all the header
	{
		Buffer[i] = BMPHeader[i];
	}
	//edit the size field
	j = width * height * 2 + BMPHEADERSIZE + DIBHEADERSIZE;
	for(i = 0; i < 4; i ++)
	{
		Buffer[i + 2] = (uint8_t)(j >> 8*i);
	}
	
	file_write_buf(Buffer, BMPHEADERSIZE);
	
	//DIB Header
	for(i = 0; i < DIBHEADERSIZE; i ++)
	{
		Buffer[i] = DIBHead[i];
	}
	Buffer[4] = (uint8_t)(width & 0xFF);
	Buffer[5] = (uint8_t)((width >> 8) & 0xFF);
	Buffer[6] = (uint8_t)((width >> 16) & 0xFF);
	Buffer[7] = (uint8_t)((width >> 24) & 0xFF);
	
	Buffer[8] = (uint8_t)(height & 0xFF);
	Buffer[9] = (uint8_t)((height >> 8) & 0xFF);
	Buffer[10] = (uint8_t)((height >> 16) & 0xFF);
	Buffer[11] = (uint8_t)((height >> 24) & 0xFF);
	
	file_write_buf(Buffer, DIBHEADERSIZE);
	
	for(i = 0; i < height ; i++ )
	{
		for(j = 0; j < width ; j++)
		{
			//Copy the data across. 

			/*Buffer[j] = Image[i*width + j];*/
			Buffer[(2 * j) + 1] = (uint8_t)(Image[i*width + j]);
			Buffer[(2 * j)] = (uint8_t)(Image[i*width + j] >> 8);
		}
		if(file_write_buf(Buffer, width * 2) != (width * 2))
		{
			print_dbg("\n\rFile write error.");
		}
		
// 		j = width % 4;
// 		if(j != 0)
// 		{//Padding is needed to make things 4 byte aligned
// 			file_write_buf(Buffer, j);
// 		}
	}
	
	
	
	free(Buffer);
	file_close();
}

#define BMP_HEADER_FILESIZE_OFFSET		2
#define BMP_HEADER_OFFSETTOARRAY_OFFSET	10
#define DIB_V5_WIDTH_OFFSET				4
#define DIB_V5_HEIGHT_OFFSET			8
#define DIB_V5_BITCOUNT_OFFSET			14
#define DIB_V5_IMAGESIZE_OFFSET			20

int ReadBigEndian(uint8_t *Buffer, int Offset, uint size)
{
	int retVal, i; 
	retVal = 0; //initialise value
	for(i = 0; i < size; i++)
	{
		retVal |= Buffer[Offset + i] << (i * 8);
	}
	return (Buffer[Offset]) | (Buffer[Offset + 1] << 8) | (Buffer[Offset + 2] << 16) | (Buffer[Offset + 3] << 24);
}
void ReadBitmap(char *Filename, Image_t *image)
{
//	Image_t image; 
	int i, j, FileSize, OffsetToArray, temp, BitCount, ImageSize;
	uint8_t Buffer[128];
	nav_filelist_reset();
	if(nav_filelist_findname((FS_STRING)Filename, false) == false)//if the file doesn't exist
	{
		print_dbg("\n\rFile ");
		print_dbg(Filename);
		print_dbg("\n\r does not exist;");
		return;
	}
	nav_setcwd((FS_STRING)Filename, false, false);
	file_open(FOPEN_MODE_R);
	//Read Header
	file_read_buf(Buffer, BMPHEADERSIZE);
	//Check for BM to confirm it is a Bitmap
	if((Buffer[0] != 'B') || (Buffer[1] != 'M'))
	{
		print_dbg("\n\rBitmap Parse Fail 'BM';");
		return;
	}
	//Extract file size and offset to pixel array
	FileSize = ReadBigEndian(Buffer, BMP_HEADER_FILESIZE_OFFSET, 4);
	OffsetToArray = ReadBigEndian(Buffer, BMP_HEADER_OFFSETTOARRAY_OFFSET, 4);
	
	file_read_buf(Buffer, DIBHEADERSIZE);
	temp = ReadBigEndian(Buffer, 0, 4);
	if(temp != 0x7C) //check it is a V5 BMP DIB Header
	{
		print_dbg("\n\rBMP Parse: DIB Header not V5;");
		return;
	}
	image->Width= ReadBigEndian(Buffer, DIB_V5_WIDTH_OFFSET, 4);
	image->Height = ReadBigEndian(Buffer, DIB_V5_HEIGHT_OFFSET, 4);
	BitCount = ReadBigEndian(Buffer, DIB_V5_BITCOUNT_OFFSET, 2);
	ImageSize = ReadBigEndian(Buffer, DIB_V5_IMAGESIZE_OFFSET, 4);
	print_dbg("\n\rBitmap Width = ");
	print_dbg_ulong(image->Width);
	print_dbg("\n\rBitmap Height = ");
	print_dbg_ulong(image->Height);
	print_dbg("\n\rBitmap File Size = ");
	print_dbg_ulong(FileSize);
	print_dbg("\n\rBitmap Offset to Array = ");
	print_dbg_ulong(OffsetToArray);
	print_dbg("\n\rBitmap Image Bitcount = ");
	print_dbg_ulong(BitCount);
	print_dbg("\n\rBitmap Image Size = ");
	print_dbg_ulong(ImageSize);
	
	file_seek(OffsetToArray, FS_SEEK_SET);
	j = 0;
	image->ImagePtr = mspace_malloc(sdram_msp, image->Height * image->Width);
	for(i = 0; i < ImageSize; i += 2)
	{
		image->ImagePtr[j++] = (file_getc()<<8) | (file_getc()); 
	}
	file_close();
	nav_filelist_reset();
	return;
}