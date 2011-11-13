#ifndef SHAPE_INCLUDED
#define SHAPE_INCLUDED
#include <stdio.h>
#include <Util/geometry.h>


/** This is the abstract class that all ray-traceable objects must implement. */

class RayShape{
public:
	/** The bounding box of the shape */
	BoundingBox3D bBox;

	/** This method writes the RayShape out to a .ray file, indenting the output by the specified amount.
	  * If no file is specified, the information gets written to stdout.
	  */
	virtual void write(int indent,FILE* fp=stdout)=0;
	

	///////////////////////
	// Ray-Tracing stuff //
	///////////////////////
	/** This method computes the intersection of the shape with the ray.
	  * If the ray hits the shape and either mx is less than zero or the intersection
	  * occurs at a distance less than t along the ray the intersection information in iInfo is
	  * set and a value greater than 0 is returned. Otherwise, -1 is returned. (This is useful for
	  * shadow testing when you may want to ignore hits beyond a certain distance).
	  * Either way the isectCounter is incremented by one.
	  */
	virtual double intersect(Ray3D ray,struct RayIntersectionInfo& iInfo,double mx=-1)=0;
	
	/** This method sets and returns a bounding box containing the shape.*/
	virtual BoundingBox3D setBoundingBox(void)=0;


	//////////////////
	// OpenGL stuff //
	//////////////////
	/** The OpenGL call list identifier */
	int openGLCallListID;

	/** The complexity for the rasterization of the shape */
	int openGLComplexity;

	/** This method sets up all the stuff that's necessary prior to OpenGL rendering.
	  * The value cplx represents the desired resolution of tessalation for objects such as spheres, cylinders, etc.. */
	virtual void setUpOpenGL(int cplx,int setCallList)=0;

	/** This method calls the necessary OpenGL commands to render the primitive. */
	virtual int drawOpenGL(int materialIndex)=0;

	/** This method returns a value of 1 if the RayShape's geometry doesn't change. */
	virtual int isStatic(void){return 1;}

};
#endif // SHAPE_INCLUDED
