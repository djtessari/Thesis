#include <GL/glut.h>
#include <math.h>
#include "rayCamera.h"



//////////////////
// OpenGL stuff //
//////////////////
void RayCamera::drawOpenGL(void){
	//printf("LoadCamera\n");
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position[0], position[1], position[2], direction[0], direction[1], direction[2], up[0], up[1], up[2]);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glLineWidth (1.5);

}
void RayCamera::rotateUp(Point3D center,float angle){
	/*
	glMatrixMode(GL_PROJECTION);
	glTranslatef(-center[0], -center[1], -center[2]);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(center[0], center[1], center[2]);
	glMatrixMode(GL_MODELVIEW);
	glFlush();*/
}
void RayCamera::rotateRight(Point3D center,float angle){
	//printf("Rotate up: %f\n", angle);
	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position[0], position[1], position[2],
				center[0], center[1], center[2],
				up[0], up[1], up[2]);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glFlush();*/
}
void RayCamera::moveForward(float dist){
}
void RayCamera::moveRight(float dist){
}
void RayCamera::moveUp(float dist){
}
