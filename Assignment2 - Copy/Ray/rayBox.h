#ifndef BOX_INCLUDED
#define BOX_INCLUDED
#include <Util/geometry.h>
#include "rayShape.h"

/** This class represents a box and is defined by its center and the length of the sides. */
class RayBox : public RayShape {
public:
	/** The center of the box */
	Point3D center;
	/** The lengths of the sides of the box */
	Point3D length;

	/** The material associated with the box */
	class RayMaterial *material;
	
	
	RayBox(void);

	/** This method reads in a RayBox from a .ray file.
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

#endif // BOX_INCLUDED

