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
//************************************
// Method:    FFT2DCOMPLEX
// FullName:  FFT2DCOMPLEX
// Access:    public 
// Returns:   int*
// Qualifier:
// Parameter: int * Signal
// Parameter: A_ALIGNED dsp16_complex_t * ComplexBuffer
// Parameter: int size
//************************************
void FFT2DCOMPLEX( int *Signal, dsp16_complex_t *ComplexBuffer, int size )
{
	int i, j = 0;
	int Ptr; 
	Ptr = 0;
	A_ALIGNED dsp16_complex_t Input_C_1D[FFT_SIZE];
	A_ALIGNED dsp16_complex_t Result_C_1D[FFT_SIZE];
	A_ALIGNED dsp16_complex_t Result_C_2D[FFT_SIZE*FFT_SIZE];
	A_ALIGNED dsp16_t Input_R_1D[FFT_SIZE];
	//Stage 1 - FFT Real values from Signal. Store VERTICALLY in Result_2D
	for(i = 0; i < FFT_SIZE; i ++){ //for each row
		for(j = 0; j < FFT_SIZE; j++){
			Input_R_1D[j] = Signal[Ptr++]; //copy the data across
		}
		//Do the FFT
		dsp16_trans_realcomplexfft(Result_C_1D, Input_R_1D, log_2(FFT_SIZE));
		//Copy data into 2D reult TRANSPOSED
		for(j = 0; j < FFT_SIZE; j++){
			Result_C_2D[i + (j * FFT_SIZE)].imag = Result_C_1D[j].imag * FFT_SIZE;//scale back up
			Result_C_2D[i + (j * FFT_SIZE)].real = Result_C_1D[j].real * FFT_SIZE;
		}
	}
	//Stage 2 - FFT Complex Values from Result_2D, put back into Rows
	for(i = 0; i < FFT_SIZE; i++){//for each row
		for(j = 0; j < FFT_SIZE; j++){//copy the data across
			Input_C_1D[j].imag = Result_C_2D[j + i * FFT_SIZE].imag;
			Input_C_1D[j].real = Result_C_2D[j + i * FFT_SIZE].real;
		}

		//Do Fourier
		dsp16_trans_complexfft(Result_C_1D, Input_C_1D, log_2(FFT_SIZE));
		//Copy back
		for(j = 0; j < FFT_SIZE; j++){
			ComplexBuffer[i + j * FFT_SIZE].imag = 	Result_C_1D[j].imag;
			ComplexBuffer[i + j * FFT_SIZE].real = 	Result_C_1D[j].real;
		}
	}
	return;
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

	A_ALIGNED dsp16_complex_t vect1[FFT_SIZE];
	A_ALIGNED dsp16_t vect2[FFT_SIZE];
	for(i = 0; i < FFT_SIZE; i++)
	{
		vect2[i] = Signal[i];
	}
	dsp16_trans_realcomplexfft(vect1, vect2, log_2(FFT_SIZE));
	dsp16_vect_complex_abs(vect2, vect1, FFT_SIZE);
	for(i = 0; i < FFT_SIZE; i++)
	{
		Signal[i] = vect2[i] * FFT_SIZE;
	}
// 	mspace_free(sdram_msp, vect1);
// 	mspace_free(sdram_msp, vect2);
	return Signal;
}

int FFT2Dabs( int *Signal )
{
	int i, j = 0;
	int Ptr; 
	Ptr = 0;
	A_ALIGNED dsp16_complex_t Input_C_1D[FFT_SIZE];
	A_ALIGNED dsp16_complex_t Result_C_1D[FFT_SIZE];
	A_ALIGNED dsp16_complex_t Result_C_2D[FFT_SIZE*FFT_SIZE];
	A_ALIGNED dsp16_t Input_R_1D[FFT_SIZE];
	
	//Stage 1 - FFT Real values from Signal. Store VERTICALLY in Result_2D
	for(i = 0; i < FFT_SIZE; i ++) //for each row
	{
//		print_dbg("\n\rInput to FFT: \n\r[");
		for(j = 0; j < FFT_SIZE; j++)
		{
			Input_R_1D[j] = Signal[Ptr++]; //copy the data across
//			print_dbg_ulong(Input_R_1D[j]);
//			print_dbg(", ");
		}
//		print_dbg("\b\b]");
		//Do the FFT
		dsp16_trans_realcomplexfft(Result_C_1D, Input_R_1D, log_2(FFT_SIZE));
		//Copy data into 2D reult TRANSPOSED
//		print_dbg("\n\rOutput of FFT:\n\r[");
		for(j = 0; j < FFT_SIZE; j++)
		{
			Result_C_2D[i + (j * FFT_SIZE)].imag = Result_C_1D[j].imag * FFT_SIZE;//scale back up
			Result_C_2D[i + (j * FFT_SIZE)].real = Result_C_1D[j].real * FFT_SIZE;
//			print_dbg_ulong(Result_C_2D[i + (j * FFT_SIZE)].real);
//			print_dbg(" + j");
//			print_dbg_ulong(Result_C_2D[i + (j * FFT_SIZE)].imag);
//			print_dbg(" , ");
		}
//		print_dbg("\b\b]");
	}
	//Stage 2 - FFT Complex Values from Result_2D, put back into Rows

	for(i = 0; i < FFT_SIZE; i++)//for each row
	{
//		print_dbg("\n\rInput to FFT: \n\r[");
		for(j = 0; j < FFT_SIZE; j++)//copy the data across
		{
			Input_C_1D[j].imag = Result_C_2D[j + i * FFT_SIZE].imag;
			Input_C_1D[j].real = Result_C_2D[j + i * FFT_SIZE].real;
// 			print_dbg_ulong(Input_C_1D[j].real);
// 			print_dbg(" + j");
// 			print_dbg_ulong(Input_C_1D[j].imag);
// 			print_dbg(" , ");
		}
//		print_dbg("\b\b]");
		//Do Fourier
		dsp16_trans_complexfft(Result_C_1D, Input_C_1D, log_2(FFT_SIZE));
		//Copy back
		
// 		print_dbg("\n\rOutput to FFT: \n\r[");
// 		for(j = 0; j < FFT_SIZE; j++)//copy the data across
// 		{
// 			print_dbg_ulong(Result_C_1D[j].real);
// 			print_dbg(" + j");
// 			print_dbg_ulong(Result_C_1D[j].imag);
// 			print_dbg(" , ");
// 		}
// 		print_dbg("\b\b]");
		//Calculate Abs and put back into Signal TRANSPOSED
		dsp16_vect_complex_abs(Input_R_1D, Result_C_1D, FFT_SIZE);
		
		for(j = 0; j < FFT_SIZE; j++)
		{
			Signal[i + (j*FFT_SIZE)] = Input_R_1D[j] * FFT_SIZE;
		}
	}
	return Signal;
}




