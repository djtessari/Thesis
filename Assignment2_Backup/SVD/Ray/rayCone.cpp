#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayCone.h"
#include "rayScene.h"


RayCone::RayCone(void){
	center=Point3D(0,0,0);
	height=radius=0;
	material=NULL;
}
int RayCone::read(FILE* fp,int* index){
	if(fscanf(fp," %d %lg %lg %lg %lg %lg",index,
		&(center[0]),&(center[1]),&(center[2]),
		&radius,&height) != 6){
		fprintf(stderr, "Failed to parse shape_cone for Cone\n"); 
		return 0;
	}
	return 1;
}

void  RayCone::write(int indent,FILE* fp){
	int i;
	
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"#shape_cone %d\n",material->index);
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg %lg\n",center[0],center[1],center[2]);
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg\n",radius,height);
}
void RayCone::setUpOpenGL(int cplx,int setCallList){
	openGLComplexity=cplx;
	openGLCallListID=0;
}

