/*
 * ImageProcessor.c
 *
 * Created: 28/02/2013 17:46:50
 *  Author: hslovett
 */ 
#include <asf.h>
#include "CustomDevices/CustomDevices.h"
//One Dimensional Fast Fourier Transform
int FFT1D( int *Signal, int size )
{
	int log2Size, i =0;
	double a;
	//if the number is not a power of two, fail. 
	if((size & (size - 1)) != 0)
	{
		return FAIL; 
	}
	//log2Size = log2(size);//doesn't seem to work...
	log2Size = 0;
	i = size;
	while((i & 1) == 0) //while the bit isn't in the lowest bit (already established this is a integer power of 2)
	{
		i >>= 1; 
		log2Size++;
	}
	A_ALIGNED dsp32_complex_t *vect1;
	A_ALIGNED dsp32_t *vect2;
	
	vect1 = mspace_malloc(sdram_msp, 2 * size);
	vect2 = mspace_malloc(sdram_msp, size);
	for(i = 0; i < size; i++)
	{
		vect2[i] = Signal[i];
	}
	dsp32_trans_realcomplexfft(vect1, vect2, FFT_LOG2);
	dsp32_vect_complex_abs(vect2, vect1, size);
	for(i = 0; i < size; i++)
	{
		Signal[i] = vect2[i];
	}
}
