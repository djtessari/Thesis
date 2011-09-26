#include "image.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

// allows the use of min() and max() functions
#include <algorithm>

#define e 2.7182818284590452353
using namespace std;


Pixel::Pixel(const Pixel32& p)
{
}

Pixel32::Pixel32(const Pixel& p)
{
}

//Current points - 28 (26?)

//COMPLETE - 1
int Image32::AddRandomNoise(const float& noise,Image32& outputImage) const
{

	int xMax = width();
	int yMax = height();
	srand(time(NULL));

	for (int i = 0; i < xMax; i++)
	{

		for (int j = 0; j < yMax; j++)
		{

			float rN = (( (rand() % 511) - 255) * noise);
			float gN = (( (rand() % 511) - 255) * noise);
			float bN = (( (rand() % 511) - 255) * noise);

			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;

			r+=rN;
			g+=gN;
			b+=bN;

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

//COMPLETE - 1
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

//COMPLETE - 1
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

//COMPLETE - 1
int Image32::Contrast(const float& contrast,Image32& outputImage) const
{
	int xMax = width();
	int yMax = height(); 

	float lum = 0;

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{

			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;

			lum+= (0.3*r) + (0.59*g) + (0.11*b);
		}
	}

	lum = lum / (xMax * yMax);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;

			//Pixel Adjustments
			r = (1 - contrast)*lum + (contrast * (float) pixel(i,j).r);
			g = (1 - contrast)*lum + (contrast * (float) pixel(i,j).g);
			b = (1 - contrast)*lum + (contrast * (float) pixel(i,j).b);

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

//COMPLETE - 1
int Image32::Saturate(const float& saturation,Image32& outputImage) const
{
	int xMax = width();
	int yMax = height(); 

	Luminance(outputImage);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;

			//Pixel Adjustments
			r = (1 - saturation)*r + (saturation * (float) pixel(i,j).r);
			g = (1 - saturation)*g + (saturation * (float) pixel(i,j).g);
			b = (1 - saturation)*b + (saturation * (float) pixel(i,j).b);

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

//COMPLETE - 2
int Image32::Quantize(const int& bits,Image32& outputImage) const
{

	int xMax = width();
	int yMax = height(); 
	float power = pow(2.0,bits);
	float multiply = floor(256 / (power-1));
	printf("Multiply = %f\n", multiply);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{

			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			//Pixel Adjustments
			r = floor(floor( (r * (pow(2.0, bits))) / 256 ) * multiply);
			g = floor(floor( (g * (pow(2.0, bits))) / 256 ) * multiply);
			b = floor(floor( (b * (pow(2.0, bits))) / 256 ) * multiply);

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

//COMPLETE - 2
int Image32::RandomDither(const int& bits,Image32& outputImage) const
{
	float noise = 1.0;
	noise = noise / (pow(2.0,bits));

	AddRandomNoise(noise, outputImage);
	Quantize(bits, outputImage);
	
	return 1;
}

//COMPLETE - 2
int Image32::OrderedDither2X2(const int& bits,Image32& outputImage) const
{
	int xMax = width();
	int yMax = height(); 
	float power = pow(2.0,bits);
	float multiply = floor(256 / (power-1));
	double n = 2;
	int d[2][2] = {{1, 3}, {4, 2}};

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			int x = (int) (i % (int) n);
			int y = (int) (j % (int) n);

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

			if (rE > (d[x][y] / (pow(n, 2)+1))) r = ceil(rC) * multiply;
			else r = floor(rC) * multiply;
			if (gE > (d[x][y] / (pow(n, 2)+1))) g = ceil(gC) * multiply;
			else g = floor(gC) * multiply;
			if (bE > (d[x][y] / (pow(n, 2)+1))) b = ceil(bC) * multiply;
			else b = floor(bC) * multiply;



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

//COMPLETE - 2
int Image32::FloydSteinbergDither(const int& bits,Image32& outputImage) const
{
	int xMax = width();
	int yMax = height(); 
	float power = pow(2.0,bits);
	float multiply = floor(256 / (power-1));
	printf("Multiply = %f\n", multiply);

	float err1 = 0.4375;
	float err2 = 0.1875;
	float err3 = 0.3125;
	float err4 = 0.0625;
	printf("Err1 = %f\n", err1);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{

			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			//Quantize
			r = floor(floor( (r * (pow(2.0, bits))) / 256 ) * multiply);
			g = floor(floor( (g * (pow(2.0, bits))) / 256 ) * multiply);
			b = floor(floor( (b * (pow(2.0, bits))) / 256 ) * multiply);

			float errorR = (float) newPix.r - r;
			float errorG = (float) newPix.g - g;
			float errorB = (float) newPix.b - b;

			int xLow = i - 1;
			int xHigh = i + 1;
			int yHigh = j + 1;

			if (xLow < 0) xLow = 0;
			if (xHigh >= xMax) xHigh = xMax-1;
			if (yHigh >= yMax) yHigh = yMax-1;

			Pixel32& pix1 = outputImage.pixel(xHigh, j);
			Pixel32& pix2 = outputImage.pixel(xLow, yHigh);
			Pixel32& pix3 = outputImage.pixel(i, yHigh);
			Pixel32& pix4 = outputImage.pixel(xHigh, yHigh);

			float r1 = (float) pix1.r;
			float r2 = (float) pix2.r;
			float r3 = (float) pix3.r;
			float r4 = (float) pix4.r;

			float g1 = (float) pix1.g;
			float g2 = (float) pix2.g;
			float g3 = (float) pix3.g;
			float g4 = (float) pix4.g;

			float b1 = (float) pix1.b;
			float b2 = (float) pix2.b;
			float b3 = (float) pix3.b;
			float b4 = (float) pix4.b;

			r1 += errorR*err1;
			r2 += errorR*err2;
			r3 += errorR*err3;
			r4 += errorR*err4;

			g1 += errorG*err1;
			g2 += errorG*err2;
			g3 += errorG*err3;
			g4 += errorG*err4;

			b1 += errorB*err1;
			b2 += errorB*err2;
			b3 += errorB*err3;
			b4 += errorB*err4;
			

			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			if (r1 > 255) r1 = 255;
			if (r1 < 0) r1 = 0;
			if (g1 > 255) g1 = 255;
			if (g1 < 0) g1 = 0;
			if (b1 > 255) b1 = 255;
			if (b1 < 0) b1 = 0;

			if (r2 > 255) r2 = 255;
			if (r2 < 0) r2 = 0;
			if (g2 > 255) g2 = 255;
			if (g2 < 0) g2 = 0;
			if (b2 > 255) b2 = 255;
			if (b2 < 0) b2 = 0;

			if (r3 > 255) r3 = 255;
			if (r3 < 0) r3 = 0;
			if (g3 > 255) g3 = 255;
			if (g3 < 0) g3 = 0;
			if (b3 > 255) b3 = 255;
			if (b3 < 0) b3 = 0;

			if (r4 > 255) r4 = 255;
			if (r4 < 0) r4 = 0;
			if (g4 > 255) g4 = 255;
			if (g4 < 0) g4 = 0;
			if (b4 > 255) b4 = 255;
			if (b4 < 0) b4 = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;

			pix1.r = r1;
			pix1.g = g1;
			pix1.b = b1;

			pix2.r = r2;
			pix2.g = g2;
			pix2.b = b2;

			pix3.r = r3;
			pix3.g = g3;
			pix3.b = b3;

			pix4.r = r4;
			pix4.g = g4;
			pix4.b = b4;
		}
	}
	return 1;
}

//COMPLETE - 2
int Image32::Blur3X3(Image32& outputImage) const
{
	int xMax = width();
	int yMax = height(); 

	float mask[3][3]= {
		{0.0625, 0.125, 0.0625},
		{0.125, 0.25, 0.125},
		{0.0625, 0.125, 0.0625}};

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32& newPix = outputImage.pixel(i,j);
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
					int xPos = i-1+x;
					int yPos = j-1+y;

					if (xPos < 0)
					{
						xPos = 0;
					}
					if (xPos >= xMax)
					{
						xPos = xMax-1;
					}

					if (yPos < 0)
					{
						yPos = 0;
					}
					if (yPos >= yMax)
					{
						yPos = yMax-1;
					}
					//printf("xPos = %i, yPos = %i\n", xPos, yPos);

					newR += ( (float) pixel(xPos,yPos).r * mask[x][y]);
					newG += ( (float) pixel(xPos,yPos).g * mask[x][y]);
					newB += ( (float) pixel(xPos,yPos).b * mask[x][y]);
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
	return 1;
}

//COMPLETE - 2
int Image32::EdgeDetect3X3(Image32& outputImage) const
{
		int xMax = width();
	int yMax = height(); 

	float mask[3][3]= {
		{-1, -1, -1},
		{-1, 8, -1},
		{-1, -1, -1}};

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32& newPix = outputImage.pixel(i,j);
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
					int xPos = i-1+x;
					int yPos = j-1+y;

					if (xPos < 0)
					{
						xPos = 0;
					}
					if (xPos >= xMax)
					{
						xPos = xMax-1;
					}

					if (yPos < 0)
					{
						yPos = 0;
					}
					if (yPos >= yMax)
					{
						yPos = yMax-1;
					}
					//printf("xPos = %i, yPos = %i\n", xPos, yPos);

					newR += ( (float) pixel(xPos,yPos).r * mask[x][y]);
					newG += ( (float) pixel(xPos,yPos).g * mask[x][y]);
					newB += ( (float) pixel(xPos,yPos).b * mask[x][y]);
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
	return 1;
}

//COMPLETE - 1
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

//COMPLETE - 1
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

//COMPLETE (?) - 1
int Image32::ScaleGaussian(const float& scaleFactor,Image32& outputImage) const
{
	float var = 1;
	float rad = 1;

	int xMax = width() * scaleFactor;
	int yMax = height() * scaleFactor; 
	outputImage.setSize(xMax, yMax);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);
			
			//Pixel Adjustments
			newPix = GaussianSample(i / scaleFactor, j / scaleFactor, var, rad);
		}
	}
	return 1;
}

//COMPLETE - 2
int Image32::RotateNearest(const float& angle,Image32& outputImage) const
{
	float xMax = width() / 2;
	float yMax = height() / 2; 

	//x = ucost - vsint
	//y = usint + vcost
	float a = (angle * PI/180);

	//determine new size of image
	float xCenter = width() / 2;
	float yCenter = height() / 2;

	//(0,0)
	xMax = max(xMax, ((-1)*xCenter*cos(a) - (-1)*yCenter*sin(a)));
	yMax = max(yMax, ((-1)*xCenter*sin(a) + (-1)*yCenter*cos(a))); 

	//(0,h)
	xMax = max(xMax, ((-1)*xCenter*cos(a) - yCenter*sin(a)));
	yMax = max(yMax, ((-1)*xCenter*sin(a) + yCenter*cos(a))); 

	//(w,0)
	xMax = max(xMax, (xCenter*cos(a) - (-1)*yCenter*sin(a)));
	yMax = max(yMax, (xCenter*sin(a) + (-1)*yCenter*cos(a))); 

	//(w,h)
	xMax = max(xMax, (xCenter*cos(a) - yCenter*sin(a)));
	yMax = max(yMax, (xCenter*sin(a) + yCenter*cos(a)));

	xMax=ceil(xMax * 2);
	yMax=ceil(yMax * 2);
	outputImage.setSize(xMax, yMax);

	printf("xMax = %f, yMax = %f\n",xMax, yMax);
	int xTrans = (xMax - width()) / 2;
	int yTrans = (yMax - height()) / 2;

	xCenter = xMax / 2;
	yCenter = yMax / 2;

	printf("xCenter = %f, yCenter = %f\n",xCenter, yCenter);
	printf("xTrans = %i, yTrans = %i\n", xTrans, yTrans);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);

			//x = ucost - vsint
			//y = usint + vcost

			float sampleX = ((i - xCenter)*cos(a) - (j - yCenter)*sin(a))+xCenter-xTrans;
			float sampleY = ((i - xCenter)*sin(a) + (j - yCenter)*cos(a))+yCenter-yTrans;
			
			if (sampleX < 0 || sampleX > width()-1 || sampleY < 0 || sampleY > height()-1){
				newPix.a = 0;
			}			
			//Pixel Adjustments
			else	newPix = NearestSample(sampleX, sampleY);
		}
	}
	return 1;
}

