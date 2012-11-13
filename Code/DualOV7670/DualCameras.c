/*
 * DualCameras.c
 *
 * Created: 10/11/2012 15:20:03
 *  Author: hl13g10
 */ 

#include "DualCameras.h"
#include "SCCB.h"
const char default_settings[SETTINGS_LENGTH][2]=
{
{OV_TSLB, 0x04},
{OV_COM15, 0xd0},//RGB565 / RGB555
{OV_COM7, 0x14},
{OV_HREF, 0x80},
{OV_HSTART, 0x16},
{OV_HSTOP, 0x04},
{OV_VSTRT, 0x02},
{OV_VSTOP, 0x7b},//0x7a,
{OV_VREF, 0x06},//0x0a,
{OV_COM3, 0x00},
{OV_COM14, 0x00},//
{OV_SCALING_XSC, 0x00},
{OV_SCALING_YSC, 0x00},
{OV_SCALING_DCWCTR, 0x11},
{OV_SCALING_PCLK_DIV, 0x00},//
{0xa2, 0x02},
{OV_CLKRC, 0x01},
{OV_GAM1, 0x20},
{OV_GAM2, 0x1c},
{OV_GAM3, 0x28},
{OV_GAM4, 0x3c},
{OV_GAM5, 0x55},
{OV_GAM6, 0x68},
{OV_GAM7, 0x76},
{OV_GAM8, 0x80},
{OV_GAM9, 0x88},
{OV_GAM10, 0x8f},
{OV_GAM11, 0x96},
{OV_GAM12, 0xa3},
{OV_GAM13, 0xaf},
{OV_GAM14, 0xc4},
{OV_GAM15, 0xd7},
{OV_GAM16, 0xe8},
{OV_COM8, 0xe0},
{OV_GAIN, 0x00},//AGC
{OV_AECH, 0x00},
{OV_COM4, 0x00},
{OV_COM9, 0x20},//0x38, limit the max gain
{OV_HIST6, 0x05},
{OV_HIST12, 0x07},
{OV_AEW, 0x75},
{OV_AEB, 0x63},
{OV_VPT, 0xA5},
{OV_HIST0, 0x78},
{OV_HIST1, 0x68},
{OV_HIST2, 0x03},//0x0b,
{OV_HIST7, 0xdf},//0xd8,
{OV_HIST8, 0xdf},//0xd8,
{OV_HIST9, 0xf0},
{OV_HIST10, 0x90},
{OV_HIST11, 0x94},
{OV_COM8, 0xe5},
{OV_COM5, 0x61},
{OV_COM6, 0x4b},
{0x16, 0x02},
{OV_MVFP, 0x27},//0x37,
{0x21, 0x02},
{0x22, 0x91},
{0x29, 0x07},
{0x33, 0x0b},
{0x35, 0x0b},
{0x37, 0x1d},
{0x38, 0x71},
{OV_OFON, 0x2a},//
{OV_COM12, 0x78},
{0x4d, 0x40},
{0x4e, 0x20},
{OV_GFIX, 0x0c},///////////////////////
{OV_DBLV, 0x60},//PLL
{OV_REG74, 0x19},
{0x8d, 0x4f},
{0x8e, 0x00},
{0x8f, 0x00},
{0x90, 0x00},
{0x91, 0x00},
{OV_DM_LNL, 0x00},//0x19,//0x66
{0x96, 0x00},
{0x9a, 0x80},
{0xb0, 0x84},
{0xb1, 0x0c},
{0xb2, 0x0e},
{OV_THL_ST, 0x82},
{0xb8, 0x0a},
{OV_AWBC1, 0x14},
{OV_AWBC2, 0xf0},
{OV_AWBC3, 0x34},
{OV_AWBC4, 0x58},
{OV_AWBC5, 0x28},
{OV_AWBC6, 0x3a},
{0x59, 0x88},
{0x5a, 0x88},
{0x5b, 0x44},
{0x5c, 0x67},
{0x5d, 0x49},
{0x5e, 0x0e},
{OV_LCC3, 0x04},
{OV_LCC4, 0x20},
{OV_LCC5, 0x05},
{OV_LCC6, 0x04},
{OV_LCC7, 0x08},
{OV_AWBCTR3, 0x0a},
{OV_AWBCTR2, 0x55},
{OV_AWBCTR1, 0x11},
{OV_AWBCTR0, 0x9f},//0x9e for advance AWB
{OV_GGAIN, 0x40},
{OV_BLUE, 0x40},
{OV_RED, 0x40},
{OV_COM8, 0xe7},
{OV_COM10, 0x02},//VSYNC negative
{OV_MTX1, 0x80},
{OV_MTX2, 0x80},
{OV_MTX3, 0x00},
{OV_MTX4, 0x22},
{OV_MTX5, 0x5e},
{OV_MTX6, 0x80},
{OV_MTXS, 0x9e},
{OV_COM16, 0x08},
{OV_EDGE, 0x00},
{OV_REG75, 0x05},
{OV_REG76, 0xe1},
{OV_DNSTH, 0x00},
{OV_REG77, 0x01},
{OV_COM13, 0xc2},	//0xc0,
{OV_REG4B, 0x09},
{OV_SATCTR, 0x60},
{OV_COM16, 0x38},
{OV_CONTRAS, 0x40},
{0x34, 0x11},
{OV_COM11, 0x02},//0x00,//0x02,
{OV_HIST5, 0x89},//0x88,
{0x96, 0x00},
{0x97, 0x30},
{0x98, 0x20},
{0x99, 0x30},
{0x9a, 0x84},
{0x9b, 0x29},
{0x9c, 0x03},
{OV_BD50ST, 0x4c},
{OV_BD60ST, 0x3f},
{0x78, 0x04},
{0x79, 0x01},//Some weird thing with reserved registers.
{0xc8, 0xf0},
{0x79, 0x0f},
{0xc8, 0x00},
{0x79, 0x10},
{0xc8, 0x7e},
{0x79, 0x0a},
{0xc8, 0x80},
{0x79, 0x0b},
{0xc8, 0x01},
{0x79, 0x0c},
{0xc8, 0x0f},
{0x79, 0x0d},
{0xc8, 0x20},
{0x79, 0x09},
{0xc8, 0x80},
{0x79, 0x02},
{0xc8, 0xc0},
{0x79, 0x03},
{0xc8, 0x40},
{0x79, 0x05},
{0xc8, 0x30},
{0x79, 0x26},
{OV_COM2, 0x03},
{OV_BRIGHT, 0x00},
{OV_CONTRAS, 0x40},
{OV_COM11, 0x42},//0x82,//0xc0,//0xc2,	//night mode
	
};



