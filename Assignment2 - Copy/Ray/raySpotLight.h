#ifndef SPOT_LIGHT_INCLUDED
#define SPOT_LIGHT_INCLUDED
#include "rayLight.h"

/** This class describes a spot-light light-source. This light has a fixed 
  * position in space and a fixed direction. The light attenuates both as a
  * function of the distance from the light-source and the angle between the
  * line from the light to the point and the light direction. The cutOffAngle
  * specifies the angle beyond which the light has no contribution.
  */

class RaySpotLight : public RayLight{
public:
	/** The position of the spot-light */
	Point3D location;
	/** The preferred direction the outgoing light rays */
	Point3D direction;
	
	/** The constant term of the attenuation equation */
	double constAtten;
	/** The linear term of the attenuation equation */
	double linearAtten;
	/** The quadratic term of the attenuation equation */
	double quadAtten;
	
	/** The cut-off angle for the spot light (should be in the range [0,Pi/2]) */
	double cutOffAngle;
	/** The rate at which the intensity falls off as light travels in the non-preferred direction (should be in the range [0,128]) */
	double dropOffRate;
	
	/** This method reads in the spot light from a .ray file. */
	int read(FILE* fp);

	void write(FILE* fp=stdout);

	///////////////////////
	// Ray-Tracing stuff //
	///////////////////////
	Point3D getDiffuse(Point3D cameraPosition,struct RayIntersectionInfo& iInfo);

	Point3D getSpecular(Point3D cameraPosition,struct RayIntersectionInfo& iInfo);
	
	int isInShadow(struct RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount);

	Point3D transparency(struct RayIntersectionInfo& iInfo,class RayShape* shape,Point3D cLimit);

	//////////////////
	// OpenGL stuff //
	//////////////////
	void drawOpenGL(int index);
};

#endif // SPOT_LIGHT_INCLUDED


