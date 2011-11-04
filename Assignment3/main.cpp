#include <stdio.h>
#include <stdlib.h>
#include <Util/cmdLineParser.h>
#include <Ray/rayScene.h>
#include <Ray/rayWindow.h>
#include <Util/time.h>

static int DEFAULT_COMPLEXITY=10;
static int DEFAULT_RESOLUTION=500;

void ShowUsage(const char* c){
	printf("Usage %s:\n",c);
	printf("\t --in <Ray File>\n");
	printf("\t [--width <image width=%d>] [--height <image height=%d>]\n",DEFAULT_RESOLUTION,DEFAULT_RESOLUTION);
	printf("\t [--cplx <complexity=%d>]\n",DEFAULT_COMPLEXITY);
}

int main(int argc,char* argv[]){
	RayScene scene;
	int cplx=DEFAULT_COMPLEXITY;
	int width=DEFAULT_RESOLUTION;
	int height=DEFAULT_RESOLUTION;

	cmdLineString In;
	cmdLineInt Width,Height,Complexity;
	char* paramNames[]=			{"in",	"width",	"height",	"cplx"};
	cmdLineReadable* params[]=	{&In,	&Width,		&Height,	&Complexity};


	cmdLineParse(argc-1,&argv[1],paramNames,4,params);
	if(!In.set){
		ShowUsage(argv[0]);
		return EXIT_FAILURE;
	}
	if(Complexity.set){cplx=Complexity.value;}
	if(Width.set){width=Width.value;}
	if(Height.set){height=Height.value;}

	scene.read(In.value);
	RayWindow::RayView(&scene,width,height,cplx);

	return EXIT_SUCCESS;
}