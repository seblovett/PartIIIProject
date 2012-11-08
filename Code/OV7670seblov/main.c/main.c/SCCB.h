/*
 * SCCB.h
 *
 * Created: 05/10/2012 22:41:37
 *  Author: hslovett
 */ 


#ifndef SCCB_H_
#define SCCB_H_

#include <avr/io.h>




#define SCCB_DDR		DDRC
#define SCCB_PORT		PORTC
#define SCCB_PIN		PINC

#define SCCB_SIO_C		6
#define SCCB_SIO_D		7

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
char SCCBwriteByte(char m_data);
char SCCBreadByte(void);





#endif /* SCCB_H_ */