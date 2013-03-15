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
	uint16_t *ImagePtr;
	int Height;
	int Width;
	uint8_t Format;
	} Image_t;
	


int FFT1D(int *Signal);
int FFT2Dabs(int *Signal);
int log_2(int i);

int* FFT2DCOMPLEX( int *Signal, dsp16_complex_t *ComplexBuffer, int size );
int* PrepareImage(int *Image);
//int* IFFT2D (dsp16_complex_t *Result, dsp16_complex_t *Input);
void IFFT2D (dsp16_complex_t *Signal) /*Need to test this! */;
#endif /* IMAGEPROCESSOR_H_ */