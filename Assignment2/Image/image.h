#ifndef IMAGE_INCLUDED
#define IMAGE_INCLUDED

#include <stdio.h>
#include "Image/lineSegments.h"

/** The value of pi to many significant digits/*/
#define PI 3.1415926535897932384

/** This structure represents a 4-channel, floating point precision pixel. */
class Pixel {
public:
	/** The red, green, blue, and alpha components of the pixel */
    float r, g, b, a;

	/** This constructor instantiates a pixel with 0 for the red, green and blue components, and 255 for the alpha.*/
	Pixel(void);

	////////////////////////
	// Unimplemented Code //
	////////////////////////
	/** This constructor instantiates a 32 bit pixel representation of the RGBA components. */
	Pixel(const class Pixel32& p);

};

/** This structure represents a 4-channel, 32-bit, RGBA pixel. */
class Pixel32 {
public:
	/** The red, green, blue, and alpha components of the pixel */
    unsigned char r, g, b, a;

	/** This constructor instantiates a pixel with 0 for the red, green and blue components, and 255 for the alpha.*/
	Pixel32(void);

	////////////////////////
	// Unimplemented Code //
	////////////////////////
	/** This constructor instantiates a pixel by transforming the input red, green, blue, and alpha components
	  * from floating points in the range [0,1] to integer values in the range [0,255]
	  */
	Pixel32(const Pixel& p);
};


/** This class represents an RGBA image with 8 bits per channel. */
class Image32{
	int w,h;
	Pixel32* pixels;
public:
	Image32(void);
	~Image32(void);

	/** This method sets the dimension of the image. */
	int setSize(const int& width,const int& height);

	/** This overloaded operator copies the input image into the current image. */
	Image32& operator = (const Image32& img);

	/** This method returns the width of the image */
	int width(void) const;
	/** This method returns the height of the image */
	int height(void) const;

	/** This method returns a reference to the indexed pixel.*/
	Pixel32& operator() (const int& x,const int& y);

	/** This method returns a reference to the indexed pixel.*/
	const Pixel32& operator() (const int& x,const int& y) const;

	/** This method returns a reference to the indexed pixel.*/
	Pixel32& pixel(const int& x,const int& y);

	/** This method returns a reference to the indexed pixel.*/
	const Pixel32& pixel(const int& x,const int& y) const;

	////////////////////////
	// Unimplemented Code //
	////////////////////////
	/** This method adds random noise to each pixel and writes out the new image to outputImage.
	  * The value of the input parameter should be in the range [0,1] representing the fraction
	  * of noise that should be added. The actual amount of noise added is in the range [-noise,noise].
	  * The method returns 1 if it has been implemented.
	  */
	int AddRandomNoise(const float& noise,Image32& outputImage) const;

	/** This method brightens each pixel and writes out the new image to outputImage.
	  * The value of the input parameter is the scale by which the image should be brightened. 
	  * The method returns 1 if it has been implemented.
	  */
	int Brighten(const float& brightness,Image32& outputImage) const;

	/** This method transforms a color image into a gray image and writes out the new image to outputImage.
	  * The method returns 1 if it has been implemented.
	  */
	int Luminance(Image32& outputImage) const;

	/** This method changes the contrast of the image and writes out the new image to outputImage.
	  * The value of the input parameter is the scale by which the contrast of the image should be changed.
	  * The method returns 1 if it has been implemented.
	  */
	int Contrast(const float& contrast,Image32& outputImage) const;

	/** This method changes the saturation of each pixel and writes out the new image to outputImage.
	  * The value of the input parameter is the scale by which the saturation of the pixel should be changed.
	  * The method returns 1 if it has been implemented.
	  */
	int Saturate(const float& saturation,Image32& outputImage) const;

	/** This method transforms the image so that each color is represented by a fixed number of bits and writes out the new image to outputImage.
	  * The final pixel values are obtained by quantizing.
	  * The value of the input parameter is the number of bits that should be used to represent a color component in the output image.
	  * The method returns 1 if it has been implemented.
	  */
	int Quantize(const int& bits,Image32& outputImage) const;

	/** This method transforms the image so that each color is represented by a fixed number of bits and writes out the new image to outputImage.
	  * The final pixel values are obtained by adding noise to the pixel color channels and then quantizing.
	  * The value of the input parameter is the number of bits that should be used to represent a color component in the output image.
	  * The method returns 1 if it has been implemented.
	  */
	int RandomDither(const int& bits,Image32& outputImage) const;

	/** This method transforms the image so that each color is represented by a fixed number of bits and writes out the new image to outputImage.
	  * The final pixel values are obtained by using a 2x2 dithering matrix to determine how values should be quantized.
	  * The value of the input parameter is the number of bits that should be used to represent a color component in the output image.
	  * The method returns 1 if it has been implemented.
	  */
	int OrderedDither2X2(const int& bits,Image32& outputImage) const;

	/** This method transforms the image so that each color is represented by a fixed number of bits and writes out the new image to outputImage.
	  * The final pixel values are obtained by using Floyd-Steinberg dithering for propogating quantization errors.
	  * The value of the input parameter is the number of bits that should be used to represent a color component in the output image.
	  * The method returns 1 if it has been implemented.
	  */
	int FloydSteinbergDither(const int& bits,Image32& outputImage) const;
	
	/** This method blurs the image using a 3x3 mask.
	  * The method returns 1 if it has been implemented.
	  */
	int Blur3X3(Image32& outputImage) const;

