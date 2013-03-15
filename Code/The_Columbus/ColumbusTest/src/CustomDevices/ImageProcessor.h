/*
 * ImageProcessor.h
 *
 * Created: 28/02/2013 17:46:37
 *  Author: hslovett
 */ 


#ifndef IMAGEPROCESSOR_H_
#define IMAGEPROCESSOR_H_

#define BMP_FORMAT_RGB565			1
#define BMP_FORMAT_RGB555			2
#define BMP_FORMAT_GREYSCALE		3
#define BMP_FORMAT_1xUINT			4
#define BMP_FORMAT_2xUINT8T			5
typedef struct {
	int *ImagePtr;
	int Height;
	int Width;
	uint8_t Format;
	} Image_t;
	


int FFT1D(int *Signal);
int FFT2D(int *Signal);
int log_2(int i);

int* FFT2DCOMPLEX( int *Signal, dsp16_complex_t *ComplexBuffer, int size );
#endif /* IMAGEPROCESSOR_H_ */