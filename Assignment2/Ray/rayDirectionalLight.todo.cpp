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

	diff.p[0] = matDiff[0] * color[0] * (normal.dot(direction.negate()));
	diff.p[1] = matDiff[1] * color[1] * (normal.dot(direction.negate()));
	diff.p[2] = matDiff[2] * color[2] * (normal.dot(direction.negate()));


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

	spec.p[0] = matSpec[0] * color[0] * pow(dot,falloff);
	spec.p[1] = matSpec[1] * color[1] * pow(dot,falloff);
	spec.p[2] = matSpec[2] * color[2] * pow(dot,falloff);


	return spec;
}
int RayDirectionalLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RayDirectionalLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RayDirectionalLight::drawOpenGL(int index){
}
