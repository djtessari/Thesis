#ifndef SPHERE_INCLUDED
#define SPHERE_INCLUDED
#include <Util/geometry.h>
#include "rayShape.h"

/** This class describes a sphere, and is represented by its center and radius. */
class RaySphere : public RayShape {
public:
	/** The center of the sphere */
	Point3D center;
	/** The radius of the sphere */
	double radius;
	/** The material associated with the sphere */
	class RayMaterial *material;
	
	/** The default constructore */
	RaySphere(void);

	/** This method reads in a RaySphere from a .ray file.
	  * A pointer to the material associated to the triangle is set.
	  */
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

#endif // SPHERE_INCLUDED

