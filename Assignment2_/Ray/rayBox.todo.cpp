#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "rayBox.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayBox::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	
	return -1;
}
BoundingBox3D RayBox::setBoundingBox(void){
	Point3D p1 = center;
	Point3D p2 = center;
	p1 = p1 + (length / 2);
	p2 = p2 - (length / 2);
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayBox::drawOpenGL(int materialIndex){
	return -1;
}
