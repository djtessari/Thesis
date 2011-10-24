#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>


///////////////////////
// Ray-tracing stuff //
///////////////////////

/*
	Point Tracker - Total so far: 17 (including unimplemented lights)
	~~~~~~~~~~~~~~~~~~~~~~~~~
	(1) RayScene::GetRay
	(2) RayGroup::intersect
	(2) RaySphere::intersect
	(2) RayTriangle::intersect
	(1) RayScene::GetColor
	(2) getDiffuse ( Only Directional )
	(2) getSpecular ( Only Directional )
	(2) isInShadow ( Only Directional )
	(1) RayScene::GetColor (Diff/Spec/Shadow)
	(2) RayGroup::intersect (Transformations)
	~~~~~~~~~~~~~~~~~~~~~~~~~

*/



Point3D RayScene::Reflect(Point3D v,Point3D n){
	// I - 2 * dot(N,I) * N

	Point3D out = Point3D();
	out = v - n*(2*n.dot(v));
	
	return out.unit();
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
	return 0;
}

Ray3D RayScene::GetRay(RayCamera* camera,int i,int j,int width,int height){
	double d = 1;
	double ha = camera->heightAngle;
	double wa = ha * camera->aspectRatio;

	d = ((height / 2) / tan(ha));

	RayCamera cam = *camera;

	Point3D dir = camera->direction;
	Point3D right = camera->right;
	Point3D up = camera->up;
	Point3D p0 = camera->position;

	Point3D l,r,b,t,p,u,v;
	Ray3D rayOut;

	/*printf("p0 = [%f,%f,%f]\n", p0[0], camera->position[1], camera->position[2]);
	printf("dir = [%f,%f,%f]\n", dir->index(0), dir->index(1), dir->index(2));
	printf("right = [%f,%f,%f]\n", right[0], right[1], right[2]);
	printf("up = [%f,%f,%f]\n\n", up.p[0], up.p[1], up.p[2]);*/

	/*l = p0 + (camera->direction*d) - (camera->right*d*tan(fov));
	r = p0 + (camera->direction*d) + (camera->right*d*tan(fov));
	t = p0 + (camera->direction*d) - (camera->up*d*tan(fov));
	b = p0 + (camera->direction*d) + (camera->up*d*tan(fov));*/
	
	
	l = p0 + (dir*d) - (right*d*tan(wa));
	r = p0 + (dir*d) + (right*d*tan(wa));
	t = p0 + (dir*d) + (up*d*tan(ha));
	b = p0 + (dir*d) - (up*d*tan(ha));

	//printf("l = [%f,%f,%f]\n", l.p[0], l.p[1], l.p[2]);

	u = l + (r - l)*((i + 0.5)/width); 
	v = b + (t - b)*((j + 0.5)/height); 

	p = u + v;

	/*printf("p = [%f,%f,%f]\n", p.p[0], p.p[1], p.p[2]);
	printf("u = [%f,%f,%f]\n", u.p[0], u.p[1], u.p[2]);
	printf("v = [%f,%f,%f]\n", v.p[0], v.p[1], v.p[2]);*/

	rayOut.position = p0;
	rayOut.direction = p.unit();

	return rayOut;
}

Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit){
	RayIntersectionInfo* iInfo = new RayIntersectionInfo();
	float e = 0.01;
	Ray3D reflect = Ray3D();
	Ray3D refract = Ray3D();


	Point3D c = Point3D(0,0,0);
	Point3D c2 = Point3D(0,0,0);
	Point3D c3 = Point3D(0,0,0);

	if(group->intersect(ray, *iInfo, 1.0) != -1){
		c += ambient * iInfo->material->ambient;
		c += iInfo->material->emissive;
		//Point3D lightAdd = Point3D();
		for (int i = 0; i < lightNum; i++){
			//1 = inShadow, 0 = no shadow
			int secCount = 0;

			//if(lights[i]->isInShadow(*iInfo, group, secCount)==0){
				c = c + lights[i]->getDiffuse(camera->position, *iInfo);
				c = c + lights[i]->getSpecular(camera->position, *iInfo);
			//}
		}
		//Recursive ray casting
		
		reflect.direction = Reflect(ray.direction, iInfo->normal);
		reflect.position = iInfo->iCoordinate + reflect.direction;

		ray.direction = Reflect(ray.direction, iInfo->normal);
		if (rDepth > 0 && iInfo->material->specular.length() > cLimit.length()){
			c2 = (RGetColor(reflect, rDepth - 1, cLimit / iInfo->material->specular));			
			c3 = c2 * iInfo->material->specular;
			//c3 = c3 - c;			
		}
		c += c3;

		//Point3D lightAdd = Point3D();
		/*for (int i = 0; i < lightNum; i++){
			//1 = inShadow, 0 = no shadow
			int secCount = 0;
			if(lights[i]->isInShadow(*iInfo, group, secCount)==0){
				c = c + lights[i]->getDiffuse(camera->position, *iInfo);
				c = c + lights[i]->getSpecular(camera->position, *iInfo);
			}
		}*/
		//c += iInfo->material->diffuse;
		//c += iInfo->material->specular;
	}
	else return background;

	if (c.p[0] < 0) c.p[0] = 0;
	else if (c.p[0] > 1) c.p[0] = 1;
	if (c.p[1] < 0) c.p[1] = 0;
	else if (c.p[1] > 1) c.p[1] = 1;
	if (c.p[2] < 0) c.p[2] = 0;
	else if (c.p[2] > 1) c.p[2] = 1;
	return c;
}

