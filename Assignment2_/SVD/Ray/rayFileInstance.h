#ifndef RAY_FILE_INSTANCE_INCLUDED
#define RAY_FILE_INSTANCE_INCLUDED
#include <Util/geometry.h>
#include "rayShape.h"
#include "rayScene.h"


/** This subclass of RayShape stores a reference to a .ray file included in the scene-graph.*/
class RayFileInstance : public RayShape {
	RayFile* rayFile;
public:
	RayFileInstance(RayFile* rayFile);
	
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
	int isStatic(void);
};

#endif // RAY_FILE_INSTANCE_INCLUDED

