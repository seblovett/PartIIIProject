/*
 * CustomDevices.h
 *
 * Created: 16/02/2013 14:30:50
 *  Author: hslovett
 */ 


#ifndef CUSTOMDEVICES_H_
#define CUSTOMDEVICES_H_

//Camera
#include "CustomDevices/OV7670.h"
//I2C Mux
#include "CustomDevices/PCA9542A.h"
//MotorDriver
#include "CustomDevices/MotorDriver.h"
//SDCard
#include "CustomDevices/SD_Card.h"
//Image Processing Functions
#include "CustomDevices/ImageProcessor.h"

typedef struct {
	int Status;
	SD_Status_t *SD_Card;
	Motor_Control_t *Motors;
	OV7670_t *Cameras;
	PCA9542A_t *I2CMux;
} Columbus_Status_t;
typedef struct  {
	char Command;
	int Arg;
} AutoCommand_t;

#define AUTO_COMMAND_LENGTH		14

#define SD_ERR		0x1
#define CAM_ERR		0x2
#define I2CMux_ERR	0x4
#define CAM0_NotFOUND	0x08
#define CAM1_NotFOUND	0x10
#define AutoRunCMD_ERR	0x20
#define FFT_SIZE 64


//REF : http://www.chris.com/ASCII/index.php?art=transportation/nautical
#define ASCII_SHIP "\t\t\t             |    |    | \n\r\t\t\t            )_)  )_)  )_) \n\r\t\t\t           )___))___))___)\\  \n\r\t\t\t           )____)____)_____)\\\\ \n\r\t\t\t         _____|____|____|____\\\\\\__ \n\r\t\t\t---------\\                   /--------- \n\r\t\t\t  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^ \n\r\t\t\t    ^^^^      ^^^^     ^^^    ^^\n\r\t\t\t         ^^^^      ^^^\n\r"
#define COLUMBUS " _______  _______  _                 _______  ______            _______ \n\r(  ____ \\(  ___  )( \\      |\\     /|(       )(  ___ \\ |\\     /|(  ____ \\\n\r| (    \\/| (   ) || (      | )   ( || () () || (   ) )| )   ( || (    \\/\n\r| |      | |   | || |      | |   | || || || || (__/ / | |   | || (_____ \n\r| |      | |   | || |      | |   | || |(_)| ||  __ (  | |   | |(_____  )\n\r| |      | |   | || |      | |   | || |   | || (  \\ \\ | |   | |      ) |\n\r| (____/\\| (___) || (____/\\| (___) || )   ( || )___) )| (___) |/\\____) |\n\r(_______/(_______)(_______/(_______)|/     \\||______/ (_______)\\_______)\n\n\r"
#define THE "\t\t\t_________          _______ \n\r \t\t\t\\__   __/|\\     /|(  ____ \\ \n\r \t\t\t   ) (   | )   ( || (    \\/\n\r\t\t\t   | |   | (___) || (__    \n\r \t\t\t   | |   |  ___  ||  __)   \n\r \t\t\t   | |   | (   ) || (      \n\r \t\t\t   | |   | )   ( || (____/\\\n\r \t\t\t   )_(   |/     \\|(_______/\n\r"
#define PROMPT "\n\r$>"

#define HELP	"\rColumbus Prompt Help:\n\r\
\t? : Shows this prompt\n\r \
\tA : Runs the AutoRun procedure in debug mode\r\n \
\tB : Reads a Bitmap file and prints information \n\r \
\tc : converts the working buffer from integer to fixed point\n\r\
\tC : Converts the working buffer from fixed point to integer\n\r\
\td : Saves the Working Buffer to \"Buffer_results.csv\" \n\r \
\tD : Frees the Memory pointed to by the Working Buffer \n\r \
\tf : Reads \"Buffer.csv\" as a 2D Array of FFT_SIZE by FFT_SIZE\n\r \
\tg : Saves the Complex Buffer to \"Buffer_Complex.csv\" \n\r\
\tk : Prints the Complex Buffer \n\r \
\tm : Computes the Magnitude of the 1D FFT of the Working Buffer \n\r\ 
\tM : Motor Driving Options, prefix to the following: \n\r \
\t\t F (int) : Drive Robot forward by (int) millimetres (negative number for reverse)\n\r\
\t\t L : Dive Left Wheel Forward a full rotation \n\r\
\t\t q : Resets Motors \n\r\
\t\t R : Drive Right Wheel Forward a full rotation \n\r\
\t\t T (int) : Rotate Robot by (int) degrees (postitive turns Clockwise)\n\r\
\to : Displays the fixed point value for (int)1 \n\r\
\tP : Takes and stores Stereo Photos \n\r \
\tr : displays the contents of the working buffer\n\r\
\tR : Reads contents of signal.bin, representing 1D Signal. Integers, Big Endian\n\r\
\tT : Reads contents of signal2d.bin, representing 2D Signal. \n\r \
\ts : saves the working buffer\n\r\
\tS : Saves the image in memory to a Bitmaps \n\r\
\tv : Prints the status variables \n\r \
\t1 : computes the One Dimensional FFT of the working buffer. Returns magnitude.\n\r\
\t2 : Computes the Magnitude of the Two Dimensional FFT of the Working Buffer. \n\r \
\t3 : Computes the Complex 2D FFT of the working buffer and stores it in the Complex Buffer \n\r\
"


mspace sdram_msp;
Columbus_Status_t Columbus_Status;
//TWI Methods
void twim_init (void);
void System_Test();
#endif /* CUSTOMDEVICES_H_ */