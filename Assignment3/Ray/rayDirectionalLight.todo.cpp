#include <math.h>
#include <GL/glut.h>
#include "rayDirectionalLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayDirectionalLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D diff = Point3D();
	Point3D normal = iInfo.normal;
	Point3D matDiff = iInfo.material->diffuse;
	double mult = normal.dot(direction.negate());

	diff.p[0] = matDiff[0] * color[0] * mult;
	diff.p[1] = matDiff[1] * color[1] * mult;
	diff.p[2] = matDiff[2] * color[2] * mult;


	return diff;
}
Point3D RayDirectionalLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D spec = Point3D();
	Point3D normal = iInfo.normal;
	Point3D matSpec = iInfo.material->specular;

	double falloff = iInfo.material->specularFallOff;
	Point3D camDir = cameraPosition - iInfo.iCoordinate;
	camDir = camDir.unit();
	Point3D halfAngle = direction.negate() + camDir;
	halfAngle = halfAngle.unit();

	double dot = normal.dot(halfAngle);
	double mult = pow(dot,falloff);

	spec.p[0] = matSpec[0] * color[0] * mult;
	spec.p[1] = matSpec[1] * color[1] * mult;
	spec.p[2] = matSpec[2] * color[2] * mult;


	return spec;
}
int RayDirectionalLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	Ray3D testRay = Ray3D();
	testRay.position = iInfo.iCoordinate;
	testRay.direction = direction.unit().negate();

	if(shape->intersect(testRay, iInfo, -1) != -1){
		return 1;
	}
	//1 = inShadow, 0 = no shadow
	return 0;
}
Point3D RayDirectionalLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){

	Ray3D testRay = Ray3D();
	
	testRay.direction = direction.negate();
	testRay.position = iInfo.iCoordinate + testRay.direction;

	Point3D out = Point3D(1,1,1);	

	if(shape->intersect(testRay, iInfo, -1) != -1){		
		Point3D trans = iInfo.material->transparent;
		out = out * trans;
		out = out * transparency(iInfo, shape, cLimit / trans);
	}
	
	
	//1 = inShadow, 0 = no shadow
	return out;
}

//////////////////
// OpenGL stuff //
//////////////////
void RayDirectionalLight::drawOpenGL(int index)
	{

		glPushMatrix();
			glLoadIdentity();
			GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
			GLfloat light_diffuse[] = { color[0], color[1], color[2], 1.0 };
			GLfloat light_specular[] = { color[0], color[1], color[2], 1.0 };
			GLfloat light_position[] = { -direction[0], -direction[1], -direction[2], 0.0 };
			/*GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
			GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };/**/

			glLightfv(GL_LIGHT0+index, GL_POSITION, light_position);
			glLightfv(GL_LIGHT0+index, GL_AMBIENT, light_ambient);
			glLightfv(GL_LIGHT0+index, GL_DIFFUSE, light_diffuse);
			glLightfv(GL_LIGHT0+index, GL_SPECULAR, light_specular);
			/**/
		glPopMatrix();

		glEnable(GL_LIGHT0+index);
	}
