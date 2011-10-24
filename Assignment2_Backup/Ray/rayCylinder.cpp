#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayCylinder.h"
#include "rayScene.h"


RayCylinder::RayCylinder(void){
	center=Point3D(0,0,0);
	height=radius=0;
	material=NULL;
}
int RayCylinder::read(FILE* fp,int* index){
	if(fscanf(fp," %d %lg %lg %lg %lg %lg",index,
		&(center[0]),&(center[1]),&(center[2]),
		&radius,&height) != 6){
		fprintf(stderr, "Failed to parse shape_cylinder for Cylinder\n"); 
		return 0;
	}
	return 1;
}

void  RayCylinder::write(int indent,FILE *fp){
	int i;
	
	for(i=0;i<indent;i++){fprintf(fp," ");}
	
	fprintf(fp,"#shape_cylinder %d\n",material->index);
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg %lg\n",center[0],center[1],center[2]);
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg\n",radius,height);
}

void RayCylinder::setUpOpenGL(int cplx,int setCallList){
	openGLComplexity=cplx;
	openGLCallListID=0;
}