Point3D RayScene::RGetColor(Ray3D ray,int rDepth,Point3D cLimit){
	RayIntersectionInfo* iInfo = new RayIntersectionInfo();
	float e = 0.01;
	Ray3D reflect = Ray3D();
	Ray3D refract = Ray3D();


	Point3D c = Point3D(0,0,0);
	Point3D c2 = Point3D(0,0,0);
	Point3D c3 = Point3D(0,0,0);

	if(group->intersect(ray, *iInfo, 1.0) != -1){
		c += ambient * iInfo->material->ambient;
		c += iInfo->material->emissive;
		//Point3D lightAdd = Point3D();
		for (int i = 0; i < lightNum; i++){
			//1 = inShadow, 0 = no shadow
			int secCount = 0;

			//if(lights[i]->isInShadow(*iInfo, group, secCount)==0){
				c = c + lights[i]->getDiffuse(camera->position, *iInfo);
				c = c + lights[i]->getSpecular(camera->position, *iInfo);
			//}
		}
		//Recursive ray casting
		
		reflect.direction = Reflect(ray.direction, iInfo->normal);
		reflect.position = iInfo->iCoordinate + reflect.direction;

		ray.direction = Reflect(ray.direction, iInfo->normal);
		if (rDepth > 0 && iInfo->material->specular.length() > cLimit.length()){
			c2 = (RGetColor(reflect, rDepth - 1, cLimit / iInfo->material->specular));			
			c3 = c2 * iInfo->material->specular;
			//c3 = c3 - c;			
		}
		c += c3;

		//Point3D lightAdd = Point3D();
		/*for (int i = 0; i < lightNum; i++){
			//1 = inShadow, 0 = no shadow
			int secCount = 0;
			if(lights[i]->isInShadow(*iInfo, group, secCount)==0){
				c = c + lights[i]->getDiffuse(camera->position, *iInfo);
				c = c + lights[i]->getSpecular(camera->position, *iInfo);
			}
		}*/
		//c += iInfo->material->diffuse;
		//c += iInfo->material->specular;
	}

	if (c.p[0] < 0) c.p[0] = 0;
	else if (c.p[0] > 1) c.p[0] = 1;
	if (c.p[1] < 0) c.p[1] = 0;
	else if (c.p[1] > 1) c.p[1] = 1;
	if (c.p[2] < 0) c.p[2] = 0;
	else if (c.p[2] > 1) c.p[2] = 1;
	return c;
}
//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
