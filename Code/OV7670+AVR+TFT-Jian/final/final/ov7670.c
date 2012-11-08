
#include "ov7670.h"
//#include "delay.h"
#include "ov7670config.c"

//#define delay_ms(num1) _delay_ms(num1)
//#define delay_us(num2) _delay_us(num2)
//#define F_CPU 12000000UL




//Write the OV7670 Registers

uchar wrOV7670Reg(uchar regID, uchar regDat)
{
	startSCCB();
	if(0==SCCBwriteByte(0x42))
	{
		stopSCCB();
		return(0);
	}
	delay_us(100);
  	if(0==SCCBwriteByte(regID))
	{
		stopSCCB();
		return(0);
	}
	delay_us(100);
  	if(0==SCCBwriteByte(regDat))
	{
		stopSCCB();
		return(0);
	}
  	stopSCCB();
	
  	return(1);
}

//Read the OV7670 Registers

uchar rdOV7670Reg(uchar regID, uchar *regDat)
{
	//Using write operate to set the Register Address
	startSCCB();
	if(0==SCCBwriteByte(0x42))
	{
		stopSCCB();
		return(0);
	}
	delay_us(100);
  	if(0==SCCBwriteByte(regID))
	{
		stopSCCB();
		return(0);
	}
	stopSCCB();
	
	delay_us(100);
	
	//Begin to read
	startSCCB();
	if(0==SCCBwriteByte(0x43))
	{
		stopSCCB();
		return(0);
	}
	delay_us(100);
  	*regDat=SCCBreadByte();
  	noAck();
  	stopSCCB();
  	return(1);
}




// Initial OV7670
uchar OV7670_init(void)
{
	uchar temp;
	
	uint i=0;

	
	InitSCCB();

	temp=0x80;
	if(0==wrOV7670Reg(0x12, temp)) //Reset SCCB
	{
		return 0 ;
	}
	delay_ms(10);

	for(i=0;i<CHANGE_REG_NUM;i++)
	{
		if( 0==wrOV7670Reg(pgm_read_byte( &change_reg[i][0]),pgm_read_byte( &change_reg[i][1]) ))
		{ 
			return 0;
		}
	}

	return 0x01; //ok

	
} 

