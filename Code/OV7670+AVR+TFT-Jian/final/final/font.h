
#ifndef		_FONT_H_ 
#define		_FONT_H_ 

#include <avr/pgmspace.h>

#define FONT_BIT_WIDTH 	8
#define FONT_BYTE_HIGHT 2
#define FONT_SIZE 		FONT_BIT_WIDTH*FONT_BYTE_HIGHT
#define FONT_WIDTH 		FONT_BIT_WIDTH
#define FONT_HEIGHT 	FONT_BYTE_HIGHT*8

extern unsigned char font[];
unsigned char char_buf[FONT_BIT_WIDTH][FONT_BYTE_HIGHT];

void FBufferStore(unsigned char charactor);
unsigned char FBufferRead(unsigned char column,unsigned char row);

#endif



