/*
 * ImageProcessor.c
 *
 * Created: 28/02/2013 17:46:50
 *  Author: hslovett
 */ 
#include <asf.h>
#include "CustomDevices/CustomDevices.h"

#define FFT_SIZE 64
//Returns log base 2 of i - checks if it is an integer power of 2
int log_2(int i)
{
	int ret = 0; 
	if((i & (i - 1)) != 0)
	{
		return -1;
	}
	while((i & 1) == 0) //while the bit isn't in the lowest bit (already established this is a integer power of 2)
	{
		i >>= 1;
		ret++;
	}
	
	return ret;
}
//One Dimensional Fast Fourier Transform
int FFT1D( int *Signal)
{
//	int size = 64;
	int log2Size, i =0;
//	double a;
// 	log2Size = log_2(size);
// 	if(log2Size & 1) //if it is an odd power of two
// 		return 0;
		
	//am I making this all too complex for myself?! May just stick to defined size of 256.
// 	A_ALIGNED dsp32_complex_t *vect1;
// 	A_ALIGNED dsp32_t *vect2;
	
// 	vect1 = mspace_malloc(sdram_msp, (sizeof(dsp32_complex_t) * size));
// 	vect2 = mspace_malloc(sdram_msp, (sizeof(dsp32_t) * size));

	//Defined Sizes

	A_ALIGNED dsp32_complex_t vect1[FFT_SIZE];
	A_ALIGNED dsp32_t vect2[FFT_SIZE];
	for(i = 0; i < FFT_SIZE; i++)
	{
		vect2[i] = Signal[i];
	}
	dsp32_trans_realcomplexfft(vect1, vect2, log_2(FFT_SIZE));
	dsp32_vect_complex_abs(vect2, vect1, FFT_SIZE);
	for(i = 0; i < FFT_SIZE; i++)
	{
		Signal[i] = vect2[i];
	}
// 	mspace_free(sdram_msp, vect1);
// 	mspace_free(sdram_msp, vect2);
}
