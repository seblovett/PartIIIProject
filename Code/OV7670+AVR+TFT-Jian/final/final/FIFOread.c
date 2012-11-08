
#define OV7670_SYNC		2
#define FIFO_RCLK		4
#define FIFO_WEN		6
#define FIFO_nRRST		7
#define FIFO_nOE		5

#define FIFO_AVR_DPRT		DDRA
#define FIFO_AVR_PORT		PORTA
#define FIFO_AVR_PINP		PINA


#define FIFO_RCLK_SET		{PORTD|=(1<<FIFO_RCLK);}
#define FIFO_RCLK_CLR		{PORTD&=~(1<<FIFO_RCLK);}
#define FIFO_WEN_SET		{PORTD|=(1<<FIFO_WEN);}
#define FIFO_WEN_CLR		{PORTD&=~(1<<FIFO_WEN);}
#define FIFO_nRRST_SET		{PORTD|=(1<<FIFO_nRRST);}
#define FIFO_nRRST_CLR		{PORTD&=~(1<<FIFO_nRRST);}
//#define FIFO_nOE_SET		{PORTB|=(1<<FIFO_nOE);}
#define FIFO_nOE_CLR		{PORTC&=~(1<<FIFO_nOE);}


//Initial FIFO
uchar FIFO_init(void)
{
	DDRD |=(1<<FIFO_WEN)|(1<<FIFO_nRRST)|(1<<FIFO_RCLK);
	DDRC |=(1<<FIFO_nOE);
	
	FIFO_RCLK_CLR;
	FIFO_nOE_CLR;
	FIFO_nRRST_SET;
	FIFO_WEN_CLR;
	delay_us(10);
	FIFO_RCLK_SET;
	delay_us(10);
	FIFO_RCLK_CLR;
	FIFO_nRRST_CLR;
	delay_us(10);
	FIFO_RCLK_SET;
	delay_us(1);
	FIFO_RCLK_CLR;
	FIFO_nRRST_SET;
	delay_us(10);

	return 0x01; //ok
}	

//Write one pixel in AVR
unsigned short FIFO_TO_AVR(void)
{
	unsigned short data = 0;
	
	FIFO_AVR_DPRT=0;
	
	FIFO_RCLK_SET;
	data = FIFO_AVR_PINP;
	FIFO_RCLK_CLR;

	data <<= 8;
	
	FIFO_RCLK_SET;
	data |= FIFO_AVR_PINP;
	FIFO_RCLK_CLR;
	
//	FIFO_RCLK_SET;
//	FIFO_RCLK_CLR;
//	FIFO_RCLK_SET;
//	FIFO_RCLK_CLR;
	
	return(data);
}	

/*
unsigned short FIFO_TO_AVR(void)
{
	unsigned short data1 = 0;
	unsigned short data2 = 0;
	unsigned short data3 = 0;
	
	FIFO_AVR_DPRT=0;
	
	FIFO_RCLK_SET;
	data1 = FIFO_AVR_PINP;
	FIFO_RCLK_CLR;

	data3 |= (0x0700 & (data1<<8));
	data3 |= data1>>3;
//	data <<= 8;
	
	FIFO_RCLK_SET;
	data2 |= FIFO_AVR_PINP;
	FIFO_RCLK_CLR;
	data3 |= (0x00E0 & data2);
	data3 |= (data2<<11);
	
//	FIFO_RCLK_SET;
//	FIFO_RCLK_CLR;
//	FIFO_RCLK_SET;
//	FIFO_RCLK_CLR;
	
	return(data3);
}	*/