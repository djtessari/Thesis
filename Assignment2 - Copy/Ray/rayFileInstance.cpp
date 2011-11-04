#include <stdio.h>
#include <stdlib.h>
#include "rayFileInstance.h"

RayFileInstance::RayFileInstance(RayFile* rf){
	rayFile=rf;
}
void  RayFileInstance::write(int indent,FILE* fp){
	int i;
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"#ray_file_instance %d\n",rayFile->index);
}
double RayFileInstance::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	return rayFile->scene->group->intersect(ray,iInfo,mx);
}

BoundingBox3D RayFileInstance::setBoundingBox(void){
	bBox=rayFile->scene->group->setBoundingBox();
	return bBox;
}

int RayFileInstance::isStatic(void){return rayFile->scene->group->isStatic();}

void RayFileInstance::setUpOpenGL(int cplx,int setCallList){
	openGLComplexity=cplx;
	openGLCallListID=0;
}

int RayFileInstance::drawOpenGL(int materialIndex){return rayFile->scene->group->drawOpenGL(materialIndex);}
