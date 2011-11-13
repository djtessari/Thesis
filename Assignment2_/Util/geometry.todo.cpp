#include <stdlib.h>
#include <math.h>

#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>

#include "geometry.h"


///////////////////////
// Ray-tracing stuff //
///////////////////////
double BoundingBox3D::intersect(const Ray3D& ray) const {
	Point3D pS = p[0];
	Point3D pB = p[1];
	Point3D pos = ray.position;
	Point3D dir = ray.direction;

	double t1 = 0;
	double t2 = 0;
	double tNear = -1000;
	double tFar = 1000;
	
	//Check if ray starts inside volume
	if (pos[0] < pB[0] && pos[1] < pB[1] && pos[2] < pB[2]){
		if (pos[0] > pS[0] && pos[1] > pS[1] && pos[2] > pS[2]){
			//printf("Zero reject\n");
			return 0;
		}
	}
	//Else, try to find intersect
	int out = 0;
	for (int i = 0; i < 3; i++){
		if (dir[i] == 0){
			if (pos[i] < pS[i] || pos[i] > pB[i]) return -1;
			//printf("Parallel reject\n");
		}
		else{
			t1 = (pS[i] - pos[i]) / dir[i];
			t2 = (pB[i] - pos[i]) / dir[i];
			//printf("t1: %f\n",t1);
			//printf("t2: %f\n",t2);
			if (t1 > t2) 
			{
				double temp = t1;
				t1 = t2;
				t2 = temp;
			}
			if (t1 > tNear) tNear = t1;
			if (t2 < tFar) tFar = t2;
			if (tNear > tFar){ return -1; }
			if (tFar < 0){ return -1; }
		}
	}	
	//printf("tNear: %f\n",tNear);
	//printf("tFar: %f\n",tFar);
	return tNear;
}

/////////////////////
// Animation stuff //
/////////////////////
Matrix3D::Matrix3D(const Point3D& e){
	(*this)=Matrix3D();
}

Matrix3D::Matrix3D(const Quaternion& q){
	(*this)=Matrix3D();
}
Matrix3D Matrix3D::closestRotation(void) const {
	return (*this);
}
/* While these Exp and Log implementations are the direct implementations of the Taylor series, the Log
 * function tends to run into convergence issues so we use the other ones:*/
Matrix3D Matrix3D::Exp(const Matrix3D& m,int iter){
	return m;
}
