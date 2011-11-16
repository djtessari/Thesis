#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "rayCone.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayCone::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	return -1;
}

BoundingBox3D RayCone::setBoundingBox(void){
	Point3D p;
	p=Point3D(radius,height/2,radius);
	bBox=BoundingBox3D(center+p,center-p);
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayCone::drawOpenGL(int materialIndex){
	if(materialIndex != material->index) material->drawOpenGL();

	gluCylinder(gluNewQuadric(), radius, 0, height, openGLComplexity, openGLComplexity);
	GLUquadricObj *obj = gluNewQuadric();
	gluQuadricOrientation(obj, GLU_INSIDE);
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluQuadricNormals(obj, GLU_SMOOTH);
	gluDisk(obj, 0, radius, openGLComplexity, openGLComplexity);
	
	//glLoadIdentity();
	/*glTranslatef(0.0, 0.0, height);
	GLUquadricObj *obj2 = gluNewQuadric();
	gluQuadricDrawStyle(obj2, GLU_FILL);
	gluQuadricNormals(obj2, GLU_SMOOTH);
	gluDisk(obj2, 0, radius, openGLComplexity, openGLComplexity);*/
	
	glFlush();/**/

	return material->index;
}