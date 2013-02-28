/*
 * PCA9542A.c
 *
 * Created: 15/02/2013 12:21:36
 *  Author: hslovett
 */ 

#include <asf.h>
#include "CustomDevices/CustomDevices.h"
//Camera
/*#include "CustomDevices/OV7670.h"*/
//I2C Mux
/*#include "CustomDevices/PCA9542A.h"*/
//MotorDriver
/*#include "CustomDevices/MotorDriver.h"*/
//SDCard
/*#include "CustomDevices/SD_Card.h"*/

int PCA9542A_Init()
{
	int status = twim_probe(&AVR32_TWIM0, PCA9542A_ADDR);
	if (status != STATUS_OK)
	{
		PCA9542A.Status = DEVICE_NOT_FOUND;
		return DEVICE_NOT_FOUND;
	}		
	char buff[2] = {NO_SELECT, 0};
	status = twim_write(&AVR32_TWIM0, &buff, 1, PCA9542A_ADDR, false);
	PCA9542A.Status = STATUS_OK;
	PCA9542A.ChannelSelected = NO_SELECT;
	return status;
}


void PCA9542A_Chan_Sel(unsigned char Channel)
{
	int status = 0;
	char buff[2] = {Channel, 0};
	status = twim_write(&AVR32_TWIM0, &buff, 1, PCA9542A_ADDR, false);
	if(status == STATUS_OK)
	{
		PCA9542A.ChannelSelected = Channel;
	}
	else
	{
		PCA9542A.Status = ERR_PROTOCOL;
	}
}