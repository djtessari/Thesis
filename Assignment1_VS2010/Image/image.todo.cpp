#include "image.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

// allows the use of min() and max() functions
#include <algorithm>
using namespace std;


Pixel::Pixel(const Pixel32& p)
{
}

Pixel32::Pixel32(const Pixel& p)
{
}

int Image32::AddRandomNoise(const float& noise,Image32& outputImage) const
{
	//Fix and test this
	if (0 > noise || 1 < noise)
	{
		//halt operation, bounding error
		return 1;
	}
	int xMax = width();
	int yMax = height();
	srand(time(NULL));

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			float addNoise = ( (rand() % 2) - 1) * noise;
		}
	}
	return 0;
}

int Image32::Brighten(const float& brightness,Image32& outputImage) const
{
	int xMax = width();
	int yMax = height(); 

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			//Potentially change how this works, does not evenly scale the darks
			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			r*=brightness;
			g*=brightness;
			b*=brightness;

			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;
		}
	}
	return 1;
}


int Image32::Luminance(Image32& outputImage) const
{
	int xMax = width();
	int yMax = height(); 

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			//Pixel Adjustments
			float pLum = (0.3*r) + (0.59*g) + (0.11*b);
			r=pLum;
			g=pLum;
			b=pLum;

			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;
		}
	}
	return 1;
}

int Image32::Contrast(const float& contrast,Image32& outputImage) const
{
	int xMax = width();
	int yMax = height(); 

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{

			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			//Pixel Adjustments

			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;
		}
	}
	return 0;
}

int Image32::Saturate(const float& saturation,Image32& outputImage) const
{
	return 0;
}

int Image32::Quantize(const int& bits,Image32& outputImage) const
{
	//Fix this
	int xMax = width();
	int yMax = height(); 
	float power = pow(2.0,bits);
	printf("power = %f\n",power); 

	for (int i = 100; i < 110; i++)
	{
		for (int j = 100; j < 105; j++)
		{

			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			//Pixel Adjustments
			r = floor( (r * (pow(2.0, bits))) / 256 );

			printf("r = %f\n",r);
			g = floor( (g * (pow(2.0, bits))) / 256 );
			b = floor( (b * (pow(2.0, bits))) / 256 );

			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;
		}
	}
	return 1;
}

int Image32::RandomDither(const int& bits,Image32& outputImage) const
{
	//test this
	AddRandomNoise(0.5, outputImage);
	Quantize(bits, outputImage);
	
	return 1;
}

int Image32::OrderedDither2X2(const int& bits,Image32& outputImage) const
{
	//Fix this (find out what the hell n is)
	int xMax = width();
	int yMax = height(); 
	double n = 0;

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			int d[] = {1, 3, 4, 2};

			int x = (int) (i % (int) n);
			int y =(int) (j % (int) n);

			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			//Pixel Adjustments
			float rC = (r/255) * (pow(2.0, bits) - 1);
			float gC = (g/255) * (pow(2.0, bits) - 1);
			float bC = (b/255) * (pow(2.0, bits) - 1);

			float rE = rC - floor(rC);
			float gE = gC - floor(gC);
			float bE = bC - floor(bC);

			if (rE > (d[x+y] / (pow(n, 2)+1))) r = ceil(rC);
			else r = floor(rC);
			if (gE > (d[x+y] / (pow(n, 2)+1))) g = ceil(gC);
			else g = floor(gC);
			if (bE > (d[x+y] / (pow(n, 2)+1))) b = ceil(bC);
			else b = floor(bC);



			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;
		}
	}
	return 0;
}

int Image32::FloydSteinbergDither(const int& bits,Image32& outputImage) const
{
	//Not started
	int xMax = width();
	int yMax = height(); 

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			
			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			//Pixel Adjustments

			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;
		}
	}
	return 0;
}

int Image32::Blur3X3(Image32& outputImage) const
{
	//handle border cases
	int xMax = width();
	int yMax = height(); 

	float mask[3][3] = {
		{1/16, 2/16, 1/16},
		{2/16, 4/16, 2/16},
		{1/16, 2/16, 1/16}};

	Image32 newImage = outputImage;

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = newImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			//Pixel Adjustments
			float newR = 0.0;
			float newG = 0.0;
			float newB = 0.0;

			for (int x = 0; x < 3; x++)
			{
				for (int y = 0; y < 3; y++)
				{
					newR += ( (float) outputImage.pixel(i-1+x,j-1+y).r * mask[x][y]);
					newG += ( (float) outputImage.pixel(i-1+x,j-1+y).g * mask[x][y]);
					newB += ( (float) outputImage.pixel(i-1+x,j-1+y).b * mask[x][y]);
				}
			}
			r = newR;
			g = newG;
			b = newB;

			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;
		}
	}
	outputImage = newImage;
	return 1;
}

