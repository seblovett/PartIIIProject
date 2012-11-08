//#define TFT_VSYNC 0
//#define TFT_HSYNC 1
#define TFT_ENABLE 5

//#define TFT_VSYNC_SET		{PORTC|=(1<<TFT_VSYNC);}
//#define TFT_VSYNC_CLR		{PORTC&=~(1<<TFT_VSYNC);}
//#define TFT_HSYNC_SET		{PORTC|=(1<<TFT_HSYNC);}
//#define TFT_HSYNC_CLR		{PORTC&=~(1<<TFT_HSYNC);}
#define TFT_ENABLE_SET		{PORTD|=(1<<TFT_ENABLE);}
#define TFT_ENABLE_CLR		{PORTD&=~(1<<TFT_ENABLE);}
	
uchar TFT_data_init(void)
{
//	DDRC |=(1<<TFT_VSYNC)|(1<<TFT_HSYNC)|(1<<TFT_ENABLE);
	DDRD |=(1<<TFT_ENABLE);
//	TFT_VSYNC_CLR;
//	TFT_HSYNC_SET;
	TFT_ENABLE_SET;
	return 0x01; //ok
}