	/** This method computes the edges of the image using a 3x3 mask and writes out the new image to outputImage.
	  * The method returns 1 if it has been implemented.
	  */
	int EdgeDetect3X3(Image32& outputImage) const;

	/** This method scales an image using nearest point sampling to obtain pixel values and writes out the new image to outputImage.
	  * The value of the input parameter is the factor by which the image is to be scaled.
	  * The method returns 1 if it has been implemented.
	  */
	int ScaleNearest(const float& scaleFactor,Image32& outputImage) const;

	/** This method scales an image using bilinear-interpolation to obtain pixel values and writes out the new image to outputImage.
	  * The value of the input parameter is the factor by which the image is to be scaled.
	  * The method returns 1 if it has been implemented.
	  */
	int ScaleBilinear(const float& scaleFactor,Image32& outputImage) const;

	/** This method scales an image using Gaussian-weighting to obtain pixel values and writes out the new image to outputImage.
	  * The value of the input parameter is the factor by which the image is to be scaled.
	  * The method returns 1 if it has been implemented.
	  */
	int ScaleGaussian(const float& scaleFactor,Image32& outputImage) const;

	/** This method rotates an image using nearest point sampling to obtain pixel values and writes out the new image to outputImage.
	  * The value of the input parameter is the angle of rotation (in degrees).
	  * The method returns 1 if it has been implemented.
	  */
	int RotateNearest(const float& angle,Image32& outputImage) const;

	/** This method rotates an image using bilinear-interpolation to obtain pixel values and writes out the new image to outputImage.
	  * The value of the input parameter is the angle of rotation (in degrees).
	  * The method returns 1 if it has been implemented.
	  */
	int RotateBilinear(const float& angle,Image32& outputImage) const;
	
	/** This method rotates an image using Gaussian-weighting to obtain pixel values and writes out the new image to outputImage.
	  * The value of the input parameter is the angle of rotation (in degrees).
	  * The method returns 1 if it has been implemented.
	  */
	int RotateGaussian(const float& angle,Image32& outputImage) const;


	/** This method sets the alpha-channel of the current image using the information provided in the matte image.
	  * The method returns 1 if it has been implemented.
	  */
	int SetAlpha(const Image32& matte);

	/** This method composites the overlay image on top of the current image and writes out the new image to outputImage.
	  * The method uses the values in the alpha-channel of the overlay image to determine how pixels should be blended.
	  * The method returns 1 if it has been implemented.
	  */
	int Composite(const Image32& overlay,Image32& outputImage) const;


	/** This method crops the image and writes out the new image to outputImage
	  * The values of the input parameters specify the corners of the cropping rectangle.
	  * The method returns 1 if it has been implemented.
	  */
	int Crop(const int& x1,const int& y1,const int& x2,const int& y2,Image32& outputImage) const;


	/** This method applies a fun-filter to the current image and writes out the new image to outputImage.
	  * The method returns 1 if it has been implemented.
	  */
	int FunFilter(Image32& outputImage) const;

	/** This static method applies a Beier-Neely morph and writes out the new image to outputImage.
	  * The method uses the set of line segment pairs to define correspondences between the source and destination image.
	  * The time-step parameter, in the range of [0,1], specifies the point in the morph at which the output image should be obtained.
	  * The method returns 1 if it has been implemented.
	  */
	static int BeierNeelyMorph(const Image32& source,const Image32& destination,const OrientedLineSegmentPairs& olsp,const float& timeStep,Image32& ouputImage);

	/** This method uses the correspondences defined by the line segment pairs to warp the current image into the output image.
	  * The method returns 1 if it has been implemented.
	  */
	int Warp(const OrientedLineSegmentPairs& olsp,Image32& outputImage) const;

	/** This static method cross-dissolves two image and writes out the new image to outputImage.
	  * The method generates an image which is the blend of the source and destination, using the blend-weight in the range [0,1] to
	  * determine what faction of the source and destination images should be used to generate the final output.
	  * The method returns 1 if it has been implemented.
	  */
	static int CrossDissolve(const Image32& source,const Image32& destination,const float& blendWeight,Image32& ouputImage);


	/** This method returns the value of the image, sampled at position (x,y) using nearest-point sampling.
	  * The variance of the Gaussian and the radius over which the weighted summation is performed are specified by the parameters.
	  */
	Pixel32 NearestSample(const float& x,const float& y) const;

	/** This method returns the value of the image, sampled at position (x,y) using bilinear-weighted sampling.
	  * The variance of the Gaussian and the radius over which the weighted summation is performed are specified by the parameters.
	  */
	Pixel32 BilinearSample(const float& x,const float& y) const;

	/** This method returns the value of the image, sampled at position (x,y) using Gaussian-weighted sampling.
	  * The variance of the Gaussian and the radius over which the weighted summation is performed are specified by the parameters.
	  */
	Pixel32 GaussianSample(const float& x,const float& y,const float& variance,const float& radius) const;


	/** This method reads in an image from the specified file. It uses the file extension
	  * to determine if the file should be read in as a BMP file or as a JPEG file.
	  */
	int ReadImage(char* fileName);
	/** This method writes in an image out to the specified file. It uses the file extension
	  * to determine if the file should be written out as a BMP file or as a JPEG file.
	  */
	int WriteImage(char* fileName);

};
#endif // IMAGE_INCLUDED

