#include <GL/glut.h>
#include <math.h>
#include "rayCamera.h"



//////////////////
// OpenGL stuff //
//////////////////
void RayCamera::drawOpenGL(void){
	glClearColor (1.0, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glShadeModel(GL_SMOOTH);
/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//gluLookAt(-position[0], -position[1], -position[2], direction[0], direction[1], direction[2], up[0], up[1], up[2]);
    //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	//glClear (GL_COLOR_BUFFER_BIT);

/*  draw white polygon (rectangle) with corners at
 *  (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)  
 */
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex3f (0.25, 0.25, 0.0);
        glVertex3f (0.75, 0.25, 0.0);
        glVertex3f (0.75, 0.75, 0.0);
        glVertex3f (0.25, 0.75, 0.0);
    glEnd();

/*  don't wait!  
 *  start processing buffered OpenGL routines 
 */
    glFlush ();


	/*glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
	//gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(position[0], position[1], position[2], direction[0], direction[1], direction[2], up[0], up[1], up[2]);
	//glFlush();
	//glTranslated(position[0], position[1], position[2]);
	//glMatrixMode(GL_MODELVIEW);*/

}
void RayCamera::rotateUp(Point3D center,float angle){
	glTranslatef(-center[0], -center[1], -center[2]);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(center[0], center[1], center[2]);
}
void RayCamera::rotateRight(Point3D center,float angle){
	glTranslatef(-center[0], -center[1], -center[2]);
	glRotatef(angle, 1.0, 0.0, 0.0);
	glTranslatef(center[0], center[1], center[2]);
}
void RayCamera::moveForward(float dist){
}
void RayCamera::moveRight(float dist){
}
void RayCamera::moveUp(float dist){
}
