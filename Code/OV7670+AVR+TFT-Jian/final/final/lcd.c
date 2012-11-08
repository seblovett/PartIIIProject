//  Author : Steve Gunn
//
//    Date : 30/01/2010
//
// Licence : This code was modified from the example code at www.thaieasyelec.net. 
//           This work is licensed under the Creative Commons Attribution License. 
//           To view a copy of this license, visit http://creativecommons.org/about/licenses/.

#include "avr.h"
#include "lcd.h"
#include "font.c"


void TSLCDSetWindow(int sx,int ex,int sy,int ey)
{
	// *** Y needs to be set before X ***
	TSLCDOutIns(LCD_START_ADY);
	TSLCDOutDat(sy);
	TSLCDOutIns(LCD_END_ADY);
	TSLCDOutDat(ey);
	TSLCDOutIns(LCD_GRAM_ADY);
	TSLCDOutDat(sy);
	TSLCDOutIns(LCD_START_ADX);
	TSLCDOutDat(sx);
	TSLCDOutIns(LCD_END_ADX);
	TSLCDOutDat(ex);
	TSLCDOutIns(LCD_GRAM_ADX);
	TSLCDOutDat(sx);
}
/*
void TSLCDWriteDDRAM(unsigned int adx,unsigned int ady,unsigned short data)
{
	TSLCDOutIns(LCD_GRAM_ADY);
	TSLCDOutDat(ady);
	TSLCDOutIns(LCD_GRAM_ADX);
	TSLCDOutDat(adx);
	
	TSLCDOutIns(LCD_RW_GRAM);
	
	TSLCDOutDat(data);
}*/
/*
void TSLCDSetWindow2(int sx,int ex,int sy,int ey)
{
	TSLCDOutInsDat(LCD_DRIVER_OUTPUT_CTRL, 		0x043C);
	TSLCDOutInsDat(LCD_ENTRY_MODE, 				0x1020);
	// *** Y needs to be set before X ***
	TSLCDOutIns(LCD_START_ADY);
	TSLCDOutDat(sy);
	TSLCDOutIns(LCD_END_ADY);
	TSLCDOutDat(ey);
	TSLCDOutIns(LCD_GRAM_ADY);
	TSLCDOutDat(sy);
	TSLCDOutIns(LCD_START_ADX);
	TSLCDOutDat(sx);
	TSLCDOutIns(LCD_END_ADX);
	TSLCDOutDat(ex);
	TSLCDOutIns(LCD_GRAM_ADX);
	TSLCDOutDat(sx);
}
*/
void TSLCDOutInsDat(unsigned short ins, unsigned short dat) 
{
	TSLCDOutIns(ins); 
	TSLCDOutDat(dat);
} 

void TSLCDOutDat(unsigned short dat) 
{
	Setb(LCD_RS_PORT,LCD_RS_PIN);
	Setb(LCD_RD_PORT,LCD_RD_PIN);
	Clrb(LCD_WR_PORT,LCD_WR_PIN);

	LCD_DB_DPRT = 0xFF;
	LCD_DB_PORT = dat >> 8;

	Clrb(LCD_CS_PORT,LCD_CS_PIN);
	Setb(LCD_CS_PORT,LCD_CS_PIN);

	LCD_DB_PORT = dat;

	Clrb(LCD_CS_PORT,LCD_CS_PIN);
	Setb(LCD_CS_PORT,LCD_CS_PIN);
	Setb(LCD_WR_PORT,LCD_WR_PIN);

	LCD_DB_DPRT = 0;
}


void TSLCDOutIns(unsigned short ins) 
{
	Clrb(LCD_RS_PORT,LCD_RS_PIN);
	Setb(LCD_RD_PORT,LCD_RD_PIN);
	Clrb(LCD_WR_PORT,LCD_WR_PIN);

	LCD_DB_DPRT = 0xFF;
	LCD_DB_PORT = ins >> 8;

	Clrb(LCD_CS_PORT,LCD_CS_PIN);
	Setb(LCD_CS_PORT,LCD_CS_PIN);

	LCD_DB_PORT = ins;

	Clrb(LCD_CS_PORT,LCD_CS_PIN);
	Setb(LCD_CS_PORT,LCD_CS_PIN);
	Setb(LCD_WR_PORT,LCD_WR_PIN);

	LCD_DB_DPRT = 0;
}

unsigned short TSLCDInDat(void) 
{
	unsigned short dat = 0;

	LCD_DB_DPRT = 0;

	Setb(LCD_RS_PORT,LCD_RS_PIN);
	Setb(LCD_WR_PORT,LCD_WR_PIN);
	Clrb(LCD_RD_PORT,LCD_RD_PIN);
	Clrb(LCD_CS_PORT,LCD_CS_PIN);

	dat = LCD_DB_PINP;

	Setb(LCD_CS_PORT,LCD_CS_PIN);

	dat <<= 8;

	Clrb(LCD_CS_PORT,LCD_CS_PIN);

	dat |= LCD_DB_PINP;

	Setb(LCD_CS_PORT,LCD_CS_PIN);
	Setb(LCD_RD_PORT,LCD_RD_PIN);

	return (dat);
}


