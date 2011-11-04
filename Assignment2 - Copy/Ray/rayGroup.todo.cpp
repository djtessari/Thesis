#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////

//Comparison speed: 10.96
//Bounding Boxes: 5.89
//Ordering: 4.99
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	//printf("This runs\n");
	bool ignoreMX = false;
	if (mx == -1) ignoreMX = true;
	Ray3D rayCopy = Ray3D();
	rayCopy.position = ray.position;
	rayCopy.direction = ray.direction;

	double min_t = -1;
	RayShape* min_shape = NULL;
	RayIntersectionInfo tempInfo = RayIntersectionInfo();

	double boxOut = bBox.intersect(ray);
	if (boxOut < mx || ignoreMX){
		if(boxOut > -1){

			Matrix4D matrix = getMatrix();
			ray.position = getInverseMatrix().multPosition(ray.position);
			ray.direction = getInverseMatrix().multDirection(ray.direction);
			double scaler = ray.direction.length();
			ray.direction = ray.direction.unit();

			int count = 0;
			for (int i = 0; i < sNum; i++)
			{
				RayShape* temp = shapes[i];
				double dist = temp->bBox.intersect(ray);
				if(dist < mx || ignoreMX)
				{
					if (dist > -1)
					{
						//Means we have a hit of the inner volume
						hits[count].shape = temp;
						hits[count].t = dist;
						count++;
					}					 
				}
			}
			qsort(hits,count,sizeof(RayShapeHit),RayShapeHit::Compare);
		
	
		//if (bBox.intersect(ray) > -1){
			for (int i = 0; i < count; i++)
			{
				//printf("something got hit!\n");
				//printf("i = %i\n",i);
				RayShape* temp = hits[i].shape;
		
				double t = -1;		
		
				t = temp->intersect(ray, tempInfo, mx);
				if (t > 0)
				{
					t = t / scaler;
					if (min_t == -1 || t < min_t) 
					{	
						min_t = t;
						min_shape = temp;
						iInfo.iCoordinate = tempInfo.iCoordinate;
						iInfo.normal = tempInfo.normal;
						iInfo.material = tempInfo.material;	
						break;
					}
				}
				
																																						//Checks if its a Static Ray Group with its own transform information
		
			/*StaticRayGroup* temp2 = dynamic_cast<StaticRayGroup*>(temp);
			if(temp2 != 0) 
			{  
				t = temp->intersect(rayCopy, tempInfo, mx);
				if (t > 0)
				{
					if (min_t == -1 || t < min_t) 
					{
						iInfo.iCoordinate = tempInfo.iCoordinate;
						iInfo.normal = tempInfo.normal;
						iInfo.material = tempInfo.material;
						min_t = t;
						min_shape = temp;
					}			
				}
			}
			else 
			{
				ray.position = getInverseMatrix().multPosition(rayCopy.position);
				ray.direction = getInverseMatrix().multDirection(rayCopy.direction).unit();
				t = temp->intersect(ray, tempInfo, mx);

				if (t > 0)
				{
					if (min_t == -1 || t < min_t) 
					{
						iInfo.iCoordinate = matrix.multPosition(tempInfo.iCoordinate);
						iInfo.normal = getNormalMatrix().multNormal(tempInfo.normal);
						iInfo.material = tempInfo.material;
						min_t = t;
						min_shape = temp;
					}			
				}
			}*/		
			}	
			iInfo.iCoordinate = matrix.multPosition(iInfo.iCoordinate);
			iInfo.normal = getNormalMatrix().multDirection(iInfo.normal).unit();
			//iInfo.material = iInfo.material;
		}
	}
	return min_t;

}

BoundingBox3D RayGroup::setBoundingBox(void){
	bBox = shapes[0]->setBoundingBox();
	for (int i = 1; i < sNum; i++)
	{
		bBox = bBox + shapes[i]->setBoundingBox();
	}
	bBox = bBox.transform(getMatrix());
	return bBox;
}

int StaticRayGroup::set(void){
	/*
	Because you will be transforming the ray from local to global coordinates and vice versa many times, 
	it makes sense to compute the inverses and or transposes once and then store them, 
	rather than computing the matrix inverse for each ray. To help you with this, 
	the code definese members inverseTransform and normalTransform of the class StaticRayGroup for 
	storing the necessary matrices. You should set these when the matrix is initialized in StaticRayGroup::set 
	(Ray/rayGroup.todo.cpp) and then use the calls RayGroup::getInverseMatrix and RayGroup::getNormalMatrix to 
	get a copy of the matrices.
	*/
	/*printf("Matrix:\n");
	printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n\n", 
			localTransform.m[0][0], localTransform.m[1][0], localTransform.m[2][0], localTransform.m[3][0],
			localTransform.m[0][1], localTransform.m[1][1], localTransform.m[2][1], localTransform.m[3][1],
			localTransform.m[0][2], localTransform.m[1][2], localTransform.m[2][2], localTransform.m[3][2],
			localTransform.m[0][3], localTransform.m[1][3], localTransform.m[2][3], localTransform.m[3][3]);*/


	inverseTransform = localTransform.invert();
	//p�=((ML)t)-1(p)
	normalTransform = (localTransform.transpose()).invert();

	return 1;
}
//////////////////
// OpenGL stuff //
//////////////////
int RayGroup::getOpenGLCallList(void){
	return 0;
}

int RayGroup::drawOpenGL(int materialIndex){
	return -1;
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}