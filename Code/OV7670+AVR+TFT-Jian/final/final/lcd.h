//  Author : Steve Gunn
//
//    Date : 30/01/2010
//
// Licence : This code was modified from the example code at www.thaieasyelec.net. 
//           This work is licensed under the Creative Commons Attribution License. 
//           To view a copy of this license, visit http://creativecommons.org/about/licenses/.

#ifndef _LCD_H_
#define _LCD_H_

// Display Driver is D51E5TA7601

// -------------------------------------
// Display Control System
// -------------------------------------
#define LCD_START_OSCILLATOR		0x00 
#define LCD_DRIVER_OUTPUT_CTRL		0x01
#define LCD_DRIVING_WAVEFORM_CTRL	0x02
#define LCD_ENTRY_MODE				0x03
#define LCD_DISPLAY_CTRL1			0x04
#define LCD_DISPLAY_CTRL2			0x05
#define LCD_DISPLAY_CTRL3			0x06
#define LCD_DISPLAY_CTRL4			0x07
#define LCD_BLANK_PERIOD_CTRL		0x08
#define LCD_SMLC_IMG_BR_LEVEL		0x09
#define LCD_FRAME_CYCLE_CTRL		0x0A
#define LCD_EXT_DISPLAY_INT_CTRL	0x0B
#define LCD_INTERFACE_CTRL			0x0C
#define LCD_GATE_SCAN_POS_CTRL		0x0D
#define LCD_FRAME_MARKER_POS		0x0E
#define LCD_DISPLAY_CTRL5			0x0F
// -------------------------------------
// Power Control System
// -------------------------------------
#define LCD_POWER_CTRL1				0x10
#define LCD_POWER_CTRL2				0x11
#define LCD_POWER_CTRL3				0x12
#define LCD_POWER_CTRL4				0x13
#define LCD_POWER_CTRL5				0x14
#define LCD_POWER_CTRL6				0x15
#define LCD_POWER_CTRL7				0x16
// -------------------------------------
// RAM Access Control
// -------------------------------------
#define LCD_GRAM_VER_AD				0x20
#define LCD_GRAM_HOR_AD				0x21
#define LCD_RW_GRAM					0x22
// -------------------------------------
// Gamma Control System
// -------------------------------------
#define LCD_GAMMA_CTRL1				0x28
#define LCD_GAMMA_CTRL2				0x29
#define LCD_GAMMA_CTRL3				0x2A
#define LCD_GAMMA_CTRL4				0x2B 
#define LCD_GAMMA_CTRL5				0x2C
#define LCD_GAMMA_CTRL6				0x2D
#define LCD_GAMMA_CTRL7				0x2E
#define LCD_GAMMA_CTRL8				0x2F
#define LCD_GAMMA_CTRL9				0x30
#define LCD_GAMMA_CTRL10			0x31
#define LCD_GAMMA_CTRL11			0x32
#define LCD_GAMMA_CTRL12			0x33
#define LCD_GAMMA_CTRL13			0x34
#define LCD_GAMMA_CTRL14			0x35
#define LCD_GAMMA_CTRL15			0x36
#define LCD_GAMMA_CTRL16			0x37
#define LCD_GAMMA_CTRL17			0x38
#define LCD_GAMMA_CTRL18			0x39
#define LCD_GAMMA_CTRL19			0x3A
#define LCD_GAMMA_CTRL20			0x3B
#define LCD_GAMMA_CTRL21			0x3C
#define LCD_GAMMA_CTRL22			0x3D
// -------------------------------------
// Position Control System
// -------------------------------------
#define LCD_PART_IMG1_START_AD		0x40
#define LCD_PART_IMG1_END_AD		0x41
#define LCD_PART_IMG2_START_AD		0x42
#define LCD_PART_IMG2_END_AD		0x43
#define LCD_HOR_END_AD				0x44
#define LCD_HOR_START_AD			0x45
#define LCD_VER_END_AD				0x46
#define LCD_VER_START_AD			0x47
// -------------------------------------
// SMLC DBV (Backlight Brightness According to the level of image brightness)
// -------------------------------------
#define LCD_SMLC_IMG_BR_LEVEL1		0x48
#define LCD_SMLC_IMG_BR_LEVEL2		0x49
#define LCD_SMLC_IMG_BR_LEVEL3		0x4A
#define LCD_SMLC_IMG_BR_LEVEL4		0x4B
// -------------------------------------
// ETC
// -------------------------------------
#define LCD_OTP_VCOM_CTRL1			0x50
#define LCD_OTP_VCOM_CTRL2			0x51
#define LCD_OTP_VCOM_CTRL3			0x52
#define LCD_OTP_CABC_CTRL			0x67

// -------------------------------------
// LCD orientation portrait 
// Configure for 8 bit interface: 2 x 8 bit transfers
// -------------------------------------
#define TS_SIZE_X					320
#define TS_SIZE_Y					480
#define DAT_VAL_ENTRY_MOD			0x0030
#define LCD_GRAM_ADX				LCD_GRAM_HOR_AD
#define LCD_GRAM_ADY				LCD_GRAM_VER_AD
#define LCD_START_ADX   			LCD_HOR_START_AD
#define LCD_END_ADX   				LCD_HOR_END_AD
#define LCD_START_ADY   			LCD_VER_START_AD
#define LCD_END_ADY   				LCD_VER_END_AD
/*
// -------------------------------------
// Setup basic colours
// -------------------------------------
#define TS_COL_RED					0x001F
#define TS_COL_GREEN				0x07E0
#define TS_COL_BLUE					0xF800
#define TS_COL_YELLOW				0x07FF
#define TS_COL_PURPLE				0xF81F
#define TS_COL_BLACK				0x0000
#define TS_COL_WHITE				0xFFFF
*/
//When RGB = 1

#define TS_COL_RED					0xF800
#define TS_COL_GREEN				0x07E0
#define TS_COL_BLUE					0x001F
#define TS_COL_YELLOW				0xFFE0
#define TS_COL_PURPLE				0xF81F
#define TS_COL_BLACK				0x0000
#define TS_COL_WHITE				0xFFFF

int offsetx;
int offsety;
unsigned short fore_color;
unsigned short back_color;
typedef enum
{
	TS_MODE_NORMAL,
	TS_MODE_INVERSE,
	TS_MODE_FULL,
} ts_mode_t;


void TSLCDReset(void); 
void TSLCDInit(void); 
void TSLCDSetWindow(int sx,int ex,int sy,int ey);

void TSLCDOutInsDat(unsigned short ins, unsigned short dat); 
void TSLCDOutIns(unsigned short ins); 
void TSLCDOutDat(unsigned short dat); 
unsigned short TSLCDInIns(void); 
unsigned short TSLCDInDat(void); 

void TSLCDSetOffset(int x, int y); 
void TSLCDSetForeColor(unsigned short color);
void TSLCDSetBackColor(unsigned short color); 

void TSLCDShowPic(int sx,int ex,int sy,int ey,const unsigned short *pic,ts_mode_t mode);
void TSLCDFillRect(int sx,int ex,int sy,int ey,unsigned short color,ts_mode_t mode); 
void TSLCDFillCirc(int cx,int cy,int rad,unsigned short color, ts_mode_t mode); 

void TSLCDCharDisp(char charactor,int sx,int sy,ts_mode_t mode); 
void TSLCDPrintStr(unsigned char line,unsigned char column,char *str,ts_mode_t mode); 
void TSLCDPrintTxt(unsigned char line,unsigned char column,const char *txt,ts_mode_t mode); 
void TSLCDPrintCh(unsigned char line,unsigned char column,char c,ts_mode_t mode); 

#endif

