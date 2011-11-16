#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "rayCylinder.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayCylinder::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	return -1;
}

BoundingBox3D RayCylinder::setBoundingBox(void){
	Point3D p;
	p=Point3D(radius,height/2,radius);
	bBox=BoundingBox3D(center+p,center-p);
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayCylinder::drawOpenGL(int materialIndex){
	if(materialIndex != material->index) material->drawOpenGL();

	gluCylinder(gluNewQuadric(), radius, radius, height, openGLComplexity, openGLComplexity);
	GLUquadricObj *obj = gluNewQuadric();
	gluQuadricOrientation(obj, GLU_INSIDE);
	gluDisk(obj, 0, radius, openGLComplexity, openGLComplexity);
	
	//glLoadIdentity();
	glTranslatef(0.0, 0.0, height);
	GLUquadricObj *obj2 = gluNewQuadric();
	gluQuadricDrawStyle(obj2, GLU_FILL);
	gluQuadricNormals(obj2, GLU_SMOOTH);
	gluDisk(obj2, 0, radius, openGLComplexity, openGLComplexity);
	
	glFlush();/**/
	
	return material->index;
}