//COMPELTE - 2
int Image32::RotateBilinear(const float& angle,Image32& outputImage) const
{
	float xMax = width() / 2;
	float yMax = height() / 2; 

	//x = ucost - vsint
	//y = usint + vcost
	float a = (angle * PI/180);

	//determine new size of image
	float xCenter = width() / 2;
	float yCenter = height() / 2;

	//(0,0)
	xMax = max(xMax, ((-1)*xCenter*cos(a) - (-1)*yCenter*sin(a)));
	yMax = max(yMax, ((-1)*xCenter*sin(a) + (-1)*yCenter*cos(a))); 

	//(0,h)
	xMax = max(xMax, ((-1)*xCenter*cos(a) - yCenter*sin(a)));
	yMax = max(yMax, ((-1)*xCenter*sin(a) + yCenter*cos(a))); 

	//(w,0)
	xMax = max(xMax, (xCenter*cos(a) - (-1)*yCenter*sin(a)));
	yMax = max(yMax, (xCenter*sin(a) + (-1)*yCenter*cos(a))); 

	//(w,h)
	xMax = max(xMax, (xCenter*cos(a) - yCenter*sin(a)));
	yMax = max(yMax, (xCenter*sin(a) + yCenter*cos(a)));

	xMax=ceil(xMax * 2);
	yMax=ceil(yMax * 2);
	outputImage.setSize(xMax, yMax);

	printf("xMax = %f, yMax = %f\n",xMax, yMax);
	int xTrans = (xMax - width()) / 2;
	int yTrans = (yMax - height()) / 2;

	xCenter = xMax / 2;
	yCenter = yMax / 2;

	printf("xCenter = %f, yCenter = %f\n",xCenter, yCenter);
	printf("xTrans = %i, yTrans = %i\n", xTrans, yTrans);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);

			//x = ucost - vsint
			//y = usint + vcost

			float sampleX = ((i - xCenter)*cos(a) - (j - yCenter)*sin(a))+xCenter-xTrans;
			float sampleY = ((i - xCenter)*sin(a) + (j - yCenter)*cos(a))+yCenter-yTrans;
			
			if (sampleX < 0 || sampleX > width()-1 || sampleY < 0 || sampleY > height()-1){
				newPix.a = 0;
			}			
			//Pixel Adjustments
			else	newPix = BilinearSample(sampleX, sampleY);
		}
	}
	return 1;
}
	
