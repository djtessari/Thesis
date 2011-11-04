#ifndef SCENE_INCLUDED
#define SCENE_INCLUDED
#include <Util/geometry.h>
#include <Image/image.h>
#include <GL/glut.h>
#include "rayShape.h"
#include "rayLight.h"
#include "rayGroup.h"
#include "rayKey.h"
#include "rayCamera.h"

#define STRING_BUFFER_SIZE 200

/** If a ray intersects a shape, the shape information at the point of intersection is stored in this structure. */
struct RayIntersectionInfo {
	/** The material of the intersected surface */
	class RayMaterial* material;
	/** The position, in world coordinates, of the intersection */
	Point3D iCoordinate;
	/** The normal of the shape at the point of intersection */
	Point3D normal;
	/** The texture coordinates of the the shape at the point of intersection */
	Point2D texCoordinate;
};

/** This class stores information about a vertex . */
class RayVertex {
public:
	/** The index of the vertex within the scene */
	int index;
	/** The position of the vertex */
	Point3D position;
	/** The normal at the vertex */
	Point3D normal;
	/** The texture coordinates at the vertex */
	Point2D texCoordinate;

	/** This method reads in the vertex information from a .ray file.*/
	int read(FILE* fp);
	/** This method writes out the vertex information to a .ray file. If no file is specified,
	  * the vertex is written out to stdout. */
	void write(FILE* fp=stdout);
};


/** This class stores surface material properties. */
class RayMaterial {
public:
	/** The index of the material within the scene */
	int index;
	/** The amount of ambient light the surface transmits */
	Point3D ambient;
	/** The amount of diffuse light the surface transmits */
	Point3D diffuse;
	/** The amount of specular light the surface transmits */
	Point3D specular;
	/** The amount of light the surface emits */
	Point3D emissive;
	/** The amount of transparent light the surface transmits */
	Point3D transparent;
	/** The coefficient for the specular fall-off of the material */
	double specularFallOff;
	/** The refraction index of the material */
	double refind;
	/** A pointer to the texture associated with a surface */
	class RayTexture *tex;
	/** A string for storing additional material parameters specified by the user */
	char foo[STRING_BUFFER_SIZE];

	RayMaterial(void);

	/** This method reads in the material information from a .ray file.*/
	int read(FILE* fp,int& textureIndex);
	/** This method writes out the material information to a .ray file. If no file is specified,
	  * the material is written out to stdout. */
	void write(FILE* fp=stdout);
	
	/** This method calls the OpenGL commands for setting up the material. */
	void drawOpenGL(void);
};

/** This class stores information about a texture used for texture mapping shapes */
class RayTexture{
public:
	/** The index of the texture within the scene */
	int index;
	/** The name of the texture file */
	char filename[STRING_BUFFER_SIZE];
	/** The image used as a texture */
	Image32 *img;

	RayTexture(void);
	~RayTexture(void);
	/** This method reads in the texture file name from the .ray file and reads the texture from the specified file.*/
	int read(FILE* fp);
	/** This method writes out the texture file name to a .ray file. If no file is specified,
	  * the file name is written out to stdout. */
	void write(FILE* fp=stdout);

	/** The texture handle for OpenGL rendering */
	GLuint openGLHandle;

	/** This method sets up the OpenGL texture */
	void setUpOpenGL(void);
};

/** This class stores information about the scene-graph read out from a .ray file. */
class RayFile{
public:
	/** The index of the .ray file within the scene */
	int index;
	/** The name of the .ray file */
	char filename[STRING_BUFFER_SIZE];
	/** The scene graph associated with a .ray file */
	class RayScene* scene;

	~RayFile(void);

	/** This method reads in ray-file name from the .ray file and reads the scene-graph from the specified file.*/
	int read(FILE* fp,int transformType);
	/** This method writes out ray-file name to a .ray file. If no file is specified,
	  * the ray-file name is written out to stdout. */
	void write(FILE* fp=stdout);
};

/** This class stores all of the information read out from a .ray file.*/
class RayScene{
	RayVertex* vertices;
	int vertexNum;
	RayMaterial* materials;
	int materialNum;
	RayTexture* textures;
	int textureNum;
	RayFile* rayFiles;
	int rayFileNum;
	RayKeyFile* keyFiles;
	RayKeyData* keyData;
	int keyFileNum;

	void ParseError(const char *);
	void ParseLineError(int , const char *);
	void ParseGroup(FILE* fp,int& cmndCtr,class RayGroup* current);
	void ParseJoint(FILE* fp,int& cmndCtr,class RayGroup* current);
	int  ParseShape(FILE* fp,const char* keyword,int cmndCtr,class RayGroup* current);
public:
	/** The ambient light in the scene */
	Point3D ambient;
	/** The color of the background */
	Point3D background;
	/** The camera */
	RayCamera* camera;
	/** The list of lights in the scene */
	class RayLight** lights;
	/** The number of lights in the scene */
	int lightNum;
	/** The root of the scene-graph */
	class StaticRayGroup* group;

	RayScene(void);
	~RayScene(void);

	/** This method returns the material with the specified index.*/
	RayMaterial* getMaterial(int index);

	/** This method reads in the scene-graph from a .ray file. */
	int read(char* fileName,int transformType=RayKeyData::MATRIX);
	/** This method reads in the scene-graph from a .ray file. */
	int read(FILE* fp,int transformType);
	/** This method writes out the scene-graph to a .ray file. */
	int write(char* fileName);
	/** This method writes out the scene-graph to a .ray file. If no file is specified the scene-graph is written out stdout. */
	int write(FILE* fp=stdout);

	///////////////////////
	// Ray-Tracing stuff //
	///////////////////////
	int RayTrace(const int& width,const int& height,const int& rLimit,const double& cLimit,Image32& img);

	/** This function will reflect the vector v about the normal n */
	static Point3D Reflect(Point3D v,Point3D n);

	/** This function will refract the vector about the normal using the provided indices of refraction
	  * The refracted vector is written into refract and a value of 1 is returned if the refraction
	  * succeeded (i.e. the necessary arcsin could be computed)
	  */
	static int Refract(Point3D v,Point3D n,double ir,Point3D& refract);

	/** This function returns that leaves the camera and goes through pixel (i,j) of the view plane */
	static Ray3D GetRay(RayCamera* camera,int i,int j,int width,int height);

	/** This is the function responsible for the recursive ray-tracing returning the color obtained
	  * by shooting a ray into the scene and recursing until either the recursion depth has been reached
	  * or the contribution from subsequent bounces is guaranteed to be less than the cut-off.\n
	  */
	Point3D GetColor(Ray3D ray,int rDepth,Point3D cLimit);
	Point3D RGetColor(Ray3D ray,int rDepth,Point3D cLimit);

	//////////////////
	// OpenGL stuff //
	//////////////////

	void RayView(const int& width,const int& height,const int& cplx,const int& factor=RayKeyData::MATRIX);

	/** This method calls the OpenGL commands for drawing the scene. */
	void drawOpenGL(void);

	/** This method class the OpenGL commands to set up everything that needs to be set up prior to rendering */
	void setUpOpenGL(int cplx);

	/** This method updates the current time, changing the parameter values as needed */
	void setCurrentTime(double t,int curveFit=LINEAR);
};

#endif // SCENE_INCLUDED
  

