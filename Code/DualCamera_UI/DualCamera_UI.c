/*
 * DualCamera_UI.c
 *
 * Created: 12/11/2012 08:32:27
 *  Author: hslovett
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "TWI_slave.h"


#define TWI_CMD_MASTER_WRITE 0x10
#define TWI_CMD_MASTER_READ  0x20

int main(void)
{
	unsigned char TWI_slaveAddress;
	unsigned char messageBuff[TWI_BUFFER_SIZE];
	DDRD = 0xFF;// Port D is the LED output
	DDRC = 0x00; //PortC is the switch input
	TWI_slaveAddress = 0x15;
	TWI_Slave_Initialise( (unsigned char)((TWI_slaveAddress<<TWI_ADR_BITS) | (TRUE<<TWI_GEN_BIT) )); 
	sei();
	TWI_Start_Transceiver();
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
			        TWI_Get_Data_From_Transceiver(messageBuff, 2);
			        // Check if the last operation was a reception as General Call
			        if ( TWI_statusReg.genAddressCall )
			        {
				        //Not responding to general call
			        }
			        else // Ends up here if the last operation was a reception as Slave Address Match
			        {
				        // Example of how to interpret a command and respond.
				        
				        // TWI_CMD_MASTER_WRITE stores the data to PORTB
				        if (messageBuff[0] == TWI_CMD_MASTER_WRITE)
				        {
					        PORTD = messageBuff[1];
				        }
				        // TWI_CMD_MASTER_READ prepares the data from PINB in the transceiver buffer for the TWI master to fetch.
				        if (messageBuff[0] == TWI_CMD_MASTER_READ)
				        {
					        messageBuff[0] = PINC;
					        TWI_Start_Transceiver_With_Data( messageBuff, 1 );
				        }
			        }
		        }
		        else // Ends up here if the last operation was a transmission
		        {
			        
		        }
		        // Check if the TWI Transceiver has already been started.
		        // If not then restart it to prepare it for new receptions.
		        if ( ! TWI_Transceiver_Busy() )
		        {
			        TWI_Start_Transceiver();
		        }
	        }
        }
    }
}