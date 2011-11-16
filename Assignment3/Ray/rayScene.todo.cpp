#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

///////////////////////
// Ray-tracing stuff //
///////////////////////

/*
	Point Tracker - Possible total so far: 18
	~~~~~~~~~~~~~~~~~~~~~~~~~
	(1) RayCamera::drawOpenGL
	(1) RayGroup::drawOpenGL
	(1) RaySphere::drawOpenGL
	(2) RayTriangle::drawOpenGL (problem with normals)
	(2) RayMaterial::drawOpenGL
	(3) RayLight::drawOpenGL (Not really but I'll get help)
	~10~
	(2) RayGroup::drawOpenGL - Transforms
	(2) RayGroup::getOpenGLCallList	
	(1) RayBox::drawOpenGL
	(1) Material index
	(1) RayCylinder::drawOpenGL
	(1) RayCone::drawOpenGL
	

	--Not Yet Done: 26--
	(3) RayTexture::drawOpenGL		
	(2) RayCamera::rotateUp/Right	
	(2) Full scene AA	
	(2) Allow user to raytrace
	(2) Submissions for art contest	

	(1) 4 walls, floor, ceiling
	(3) Table, Chairs, or other furnishings
	(1) A transparent surface
	(1) Three Texture Mapped Surfaces
	(1) Three point or spot light sources
	
	(2) Lamp with keyboard/mouse controls
	(2) A mirror
	(2) Shadows on at least one surface
	(2) An object that responds to mouse clicks

	Plan: (13)
	(1) 4 walls, floor, ceiling
	(3) RayTexture::drawOpenGL		
	(2) RayCamera::rotateUp/Right
	(2) Submissions for art contest
	(3) Table, Chairs, or other furnishings
	(1) A transparent surface
	(1) Three point or spot light sources
	~~~~~~~~~~~~~~~~~~~~~~~~~

*/
	bool enterMaterial = true;

Point3D RayScene::Reflect(Point3D v,Point3D n){
	// I - 2 * dot(N,I) * N

	Point3D out = Point3D();
	out = v - n*(2*n.dot(v));
	
	return out.unit();
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
	if(enterMaterial) {ir = 1 / ir;}
	//ir = 1 / ir;
	double c1 = -n.dot(v);
	Point3D R1 = v - n*(2*n.dot(v));
	double c2 = sqrt( 1 - pow(ir,2) * (1-pow(c1,2)));
	Point3D R2 = (v * ir) + (n * ((c1 - c2) * ir));
	refract = R2;

	enterMaterial = !enterMaterial;

	return 1;
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
	double AA = 1; //For aliasing
	Point3D cOut = Point3D(0,0,0);
	Ray3D backup = ray;
	srand( time(NULL) );
	for (int jitter = 0; jitter < AA; jitter++){
		enterMaterial = true;
		ray = backup;
		RayIntersectionInfo* iInfo = new RayIntersectionInfo();
		float e = 0.01;
		Ray3D reflect = Ray3D();
		Ray3D refract = Ray3D();

		if (AA > 1){
			for(int r = 0; r < 3; r++)
			{
				ray.position[r] += (((rand() % 2) - 0.5) / 100.0);
			}
		}

		Point3D c = Point3D(0,0,0);
		Point3D c2 = Point3D(0,0,0);
		Point3D c3 = Point3D(0,0,0);

		if(group->intersect(ray, *iInfo, -1) != -1){
			c += ambient * iInfo->material->ambient;
			c += iInfo->material->emissive;
			//Point3D lightAdd = Point3D();

			//Reflected Rays
			reflect.direction = Reflect(ray.direction, iInfo->normal);
			reflect.position = iInfo->iCoordinate + (reflect.direction * e);
		
			if (rDepth > 0 && iInfo->material->specular.length() > cLimit.length()){
				c2 = (RGetColor(reflect, rDepth - 1, cLimit / iInfo->material->specular));			
				c3 = c2 * iInfo->material->specular;
				//c3 = c3 - c;			
			}
			c += c3;

			//Refracted Rays
			Refract(ray.direction, iInfo->normal, 1 / iInfo->material->refind, refract.direction);
			//refract.direction = ray.direction;
			refract.position = iInfo->iCoordinate + (refract.direction * e);
		
			if (rDepth > 0 && iInfo->material->transparent.length() > cLimit.length()){
				c2 = (RGetColor(refract, rDepth - 1, cLimit / iInfo->material->transparent));			
				c3 = c2 * iInfo->material->transparent;
				//c3 = c3 - c;			
			}
			c += c3;

			for (int i = 0; i < lightNum; i++){
				//1 = inShadow, 0 = no shadow
				int secCount = 0;			
				c2 = lights[i]->getDiffuse(camera->position, *iInfo);
				c2 = c2 + lights[i]->getSpecular(camera->position, *iInfo);
				c2 = c2 * lights[i]->transparency(*iInfo, group, cLimit);
				c = c + c2;
			}
		
		}
		else c = background;
		if (c.p[0] < 0) c.p[0] = 0;
		else if (c.p[0] > 1) c.p[0] = 1;
		if (c.p[1] < 0) c.p[1] = 0;
		else if (c.p[1] > 1) c.p[1] = 1;
		if (c.p[2] < 0) c.p[2] = 0;
		else if (c.p[2] > 1) c.p[2] = 1;

		cOut += c;
	}
	//else return background;

	cOut = cOut / AA;

	if (cOut.p[0] < 0) cOut.p[0] = 0;
	else if (cOut.p[0] > 1) cOut.p[0] = 1;
	if (cOut.p[1] < 0) cOut.p[1] = 0;
	else if (cOut.p[1] > 1) cOut.p[1] = 1;
	if (cOut.p[2] < 0) cOut.p[2] = 0;
	else if (cOut.p[2] > 1) cOut.p[2] = 1;
	return cOut;
}

