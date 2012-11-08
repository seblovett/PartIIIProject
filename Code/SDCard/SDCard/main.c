/*---------------------------------------------------------------*/
/* Petit FAT file system module test program R0.02 (C)ChaN, 2009 */
/*---------------------------------------------------------------*/
#define F_CPU 12000000UL
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "diskio.h"
#include "pff.h"
#include "uart.h"
#include "xitoa.h"

/*---------------------------------------------------------*/
/* Work Area                                               */
/*---------------------------------------------------------*/

char Line[128];		/* Console input buffer */



/*-----------------------------------------------------------------------*/
/* Main                                                                  */


void flushBuffer( char *Line ) 
{
	for(int i = 0; i < sizeof(Line); i++)
	{
		Line[i] = 0;
	}
}

int main (void)
{
	char *ptr;
	long p1, p2;
	BYTE res;
	WORD s1, s2, s3, ofs, cnt, w;
	FATFS fs;			/* File system object */
	DIR dir;			/* Directory object */
	FILINFO fno;		/* File information */


	BYTE mcusr = MCUSR;
	MCUSR = 0x00;

	//	PORTB = 0b101011;	/* u z H L H u */
	//	DDRB =  0b001110;
	PORTB = 0b00010000;      // SS high
	DDRB =  0b10110000;      // !SS,SCK and MOSI outputs

	USART0_Init(MYUBBR0);
	


	USART0_SendString("\tJWBXP\n\rMCUSR: ");
	USART0_SendHex(mcusr);

	for (;;) 
	{
		USART0_SendString("\n\r>");
		USART0_GetLine(Line, sizeof(Line));
		ptr = Line;
		
		switch(*ptr++)
		{
			case 'd':
				USART0_SendHex(disk_initialize());
				break;
				
			case 'm':
				USART0_SendHex(pf_mount(&fs));
				break;
				
			case 'l':
				while (*ptr == ' ') ptr++;
				res = pf_opendir(&dir, ptr);
				if (res) { USART0_SendHex(res); break; }
				s1 = 0;
				for(;;) 
				{
					res = pf_readdir(&dir, &fno);
					if (res != FR_OK) { USART0_SendChar(res); break; }
					
					if (!fno.fname[0]) break;
					if (fno.fattrib & AM_DIR)
					{
						USART0_SendString("\t<DIR>\t");
						USART0_SendString(fno.fname);
					}											
						
					else
					{
						USART0_SendChar('\t');
						USART0_SendInt(fno.fsize);
						USART0_SendChar('\t');
						USART0_SendString(fno.fname);
						USART0_SendString("\n\r");
					}										
					s1++;
				}
				USART0_SendString("\n\rItem(s) = ");
				USART0_SendInt(s1);
				
				break;
				
			case 'o': //open file
				while(*ptr == ' ')
					ptr++; //skip all whitespace
				
				USART0_SendHex(pf_open(ptr));
				break;
				
			case 'r':
				res = pf_read(Line, sizeof(Line), &s1);
				USART0_SendHex(res);
				USART0_SendString("\n\rRead Data:\n\r\"");
				USART0_SendString(Line);
				USART0_SendString("\"\n\r");
				break;
				
			case 'W':
				flushBuffer(Line);
				USART0_SendString("\n\rTypeWriteData:\n\r>");
				USART0_GetLine(Line, sizeof(Line));
				
				pf_write(&Line, sizeof(Line), &s1);
				USART0_SendInt(s1);
				pf_write(0, 0, &s1);
				break;
		}
		
	}

}


