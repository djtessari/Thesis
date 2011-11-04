#ifndef RAY_LIGHT_INCLUDED
#define RAY_LIGHT_INCLUDED
#include "rayShape.h"

/** This abstract class represents a light source in the scene. */

class RayLight{
public:
	/** The color that the light source emits */
	Point3D color;

	/** This virtual method is responsible for reading in the light from a .ray file. */
	virtual int read(FILE* fp)=0;
	/** This virtual method is responsible for writing out the light source to a .ray file. If no file is specified, the light source is written out stdout. */
	virtual void write(FILE* fp=stdout)=0;


	///////////////////////
	// Ray-Tracing stuff //
	///////////////////////
	/** This virtual method returns the diffuse contribution of the light source to the specified hit location. 
	  * It computes the amount of diffuse light reaching the hit location and scales that using the material properties of the hit location.
	  * The returned value is a 3D point whose coefficients should all be in the range [0,1].
	  */
	virtual Point3D getDiffuse(Point3D cameraPosition,struct RayIntersectionInfo& iInfo)=0;

	/** This virtual method returns the specular contribution of the light source to the specified hit location. 
	  * It computes the amount of diffuse light reaching the hit location, using the normal direction at the
	  * hit location (in iInfo), and scales that using the material properties of the hit location.
	  * The returned value is a 3D point whose coefficients should all be in the range [0,1].
	  */
	virtual Point3D getSpecular(Point3D cameraPosition,struct RayIntersectionInfo& iInfo)=0;

	/** This virtual method tests if the intersection point represented by iInfo is in shadow from the light source.
	  * The value of isectCount is incremented according to the number of intersection tests performed in
	  * order to detemine if the point of intersection is in shadow. The returned value is either 0 if the
	  * the intersection point is not in shadow or 1 if it is.
	  */
	virtual int isInShadow(struct RayIntersectionInfo& iInfo,class RayShape* shape,int &isectCount)=0;
	/** This virtual method tests if the intersection point represented by iInfo is in partial shadow from the light source.
	  * A ray is cast from the hit location to the light source, and the transparency values are accumulated. If the
	  * transparency value falls below cLimit, the testing terminates. In computing the transparency value,
	  * isectCount is incremented according to the number of intersection tests performed and rayCount is incremented
	  * according to the number of rays that need to be cast. The returned value is a 3D
	  * point whose coefficients should all be in the range [0,1].
	  */
	virtual Point3D transparency(struct RayIntersectionInfo& iInfo,class RayShape* shape,Point3D cLimit)=0;


	//////////////////
	// OpenGL stuff //
	//////////////////
	/** This method calls the necessary OpenGL commands to render the light.
	  * index specifices the index of the light that is to be drawn.
	  */
	virtual void drawOpenGL(int index)=0;

};
#endif // RAY_LIGHT_INCLUDED
  