int Image32::EdgeDetect3X3(Image32& outputImage) const
{
	//Finish blur, then copy here and change
	return 0;
}
int Image32::ScaleNearest(const float& scaleFactor,Image32& outputImage) const
{
	int xMax = width() * scaleFactor;
	int yMax = height() * scaleFactor; 
	outputImage.setSize(xMax, yMax);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);
			
			//Pixel Adjustments
			newPix = NearestSample(i / scaleFactor, j / scaleFactor);
		}
	}
	return 1;
}

int Image32::ScaleBilinear(const float& scaleFactor,Image32& outputImage) const
{
	int xMax = width() * scaleFactor;
	int yMax = height() * scaleFactor; 
	outputImage.setSize(xMax, yMax);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);
			
			//Pixel Adjustments
			newPix = BilinearSample(i / scaleFactor, j / scaleFactor);
		}
	}
	return 1;
}

int Image32::ScaleGaussian(const float& scaleFactor,Image32& outputImage) const
{
	int xMax = width() * scaleFactor;
	int yMax = height() * scaleFactor; 
	outputImage.setSize(xMax, yMax);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);
			
			//Pixel Adjustments
			//newPix = GaussianSample(i / scaleFactor, j / scaleFactor);
		}
	}
	return 1;
}

int Image32::RotateNearest(const float& angle,Image32& outputImage) const
{
	return 0;
}

int Image32::RotateBilinear(const float& angle,Image32& outputImage) const
{
	return 0;
}
	
int Image32::RotateGaussian(const float& angle,Image32& outputImage) const
{
	return 0;
}


int Image32::SetAlpha(const Image32& matte)
{
	return 0;
}

int Image32::Composite(const Image32& overlay,Image32& outputImage) const
{
	return 0;
}

int Image32::CrossDissolve(const Image32& source,const Image32& destination,const float& blendWeight,Image32& ouputImage)
{
	return 0;
}
int Image32::Warp(const OrientedLineSegmentPairs& olsp,Image32& outputImage) const
{
	return 0;
}

int Image32::FunFilter(Image32& outputImage) const
{
	return 0;
}

int Image32::Crop(const int& x1,const int& y1,const int& x2,const int& y2,Image32& outputImage) const
{
	int xMax = width();
	int yMax = height(); 

	Image32* newImage = new Image32();
	newImage->setSize(x2 - x1, y2 - y1);

	int xI = 0;
	int yI = 0;

	for (int i = x1; i < x2; i++)
	{
		yI = 0;
		for (int j = y1; j < y2; j++)
		{			
			Pixel32 &newPix = newImage->pixel(i, j);
			newPix = outputImage.pixel(i,j);	
			yI++;
		}
		xI++;
	}
	outputImage = *newImage;
	return 1;
}

Pixel32 Image32::NearestSample(const float& x,const float& y) const
{
	int iu = floor(x+0.5);
	int iv = floor(y+0.5);
	Pixel32 returnPix = pixel(iu, iv);
	return returnPix;
}

Pixel32 Image32::BilinearSample(const float& x,const float& y) const
{
	int x1 = floor(x);
	int x2 = x1+1;

	int y1 = floor(y);
	int y2 = y1+1;

	if (x1 < 0) x1 = 0;
	if (y1 < 0) y1 = 0;
	if (x2 >= w) x2 = w-1;
	if (y2 >= h) y2 = h-1;

	float dx = x - x1;
	float dy = y - y1;

	Pixel32 newPix = Pixel32();

	float rA, gA, bA;
	float rB, gB, bB;

	rA = ((1-dx) * (float) pixel(x1, y1).r) + ((dx * (float) pixel(x2, y1).r));
	gA = ((1-dx) * (float) pixel(x1, y1).g) + ((dx * (float) pixel(x2, y1).g));
	bA = ((1-dx) * (float) pixel(x1, y1).b) + ((dx * (float) pixel(x2, y1).b));

	rB = ((1-dx) * (float) pixel(x1, y2).r) + ((dx * (float) pixel(x2, y2).r));
	gB = ((1-dx) * (float) pixel(x1, y2).g) + ((dx * (float) pixel(x2, y2).g));
	bB = ((1-dx) * (float) pixel(x1, y2).b) + ((dx * (float) pixel(x2, y2).b));

	newPix.r = (rA * (1-dy)) + (rB * dy);
	newPix.g = (gA * (1-dy)) + (gB * dy);
	newPix.b = (bA * (1-dy)) + (bB * dy);

	return newPix;
}

Pixel32 Image32::GaussianSample(const float& x,const float& y,const float& variance,const float& radius) const
{
	return Pixel32();
}
/*
	int xMax = width();
	int yMax = height(); 

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{

			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			//Pixel Adjustments

			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;
		}
	}
*/