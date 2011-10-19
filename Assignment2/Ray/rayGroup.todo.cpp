#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	//printf("This runs\n");
	bool mxBound = false;
	if (mx > 0) mxBound = true;

	double min_t = -1;
	RayShape* min_shape = NULL;
	RayIntersectionInfo tempInfo = RayIntersectionInfo();

	for (int i = 0; i < sNum; i++)
	{
		//printf("i = %i\n",i);
		RayShape* temp = shapes[i];
		double t = temp->intersect(ray, tempInfo, mx);
		if (t > 0)
		{
			if (min_t == -1 || t < min_t) 
			{
				iInfo.iCoordinate = tempInfo.iCoordinate;
				iInfo.normal = tempInfo.normal;
				iInfo.material = tempInfo.material;
				min_t = t;
				min_shape = temp;
			}			
		}
	}


	return min_t;
}

BoundingBox3D RayGroup::setBoundingBox(void){
	return bBox;
}

int StaticRayGroup::set(void){
	return 1;
}
//////////////////
// OpenGL stuff //
//////////////////
int RayGroup::getOpenGLCallList(void){
	return 0;
}

int RayGroup::drawOpenGL(int materialIndex){
	return -1;
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
