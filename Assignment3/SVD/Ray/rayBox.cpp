#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayBox.h"
#include "rayScene.h"

RayBox::RayBox(void){
	center=Point3D();
	length=Point3D();
	material=NULL;
}
int RayBox::read(FILE* fp,int* index){
	if(fscanf(fp," %d %lg %lg %lg %lg %lg %lg",index,
		&(center[0]),&(center[1]),&(center[2]),
		&(length[0]),&(length[1]),&(length[2])) != 7){
		fprintf(stderr, "Failed to parse shape_box for Box\n"); 
		return 0;
	}
	return 1;
}
void  RayBox::write(int indent,FILE* fp){
	int i;
	
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"#shape_box %d\n",material->index);
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg %lg\n",center[0],center[1],center[2]);
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg %lg\n",length[0],length[1],length[2]);
}

void RayBox::setUpOpenGL(int cplx,int setCallList){
	openGLComplexity=cplx;
	openGLCallListID=0;
}
