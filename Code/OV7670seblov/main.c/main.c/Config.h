/*
 * Config.h
 * This file includes all global declarations, pin out and includes
 * Created: 05/10/2012 21:48:57
 *  Author: hslovett
 */ 

#define Device ATMega644P
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "TWI_Master.h"
#include "UART.h"
#include "ov7670.h"
// #include "ff.h"
// #include "ffconf.h"
// #include "diskio.h"


#ifndef CONFIG_H_
#define CONFIG_H_

//OV7670 Control Lines
#define OV7670_CTRL_PORT PORTD
#define OV7670_CTRL_DDR DDRD
#define OV7670_VSYNC	2	//MUST BE AN INTERRUPT PIN
#define FIFO_WRST		3
#define FIFO_RCLK		4
#define FIFO_nOE		5
#define FIFO_WEN		6
#define FIFO_nRRST		7

//OV7670 Data Lines
#define FIFO_AVR_DPRT		DDRA
#define FIFO_AVR_PORT		PORTA
#define FIFO_AVR_PINP		PINA






//Comms interfaces Uncomment to enable.
#define UART0



//#define NULL 0
#endif /* CONFIG_H_ */