//COMPLETE (?) - 2
int Image32::RotateGaussian(const float& angle,Image32& outputImage) const
{
	float xMax = width() / 2;
	float yMax = height() / 2; 

	float var = 1;
	float rad = 1;

	//x = ucost - vsint
	//y = usint + vcost
	float a = (angle * PI/180);

	//determine new size of image
	float xCenter = width() / 2;
	float yCenter = height() / 2;

	//(0,0)
	xMax = max(xMax, ((-1)*xCenter*cos(a) - (-1)*yCenter*sin(a)));
	yMax = max(yMax, ((-1)*xCenter*sin(a) + (-1)*yCenter*cos(a))); 

	//(0,h)
	xMax = max(xMax, ((-1)*xCenter*cos(a) - yCenter*sin(a)));
	yMax = max(yMax, ((-1)*xCenter*sin(a) + yCenter*cos(a))); 

	//(w,0)
	xMax = max(xMax, (xCenter*cos(a) - (-1)*yCenter*sin(a)));
	yMax = max(yMax, (xCenter*sin(a) + (-1)*yCenter*cos(a))); 

	//(w,h)
	xMax = max(xMax, (xCenter*cos(a) - yCenter*sin(a)));
	yMax = max(yMax, (xCenter*sin(a) + yCenter*cos(a)));

	xMax=ceil(xMax * 2);
	yMax=ceil(yMax * 2);
	outputImage.setSize(xMax, yMax);

	printf("xMax = %f, yMax = %f\n",xMax, yMax);
	int xTrans = (xMax - width()) / 2;
	int yTrans = (yMax - height()) / 2;

	xCenter = xMax / 2;
	yCenter = yMax / 2;

	printf("xCenter = %f, yCenter = %f\n",xCenter, yCenter);
	printf("xTrans = %i, yTrans = %i\n", xTrans, yTrans);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{
			Pixel32 &newPix = outputImage.pixel(i, j);

			//x = ucost - vsint
			//y = usint + vcost

			float sampleX = ((i - xCenter)*cos(a) - (j - yCenter)*sin(a))+xCenter-xTrans;
			float sampleY = ((i - xCenter)*sin(a) + (j - yCenter)*cos(a))+yCenter-yTrans;
			
			if (sampleX < 0 || sampleX > width()-1 || sampleY < 0 || sampleY > height()-1){
				newPix.a = 0;
			}			
			//Pixel Adjustments
			else	newPix = GaussianSample(sampleX, sampleY, var, rad);
		}
	}
	return 1;
}

