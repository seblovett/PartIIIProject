/*
 * main.c
 *
 * Created: 05/10/2012 21:46:52
 *  Author: hslovett
 */ 
#include "Config.h"

// ISR(TIMER0_COMPA_vect)//call every 10 ms.
// {
// 	disk_timerproc();
// }
//unsigned char TWI_Buffer[TWI_BUFFER_SIZE];
int main(void)
{
// 	DSTATUS driveStatus;
// 	FATFS FileSystemObject;

	
	USART0_Init(MYUBBR0);//bit rate 250000
	USART0_SendString("Starting Up...\n\r");
	TWI_Master_Initialise();
	USART0_SendString("TWI Initialised.\n\r");
	sei(); //turn global interrupts on
	while(1 != FIFO_init()); //initialise buffer
	USART0_SendString("FIFO Buffer Initialised\n\r");
	//_delay_ms(1000);
	USART0_SendString("OV7670 Initialise ");	
	if(1 ==	OV7670_init())
	{
		USART0_SendString("Complete\n\r");
	}
	else
	{
					
		USART0_SendString("Fail\n\r");
	}
// 
// //initialising SD card
// 	TIMSK0 |= (1<<OCIE0A);
// 	OCR0A = 117; //needs to be 10ms interrupt
// 	TCCR0B |= (1<<CS02) | (1 <<CS00); //1024 prescaler.
	
// 	PORTB = 0b00010000;      // SS high
// 	DDRB =  0b10110000;      // !SS,SCK and MOSI outputs

	
    while(1)
	{
		switch(Received0)
		{
			case 'A':
				USART0_SendString("\n\rTWI Sent;\n\r");
				if(1 == wrOV7670Reg(OV_COM7, 0x80))
				{
					USART0_SendString("Success!\n\r");
				}
				else
				{
					USART0_SendString("Fail\n\r");
				}
				Received0 = 0;
				break;
				
			case 'R':
				USART0_SendString("\n\rTWI Read;\n\r");
				unsigned char Data;
				if(1 == rdOV7670Reg(OV_PID, &Data))
				{
					USART0_SendString("TWI Data Returned:\r\n");
					USART0_SendHex(Data);
				}
				else
				{
					USART0_SendString("Read Fail.\n\r");
				}
				Received0 = 0;
				break;
				
			case 'I':
				USART0_SendString("\n\rOV7670 Initialise ");
				if(1 ==	OV7670_init())
				{
					USART0_SendString("Complete\n\r");
				}
				else
				{
					
					USART0_SendString("Fail\n\r");
				}
				Received0 = 0;
				break;
			case 'T':
				TWI_Master_Initialise();
				Received0 = 0;
				break;
			case 'P':
				LoadImageToBuffer();
				while (1 != GetImageIfAvailiable()) ;
				Received0 = 0;
				break;
			case 'q':
				wrOV7670Reg(OV_COM7, 0x80);
				Received0 = 0;
				break;
			
// 			case 'S':
// 				Received0 = 0;
// 				
// 				if(f_mount(0, &FileSystemObject) != FR_OK){
// 					USART0_SendString("Fat Mount Error\n\r");
// 				}
// 				_delay_ms(100);
// 				driveStatus = disk_initialize(0);
// 				if(	(driveStatus & STA_NOINIT) ||
// 					(driveStatus & STA_NODISK) ||
// 					(driveStatus & STA_PROTECT)	)
// 				{
// 					USART0_SendString("Initialise Failure\n\rStatus:");
// 					USART0_SendHex(driveStatus);
// 					f_mount(0,0);
// 					break;
// 				}
// 				FIL logFile;
// 				
// 				if(f_open(&logFile, "/GpsLog.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS) != FR_OK)
// 				{
// 					USART0_SendString("File Open Error\n\r");
// 					f_close(&logFile);
// 					f_mount(0,0);	
// 					break;
// 				}
// 				
// 				unsigned int bytesWritten;
// 				f_write(&logFile, "New Log Opened!\n", 16, &bytesWritten);
// 				
// 				f_close(&logFile);
// 				f_mount(0,0);
// 				USART0_SendString("Success!\n\r");
// 				Received0 = 0;
// 				break;
				
			
			default:
				Received0 = Received0;
				break;
		}
		
	}		
}