unsigned short TSLCDInIns(void) 
{
	unsigned short ins = 0;

	LCD_DB_DPRT = 0;

	Clrb(LCD_RS_PORT,LCD_RS_PIN);
	Setb(LCD_WR_PORT,LCD_WR_PIN);
	Clrb(LCD_RD_PORT,LCD_RD_PIN);
	Clrb(LCD_CS_PORT,LCD_CS_PIN);

	ins = LCD_DB_PINP;

	Setb(LCD_CS_PORT,LCD_CS_PIN);

	ins <<= 8;

	Clrb(LCD_CS_PORT,LCD_CS_PIN);

	ins |= LCD_DB_PINP;

	Setb(LCD_CS_PORT,LCD_CS_PIN);
	Setb(LCD_RD_PORT,LCD_RD_PIN);

	return (ins);
}

void TSLCDReset(void) 
{
	Orb(LCD_RST_DPRT,LCD_RST_PIN);
	Orb(LCD_RS_DPRT,LCD_RS_PIN);
	Orb(LCD_CS_DPRT,LCD_CS_PIN);
	Orb(LCD_RD_DPRT,LCD_RD_PIN);
	Orb(LCD_WR_DPRT,LCD_WR_PIN);
	Clrb(LCD_RST_PORT,LCD_RST_PIN);
	delay_ms(50);
	Setb(LCD_RST_PORT,LCD_RST_PIN);
	Setb(LCD_CS_PORT,LCD_CS_PIN);
	delay_ms(100);
}




void TSLCDInit(void) 
{
	// Driver Code for D51E5TA7601

// 	TSLCDOutInsDat(LCD_START_OSCILLATOR, 		0x0001);
	delay_ms(50);

	// Display Control
	TSLCDOutInsDat(LCD_DRIVER_OUTPUT_CTRL, 		0x003C);
	TSLCDOutInsDat(LCD_DRIVING_WAVEFORM_CTRL, 	0x0100);
	TSLCDOutInsDat(LCD_ENTRY_MODE, 				0x1030);
	TSLCDOutInsDat(LCD_BLANK_PERIOD_CTRL, 		0x0000);
	TSLCDOutInsDat(LCD_FRAME_CYCLE_CTRL, 		0x0500);
	TSLCDOutInsDat(LCD_EXT_DISPLAY_INT_CTRL, 	0x0000);
	TSLCDOutInsDat(LCD_INTERFACE_CTRL, 			0x0770);
	TSLCDOutInsDat(LCD_GATE_SCAN_POS_CTRL, 		0x0000);
	TSLCDOutInsDat(LCD_FRAME_MARKER_POS, 		0x0001);

	// Power Control
	TSLCDOutInsDat(LCD_POWER_CTRL2,				0x0406);
	TSLCDOutInsDat(LCD_POWER_CTRL3,				0x000E);
	TSLCDOutInsDat(LCD_POWER_CTRL4,				0x0222);
	TSLCDOutInsDat(LCD_POWER_CTRL5,				0x0015);
	TSLCDOutInsDat(LCD_POWER_CTRL6,				0x4277);
	TSLCDOutInsDat(LCD_POWER_CTRL7,				0x0000);

	// Gamma Control
	TSLCDOutInsDat(LCD_GAMMA_CTRL9,				0x6A50);
	TSLCDOutInsDat(LCD_GAMMA_CTRL10,			0x00C9);
	TSLCDOutInsDat(LCD_GAMMA_CTRL11,			0xC7BE);
	TSLCDOutInsDat(LCD_GAMMA_CTRL12,			0x0003);
	TSLCDOutInsDat(LCD_GAMMA_CTRL15,			0x3443);
	TSLCDOutInsDat(LCD_GAMMA_CTRL20,			0x0000);
	TSLCDOutInsDat(LCD_GAMMA_CTRL21,			0x0000);
	TSLCDOutInsDat(LCD_GAMMA_CTRL5,				0x6A50);
	TSLCDOutInsDat(LCD_GAMMA_CTRL6,				0x00C9);
	TSLCDOutInsDat(LCD_GAMMA_CTRL7,				0xC7BE);
	TSLCDOutInsDat(LCD_GAMMA_CTRL8,				0x0003);
	TSLCDOutInsDat(LCD_GAMMA_CTRL14,			0x3443);
	TSLCDOutInsDat(LCD_GAMMA_CTRL18,			0x0000);
	TSLCDOutInsDat(LCD_GAMMA_CTRL19,			0x0000);
	TSLCDOutInsDat(LCD_GAMMA_CTRL1,				0x6A50);
	TSLCDOutInsDat(LCD_GAMMA_CTRL2,				0x00C9);
	TSLCDOutInsDat(LCD_GAMMA_CTRL3,				0xC7BE);
	TSLCDOutInsDat(LCD_GAMMA_CTRL4,				0x0003);
	TSLCDOutInsDat(LCD_GAMMA_CTRL13,			0x3443);
	TSLCDOutInsDat(LCD_GAMMA_CTRL16,			0x0000);
	TSLCDOutInsDat(LCD_GAMMA_CTRL17,			0x0000);
	delay_ms(20);

	// Power Control 
	TSLCDOutInsDat(LCD_POWER_CTRL3,				0x200E);
	delay_ms(160);
	TSLCDOutInsDat(LCD_POWER_CTRL3,				0x2003);
	delay_ms(40);
	
	//Partial Screen1
//	TSLCDOutInsDat(LCD_PART_IMG1_START_AD,		0x0000);
//	TSLCDOutInsDat(LCD_PART_IMG1_END_AD,		0x00F0);

	// RAM Adddress Position
	TSLCDOutInsDat(LCD_HOR_END_AD,				0x013F);
	TSLCDOutInsDat(LCD_HOR_START_AD,			0x0000);
	TSLCDOutInsDat(LCD_VER_END_AD,				0x01DF);
	TSLCDOutInsDat(LCD_VER_START_AD,			0x0000);
	TSLCDOutInsDat(LCD_GRAM_VER_AD,				0x0000);
	TSLCDOutInsDat(LCD_GRAM_HOR_AD,				0x013F);

	// Back Light Control
	TSLCDOutInsDat(LCD_OTP_CABC_CTRL,			0x0200); 
	// For still image, choose the code below
	TSLCDOutInsDat(LCD_DISPLAY_CTRL1,			0x7000); 
	TSLCDOutInsDat(LCD_DISPLAY_CTRL2,			0x0002); 
	TSLCDOutInsDat(LCD_SMLC_IMG_BR_LEVEL1,		0x4B90); 
	TSLCDOutInsDat(LCD_SMLC_IMG_BR_LEVEL2,		0x95A0);
	TSLCDOutInsDat(LCD_SMLC_IMG_BR_LEVEL3,		0xA0AC);
	TSLCDOutInsDat(LCD_SMLC_IMG_BR_LEVEL4,		0xB5CE);
	// For motion picture, choose the line below
//	TSLCDOutInsDat(LCD_DISPLAY_CTRL1,			0x40FF);

	// Display Control
	TSLCDOutInsDat(LCD_DISPLAY_CTRL4,			0x0012);
	delay_ms(40);
	TSLCDOutInsDat(LCD_DISPLAY_CTRL4,			0x0017);
}

