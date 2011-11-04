#ifndef CONE_INCLUDED
#define CONE_INCLUDED
#include <Util/geometry.h>
#include "rayShape.h"

/** This class represents a cone whose central axis isparallel to the y-axis, and 
  * is defined by the center of the cone, the height from the tip to the base
  * and the base of the cone. */

class RayCone : public RayShape {
public:
	/** The center of the cylinder */
	Point3D center;
	/** The height of the cylinder */
	double height;
	/** The radius of the cylinder */
	double radius;
	/** The material associated with the cylinder */
	class RayMaterial *material;
	
	RayCone(void);

	/** This method reads in a RayCone from a .ray file. A pointer to the material associated to the triangle is set.*/
	int read(FILE* fp,int* materialIndex);

	void write(int indent,FILE* fp=stdout);
	
	///////////////////////
	// Ray-Tracing stuff //
	///////////////////////
	double intersect(Ray3D ray,struct RayIntersectionInfo& iInfo,double mx=-1);
	
	BoundingBox3D setBoundingBox(void);

	//////////////////
	// OpenGL stuff //
	//////////////////
	void setUpOpenGL(int cplx,int setCallList);

	int drawOpenGL(int materialIndex);
};

#endif // CONE_INCLUDED
