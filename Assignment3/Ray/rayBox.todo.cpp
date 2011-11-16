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
	bBox=BoundingBox3D(center-(length/2),center+(length/2));
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayBox::drawOpenGL(int materialIndex){
	GLfloat n[6][3] = {  /* Normals for the 6 faces of a box. */
		{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
	GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
		{0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
		{4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
	GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = (center[0] - (length[0]*0.5));
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = (center[0] + (length[0]*0.5));
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = (center[1] - (length[1]*0.5));
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = (center[1] + (length[1]*0.5));
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = (center[2] - (length[2]*0.5));
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = (center[2] + (length[2]*0.5));

	material->drawOpenGL();
	int i;
	for (i = 0; i < 6; i++) {
		glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}

	return -1;
}