#include <stdio.h>
#include <stdlib.h>

#include "Image/bmp.h"
#include "Image/jpeg.h"
#include "Image/image.h"
#include "Util/cmdLineParser.h"

void ShowUsage(char* ex){
	printf("Usage %s:\n",ex);
	printf("\t--in <input image> --out <output image>\n");
	printf("\t[--noisify        <size of noise>]\n");
	printf("\t[--brighten       <brightening factor>]\n");
	printf("\t[--gray]\n");
	printf("\t[--contrast       <contrast factor]\n");
	printf("\t[--saturate       <saturation factor>]\n");
	printf("\t[--quantize       <bits per channel>]\n");
	printf("\t[--rDither        <bits per channel with random dithering>]\n");
	printf("\t[--oDither2x2     <bits per channel with ordered dithering>]\n");
	printf("\t[--fsDither       <bits per channel with Floyd-Steinberg dithering>]\n");
	printf("\t[--composite      <overlay image> <matte image>\n");
	printf("\t[--bnMorph        <destination image> <line segment pair list> <time step>\n");
	printf("\t[--crop           <x1> <y1> <x2> <y2>\n");
	printf("\t[--scaleNearest   <scale factor>\n");
	printf("\t[--scaleBilinear  <scale factor>\n");
	printf("\t[--scaleGaussian  <scale factor>\n");
	printf("\t[--rotateNearest  <angle>\n");
	printf("\t[--rotateBilinear <angle>\n");
	printf("\t[--rotateGaussian <angle>\n");
	printf("\t[--blur3x3]\n");
	printf("\t[--edges3x3]\n");
	printf("\t[--fun]\n");
}
int ReadImage(char* fileName,Image32& img){
	char* ext=GetFileExtension(fileName);
	int ret=0;
	if(!strcasecmp(ext,"bmp")){ret=BMPReadImage(fileName,img);}
	else if(!strcasecmp(ext,"jpg") || !strcasecmp(ext,"jpeg")){ret=JPEGReadImage(fileName,img);}
	else {};	// Unknown format
	delete[] ext;
	return ret;
}
int WriteImage(char* fileName,Image32& img){
	char* ext=GetFileExtension(fileName);
	int ret=0;
	if(!(img.width()*img.height())){
		delete[] ext;
		return 0;
	}
	if(!strcasecmp(ext,"bmp")){ret=BMPWriteImage(img,fileName);}
	else if(!strcasecmp(ext,"jpg") || !strcasecmp(ext,"jpeg")){ret=JPEGWriteImage(img,fileName);}
	else {};	// Unknown format
	delete[] ext;
	return ret;
}

