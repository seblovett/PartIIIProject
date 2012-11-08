/*
 * PORTAtoSPI.c
 *
 * Created: 06/11/2012 11:07:20
 *  Author: hslovett
 */ 


#include <avr/io.h>

#define SS	PB4
#define SPI_CLK	PB7
#define MOSI	PB5
#define MISO	PB6
void SPI_Init(void)
{
	SPCR = (1<<SPE);
	DDRB = (1 << MISO);//MISO is output, all others are input
}
int main(void)
{
    while(1)
    {
        SPDR = 0x55;
		while(SPSR & (1 << SPIF))
			;//do nothing
    }
}