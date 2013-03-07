/*
 * ImageProcessor.c
 *
 * Created: 28/02/2013 17:46:50
 *  Author: hslovett
 */ 
#include <asf.h>
#include "CustomDevices/CustomDevices.h"

/*#define FFT_SIZE 64*/
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

int FFT2D( int *Signal )
{
	int i, j = 0;
	int Ptr; 
	Ptr = 0;
	A_ALIGNED dsp32_complex_t Input_C_1D[FFT_SIZE];
	A_ALIGNED dsp32_complex_t Result_C_1D[FFT_SIZE];
	A_ALIGNED dsp32_complex_t Result_C_2D[FFT_SIZE*FFT_SIZE];
	A_ALIGNED dsp32_t Input_R_1D[FFT_SIZE];
	
	//Stage 1 - FFT Real values from Signal. Store VERTICALLY in Result_2D
	for(i = 0; i < FFT_SIZE; i ++) //for each row
	{
		for(j = 0; j < FFT_SIZE; j++)
		{
			Input_R_1D[j] = Signal[Ptr++]; //copy the data across
		}
		//Do the FFT
		dsp32_trans_realcomplexfft(Result_C_1D, Input_R_1D, log_2(FFT_SIZE));
		//Copy data into 2D reult TRANSPOSED
		for(j = 0; j < FFT_SIZE; j++)
		{
			Result_C_2D[i + (j * FFT_SIZE)].imag = Result_C_1D[j].imag;
			Result_C_2D[i + (j * FFT_SIZE)].real = Result_C_1D[j].real;
		}
	}
	//Stage 2 - FFT Complex Values from Result_2D, put back into Rows

	for(i = 0; i < FFT_SIZE; i++)//for each row
	{
		for(j = 0; j < FFT_SIZE; j++)//copy the data across
		{
			Input_C_1D[j].imag = Result_C_2D[j + i * FFT_SIZE].imag;
			Input_C_1D[j].real = Result_C_2D[j + i * FFT_SIZE].real;
		}
		//Do Fourier
		dsp32_trans_realcomplexfft(Result_C_1D, Input_C_1D, log_2(FFT_SIZE));
		//Copy back
// 		for(j = 0; j < FFT_SIZE; j++)//copy the data across
// 		{
// 			Result_C_2D[j + i * FFT_SIZE]->imag = Input_C_1D[j].imag;
// 			Result_C_2D[j + i * FFT_SIZE]->real = Input_C_1D[j].real;
// 		}

		//Calculate Abs and put back into Signal TRANSPOSED
		dsp32_vect_complex_abs(Input_R_1D, Result_C_1D, FFT_SIZE);
		
		for(j = 0; j < FFT_SIZE; j++)
		{
			Signal[i + (j*FFT_SIZE)] = Input_R_1D[j];
		}
	}
	//Stage 3 - Transpose Result_2D while returning abs values into Signal

}