//Not Started - 1
int Image32::SetAlpha(const Image32& matte)
{/*
	int xMax = width();
	int yMax = height(); 

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{

			Pixel32 &newPix = pixel(i, j);
			newPix.a = matte.pixel(i,j).a;
			
			//Pixel Adjustments

			/*if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;

			newPix.r = r;
			newPix.g = g;
			newPix.b = b;
		}
	}*/
	return 0;
}

//Not Started - ^^
int Image32::Composite(const Image32& overlay,Image32& outputImage) const
{
	/*int xMax = width();
	int yMax = height(); 
	const Image32 matte = outputImage;

	overlay.SetAlpha(matte);

	for (int i = 0; i < xMax; i++)
	{
		for (int j = 0; j < yMax; j++)
		{

			Pixel32 &newPix = pixel(i, j);
			Pixel32 &overPix = overlay.pixel(i,j);
			
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;
			
			float rO = (float) overPix.r;
			float gO = (float) overPix.g;
			float bO = (float) overPix.b;
			float a = (float) overPix.a;

			r = rO + (255-a)*r;
			r = bO + (255-a)*b;
			r = gO + (255-a)*g;

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
	}*/
	return 0;
}

//Not Started - part of Bier
int Image32::CrossDissolve(const Image32& source,const Image32& destination,const float& blendWeight,Image32& ouputImage)
{
	return 0;
}

