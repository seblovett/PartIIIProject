/*
 * CustomDevices.h
 *
 * Created: 16/02/2013 14:30:50
 *  Author: hslovett
 */ 


#ifndef CUSTOMDEVICES_H_
#define CUSTOMDEVICES_H_

//Camera
#include "CustomDevices/OV7670.h"
//I2C Mux
#include "CustomDevices/PCA9542A.h"
//MotorDriver
#include "CustomDevices/MotorDriver.h"
//SDCard
#include "CustomDevices/SD_Card.h"
//Image Processing Functions
#include "CustomDevices/ImageProcessor.h"

typedef struct {
	int Status;
	SD_Status_t *SD_Card;
	Motor_Control_t *Motors;
	OV7670_t *Cameras;
	PCA9542A_t *I2CMux;
} Columbus_Status_t;

#define SD_ERR		0x1
#define CAM_ERR		0x2
#define I2CMux_ERR	0x4

#define FFT_SIZE 256

mspace sdram_msp;
Columbus_Status_t Columbus_Status;
//TWI Methods
void twim_init (void);
void System_Test();
#endif /* CUSTOMDEVICES_H_ */