/*
 * DualCamera_UI.c
 *
 * Created: 12/11/2012 08:32:27
 *  Author: hslovett
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "TWI_slave.h"

#define ButtonMask	0x0F

#define TWI_CMD_MASTER_WRITE 0x10
#define TWI_CMD_MASTER_READ  0x20

// When there has been an error, this function is run and takes care of it
unsigned char TWI_Act_On_Failure_In_Last_Transmission ( unsigned char TWIerrorMsg );

int main(void)
{
	
	char ButtonStatus = 0xFF;
	unsigned char TWI_slaveAddress;
	unsigned char messageBuff[TWI_BUFFER_SIZE];
	DDRD = 0xFF;// Port D is the LED output
	DDRC = 0x00; //PortC is the switch input
	//PORTC = 0xFF;
	TWI_slaveAddress = 0x15;
	TWI_Slave_Initialise( (unsigned char)((TWI_slaveAddress<<TWI_ADR_BITS) | (TRUE<<TWI_GEN_BIT) )); 
	sei();
	TWI_Start_Transceiver();
    while(1)
    {
		
		ButtonStatus = (ButtonStatus & PINC) & ButtonMask;
		//PORTD = ButtonStatus;
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
				        // Put data received out to PORTB as an example.
				        PORTB = messageBuff[0];
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
					        messageBuff[0] = ButtonStatus;
					        TWI_Start_Transceiver_With_Data( messageBuff, 1 );
							ButtonStatus = ButtonMask; //clear all logged button presses
				        }
			        }
		        }
		        else // Ends up here if the last operation was a transmission
		        {
			        //__no_operation(); // Put own code here.
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
		        //TWI_Act_On_Failure_In_Last_Transmission( TWI_Get_State_Info() );
	        }
		}			
    }
}

unsigned char TWI_Act_On_Failure_In_Last_Transmission ( unsigned char TWIerrorMsg )
{
	// A failure has occurred, use TWIerrorMsg to determine the nature of the failure
	// and take appropriate actions.
	// Se header file for a list of possible failures messages.
	
	// This very simple example puts the error code on PORTB and restarts the transceiver with
	// all the same data in the transmission buffers.
	//PORTB = TWIerrorMsg;
	TWI_Start_Transceiver();
	
	return TWIerrorMsg;
}