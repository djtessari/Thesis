#include <stdio.h>
#include <stdlib.h>
#include <Util/cmdLineParser.h>
#include <Ray/rayScene.h>
#include <Util/time.h>

void ShowUsage(const char* c){
	printf("Usage %s:\n",c);
	printf("\t --in <Ray File> --out <Output Image>\n");
	printf("\t --width <image width> --height <image height>\n");
	printf("\t --rLimit <recursion limit> --cLimit <cut-off>\n");
}

int main(int argc,char* argv[]){
	Image32 img;
	RayScene scene;
	double t;
	cmdLineString In,Out;
	cmdLineInt Width,Height,RLimit;
	cmdLineFloat CLimit;
	char* paramNames[]=			{"in",	"out",	"width",	"height",	"rLimit",	"cLimit"};
	cmdLineReadable* params[]=	{&In,	&Out,	&Width,		&Height,	&RLimit,	&CLimit};


	cmdLineParse(argc-1,&argv[1],paramNames,6,params);
	if(!In.set || !Out.set || !Width.set || !Height.set || !RLimit.set || !CLimit.set){
		ShowUsage(argv[0]);
		return EXIT_FAILURE;
	}

	scene.read(In.value);
	scene.camera->aspectRatio=(float)Width.value/(float)Height.value;
	scene.group->setBoundingBox();
	
	t=GetTime();
	scene.RayTrace(Width.value,Height.value,RLimit.value,CLimit.value,img);
	printf("Ray Tracing Time: %f\n",GetTime()-t);

	img.WriteImage(Out.value);

	return EXIT_SUCCESS;
}
