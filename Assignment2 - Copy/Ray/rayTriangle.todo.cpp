#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void){
}
double RayTriangle::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	
	RayVertex* t1 = v[0];
	RayVertex* t2 = v[1];
	RayVertex* t3 = v[2];
	Point3D p0 = ray.position;
	Point3D dir = ray.direction;
	double d = 0;
	/*printf("t1 Normal = (%f, %f, %f)\n",t1->normal.p[0],v[0]->normal[1],t1->normal.p[2]);
	printf("t2 Normal = (%f, %f, %f)\n",t2->normal.p[0],t2->normal.p[1],t2->normal.p[2]);
	printf("t3 Normal = (%f, %f, %f)\n",t3->normal.p[0],t3->normal.p[1],t3->normal.p[2]);*/
	Point3D normal = (t2->position - t1->position).crossProduct(t3->position - t1->position).unit();

	double t = -1;
	t = -((ray.position.dot(normal) + d) / (ray.direction.dot(normal)));

	Point3D p = ray.position + (ray.direction * t);

	Point3D v1 = Point3D();
	Point3D v2 = Point3D();
	Point3D n = Point3D();
	double test = 0;
	//t1 and t2
	v1 = t1->position - p0;
	v2 = t2->position - p0;
	n = v2.crossProduct(v1);
	test = (p - p0).dot(n);

	if (test >= 0){

		v1 = t2->position - p0;
		v2 = t3->position - p0;
		n = v2.crossProduct(v1);
		test = (p - p0).dot(n);
	
		if (test >= 0){

			v1 = t3->position - p0;
			v2 = t1->position - p0;
			n = v2.crossProduct(v1);
			test = (p - p0).dot(n);
			
			if (test >= 0){
				
				iInfo.iCoordinate = p;
				iInfo.normal = normal;
				iInfo.material = material;
				return t;
			}
		}
	}
	
	
	return -1;
}

BoundingBox3D RayTriangle::setBoundingBox(void){
	Point3D pointArr[3]; 
	pointArr[0] = v[0]->position;
	pointArr[1] = v[1]->position;
	pointArr[2] = v[2]->position;

	bBox = BoundingBox3D(pointArr, 3);
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	return -1;
}
