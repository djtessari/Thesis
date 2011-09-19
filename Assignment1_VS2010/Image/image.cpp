#include <string.h>
#include <stdlib.h>
#include "image.h"
#include <Util/cmdLineParser.h>
#include <Image/bmp.h>
#include <Image/jpeg.h>



Pixel::Pixel(void){
	r=g=b=0;
	a=1;
}

Pixel32::Pixel32(void){
	r=g=b=0;
	a=255;
}

Image32::Image32(void){
	w=h=0;
	pixels=NULL;
}
Image32::~Image32(void){
	if(pixels){delete[] pixels;}
	pixels=NULL;
	w=h=0;
}
int Image32::setSize(const int& width,const int& height){
	if(w!=width || h!=height){
		if(pixels){delete[] pixels;}
		pixels=NULL;
		w=h=0;
		if(!width*height){return 0;}
		pixels=new Pixel32[width*height];
		if(!pixels){
			fprintf(stderr,"Failed to allocate memory for image: %dx%d\n",width,height);
			exit(0);
		}
	}
	w=width;
	h=height;
	memset(pixels,0,sizeof(Pixel32)*w*h);
	return width*height;
}
Image32& Image32::operator = (const Image32& img){
	setSize(img.width(),img.height());
	memcpy(pixels,img.pixels,sizeof(Pixel32)*w*h);
	return *this;
}

Pixel32& Image32::operator() (const int& x,const int& y){
	if(x<0 || x>=w || y<0 || y>=h){
		fprintf(stderr,"Pixel index out of range: (%d,%d) not in [0,%d]x[0,%d]\n",x,y,w,h);
		exit(0);
	}
	return pixels[x+y*w];
}
const Pixel32& Image32::operator() (const int& x,const int& y) const{
	if(x<0 || x>=w || y<0 || y>=h){
		fprintf(stderr,"Pixel index out of range: (%d,%d) not in [0,%d]x[0,%d]\n",x,y,w,h);
		exit(0);
	}
	return pixels[x+y*w];
}
Pixel32& Image32::pixel(const int& x,const int& y){
	if(x<0 || x>=w || y<0 || y>=h){
		fprintf(stderr,"Pixel index out of range: (%d,%d) not in [0,%d]x[0,%d]\n",x,y,w,h);
		exit(0);
	}
	return pixels[x+y*w];
}
const Pixel32& Image32::pixel(const int& x,const int& y) const{
	if(x<0 || x>=w || y<0 || y>=h){
		fprintf(stderr,"Pixel index out of range: (%d,%d) not in [0,%d]x[0,%d]\n",x,y,w,h);
		exit(0);
	}
	return pixels[x+y*w];
}
int Image32::width(void) const {return w;}
int Image32::height(void) const {return h;}

int Image32::BeierNeelyMorph(const Image32& source,const Image32& destination,const OrientedLineSegmentPairs& olsp,const float& timeStep,Image32& outputImage){
	OrientedLineSegmentPairs olsp1,olsp2;
	OrientedLineSegment ols;
	Image32 temp1,temp2;
	int i;

	// Generate the in-between line segment pairs
	if(!olsp1.setCount(olsp.count) || !olsp2.setCount(olsp.count)){return 0;}
	for(i=0;i<olsp.count;i++){
		olsp1.segments1[i]=olsp.segments1[i];
		olsp2.segments1[i]=olsp.segments2[i];
		OrientedLineSegment::Blend(olsp.segments1[i],olsp.segments2[i],timeStep,ols);
		olsp1.segments2[i]=ols;
		olsp2.segments2[i]=ols;
	}

	// Generate the in-between morphs
	if(!source.Warp(olsp1,temp1) || !destination.Warp(olsp2,temp2)){return 0;}

	// Cross-dissolve to get the final image
	return CrossDissolve(temp1,temp2,timeStep,outputImage);
}
int Image32::ReadImage(char* fileName){
	char* ext=GetFileExtension(fileName);
	int ret=0;
	if(!strcasecmp(ext,"bmp")){ret=BMPReadImage(fileName,*this);}
	else if(!strcasecmp(ext,"jpg") || !strcasecmp(ext,"jpeg")){ret=JPEGReadImage(fileName,*this);}
	else {};	// Unknown format
	delete[] ext;
	return ret;
}
int Image32::WriteImage(char* fileName){
	char* ext=GetFileExtension(fileName);
	int ret=0;
	if(!(width()*height())){
		delete[] ext;
		return 0;
	}
	if(!strcasecmp(ext,"bmp")){ret=BMPWriteImage(*this,fileName);}
	else if(!strcasecmp(ext,"jpg") || !strcasecmp(ext,"jpeg")){ret=JPEGWriteImage(*this,fileName);}
	else {};	// Unknown format
	delete[] ext;
	return ret;
}
