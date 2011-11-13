#ifndef POINT_LIGHT_INCLUDED
#define POINT_LIGHT_INCLUDED
#include "rayLight.h"

/** This class describes a point-light light-source. This light has a fixed 
  * position and the light attenuates as function of the distance from the light-source.
  */
class RayPointLight : public RayLight{
public:
	/** The position of the spot-light */
	Point3D location;
	/** The constant term of the attenuation equation */
	double constAtten;
	/** The linear term of the attenuation equation */
	double linearAtten;
	/** The quadratic term of the attenuation equation */
	double quadAtten;		
	
	/** This method reads in the point light from a .ray file. */
	int read(FILE* fp);

	void write(FILE* fp=stdout);

	///////////////////////
	// Ray-Tracing stuff //
	///////////////////////
	Point3D getDiffuse(Point3D cameraPosition,struct RayIntersectionInfo& iInfo);

	Point3D getSpecular(Point3D cameraPosition,struct RayIntersectionInfo& iInfo);
	
	int isInShadow(struct RayIntersectionInfo& iInfo,class RayShape* shape,int& isectCount);

	Point3D transparency(struct RayIntersectionInfo& iInfo,class RayShape* shape,Point3D cLimit);


	//////////////////
	// OpenGL stuff //
	//////////////////
	void drawOpenGL(int index);
};

#endif // POINT_LIGHT_INCLUDED


