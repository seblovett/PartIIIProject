
#include "SCCB.h"
//#include "delay.h"

/*
-----------------------------------------------
Function: Initial the SCCB port in AVR
-----------------------------------------------
*/
void InitSCCB(void)
{
	SCCB_DDR|=(1<<SCCB_SIO_C)|(1<<SCCB_SIO_D);  //|(1<<FIFO_WEN)|(1<<FIFO_nRRST)|(1<<FIFO_RCLK);
	SCCB_PORT|=(1<<SCCB_SIO_C)|(1<<SCCB_SIO_D);
}
/*
-----------------------------------------------
Function: Generate the start phase for SCCB following the datasheet
-----------------------------------------------
*/
void startSCCB(void)
{
	SIO_D_SET;     
    delay_us(100);

    SIO_C_SET;
    delay_us(100);
 
    SIO_D_CLR;
    delay_us(100);

    SIO_C_CLR;
    delay_us(100);


}
/*
-----------------------------------------------
Function: Generate the stop phase of SCCB following the datasheet
-----------------------------------------------
*/
void stopSCCB(void)
{
	SIO_D_CLR;
    delay_us(100);
 
    SIO_C_SET;
    delay_us(100);
  

    SIO_D_SET;
    delay_us(100);
 //   SCCB_DDR&= ~(SCCB_SIO_D);

}

/*
-----------------------------------------------
Function: noACK
-----------------------------------------------
*/
void noAck(void)
{
	
	SIO_D_SET;
	delay_us(100);
	
	SIO_C_SET;
	delay_us(100);
	
	SIO_C_CLR;
	delay_us(100);
	
	SIO_D_CLR;
	delay_us(100);

}

/*
-----------------------------------------------
Function: Write one Byte data through SCCB
-----------------------------------------------
*/
uchar SCCBwriteByte(uchar m_data)
{
	unsigned char j,tem;

	for(j=0;j<8;j++)
	{
		if((m_data<<j)&0x80)
		{
			SIO_D_SET;
		}
		else
		{
			SIO_D_CLR;
		}
		delay_us(100);
		SIO_C_SET;
		delay_us(100);
		SIO_C_CLR;
		delay_us(100);

	}
	delay_us(100);
	
	SIO_D_IN;	//Set SDA as input
	delay_us(100);
	SIO_C_SET;
	delay_us(1000);
	if(SIO_D_STATE)
	{
		tem=0;   //SDA=1 send fail, return 0
	}
	else
	{
		tem=1;   //SDA=0 send succeed, reture 1
	}
	SIO_C_CLR;
	delay_us(100);	
    SIO_D_OUT;	//Set SDA as output

	return(tem);  
}

/*
-----------------------------------------------
Function: Read one byte data through SCCB
-----------------------------------------------
*/
uchar SCCBreadByte(void)
{
	unsigned char read,j;
	read=0x00;
	
	SIO_D_IN;/*����SDAΪ����*/
	delay_us(100);
	for(j=8;j>0;j--) //ѭ��8�ν�������
	{		     
		delay_us(100);
		SIO_C_SET;
		delay_us(100);
		read=read<<1;
		if(SIO_D_STATE) 
		{
			read=read+1;
		}
		SIO_C_CLR;
		delay_us(100);
	}	
	return(read);
}
