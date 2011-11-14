#include <GL/glut.h>
#include <math.h>
#include "rayCamera.h"



//////////////////
// OpenGL stuff //
//////////////////
void RayCamera::drawOpenGL(void){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position[0], position[1], position[2], direction[0], direction[1], direction[2], up[0], up[1], up[2]);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

}
void RayCamera::rotateUp(Point3D center,float angle){
	//glTranslatef(-center[0], -center[1], -center[2]);
	//glRotatef(angle, 0.0, 1.0, 0.0);
	//glTranslatef(center[0], center[1], center[2]);
}
void RayCamera::rotateRight(Point3D center,float angle){
	//glTranslatef(-center[0], -center[1], -center[2]);
	//glRotatef(angle, 1.0, 0.0, 0.0);
	//glTranslatef(center[0], center[1], center[2]);
}
void RayCamera::moveForward(float dist){
}
void RayCamera::moveRight(float dist){
}
void RayCamera::moveUp(float dist){
}
