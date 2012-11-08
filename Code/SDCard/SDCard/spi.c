#include <avr/io.h> 
#include <util/delay.h>
#include "integer.h"

void dly_100us(void)
{
	_delay_us(100.0);
}

void init_spi (void) 
{
   // Configure for: PB4 - /SS
   //                PB5 - MOSI
   //                PB6 - MISO
   //                PB7 - SCK

   PORTB = 0b00010000;      // SS high 
   DDRB =  0b10110000;      // !SS,SCK and MOSI outputs 

   /* Set MOSI and SCK output, all others input */ 
   //DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK); 
   /* Enable SPI, Master, set clock rate fck/16 */ 
   SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

}


//----------------------------------------------------------------------- 
// Transmit a byte to MMC via SPI  (Platform dependent)                   
//----------------------------------------------------------------------- 

BYTE xmit_spi(BYTE c) { 
   SPDR = c; 
   while (!(SPSR & (1<<SPIF))); 
   return SPDR; 
} 

//----------------------------------------------------------------------- 
// Receive a byte from MMC via SPI  (Platform dependent)                  
//----------------------------------------------------------------------- 

BYTE rcv_spi(void) { 
   return xmit_spi(0xFF); 
} 