void TSLCDSetOffset(int x, int y)
{
	offsetx = x;
	offsety = y;
}


void TSLCDSetForeColor(unsigned short color) 
{
	fore_color = color;
}


void TSLCDSetBackColor(unsigned short color) 
{
	back_color = color;
}

void TSLCDShowPic(int sx,int ex,int sy,int ey,const unsigned short *pic,ts_mode_t mode)
//show picture from code memory with specific size
{
	unsigned long k = 0;
	unsigned short color;
	unsigned int i,j;

    TSLCDSetWindow(sx, ex, sy, ey);
	TSLCDOutIns(LCD_RW_GRAM);

	switch(mode)
	{
		case TS_MODE_FULL:
			for (j=0; j < ey - sy + 1; j++)
				for (i=0; i < ex - sx + 1; i++)
				{
					TSLCDOutDat(pgm_read_word(&pic[k]));
					k++;
				}
			break;
		case TS_MODE_NORMAL:
			for (j=0; j < ey - sy + 1; j++)
				for (i=0; i < ex - sx + 1; i++)
				{
					if (pgm_read_word(&pic[k]) == TS_COL_WHITE)
					{
						color = TSLCDInDat(); 		// ignore invalid data
						color = TSLCDInDat();
						TSLCDOutDat(color);
					}
					else
					{
						TSLCDOutDat(pgm_read_word(&pic[k]));
					}
					k++;
				}
			break;
		case TS_MODE_INVERSE:
			break;
	}
}

void TSLCDFillRect(int sx,int ex,int sy,int ey,unsigned short color,ts_mode_t mode) //draw a rectangular
{
	unsigned int i,j;

    TSLCDSetWindow(sx, ex, sy, ey);
	TSLCDOutIns(LCD_RW_GRAM);

	switch(mode)
	{
		case TS_MODE_FULL:
		case TS_MODE_NORMAL:
			for (j=0; j < ey - sy + 1; j++)
				for (i=0; i < ex - sx + 1; i++)
					TSLCDOutDat(color);
			break;
		case TS_MODE_INVERSE:
			for (j=0; j < ey - sy + 1; j++)
				for (i=0; i < ex - sx + 1; i++)
				{
					color = TSLCDInDat(); 		// ignore invalid data
					color = TSLCDInDat();
					TSLCDOutDat(~color);
				}
			break;
	}
}

