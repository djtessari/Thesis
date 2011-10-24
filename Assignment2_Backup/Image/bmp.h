#ifndef BMP_INCLUDED
#define BMP_INCLUDED



#include "image.h"

/** This function read in a BMP file, returning 0 on failure.*/
int BMPReadImage(char* fileName, Image32& img);
/** This function read in a BMP file, returning 0 on failure.*/
int BMPReadImage(FILE *fp, Image32& img);

/** This function writes out a BMP file, returning 0 on failure.*/
int BMPWriteImage(Image32& img, char* fileName);
/** This function writes out a BMP file, returning 0 on failure.*/
int BMPWriteImage(Image32& img, FILE *fp);



#endif // BMP_INCLUDED
