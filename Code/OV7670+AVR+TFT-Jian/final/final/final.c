#include "stdio.h"
#include "avr/io.h"
#include "config.h"
#include "VARIABLE.h"
//#define F_CPU 12000000UL
//#include "util/delay.h"
#include "delay.c"
#include "ov7670.c"
#include "FIFOread.c"
#include "SCCB.c"
#include "avr/interrupt.h"
#include "avr.h"
#include "lcd.c"
//#include "TFT.c"


//Global Signal for INT0
volatile int TIMES=1;

//Interrupt Service Routine for INT0 to Generate WEN
ISR(INT0_vect)
{
	if (TIMES==1)
	{
		FIFO_WEN_SET;
		TIMES++;
	}
	else if (TIMES==2)
	{
		FIFO_WEN_CLR;
		TIMES++;
	}
	else if (TIMES<57)
	{
		TIMES++;
	}
	else
	{
		TIMES=1;
	}
}



void main(void)
{
	delay_ms(100);
	TSLCDReset();
	TSLCDInit();
// Example Display
	TSLCDFillRect(0,TS_SIZE_X-1,0,TS_SIZE_Y-1,TS_COL_BLUE,TS_MODE_NORMAL);
	TSLCDFillRect(0,TS_SIZE_X-1,0,70,TS_COL_WHITE,TS_MODE_NORMAL);
	TSLCDFillRect(10,60,100,200,TS_COL_RED,TS_MODE_NORMAL);
	TSLCDFillRect(20,80,90,130,TS_COL_BLACK,TS_MODE_NORMAL);
	TSLCDFillRect(30,90,100,140,TS_COL_YELLOW,TS_MODE_NORMAL);
	TSLCDFillRect(20,80,160,200,TS_COL_BLACK,TS_MODE_NORMAL);
	TSLCDFillRect(30,90,170,210,TS_COL_RED,TS_MODE_NORMAL);
	TSLCDFillRect(195,205,71,TS_SIZE_Y-1,TS_COL_WHITE,TS_MODE_NORMAL);
	delay_ms(1000);
	TSLCDFillCirc(200,155,60,TS_COL_WHITE,TS_MODE_FULL);
	TSLCDFillCirc(200,155,50,TS_COL_BLUE,TS_MODE_FULL);
	TSLCDFillCirc(200,155,40,TS_COL_BLACK,TS_MODE_FULL);
	TSLCDFillCirc(200,155,30,TS_COL_RED,TS_MODE_FULL);
	delay_ms(1000);
	TSLCDSetBackColor(TS_COL_BLACK);
	TSLCDSetForeColor(TS_COL_YELLOW);
	TSLCDPrintStr(2,6,"** LCD Initial Succeed! **",TS_MODE_FULL);

//	DDRA = 0b00000000;
//	PORTB &= ~(1<<LCD_CS_PIN);
//	PORTB &= ~(1<<LCD_WR_PIN);
	delay_ms(100);
	   while(1!=OV7670_init());		//initial ov7660
	delay_ms(100);
	   while(1!=FIFO_init());		//initial FIFO reading sequence
	   
//to give FPGA a reset 
/*	delay_ms(1);					
	 DDRD |= (1<<5);
	 PORTD &= ~(1<<5);
	 delay_ms(1);
	 PORTD |= (1<<5);
	 delay_ms(100);
	 PORTD &= ~(1<<5);
	 */

// initial the int0 interrupt for WEN   
	  DDRD &= ~(1<<OV7670_SYNC);		//set OV7670_SYNC as input for INT0
	  PORTD |= (1<<OV7670_SYNC);		//Enable OV7670_SYNC pull-up resistor
	  
	  EIMSK = 1<<INT0;				//Enable INT0
	  EICRA = 1<<ISC01;				//Trigger INT0 on the falling edge
	  
	  sei();						//Enable Global Interrupt
	  
		TSLCDSetWindow(0,319,0,479);
		TSLCDOutIns(LCD_RW_GRAM);
	
	  while (1)						//Main routine to display on TFT
	  {
		  if (TIMES=2)
		  {
			  	unsigned int i,j;
				unsigned short Temp;
				

				
				for (j=0; j < 480; j++)
				{
						if (j==240)
						{
							FIFO_nRRST_CLR;
							FIFO_RCLK_SET;
							FIFO_RCLK_CLR;
							FIFO_nRRST_SET;
						}
					for (i=0; i < 320; i++)
					{
							Temp=FIFO_TO_AVR();
							TSLCDOutDat(Temp);					
					}

				}				
			FIFO_nRRST_CLR;
			FIFO_RCLK_SET;
			FIFO_RCLK_CLR;
			FIFO_nRRST_SET;
		  }
	  }
}	  		  