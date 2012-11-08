//  Author : Steve Gunn
//
//    Date : 30/01/2010
//
// Licence : This code was modified from the example code at www.thaieasyelec.net. 
//           This work is licensed under the Creative Commons Attribution License. 
//           To view a copy of this license, visit http://creativecommons.org/about/licenses/.

#ifndef _AVR_H_
#define _AVR_H_

//#define F_CPU			1000000UL
//#define F_CPU_MHZ		1

#include <avr/io.h>
//#include "delay.c"
//#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define Orb(port,bitnum)		port |= _BV(bitnum)
#define Setb(port,bitnum)		port |= _BV(bitnum)
#define Clrb(port,bitnum)		port &= ~(_BV(bitnum))
#define Rdb(pinp,bitnum)		(pinp & _BV(bitnum))

//#define delay_ms(x)		_delay_ms(x)

#define LCD_RST_DPRT	DDRC
#define LCD_RST_PORT	PORTC
#define LCD_RST_PIN		PC0

#define LCD_RS_DPRT		DDRC
#define LCD_RS_PORT		PORTC
#define LCD_RS_PIN		PC1

#define LCD_CS_DPRT		DDRC
#define LCD_CS_PORT		PORTC
#define LCD_CS_PIN		PC2

#define LCD_RD_DPRT		DDRC
#define LCD_RD_PORT		PORTC
#define LCD_RD_PIN		PC3

#define LCD_WR_DPRT		DDRC
#define LCD_WR_PORT		PORTC
#define LCD_WR_PIN		PC4

#define LCD_DB_DPRT		DDRA
#define LCD_DB_PORT		PORTA
#define LCD_DB_PINP		PINA
/*
#define TC_CS_DPRT		DDRD
#define TC_CS_PORT		PORTD
#define TC_CS_PIN		PD4

#define TC_PEN_DPRT		DDRD
#define TC_PEN_PORT		PORTD
#define TC_PEN_PINP		PIND
#define TC_PEN_PIN		PD2

#define MOSI_DPRT		DDRD
#define MOSI_PORT		PORTD
#define MOSI_PIN		PD5

#define SCK_DPRT		DDRD
#define SCK_PORT		PORTD
#define SCK_PIN			PD7
*/
#endif
