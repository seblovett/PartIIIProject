/*
 * PCA9542A.c
 *
 * Created: 13/11/2012 23:24:40
 *  Author: hslovett
 */ 
#include "PCA9542A.h"


unsigned char PCA9542A_Init()
{
	unsigned char messageBuf[TWI_BUFFER_SIZE];
	messageBuf[0] = (PCA9542A_ADDR  <<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consit of General Call code or the TWI slave address.
	messageBuf[1] = NO_SELECT;             // The first byte is used for commands.
	// The second byte is used for the data.
	TWI_Start_Transceiver_With_Data( messageBuf, 2 );
	
	while(TWI_Transceiver_Busy()) ; //Wait for transceiver to clear
	
	return TWI_statusReg.lastTransOK;
}

unsigned char PCA9542A_SetChannel( uint8_t Channel )
{
	unsigned char messageBuf[TWI_BUFFER_SIZE];
	messageBuf[0] = (PCA9542A_ADDR  <<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consit of General Call code or the TWI slave address.
	messageBuf[1] = Channel;             // The first byte is used for commands.
		                    // The second byte is used for the data.
	TWI_Start_Transceiver_With_Data( messageBuf, 2 );
		
	while(TWI_Transceiver_Busy()) ; //Wait for transceiver to clear
		
	return TWI_statusReg.lastTransOK;
}

unsigned char PCA9542A_ReadChannel()
{
	unsigned char messageBuf[TWI_BUFFER_SIZE];
	messageBuf[0] = (PCA9542A_ADDR  <<TWI_ADR_BITS) | (TRUE<<TWI_READ_BIT); // The first byte must always consit of General Call code or the TWI slave address.

	TWI_Start_Transceiver_With_Data( messageBuf, 1 );
	
	while(TWI_Transceiver_Busy()) ; //Wait for transceiver to clear
	// Get the received data from the transceiver buffer
	TWI_Get_Data_From_Transceiver( messageBuf, 2 );
	return TWI_statusReg.lastTransOK;
}