void TSLCDFillCirc(int cx,int cy,int rad,unsigned short color, ts_mode_t mode) //draw a circle
{
	int i,j;
	unsigned short color_buf;
	unsigned short rad2 = rad*rad;

    TSLCDSetWindow(cx - rad, cx + rad, cy - rad, cy + rad);
	TSLCDOutIns(LCD_RW_GRAM);

	switch(mode)
	{
		case TS_MODE_NORMAL:
			for (j=-rad; j<=rad; j++)
				for (i=-rad; i<=rad; i++)
					if (i*i + j*j < rad2)
					{
						TSLCDOutDat(color);
					}
					else
					{
						// Perform read to advance address counter
						color_buf = TSLCDInDat(); 		
					}
			break;
		case TS_MODE_INVERSE:
			for (j=-rad; j<=rad; j++)
				for (i=-rad; i<=rad; i++)
					if (i*i + j*j < rad2)
					{
						color_buf = TSLCDInDat(); 		// ignore invalid data
						color_buf = TSLCDInDat();
						TSLCDOutDat(~color_buf);
					}
					else
					{
						color_buf = TSLCDInDat(); 		// ignore invalid data
						color_buf = TSLCDInDat();
						TSLCDOutDat(color_buf);
					}
			break;
		case TS_MODE_FULL:
			for (j=-rad; j<=rad; j++)
				for (i=-rad; i<=rad; i++)
					if (i*i + j*j < rad2)
					{
						TSLCDOutDat(color);
					}
					else
					{
						TSLCDOutDat(back_color);
					}
			break;
	}
}

void TSLCDCharDisp(char character,int sx,int sy,ts_mode_t mode) 
{
	int i,j;
	int ex,ey;
	unsigned short c;

	ex = sx + FONT_WIDTH - 1;
	ey = sy + FONT_HEIGHT - 1;

	FBufferStore(character - 0x20);

    TSLCDSetWindow(sx, ex, sy, ey);
	TSLCDOutIns(LCD_RW_GRAM);

	switch(mode)
	{
		case TS_MODE_NORMAL:
			for (j=ey-sy; j>=0; j--)
				for (i=0; i<ex - sx + 1; i++)
				{
					if (FBufferRead(i,j))
					{
						TSLCDOutDat(fore_color);
					}
					else
					{
						c = TSLCDInDat(); 		// ignore invalid data
	//					c = TSLCDInDat();
	//					TSLCDOutDat(c);
					}
				}
			break;
		case TS_MODE_INVERSE:
			for (j=ey-sy; j>=0; j--)
				for (i=0; i<ex - sx + 1; i++)
				{
					c = TSLCDInDat(); 			// ignore invalid data
					c = TSLCDInDat();
					if (FBufferRead(i,j))
					{
						TSLCDOutDat(~c);
					}
					else
					{
						TSLCDOutDat(c);
					}
				}
			break;
		case TS_MODE_FULL:
			for (j=ey-sy; j>=0; j--)
				for (i=0; i<ex - sx + 1; i++)
				{
					if (FBufferRead(i,j))
					{
						TSLCDOutDat(fore_color);
					}
					else
					{
						TSLCDOutDat(back_color);
					}
				}
			break;
	}
}

void TSLCDPrintStr(unsigned char line,unsigned char column,char *str,ts_mode_t mode) 
{
	int i = 0;
	int posx = offsetx + column*FONT_WIDTH;
	int posy = offsety + line*FONT_HEIGHT;

	while(str[i])
	{
		TSLCDCharDisp(str[i],posx,posy,mode);
		posx += FONT_WIDTH;
		i++;
	}
}

void TSLCDPrintTxt(unsigned char line,unsigned char column,const char *txt,ts_mode_t mode)
{
	// Print text from code memory
	int i = 0;
	int posx = offsetx + column*FONT_WIDTH;
	int posy = offsety + line*FONT_HEIGHT;

	while(pgm_read_byte(&txt[i]))
	{
		TSLCDCharDisp(pgm_read_byte(&txt[i]),posx,posy,mode);
		posx += FONT_WIDTH;
		i++;
	}
}

void TSLCDPrintCh(unsigned char line,unsigned char column,char c,ts_mode_t mode) //print a character on LCD
{
	int posx = offsetx + column*FONT_WIDTH;
	int posy = offsety + line*FONT_HEIGHT;

	TSLCDCharDisp(c,posx,posy,mode);
}





