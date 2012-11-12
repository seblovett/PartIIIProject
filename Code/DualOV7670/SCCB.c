
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
    _delay_us(100);

    SIO_C_SET;
    _delay_us(100);
 
    SIO_D_CLR;
    _delay_us(100);

    SIO_C_CLR;
    _delay_us(100);


}
/*
-----------------------------------------------
Function: Generate the stop phase of SCCB following the datasheet
-----------------------------------------------
*/
void stopSCCB(void)
{
	SIO_D_CLR;
    _delay_us(100);
 
    SIO_C_SET;
    _delay_us(100);
  

    SIO_D_SET;
    _delay_us(100);
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
	_delay_us(100);
	
	SIO_C_SET;
	_delay_us(100);
	
	SIO_C_CLR;
	_delay_us(100);
	
	SIO_D_CLR;
	_delay_us(100);

}

/*
-----------------------------------------------
Function: Write one Byte data through SCCB
-----------------------------------------------
*/
unsigned char SCCBwriteByte(unsigned char m_data)
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
		_delay_us(100);
		SIO_C_SET;
		_delay_us(100);
		SIO_C_CLR;
		_delay_us(100);

	}
	_delay_us(100);
	
	SIO_D_IN;	//Set SDA as input
	_delay_us(100);
	SIO_C_SET;
	_delay_us(1000);
	if(SIO_D_STATE)
	{
		tem=0;   //SDA=1 send fail, return 0
	}
	else
	{
		tem=1;   //SDA=0 send succeed, reture 1
	}
	SIO_C_CLR;
	_delay_us(100);	
    SIO_D_OUT;	//Set SDA as output

	return(tem);  
}

/*
-----------------------------------------------
Function: Read one byte data through SCCB
-----------------------------------------------
*/
unsigned char SCCBreadByte(void)
{
	unsigned char read,j;
	read=0x00;
	
	SIO_D_IN;/*设置SDA为输入*/
	_delay_us(100);
	for(j=8;j>0;j--) //循环8次接收数据
	{		     
		_delay_us(100);
		SIO_C_SET;
		_delay_us(100);
		read=read<<1;
		if(SIO_D_STATE) 
		{
			read=read+1;
		}
		SIO_C_CLR;
		_delay_us(100);
	}	
	return(read);
}