//ISR for controlling WEN.
ISR(INT0_vect)
{
	//printf("ISR INT0 Entered\n");
	if (VSYNC_0_Count==1)//start a frame read
	{
		FIFO_WEN_0_SET;
		VSYNC_0_Count++;
	}
	else if (VSYNC_0_Count==2)//end a frame read
	{
		FIFO_WEN_0_CLR;
		VSYNC_0_Count++;
	}
	else if(VSYNC_0_Count == 3)
	{
		FIFO_WEN_0_CLR;
	}
	else
	{
		FIFO_WEN_0_CLR
		VSYNC_0_Count = 0;//wait for a read to be started
	}
}
//ISR for controlling WEN.
ISR(INT1_vect)
{
	//printf("ISR INT1 Entered\n");
	if (VSYNC_1_Count==1)//start a frame read
	{
		FIFO_WEN_1_SET;
		VSYNC_1_Count++;
	}
	else if (VSYNC_1_Count==2)//end a frame read
	{
		FIFO_WEN_1_CLR;
		VSYNC_1_Count++;
	}
	else if(VSYNC_1_Count == 3)
	{
		FIFO_WEN_1_CLR;
	}
	else
	{
		FIFO_WEN_1_CLR
		VSYNC_1_Count = 0;//wait for a read to be started
	}
}

