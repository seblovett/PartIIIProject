/*
 * SD_Card.h
 *
 * Created: 10/02/2013 17:11:51
 *  Author: hslovett
 */ 


#ifndef SD_CARD_H_
#define SD_CARD_H_

#define SIGNAL_FILE "signal.bin"
#define  TWOD_SIGNAL_FILE "signal2d.bin"

typedef struct {
	uint8_t Status;
	uint32_t Memory_size;
	} SD_Status_t;
SD_Status_t SD_Status;

void local_pdca_init(void);
void sd_mmc_resources_init(void);
static void pdca_int_handler(void);
void wait();
void Log_Write_ulong(unsigned long n);
void Log_Write(char *buff, int length);
void SaveBuff( int * WorkingBuffer , int size);
int Read2DSignal( int * WorkingBuffer );
int ReadSignal( int * WorkingBuffer );
#endif /* SD_CARD_H_ */
