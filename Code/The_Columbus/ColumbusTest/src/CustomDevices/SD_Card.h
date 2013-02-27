/*
 * SD_Card.h
 *
 * Created: 10/02/2013 17:11:51
 *  Author: hslovett
 */ 


#ifndef SD_CARD_H_
#define SD_CARD_H_


typedef struct {
	uint8_t Status;
	uint32_t Memory_size;
	} SD_Status_t;
SD_Status_t SD_Status;

void local_pdca_init(void);
void sd_mmc_resources_init(void);
static void pdca_int_handler(void);
void wait();
#endif /* SD_CARD_H_ */