void PrepareImage(Image_t *Image)
{
	int row, col;
	uint16_t *PreparedImage;
	//Allocate some memory in the RAM
	PreparedImage = mspace_malloc(sdram_msp, 256*256 );
	
	//print_dbg("\n\rPrepared Image Pointer = ");
	//print_dbg_ulong(PreparedImage);
	for(row = 0; row < 256; row ++)
	{
		for(col = 0; col < 256; col++)
		{
			if(row < 240)
				PreparedImage[row*256 + col] = Image->ImagePtr[row * 256 + col];
			else
				PreparedImage[row *256 + col] = 0;//Image->ImagePtr[(row - 240) * 256 + col + 32];
		}
	}	
	
 	mspace_free(sdram_msp, Image->ImagePtr); //free up the old image
 	Image->ImagePtr = PreparedImage; //move the pointer to the prepared image
 	Image->Height = 256;
 	Image->Width = 256;
	//SaveBitmap(PreparedImage, 256, 256, "PreparedImage.bmp");
	//mspace_free(sdram_msp, PreparedImage);
	//return PreparedImage;
}


//************************************
// Method:    IFFT2D
// FullName:  IFFT2D
// Access:    public 
// Returns:   void
// Qualifier: 
// Parameter: dsp16_complex_t * Signal
//************************************
void IFFT2D (dsp16_complex_t *Signal) //Need to test this! 
{
	int i, j = 0;
	int Ptr;
	Ptr = 0;
	A_ALIGNED dsp16_complex_t Input_C_1D[FFT_SIZE];
	A_ALIGNED dsp16_complex_t Result_C_1D[FFT_SIZE];
	A_ALIGNED dsp16_complex_t Result_C_2D[FFT_SIZE*FFT_SIZE];
	A_ALIGNED dsp16_t Input_R_1D[FFT_SIZE];

	
	//Stage 1 - FFT Real values from Signal. Store VERTICALLY in Result_2D
	for(i = 0; i < FFT_SIZE; i ++) //for each row
	{
		for(j = 0; j < FFT_SIZE; j++)
		{
			Input_C_1D[j].real = Signal[Ptr].real; //copy the data across
			Input_C_1D[j].imag = Signal[Ptr].imag;
		}

		//Do the FFT
		dsp16_trans_complexifft(Result_C_1D, Input_C_1D, log_2(FFT_SIZE));
		//Copy data into 2D result TRANSPOSED

		for(j = 0; j < FFT_SIZE; j++)
		{
			Result_C_2D[i + (j * FFT_SIZE)].imag = Result_C_1D[j].imag * FFT_SIZE;//scale back up
			Result_C_2D[i + (j * FFT_SIZE)].real = Result_C_1D[j].real * FFT_SIZE;
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
		dsp16_trans_complexifft(Result_C_1D, Input_C_1D, log_2(FFT_SIZE));
		//Copy back
		

		//Put back into Signal TRANSPOSED
		//dsp16_vect_complex_abs(Input_R_1D, Result_C_1D, FFT_SIZE);
		
		for(j = 0; j < FFT_SIZE; j++)
		{
			Signal[i + j * FFT_SIZE].imag = 	Result_C_1D[j].imag;
			Signal[i + j * FFT_SIZE].real = 	Result_C_1D[j].real;
			//Signal[i + (j*FFT_SIZE)] = Input_R_1D[j] * FFT_SIZE;
		}
	}
	
	//return Signal;
}

void ComplexMultiply(dsp16_complex_t *Result_Input1, dsp16_complex_t *Input2, int size)
{
	int i = 0;
	dsp16_complex_t c;
	for(i = 0; i < size; i++)
	{
		//(a+jb).(c+jd) = (ac - bd) + j(ad + bc)
		c.real = (Result_Input1[i].real * Input2[i].real) - (Result_Input1[i].imag * Input2[i].imag);
		c.imag = (Result_Input1[i].real * Input2[i].imag) + (Result_Input1[i].imag * Input2[i].real);
		Result_Input1[i].imag = c.imag;
		Result_Input1[i].real = c.real;
	}
}