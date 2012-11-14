/*
 * Config.h
 *
 * Created: 25/10/2012 21:58:56
 *  Author: hslovett
 */ 
#define F_CPU 12000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "TWI_Master.h"
#include "ff.h"
#include "diskio.h"
#include "Bitmap.h"
#include "DualCameras.h"
#include "PCA9542A.h"
#ifndef CONFIG_H_
#define CONFIG_H_


void IO_Init(void);

#define TRUE 1
#define FALSE 0

FIL Files[2];
char Buff[1024];

#define BMPFileSize		153738
#define RGBFileSize		153600
//////////////////////////////////////////////////////////////////////////
//	Port A
//////////////////////////////////////////////////////////////////////////
#define FIFO_AVR_DPRT		DDRA
#define FIFO_AVR_PORT		PORTA
#define FIFO_AVR_PINP		PINA
//////////////////////////////////////////////////////////////////////////
//	Port B
//////////////////////////////////////////////////////////////////////////
#define SD_WP			PB0
#define SD_CD			PB1
//#define 				PB2
//#define 				PB3
#define SPI_nSS_SD		PB4
#define SPI_MOSI		PB5
#define SPI_MISO		PB6
#define SPI_SCK			PB7
//////////////////////////////////////////////////////////////////////////
//	Port C
//////////////////////////////////////////////////////////////////////////
#define TWI_SCL			PC0
#define TWI_SDA			PC1
#define FIFO_RCLK_1		PC2
#define FIFO_nRRST_1	PC3
#define FIFO_WEN_1		PC4
#define FIFO_WRST_1		PC5
#define FIFO_nOE_0		PC6
#define FIFO_nOE_1		PC7
//////////////////////////////////////////////////////////////////////////
//	Port D
//////////////////////////////////////////////////////////////////////////
#define USART0_RX		PD0
#define USART0_TX		PD1
#define OV7670_VSYNC_0	PD2	//MUST BE AN INTERRUPT PIN
#define OV7670_VSYNC_1	PD3	//MUST BE AN INTERRUPT PIN
#define FIFO_RCLK_0		PD4
#define FIFO_nRRST_0	PD5
#define FIFO_WEN_0		PD6
#define FIFO_WRST_0		PD7



#endif /* CONFIG_H_ */