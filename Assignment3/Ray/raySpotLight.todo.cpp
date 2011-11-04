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

	Point3D temp = location - iInfo.iCoordinate;
	double dist = sqrt(temp.dot(temp));
	double mult = normal.dot(temp.unit());

	Point3D light = Point3D(0,0,0);
	Point3D L = temp.unit().negate();	
	if( ( L.dot(direction.unit()) / (L.length() * direction.length())) > cos(cutOffAngle) )
	{
		double atten = 0;
		atten = (constAtten + (linearAtten*dist) + (quadAtten*pow(dist,2.0)));
		light = ( (color * abs(pow(L.dot(direction.unit()),dropOffRate))) / atten);
	}

	diff.p[0] = matDiff[0] * light[0] * mult;
	diff.p[1] = matDiff[1] * light[1] * mult;
	diff.p[2] = matDiff[2] * light[2] * mult;


	return diff;
}
Point3D RaySpotLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D spec = Point3D();
	Point3D normal = iInfo.normal;
	Point3D matSpec = iInfo.material->specular;

	Point3D temp = location - iInfo.iCoordinate;
	double dist = sqrt(temp.dot(temp));

	double falloff = iInfo.material->specularFallOff;
	Point3D camDir = cameraPosition - iInfo.iCoordinate;
	camDir = camDir.unit();
	Point3D halfAngle = temp.unit() + camDir;
	halfAngle = halfAngle.unit();

	double dot = normal.dot(halfAngle);
	double mult = pow(dot,falloff);

	Point3D light = Point3D(0,0,0);
	Point3D L = temp.unit().negate();	
	if( ( L.dot(direction.unit()) / (L.length() * direction.length())) > cos(cutOffAngle) )
	{
		double atten = 0;
		atten = (constAtten + (linearAtten*dist) + (quadAtten*pow(dist,2.0)));
		light = ( (color * abs(pow(L.dot(direction.unit()),dropOffRate))) / atten);
	}

	spec.p[0] = matSpec[0] * light[0] * mult;
	spec.p[1] = matSpec[1] * light[1] * mult;
	spec.p[2] = matSpec[2] * light[2] * mult;

	return spec;
}

int RaySpotLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	Point3D temp = location - iInfo.iCoordinate;
	double dist = sqrt(temp.dot(temp));
	double atten = 0;
	atten = (constAtten + (linearAtten*dist) + (quadAtten*pow(dist,2.0)));

	Ray3D testRay = Ray3D();
	testRay.position = iInfo.iCoordinate;
	testRay.direction = temp.unit();

	if(shape->intersect(testRay, iInfo, dist) != -1){
		return 1;
	}
	//1 = inShadow, 0 = no shadow
	return 0;
}

Point3D RaySpotLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	Point3D temp = location - iInfo.iCoordinate;
	double dist = sqrt(temp.dot(temp));
	double atten = 0;
	atten = (constAtten + (linearAtten*dist) + (quadAtten*pow(dist,2.0)));

	Ray3D testRay = Ray3D();
	
	testRay.direction = temp.unit();
	testRay.position = iInfo.iCoordinate + testRay.direction;

	Point3D out = Point3D(1,1,1);	

	if(shape->intersect(testRay, iInfo, dist) != -1){		
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
void RaySpotLight::drawOpenGL(int index){
}
