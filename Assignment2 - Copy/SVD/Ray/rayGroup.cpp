#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rayGroup.h"

/////////////////
// RayShapeHit //
/////////////////
int RayShapeHit::Compare(const void* v1,const void* v2){
	RayShapeHit *i1=(RayShapeHit*)v1;
	RayShapeHit *i2=(RayShapeHit*)v2;
	if(i1->t < i2->t){return -1;}
	else if(i2->t<i1->t){return 1;}
	else{return 0;}
}
//////////////
// RayGroup //
//////////////
RayGroup::RayGroup(void){
	shapes=NULL;
	hits=NULL;
	sNum=0;
}

void RayGroup::addShape(RayShape* s){
	RayShape** tempShapes=shapes;
	shapes=new RayShape*[sNum+1];
	for(int i=0;i<sNum;i++){shapes[i]=tempShapes[i];}
	if(tempShapes){delete[] tempShapes;}
	shapes[sNum]=s;
	if(hits){delete[] hits;}
	hits=new RayShapeHit[sNum+1];

	sNum++;
}
int RayGroup::shapeNum(void){return sNum;}
void RayGroup::write(int indent,FILE* fp){
	writeBegin(indent,fp);
	for(int i=0;i<sNum;i++){shapes[i]->write(indent+2,fp);}
	writeEnd(indent,fp);
}

RayGroup::~RayGroup(void){
	for(int i=0;i<sNum;i++){if(shapes[i]){delete shapes[i];}}
	if(shapes){delete[] shapes;}
	shapes=NULL;
	if(hits){delete[] hits;}
	hits=NULL;
	sNum=0;
}
void RayGroup::setUpOpenGL(int cplx,int setCallList){
	int i,s=1;
	openGLComplexity=cplx;
	openGLCallListID=0;

	// Test if all of the child nodes are static 
	for(i=0;i<sNum;i++){if(!shapes[i]->isStatic()){s=0;}}
	for(i=0;i<sNum;i++){shapes[i]->setUpOpenGL(cplx,setCallList && (!s));}

	// If the children are all static and the setCallList flag is on, generate the call list
	if(setCallList && s){openGLCallListID=getOpenGLCallList();}
}

////////////////////
// StaticRayGroup //
////////////////////
StaticRayGroup::StaticRayGroup(void) : RayGroup(){localTransform=Matrix4D::IdentityMatrix();}

int StaticRayGroup::read(FILE* fp){
	if(fscanf(fp," %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg", 
		&(localTransform(0,0)),&(localTransform(1,0)),
		&(localTransform(2,0)),&(localTransform(3,0)),
		&(localTransform(0,1)),&(localTransform(1,1)),
		&(localTransform(2,1)),&(localTransform(3,1)),
		&(localTransform(0,2)),&(localTransform(1,2)),
		&(localTransform(2,2)),&(localTransform(3,2)),
		&(localTransform(0,3)),&(localTransform(1,3)),
		&(localTransform(2,3)),&(localTransform(3,3))) != 16){
		fprintf(stderr, "Failed to parse group_begin for StaticGroup\n"); 
		return 0;
	}
	return set();
}
int StaticRayGroup::set(Matrix4D m){
	localTransform=m;
	return set();
}

void StaticRayGroup::writeBegin(int indent,FILE* fp){
	int i;
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"#group_begin\n");

	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg %lg %lg\n",
		localTransform(0,0),localTransform(1,0),
		localTransform(2,0),localTransform(3,0));
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg %lg %lg\n",
		localTransform(0,1),localTransform(1,1),
		localTransform(2,1),localTransform(3,1));
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg %lg %lg\n",
		localTransform(0,2),localTransform(1,2),
		localTransform(2,2),localTransform(3,2));
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"  %lg %lg %lg %lg\n",
		localTransform(0,3),localTransform(1,3),
		localTransform(2,3),localTransform(3,3));
}
void StaticRayGroup::writeEnd(int indent,FILE* fp){
	int i;
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"#group_end\n");
}

int StaticRayGroup::isStatic(void){
	for(int i=0;i<sNum;i++){if(!shapes[i]->isStatic()){return 0;}}
	return 1;
}
Matrix4D StaticRayGroup::getMatrix(void){return localTransform;}
Matrix4D StaticRayGroup::getInverseMatrix(void){return inverseTransform;}
Matrix4D StaticRayGroup::getNormalMatrix(void){return normalTransform;}

//////////////////////////
// ParametrizedRayGroup //
//////////////////////////
int ParametrizedRayGroup::isStatic(void){return 0;}
void ParametrizedRayGroup::writeBegin(int indent,FILE* fp){
	for(int i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"#joint_begin %s\n",pName);
}
void ParametrizedRayGroup::writeEnd(int indent,FILE* fp){
	int i;
	for(i=0;i<indent;i++){fprintf(fp," ");}
	fprintf(fp,"#joint_end\n");
}
Matrix4D ParametrizedRayGroup::getInverseMatrix(void){return getMatrix().invert();}
Matrix4D ParametrizedRayGroup::getNormalMatrix(void){return getMatrix().invert().transpose();}

//////////////////////////
// ParametrizedMatrix4D //
//////////////////////////
Matrix4D ParametrizedMatrix4D::getMatrix(void){return *value;}
