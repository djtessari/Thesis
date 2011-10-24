#include <math.h>
#include <GL/glut.h>
#include "rayPointLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayPointLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D diff = Point3D();
	Point3D normal = iInfo.normal;
	Point3D matDiff = iInfo.material->diffuse;

	Point3D temp = location - iInfo.iCoordinate;
	double dist = sqrt(temp.dot(temp));
	double atten = 0;
	atten = (constAtten + (linearAtten*dist) + (quadAtten*pow(dist,2.0)));

	double mult = normal.dot(temp.unit());

	diff.p[0] = matDiff[0] * (color[0] / atten) * mult;
	diff.p[1] = matDiff[1] * (color[1] / atten) * mult;
	diff.p[2] = matDiff[2] * (color[2] / atten) * mult;


	return diff;
}
Point3D RayPointLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D spec = Point3D();
	Point3D normal = iInfo.normal;
	Point3D matSpec = iInfo.material->specular;

	Point3D temp = location - iInfo.iCoordinate;
	double dist = sqrt(temp.dot(temp));
	double atten = 0;
	atten = (constAtten + (linearAtten*dist) + (quadAtten*pow(dist,2.0)));

	double falloff = iInfo.material->specularFallOff;
	Point3D camDir = cameraPosition - iInfo.iCoordinate;
	camDir = camDir.unit();
	Point3D halfAngle = temp.unit() + camDir;
	halfAngle = halfAngle.unit();

	double dot = normal.dot(halfAngle);
	double mult = pow(dot,falloff);

	spec.p[0] = matSpec[0] * (color[0] / atten) * mult;
	spec.p[1] = matSpec[1] * (color[1] / atten) * mult;
	spec.p[2] = matSpec[2] * (color[2] / atten) * mult;


	return spec;
}
int RayPointLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	Point3D temp = location - iInfo.iCoordinate;
	double dist = sqrt(temp.dot(temp));
	double atten = 0;
	atten = (constAtten + (linearAtten*dist) + (quadAtten*pow(dist,2.0)));

	Ray3D testRay = Ray3D();
	testRay.position = iInfo.iCoordinate;
	testRay.direction = temp.unit();

	if(shape->intersect(testRay, iInfo, -1) != -1){
		return 1;
	}
	//1 = inShadow, 0 = no shadow
	return 0;
}
Point3D RayPointLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	Point3D temp = location - iInfo.iCoordinate;
	double dist = sqrt(temp.dot(temp));
	double atten = 0;
	atten = (constAtten + (linearAtten*dist) + (quadAtten*pow(dist,2.0)));

	Ray3D testRay = Ray3D();
	
	testRay.direction = temp.unit();
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
void RayPointLight::drawOpenGL(int index){
}
