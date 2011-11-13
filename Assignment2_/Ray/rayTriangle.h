#ifndef TRIANGLE_INCLUDED
#define TRIANGLE_INCLUDED
#include <Util/geometry.h>
#include "rayShape.h"
#include "rayScene.h"

/** This class represents a triangle and is specified by three pointers to
  * the three vertices that define it.
  */

class RayTriangle : public RayShape {
	Point3D v1;
	Point3D v2;
	Plane3D plane;
	void initialize(void);
public:
	/** The vertices of the triangle */
	class RayVertex* v[3];

	/** The material associated with the triangle */
	class RayMaterial *material;

	RayTriangle(void);

	/** This method reads in a RayTriangle from a .ray file.
	  * A pointer to the material associated to the triangle is set.
	  * The vertex positions are determined by reading in the vertex indices from the file
	  * and then looking them up in the vertex list vList
	  */
	int read(FILE* fp,int* materialIndex,RayVertex* vList,int vSize);

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
#endif // TRIANGLE_INCLUDED


