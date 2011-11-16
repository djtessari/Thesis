#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySphere.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	//return -1;
	bool mxBound = false;
	if (mx > 0) mxBound = true;

	//printf("Running Sphere Intersect\n");

	double rsquare = pow(radius,2);

	Point3D l = center - ray.position;
	double tca = l.dot(ray.direction);
	double dsquare = l.dot(l) - (pow(tca,2));


	//determines if there is an intersection with the sphere first
	if (dsquare > rsquare) return -1;


	//We know it intersects, now we find the values to return
	double thc = sqrt(rsquare - dsquare);
	double t1 = tca - thc;
	double t2 = tca + thc;

	double t = -1;
	if (t1 > t2)
	{
		t = t2;
	}
	else
	{
		t = t1;
	}
	Point3D p = ray.position + ray.direction*t;
	double mag = sqrt(
		pow(p.p[0] - center.p[0],2) + 
		pow(p.p[1] - center.p[1],2) + 
		pow(p.p[2] - center.p[2],2));

	Point3D normal = (p - center) / mag;
	/*printf("mag = %f\n", mag);
	printf("p(%f, %f, %f)\n", p.p[0], p.p[1], p.p[2]);
	printf("center(%f, %f, %f)\n", center.p[0], center.p[1], center.p[2]);
	printf("normal(%f, %f, %f)\n", normal.p[0], normal.p[1], normal.p[2]);*/

	
	iInfo.iCoordinate = p;
	iInfo.normal = normal;
	iInfo.material = material;

	return t;
}
BoundingBox3D RaySphere::setBoundingBox(void){
	Point3D p=Point3D(radius,radius,radius);
	bBox=BoundingBox3D(center+p,center-p);
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RaySphere::drawOpenGL(int materialIndex){
	//glColor3f(1.0, 1.0, 1.0);
	//printf("Drawing sphere\n");
	if(materialIndex != material->index) material->drawOpenGL();
	gluSphere(gluNewQuadric(), radius, openGLComplexity, openGLComplexity);
	glFlush();/**/
	return material->index;
}
