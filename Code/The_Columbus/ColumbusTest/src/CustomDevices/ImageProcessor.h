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
	


void FFT1D( int *Signal, dsp16_complex_t *ComplexBuffer);
int FFT2Dabs(int *Signal);
int log_2(int i);

void FFT2DCOMPLEX( int *Signal, dsp16_complex_t *ComplexBuffer, int size );
void PrepareImage(Image_t *Image);
//int* IFFT2D (dsp16_complex_t *Result, dsp16_complex_t *Input);
void IFFT2D (dsp16_complex_t *Signal); /*Need to test this! */;
int FFT1D_Abs( int *Signal);
void Complex_Abs( int *Signal, dsp16_complex_t *ComplexBuffer, int size);
#endif /* IMAGEPROCESSOR_H_ */