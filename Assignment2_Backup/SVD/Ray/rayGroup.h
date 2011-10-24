#ifndef GROUP_INCLUDED
#define GROUP_INCLUDED
#include <Util/geometry.h>
#include "rayShape.h"
#include "rayScene.h"



/** This class can be used for sorting shapes based on the intersections of their bounding volumes with a given ray.*/
class RayShapeHit{
public:
	/** The distance along the ray to the point of intersection */
	float t;
	/** The shape that was intersected */
	RayShape* shape;

	/** This is a static method for sorting the hits by the order in which they occured.
	  * For example after the bounding volumes have been intersected and the distance and shapes have been written into
	  * an array of RayShapes, the array can be sorted by calling:\n
	  *			qsort(hits,hitNum,sizeof(RayShapeHit),RayShapeHit::Compare); */
	static int Compare(const void* v1,const void* v2);
};


/** This class represents a node in the scene graph with an associated transformation.*/
class RayGroup : public RayShape{
public:
	/** The number of shapes associated to the node */
	int sNum;
	/** The shapes that are associated to the node */
	RayShape** shapes;
	/** An array of RayShapeHit elements that can be used for bounding-volume sorting*/
	class RayShapeHit* hits;

	RayGroup(void);
	~RayGroup(void);

	/** This method allows one to add a shape to the node. */
	void addShape(RayShape* shape);
	/** This method returns the number of shapes associated to the node. */
	int  shapeNum(void);

	void write(int indent,FILE* fp=stdout);

	/** This virtual method specifies how the header of the node should be written out to a .ray file. */
	virtual void writeBegin(int indent,FILE* fp=stdout)=0;
	/** This virtual method specifies how the footer of the node should be written out to a .ray file. */
	virtual void writeEnd(int indent, FILE* fp=stdout)=0;

	/** This method returns the transformation associated with the group. */
	virtual Matrix4D getMatrix(void)=0;
	/** This method returns the inverse of the transformation associated with the group. */
	virtual Matrix4D getInverseMatrix(void)=0;
	/** This method returns the transformation that acts on the surface normals. */
	virtual Matrix4D getNormalMatrix(void)=0;

	BoundingBox3D setBoundingBox(void);

	double intersect(Ray3D ray,struct RayIntersectionInfo& iInfo,double mx=-1);

	//////////////////
	// OpenGL stuff //
	//////////////////
	void setUpOpenGL(int cplx,int setCallList);

	int drawOpenGL(int materialIndex);

	/** This method generates an OpenGL call list and returns the handle. */
	int getOpenGLCallList(void);
};

/** This subclass of RayGroup represents a node in the scene graph whose transformation matrix is constant. */
class StaticRayGroup : public RayGroup{
	/** The inverse of the transformation associated with the static group */
	Matrix4D inverseTransform;
	/** The transformation that acts on the surface normals. */
	Matrix4D normalTransform;
public:
	/** The constant transformation associated to the node.*/
	Matrix4D localTransform;

	StaticRayGroup(void);

	/** This method sets the the transformation matrix of the node. */
	int set(Matrix4D xForm);
	/** This method reads in the transformation matrix from a .ray file. */
	int read(FILE* fp);

	/** This method sets the invers and normal transformations of the matrix.*/
	int set(void);

	Matrix4D getMatrix(void);
	Matrix4D getInverseMatrix(void);
	Matrix4D getNormalMatrix(void);
	void writeBegin(int indent,FILE* fp=stdout);
	void writeEnd(int indent,FILE* fp=stdout);

	//////////////////
	// OpenGL stuff //
	//////////////////
	/** This method returns TRUE if the subtree beneath the group represents a static object in the scene. If any of nodes
	  * in the scene graph beneath are not static, this method will return FALSE. */
	int isStatic(void);
};

/** This abstract subclass of RayGroup represents a node in the scene graph whose transformation matrix is parametrizable. */
class ParametrizedRayGroup : public RayGroup{
public:
	char pName[100];
	virtual Matrix4D getMatrix(void)=0;
	Matrix4D getInverseMatrix(void);
	Matrix4D getNormalMatrix(void);

	/** This method writes the header of the node into a .ray file. */
	void writeBegin(int indent,FILE* fp=stdout);
	/** This method writes the footer of the node into a .ray file. */
	void writeEnd(int indent,FILE* fp=stdout);

	//////////////////
	// OpenGL stuff //
	//////////////////
	/** This method always returns false.*/
	int isStatic(void);
};

/** This class represents a parametrizable transformation that simply stores a pointer to the matrix. */
class ParametrizedMatrix4D : public ParametrizedRayGroup{
public:
	const Matrix4D* value;
	Matrix4D getMatrix(void);
};
/** This class represents a parametrizable transformation that stores a pointer to the Euler angles of the rotation
  * and a pointer to the translation vector. */
class ParametrizedEulerAnglesAndTranslation : public ParametrizedRayGroup{
public:
	EulerAnglesAndTranslation* value;
	Matrix4D getMatrix(void);
};
/** This class represents a parametrizable transformation that stores a pointer to the 3x3 matrix approximating the rotation
  * and a pointer to the translation vector. When it returns a transformation, it computes the closest 3x3 rotation matrix
  * to the matrix pointed to.*/
class ParametrizedClosestRotationAndTranslation : public ParametrizedRayGroup{
public:
	RotationAndTranslation* value;
	Matrix4D getMatrix(void);
};
/** This class represents a parametrizable transformation that stores a pointer to the 3x3 skew-symmetric logarithm of the
  * rotation and a pointer to the translation vector. When it returns a transformation, it exponentiates the 3x3 skew-symmetric
  * matrix to obtain the appropriate rotation. */
class ParametrizedRotationLogarithmAndTranslation : public ParametrizedRayGroup{
public:
	LogRotationAndTranslation* value;
	Matrix4D getMatrix(void);
};
/** This class represents a parametrizable transformation that stores a pointer to the quaternion describing the rotation 
  * and a pointer to the translation vector. When it returns a transformation, it computes the rotational component from the
  * unit-quaternion obtained by normalizing. */
class ParametrizedQuaternionAndTranslation : public ParametrizedRayGroup{
public:
	QuaternionAndTranslation *value;
	Matrix4D getMatrix(void);
};


#endif // GROUP_INCLUDED