int main(int argc,char* argv[]){
	Image32 inImage,outImage;

	cmdLineString In,Out;
	cmdLineFloat RandomNoise,Brightness,Contrast,Saturation,ScaleNearest,ScaleBilinear,ScaleGaussian,RotateNearest,RotateBilinear,RotateGaussian;
	cmdLineInt Quantize,RDither,ODither2X2,FSDither;
	cmdLineStringArray Composite(2),BNMorph(3);
	cmdLineIntArray Crop(4);
	cmdLineReadable Gray,Blur3X3,Edges3X3,Fun;

	char* paramNames[]={
		"in","out",
		"noisify","brighten","gray","contrast","saturate",
		"quantize","rDither","oDither2x2","fsDither",
		"blur3x3","edges3x3",
		"composite",
		"scaleNearest","scaleBilinear","scaleGaussian",
		"rotateNearest","rotateBilinear","rotateGaussian",
		"fun","crop",
		"bnMorph"
	};
	cmdLineReadable* params[]=
	{
		&In,&Out,
		&RandomNoise,&Brightness,&Gray,&Contrast,&Saturation,
		&Quantize,&RDither,&ODither2X2,&FSDither,
		&Blur3X3,&Edges3X3,
		&Composite,
		&ScaleNearest,&ScaleBilinear,&ScaleGaussian,
		&RotateNearest,&RotateBilinear,&RotateGaussian,
		&Fun,&Crop,
		&BNMorph,
	};
	cmdLineParse(argc-1,&argv[1],paramNames,sizeof(paramNames)/sizeof(char*),params);

	// Check that the input and output files have been set
	if(!In.set || !Out.set){
		if(!In.set)	{printf("Input image was not set\n");}
		else		{printf("Output image was not set\n");}
		ShowUsage(argv[0]);
		return EXIT_FAILURE;
	}

	// Try to read in the input image
	if(!ReadImage(In.value,inImage)){
		printf("Could not read image: %s\n",In.value);
		return EXIT_FAILURE;
	}
	printf("Input dimensions: %dx%d\n",inImage.width(),inImage.height());

	outImage = inImage;

	// Filter the image
	if(RandomNoise.set){
		if(!inImage.AddRandomNoise(RandomNoise.value,outImage)){
			printf("Could not add noise to the image\n");
		}
	}
	if(Brightness.set){
		if(!inImage.Brighten(Brightness.value,outImage)){
			printf("Could not change the brightness of the image\n");
		}
	}
	if(Gray.set){
		if(!inImage.Luminance(outImage)){
			printf("Could not compute a luminance image\n");
		}
	}
	if(Contrast.set){
		if(!inImage.Contrast(Contrast.value,outImage)){
			printf("Could not change the contrast of the image\n");
		}
	}
	if(Saturation.set){
		if(!inImage.Saturate(Saturation.value,outImage)){
			printf("Could not change saturation of the image\n");
		}
	}
	if(Quantize.set){
		if(!inImage.Quantize(Quantize.value,outImage)){
			printf("Could not change the number of bits per channel (quanitzation)\n");
		}
	}

	if(RDither.set){
		if(!inImage.RandomDither(RDither.value,outImage)){
			printf("Could not change the number of bits per channel (random dither)\n");
		}
	}
	if(Composite.set){
		Image32 overlay,matte;
		// Read in the target image
		if(!ReadImage(Composite.value[0],overlay)){
			printf("Could not read overlay image for compositing: %s\n",Composite.value[0]);
		}
		// Read in the matte image
		else  if(!ReadImage(Composite.value[1],matte)){
			printf("Could not read matte image for compositing: %s\n",Composite.value[1]);
		}
		// Set the alpha value of the overlay image using the values of the matte image
		else if(!overlay.SetAlpha(matte)){
			printf("could not use matte to set the alpha value\n");
		}
		// Perform the compositing
		else if(!inImage.Composite(overlay,outImage)){
			printf("Could not composite images\n");
		}
	}
	if(Blur3X3.set){
		if(!inImage.Blur3X3(outImage)){
			printf("Could not blur the image\n");
		}
	}
	if(Edges3X3.set){
		if(!inImage.EdgeDetect3X3(outImage)){
			printf("Could not detect the edges of the image\n");
		}
	}
	if(ODither2X2.set){
		if(!inImage.OrderedDither2X2(ODither2X2.value,outImage)){
			printf("Could not change the number of bits per channel (ordered dither)\n");
		}
	}
	if(FSDither.set){
		if(!inImage.FloydSteinbergDither(FSDither.value,outImage)){
			printf("Could not change the number of bits per channel (Floyd-Steinberg dither)\n");
		}
	}
	if(ScaleNearest.set){
		if(!inImage.ScaleNearest(ScaleNearest.value,outImage)){
			printf("Could not scale the image\n");
		}
	}
	if(ScaleBilinear.set){
		if(!inImage.ScaleBilinear(ScaleBilinear.value,outImage)){
			printf("Could not scale the image\n");
		}
	}
	if(ScaleGaussian.set){
		if(!inImage.ScaleGaussian(ScaleGaussian.value,outImage)){
			printf("Could not scale the image\n");
		}
	}
	if(RotateNearest.set){
		if(!inImage.RotateNearest(RotateNearest.value,outImage)){
			printf("Could not rotate the image\n");
		}
	}
	if(RotateBilinear.set){
		if(!inImage.RotateBilinear(RotateBilinear.value,outImage)){
			printf("Could not rotate the image\n");
		}
	}
	if(RotateGaussian.set){
		if(!inImage.RotateGaussian(RotateGaussian.value,outImage)){
			printf("Could not rotate the image\n");
		}
	}

	if(Fun.set){
		if(!inImage.FunFilter(outImage)){
			printf("Could not apply a fun filter to the image\n");
		}
	}
	if(Crop.set){
		if(!inImage.Crop(Crop.value[0],Crop.value[1],Crop.value[2],Crop.value[3],outImage)){
			printf("Could not crop the image\n");
		}
	}

	if(BNMorph.set){
		float timeStep=(float)atof(BNMorph.value[2]);
		Image32 dest;
		OrientedLineSegmentPairs olsp;

		// Read the destination image
		if(!ReadImage(BNMorph.value[0],dest)){
			printf("Could not read destination image for morph: %s\n",BNMorph.value[0]);
		}
		// Read in the list of corresponding line segments
		else if(!olsp.read(BNMorph.value[1])){
			printf("Could not read in oriented line segment pairs from: %s\n",BNMorph.value[1]);
		}
		// Perform the morph
		else if(!Image32::BeierNeelyMorph(inImage,dest,olsp,timeStep,outImage)){
			printf("Could not morph images\n");
		}
	}


	printf("Output dimensions: %dx%d\n",outImage.width(),outImage.height());
	// Try to write out the output image
	if(!WriteImage(Out.value,outImage)){
		printf("Could not write image: %s\n",Out.value);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