Point3D RayScene::RGetColor(Ray3D ray,int rDepth,Point3D cLimit){
	RayIntersectionInfo* iInfo = new RayIntersectionInfo();
	float e = 0.01;
	Ray3D reflect = Ray3D();
	Ray3D refract = Ray3D();


	Point3D c = Point3D(0,0,0);
	Point3D c2 = Point3D(0,0,0);
	Point3D c3 = Point3D(0,0,0);

	if(group->intersect(ray, *iInfo, -1) != -1){
		c += ambient * iInfo->material->ambient;
		c += iInfo->material->emissive;
		//Point3D lightAdd = Point3D();

		//Reflected Rays
		reflect.direction = Reflect(ray.direction, iInfo->normal);
		reflect.position = iInfo->iCoordinate + (reflect.direction * e);
		
		if (rDepth > 0 && iInfo->material->specular.length() > cLimit.length()){
			c2 = (RGetColor(reflect, rDepth - 1, cLimit / iInfo->material->specular));			
			c3 = c2 * iInfo->material->specular;
			//c3 = c3 - c;			
		}
		c += c3;

		//Refracted Rays
		Refract(ray.direction, iInfo->normal, 1 / iInfo->material->refind, refract.direction);
		//refract.direction = ray.direction;
		refract.position = iInfo->iCoordinate + (refract.direction * e);
		
		if (rDepth > 0 && iInfo->material->transparent.length() > cLimit.length()){
			c2 = (RGetColor(refract, rDepth - 1, cLimit / iInfo->material->transparent));			
			c3 = c2 * iInfo->material->transparent;
			//c3 = c3 - c;			
		}
		c += c3;

		for (int i = 0; i < lightNum; i++){
			//1 = inShadow, 0 = no shadow
			int secCount = 0;			
			c2 = lights[i]->getDiffuse(camera->position, *iInfo);
			c2 += lights[i]->getSpecular(camera->position, *iInfo);
			c2 = c2 * lights[i]->transparency(*iInfo, group, cLimit / iInfo->material->transparent);
			c = c + c2;
		}
		if (c.length() < cLimit.length())
		{
			return Point3D(0,0,0);
		}
		
	}
	else return c;

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
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 1.0, 1.0);
	//glColor3f(diffuse[0], diffuse[1], diffuse[2]);

	GLfloat mat_specular[] = {specular[0], specular[1], specular[2], 1.0};
	GLfloat mat_shininess[] = { specularFallOff };
	GLfloat mat_ambient[] = {ambient[0], ambient[1], ambient[2], 1.0};
	GLfloat mat_diffuse[] = {diffuse[0], diffuse[1], diffuse[2], 1.0};
	GLfloat mat_emissive[] = {emissive[0], emissive[1], emissive[2], 1.0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emissive);
}
void RayTexture::setUpOpenGL(void){
}
