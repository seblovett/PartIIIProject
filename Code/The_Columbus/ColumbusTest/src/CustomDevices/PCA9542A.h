/*
 * PCA9542A.h
 *
 * Created: 15/02/2013 12:21:46
 *  Author: hslovett
 */ 


#ifndef PCA9542A_H_
#define PCA9542A_H_

#define A0	0
#define A1	0
#define A2	1
#define PCA9542A_ADDR (0x70 | (A2 << 2) | (A1 << 1) | A0)

#define NO_SELECT		0x00
#define I2C_CHANNEL_0	0x04
#define I2C_CHANNEL_1	0x05

//Status Codes
#define SUCCESS		0
#define DEVICE_NOT_FOUND	2


int PCA9542A_Init();
//void PCA9542A_Channel_Select(uint8_t Channel);
void PCA9542A_Chan_Sel(unsigned char Channel);
#endif /* PCA9542A_H_ */