//Write Register Method
unsigned char wrOV7670Reg(unsigned char regID, unsigned char regDat)
{
	/*	I2C Traffic Generated:
	 *	S | OV_7670 + W | A | RegID | A | Data | A | P |
	 */
	//I2C Interface
	unsigned char messageBuf[TWI_BUFFER_SIZE];
	messageBuf[0] = (OV7670_ADDR  <<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consit of General Call code or the TWI slave address.
	messageBuf[1] = regID;             // The first byte is used for commands.
	messageBuf[2] = regDat;                        // The second byte is used for the data.
	TWI_Start_Transceiver_With_Data( messageBuf, 3 );
	
	while(TWI_Transceiver_Busy()) ; //Wait for transceiver to clear
	
	return TWI_statusReg.lastTransOK;
}

//Read Register Method
unsigned char rdOV7670Reg(unsigned char regID, unsigned char *regDat)
{
	/*	I2C Traffic Generated:
	 *	S	|	OV_ADDR + W	| A | RegID | A | P |
	 *	S	|	OV_ADDR + R | A | Data	|~A | P |
	 */
	//I2C Interface
	unsigned char messageBuf[TWI_BUFFER_SIZE]; //Initialise a buffer
	messageBuf[0] = (OV7670_ADDR<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
	messageBuf[1] = regID;             // The first byte is used for Address Pointer.
	TWI_Start_Transceiver_With_Data( messageBuf, 2 );
	
	// Request/collect the data from the Slave
	messageBuf[0] = (OV7670_ADDR<<TWI_ADR_BITS) | (TRUE<<TWI_READ_BIT); // The first byte must always consist of General Call code or the TWI slave address.
	TWI_Start_Transceiver_With_Data( messageBuf, 2 );              
    
	// Get the received data from the transceiver buffer
	TWI_Get_Data_From_Transceiver( messageBuf, 2 );
	*regDat = messageBuf[1];       
	return TWI_statusReg.lastTransOK;
}


unsigned char OV7670_init()
{
	uint8_t i = 0;
	if(0==wrOV7670Reg(OV_COM7, 0x80)) //Reset Camera
	{
		return 1;
	}
	_delay_ms(10);
	for(i=0; i<SETTINGS_LENGTH; i++)
	{
		if( 0==wrOV7670Reg(default_settings[i][0], default_settings[i][1] ))
		{
			return 1;
		}
		_delay_ms(1);
	}
	
	return 0;
}

void FIFO_init( void )
{

	//disable both outputs
	FIFO_nOE_0_SET;
	FIFO_nOE_1_SET;
	//Reset Buffer 0
	FIFO_WRST_0_CLR;
	FIFO_RCLK_0_CLR;
	//FIFO_nOE_0_CLR;

	FIFO_nRRST_0_SET;
	FIFO_WEN_0_CLR;
	_delay_us(10);
	FIFO_RCLK_0_SET;
	_delay_us(10);
	FIFO_RCLK_0_CLR;
	FIFO_nRRST_0_CLR;
	_delay_us(10);
	FIFO_RCLK_0_SET;
	_delay_us(10);
	FIFO_RCLK_0_CLR;
	FIFO_nRRST_0_SET;
	_delay_us(10);
	FIFO_WRST_0_SET;
	
	//Reset Buffer 1
	FIFO_WRST_1_CLR;
	FIFO_RCLK_1_CLR;

	//FIFO_nOE_1_CLR;

	FIFO_nRRST_1_SET;
	FIFO_WEN_1_CLR;
	_delay_us(10);
	FIFO_RCLK_1_SET;
	_delay_us(10);
	FIFO_RCLK_1_CLR;
	FIFO_nRRST_1_CLR;
	_delay_us(10);
	FIFO_RCLK_1_SET;
	_delay_us(10);
	FIFO_RCLK_1_CLR;
	FIFO_nRRST_1_SET;
	_delay_us(10);
	FIFO_WRST_1_SET;

}

//Write one pixel in AVR
uint16_t FIFO_TO_AVR(uint8_t ID)
{
	uint16_t data = 0;
	
	DDRA = 0;
	if(ID == 1)
	{
		FIFO_RCLK_1_SET;
		data = PINA;
		FIFO_RCLK_1_CLR;
		data <<= 8;
		FIFO_RCLK_1_SET;
		data |= PINA;
		FIFO_RCLK_1_CLR;
	}		
	else
	{	
		FIFO_RCLK_0_SET;
		data = PINA;
		FIFO_RCLK_0_CLR;
		data <<= 8;
		FIFO_RCLK_0_SET;
		data |= PINA;
		FIFO_RCLK_0_CLR;
	}		
	return(data);
}


//Resets both pointers
void FIFO_Reset(uint8_t CameraID)
{

	FIFO_nOE_0_SET;	
	FIFO_nOE_1_SET;

	if(CameraID == 0)
	{
		FIFO_WRST_0_CLR;
		FIFO_nRRST_0_CLR;
		FIFO_RCLK_0_SET;
		FIFO_RCLK_0_CLR;
		FIFO_nRRST_0_SET;
		FIFO_WRST_0_SET;
	}
	else
	{
		FIFO_WRST_1_CLR;
		FIFO_nRRST_1_CLR;
		FIFO_RCLK_1_SET;
		FIFO_RCLK_1_CLR;
		FIFO_nRRST_1_SET;
		FIFO_WRST_1_SET;
	}
	
}
void LoadImagesToBuffer()
{
	VSYNC_0_Count = 0;
	VSYNC_1_Count = 0;
	FIFO_Reset(0);
	FIFO_Reset(1);
	VSYNC_0_Count = 1;
	VSYNC_1_Count = 1;
	
}
uint8_t GetImageIfAvailiable(FIL *File, uint8_t CameraID)
{

	if(	((CameraID == 0) && (VSYNC_0_Count == 3)) || 
		((CameraID == 1) && (VSYNC_1_Count == 3)) )
	{
		
		//Write Bitmap Headers
		WriteBMPHeader(File);
		WriteDIBHeader(File);
		if (CameraID == 0)
		{
			//Enable output of Camera 0
			FIFO_nOE_0_CLR;
			//Reset Read Pointer
			FIFO_nRRST_0_CLR;
			FIFO_RCLK_0_SET;
			FIFO_RCLK_0_CLR;
			FIFO_nRRST_0_SET;
		}		
		else 
		{
			//Enable output of Camera 0
			FIFO_nOE_1_CLR;
			//Reset Read Pointer
			FIFO_nRRST_1_CLR;
			FIFO_RCLK_1_SET;
			FIFO_RCLK_1_CLR;
			FIFO_nRRST_1_SET;
		}
		int i, j;
		uint32_t pointer;
		uint16_t Temp;
		uint32_t p;
		FRESULT fr;
		//for(j = HEIGHT; j>0; j--)
		for(j = 0; j < HEIGHT; j++)
		{
			pointer = 0;
			for(i = 0; i < WIDTH; i++)
			{
				Temp = FIFO_TO_AVR(CameraID);
				//USART0_Senduint16(Temp);

				
				Buff[pointer++] = (uint8_t)(Temp >> 8);

				Buff[pointer++] = (uint8_t)Temp;
			}
			pointer = (uint32_t)j * (uint32_t)WIDTH * 2 + BMPHEADERSIZE + DIBHEADERSIZE;
			f_lseek(File, pointer);
			fr = f_write(File, Buff, WIDTH * 2, &p);
			if(fr != FR_OK)
			{

				//printf("Write Fail.\n");

				VSYNC_0_Count = 0;
				VSYNC_1_Count = 0;
				FIFO_Reset(CameraID);
				FIFO_nOE_0_SET;
				FIFO_nOE_1_SET;
				return 1;
			}
		}
		FIFO_Reset(CameraID);

		//fr = f_close(File);

		FIFO_nOE_0_SET;
		FIFO_nOE_1_SET;
		return 0;
	}
	else
	{
		return 2;
	}
}

unsigned char SCCB_wrOV7670Reg(unsigned char regID, unsigned char regDat)
{
	startSCCB();
	if(0==SCCBwriteByte(0x42))
	{
		stopSCCB();
		return(0);
	}
	_delay_us(100);
	if(0==SCCBwriteByte(regID))
	{
		stopSCCB();
		return(0);
	}
	_delay_us(100);
	if(0==SCCBwriteByte(regDat))
	{
		stopSCCB();
		return(0);
	}
	stopSCCB();
	
	return(1);
}

//Read the OV7670 Registers

unsigned char SCCB_rdOV7670Reg(unsigned regID, unsigned char *regDat)
{
	//Using write operate to set the Register Address
	startSCCB();
	if(0==SCCBwriteByte(0x42))
	{
		stopSCCB();
		return(0);
	}
	_delay_us(100);
	if(0==SCCBwriteByte(regID))
	{
		stopSCCB();
		return(0);
	}
	stopSCCB();
	
	_delay_us(100);
	
	//Begin to read
	startSCCB();
	if(0==SCCBwriteByte(0x43))
	{
		stopSCCB();
		return(0);
	}
	_delay_us(100);
	*regDat=SCCBreadByte();
	noAck();
	stopSCCB();
	return(1);
}




// Initial OV7670
unsigned char OV7670_SCCB_init(void)
{
	unsigned char temp;
	
	unsigned int i=0;

	
	InitSCCB();

	temp=0x80;
	if(0==SCCB_wrOV7670Reg(0x12, temp)) //Reset SCCB
	{
		return 1 ;
	}
	_delay_ms(10);

	for(i=0;i<SETTINGS_LENGTH;i++)
	{
		if( 0==SCCB_wrOV7670Reg(default_settings[i][0],default_settings[i][1] ))
		{
			return 2;
		}
	}

	return 0; //ok

	
}