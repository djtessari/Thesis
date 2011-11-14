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
	Point3D pList[3];
	pList[0]=v[0]->position;
	pList[1]=v[1]->position;
	pList[2]=v[2]->position;
	bBox=BoundingBox3D(pList,3);
	for(int i=0;i<3;i++){
		bBox.p[0][i]-=RAYEPS;
		bBox.p[1][i]+=RAYEPS;
	}
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	//glColor3f(0.0, 1.0, 0.0);
	v[0]->normal = v[0]->normal.unit();
	v[1]->normal = v[1]->normal.unit();
	v[2]->normal = v[2]->normal.unit();

	Point3D normal = (v[1]->position - v[0]->position).crossProduct(v[2]->position - v[0]->position).unit();
	Point3D iNormal = normal.negate();

	material->drawOpenGL();
	glBegin(GL_TRIANGLES);
		/*glVertex3f(1.0, 0.0, 0.0);
        glVertex3f (0.0, 1.0, 0.0);
        glVertex3f (0.0, 0.0, 0.0);/**/
		glVertex3f(v[0]->position[0], v[0]->position[1], v[0]->position[2]);
		glNormal3f(-v[0]->normal[0], -v[0]->normal[1], -v[0]->normal[2]);
		glNormal3f(v[0]->normal[0], v[0]->normal[1], v[0]->normal[2]);
		

		glVertex3f(v[1]->position[0], v[1]->position[1], v[1]->position[2]);
		glNormal3f(-v[1]->normal[0], -v[1]->normal[1], -v[1]->normal[2]);
		glNormal3f(v[1]->normal[0], v[1]->normal[1], v[1]->normal[2]);
		

		glVertex3f(v[2]->position[0], v[2]->position[1], v[2]->position[2]);
		glNormal3f(-v[2]->normal[0], -v[2]->normal[1], -v[2]->normal[2]);
		glNormal3f(v[2]->normal[0], v[2]->normal[1], v[2]->normal[2]);
		

		
		/**/
	glEnd();
	glFlush();

	return -1;
}
