#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raySphere.h"
#include "rayScene.h"

RaySphere::RaySphere(void){
	center=Point3D(0,0,0);
	radius=0;
	material=NULL;
}
int RaySphere::read(FILE* fp,int* index){
	if(fscanf(fp," %d %lg %lg %lg %lg",index,
		&(center[0]),&(center[1]),&(center[2]), &radius) != 5){ 
		fprintf(stderr, "Failed to parse shape_sphere for Sphere\n"); 
		return 0;
	}
	return 1;
}
void  RaySphere::write(int indent,FILE* fp){
	int i;
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"#shape_sphere %d\n",material->index);
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg %lg\n",center[0],center[1],center[2]);
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg\n",radius);
}
void RaySphere::setUpOpenGL(int cplx,int setCallList){
	openGLComplexity=cplx;
	openGLCallListID=0;
}
