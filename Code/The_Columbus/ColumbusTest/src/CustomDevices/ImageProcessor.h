/*
 * ImageProcessor.h
 *
 * Created: 28/02/2013 17:46:37
 *  Author: hslovett
 */ 


#ifndef IMAGEPROCESSOR_H_
#define IMAGEPROCESSOR_H_
typedef struct {
	int *ImagePtr;
	} ImageProcessor_t;
	
	
//Load image to bitmap
int LoadImage(char *Filename);
int SaveImage(char *Filename);

int FFT1D(int *Signal);
int FFT2D(int *Signal);
int log_2(int i);

int* FFT2DCOMPLEX( int *Signal, dsp16_complex_t *ComplexBuffer, int size );
#endif /* IMAGEPROCESSOR_H_ */