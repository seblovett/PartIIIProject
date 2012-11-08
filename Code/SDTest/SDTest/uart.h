


/* set the UART baud rate */
#ifndef BAUD_RATE
//#define BAUD_RATE   19200
//#define BAUD_RATE   38400
#define BAUD_RATE   57600
//#define BAUD_RATE   76800
//#define BAUD_RATE   125000
#endif

/* function prototypes */
void uart_init(void);
void putch(char);
char getch(void);
void getNch(uint8_t);
char gethex(void);
void puthex(char);

