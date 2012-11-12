
#ifndef _SCCB_H
#define _SCCB_H
#define F_CPU 12000000UL
#include <util/delay.h>
#include <avr/io.h>
//#include "VARIABLE.h"



#define SCCB_DDR		DDRD
#define SCCB_PORT		PORTD
#define SCCB_PIN		PIND

#define SCCB_SIO_C		0
#define SCCB_SIO_D		1

#define SIO_C_SET		{SCCB_PORT|=(1<<SCCB_SIO_C);}
#define SIO_C_CLR		{SCCB_PORT&=~(1<<SCCB_SIO_C);}
#define SIO_D_SET		{SCCB_PORT|=(1<<SCCB_SIO_D);}
#define SIO_D_CLR		{SCCB_PORT&=~(1<<SCCB_SIO_D);}

#define SIO_D_IN		{SCCB_DDR&=~(1<<SCCB_SIO_D);}
#define SIO_D_OUT		{SCCB_DDR|=(1<<SCCB_SIO_D);}

#define SIO_D_STATE	((SCCB_PIN&(1<<SCCB_SIO_D))==(1<<SCCB_SIO_D))


///////////////////////////////////////////
void DelaySCCB(void);
void InitSCCB(void);
void startSCCB(void);
void stopSCCB(void);
void noAck(void);
unsigned char SCCBwriteByte(unsigned char m_data);
unsigned char SCCBreadByte(void);


#endif /* _SCCB_H */


