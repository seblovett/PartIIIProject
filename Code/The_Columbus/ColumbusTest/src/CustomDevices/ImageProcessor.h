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


#endif /* IMAGEPROCESSOR_H_ */