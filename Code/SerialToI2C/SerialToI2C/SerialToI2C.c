/*
 * SerialToI2C.c
 *
 * Created: 04/11/2012 21:58:28
 *  Author: hslovett
 */ 

#define TWI_SLAVE_ADDR 0x2A
// Sample TWI transmission commands
#define TWI_CMD_MASTER_WRITE	0x10
#define TWI_CMD_MASTER_READ		0x20
#define TWI_Read_Image_Line		0x30
#define F_CPU 12000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "TWI_slave.h"
int main(void)
{
	uint8_t Temp;
	TWI_Slave_Initialise(TWI_SLAVE_ADDR);
	sei();
	TWI_Start_Transceiver();
	
	DDRB = 0xFF;

    while(1)
    {

         // Check if the TWI Transceiver has completed an operation.
         if ( ! TWI_Transceiver_Busy() )
         {
	         // Check if the last operation was successful
	         if ( TWI_statusReg.lastTransOK )
	         {
		         // Check if the last operation was a reception
		         if ( TWI_statusReg.RxDataInBuf )
		         {
			         TWI_Get_Data_From_Transceiver(TWI_buf, 2);
			         // Check if the last operation was a reception as General Call
			         if ( TWI_statusReg.genAddressCall )
			         {
				         // Put data received out to PORTB as an example.
				         PORTB = TWI_buf[0];
			         }
			         else // Ends up here if the last operation was a reception as Slave Address Match
			         {
				         // Example of how to interpret a command and respond.
				         
				         // TWI_CMD_MASTER_WRITE stores the data to PORTB
				         if (TWI_buf[0] == TWI_CMD_MASTER_WRITE)
				         {
					         PORTB = TWI_buf[1];
				         }
				         // TWI_CMD_MASTER_READ prepares the data from PINB in the transceiver buffer for the TWI master to fetch.
				         if (TWI_buf[0] == TWI_CMD_MASTER_READ)
				         {
					         TWI_buf[0] = 0x1F;
					         TWI_Start_Transceiver_With_Data( TWI_buf, 1 );
				         }
						 
						 if(TWI_buf[0] == TWI_Read_Image_Line)
						 {
							Temp = TWI_buf[1];
							for(int i = 0; i < Temp; /*Intentionally left blank*/) 
							{
								
								TWI_buf[i++] = 0x00;
								TWI_buf[i++] = 0xF8;
							}
							TWI_Start_Transceiver_With_Data( TWI_buf, Temp );								
						 }							 
			         }
		         }
		         else // Ends up here if the last operation was a transmission
		         {
			          // Put own code here.
		         }
		         // Check if the TWI Transceiver has already been started.
		         // If not then restart it to prepare it for new receptions.
		         if ( ! TWI_Transceiver_Busy() )
		         {
			         TWI_Start_Transceiver();
		         }
	         }
	         else // Ends up here if the last operation completed unsuccessfully
	         {
		         
	         }
		} 
    }
}