#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"

RayTriangle::RayTriangle(void){
	v[0]=v[1]=v[2]=NULL;
	material=NULL;
}
int RayTriangle::read(FILE* fp,int* index,RayVertex* vList,int vSize){
	int v1,v2,v3;
	if(fscanf(fp," %d %d %d %d",index,&v1,&v2,&v3) != 4){
		fprintf(stderr, "Failed to parse shape_triangle for Triangle\n"); 
		return 0;
	}
	if(v1<0 || v1>=vSize || v2<0 || v2>=vSize || v3<0 || v3>=vSize){
		fprintf(stderr, "Vertex index not within bounds for Triangle\n");
		return 0;
	}
	if(v1==v2 || v1==v3 || v2==v3){
		fprintf(stderr,"Vertices must be distinct in Triangle (%d %d %d)\n",v1,v2,v3);
		return 0;
	}
	v[0]=&(vList[v1]);
	v[1]=&(vList[v2]);
	v[2]=&(vList[v3]);

	initialize();
	return 1;
}

void  RayTriangle::write(int indent,FILE* fp){
	int i;
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"#shape_triangle %d\n",material->index);
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %d %d %d\n",v[0]->index,v[1]->index,v[2]->index);
}

void RayTriangle::setUpOpenGL(int cplx,int setCallList){
	openGLComplexity=cplx;
	openGLCallListID=0;
}