//Not Started - part of Bier
int Image32::Warp(const OrientedLineSegmentPairs& olsp,Image32& outputImage) const
{
	return 0;
}

//Not Started - 2
int Image32::FunFilter(Image32& outputImage) const
{
	/*int xMax = width();
	int yMax = height();

	float a = 30;

	int xCenter = xMax / 2;
	int yCenter = yMax / 2;

	for (int i = 0; i < xMax; i++) {
		for (int j = 0; j < yMax; j++) {

			Pixel32 &newPix = outputImage.pixel(i, j);
			float r = (float) newPix.r;
			float g = (float) newPix.g;
			float b = (float) newPix.b;

			float u = rot(dist(i,xCenter)*a);
			float v = rot(dist(j,yCenter)*a);

			newPix = BilinearSample(u,v);

		}
	}*/
		return 0;
}

//COMPLETE - 1
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
			Pixel32 &newPix = newImage->pixel(xI, yI);
			newPix = outputImage.pixel(i,j);	
			yI++;
		}
		xI++;
	}
	outputImage = *newImage;
	return 1;
}

//COMPLETE - 1
Pixel32 Image32::NearestSample(const float& x,const float& y) const
{
	int iu = floor(x+0.5);
	int iv = floor(y+0.5);
	Pixel32 returnPix = pixel(iu, iv);
	return returnPix;
}

//COMPLETE - 1
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

//Test - 1
Pixel32 Image32::GaussianSample(const float& x,const float& y,const float& variance,const float& radius) const
{
	float filterSum = 0; //Used to normalize

	Pixel32 newPix = Pixel32();

	float r = 0;
	float g = 0;
	float b = 0;

	for (int i = 0; i < (ceil(radius) * 2); i++){
		for (int j = 0; j < (ceil(radius) * 2); j++){
			
			float numer = -1 * ( pow((i-radius),2) + pow((j-radius),2));
			float denom = 2 * variance;
			float gauss = (1/sqrt(2*PI*variance)) * pow((float) e, (float) ( numer / denom));
			filterSum+=gauss;

			int xI = x - ceil(radius) + i;
			int yI = y - ceil(radius) + j;



			if (xI < 0) xI = 0;
			if (yI < 0) yI = 0;
			if (xI >= width()) xI = width()-1;
			if (yI >= height()) yI = height()-1;


			r += (gauss * floor((float) pixel(xI, yI).r) );
			g += (gauss * floor((float) pixel(xI, yI).g) );
			b += (gauss * floor((float) pixel(xI, yI).b) );

		}
	}
	float normalizer = (1 / filterSum );

	r = r * normalizer;
	g = g * normalizer;
	b = b * normalizer;


	if (r > 255) r = 255;
	if (r < 0) r = 0;
	if (g > 255) g = 255;
	if (g < 0) g = 0;
	if (b > 255) b = 255;
	if (b < 0) b = 0;

	newPix.r = r;
	newPix.g = g;
	newPix.b = b;

	return newPix;
}