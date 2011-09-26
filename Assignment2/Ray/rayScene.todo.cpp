#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>


///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v,Point3D n){
	return Point3D();
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
	return 0;
}

Ray3D RayScene::GetRay(RayCamera* camera,int i,int j,int width,int height){
	double d = 10;
	float fov = 90;
	fov = (180 / (fov*PI));


	Point3D p0 = camera->position;
	Point3D l,r,b,t,p,u,v;
	Ray3D rayOut;

	l = p0 + (camera->direction*d) - (camera->right*d*tan(fov));
	r = p0 + (camera->direction*d) + (camera->right*d*tan(fov));
	t = p0 + (camera->direction*d) - (camera->up*d*tan(fov));
	b = p0 + (camera->direction*d) + (camera->up*d*tan(fov));

	u = l + (r - l)*((i + 0.5)/width); 
	v = b + (t - b)*((j + 0.5)/height); 

	p = u + v;

	rayOut.position = p0;
	rayOut.direction = p;

	return rayOut;
}

Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit){
	return Point3D();
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
