#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySpotLight.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RaySpotLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D diff = Point3D();
	Point3D normal = iInfo.normal;
	Point3D matDiff = iInfo.material->diffuse;

	diff[0] = matDiff[0] * (normal.dot(direction)) * color[0];
	diff[1] = matDiff[1] * (normal.dot(direction)) * color[1];
	diff[2] = matDiff[2] * (normal.dot(direction)) * color[2];

	return diff;
}
Point3D RaySpotLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	return Point3D();
}
int RaySpotLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RaySpotLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RaySpotLight::drawOpenGL(int index){
}
