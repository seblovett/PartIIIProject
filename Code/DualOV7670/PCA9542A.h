/*
 * PCA9542A.h
 *
 * Created: 13/11/2012 23:24:48
 *  Author: hslovett
 */ 


#ifndef PCA9542A_H_
#define PCA9542A_H_
#include "Config.h"

#define A0	0
#define A1	0
#define A2	1
#define PCA9542A_ADDR (0x70 | (A2 << 2) | (A1 << 1) | A0)

#define NO_SELECT	0x00
#define CH0			0x04
#define CH1			0x05

unsigned char PCA9542A_Init();
unsigned char PCA9542A_SetChannel(uint8_t Channel); 

#endif /* PCA9542A_H_ */