#include <stdlib.h>
#include <math.h>

#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>

#include "geometry.h"


///////////////////////
// Ray-tracing stuff //
///////////////////////
double BoundingBox3D::intersect(const Ray3D& ray) const {
	Point3D pt;
	double t;
	double dist=-1.0;
	
	/* If the ray is inside the box... */
	if(	ray.position.p[0]>=p[0].p[0] && ray.position.p[0]<=p[1].p[0] &&
		ray.position.p[1]>=p[0].p[1] && ray.position.p[1]<=p[1].p[1] &&
		ray.position.p[2]>=p[0].p[2] && ray.position.p[2]<=p[1].p[2]){return 0.0;}

	// The ray is outside the box
	if(ray.direction.p[0]>0){
		t=(p[0].p[0]-ray.position.p[0])/ray.direction.p[0];
		if(t>=0){
			pt=ray(t);
			if(pt.p[1]>=p[0].p[1] && pt.p[1]<=p[1].p[1] && pt.p[2]>=p[0].p[2] && pt.p[2]<=p[1].p[2]){return t;}
		}
	}
	else if(ray.direction.p[0]<0){
		t=(p[1].p[0]-ray.position.p[0])/ray.direction.p[0];
		if(t>=0){
			pt=ray(t);
			if(pt.p[1]>=p[0].p[1] && pt.p[1]<=p[1].p[1] && pt.p[2]>=p[0].p[2] && pt.p[2]<=p[1].p[2]){return t;}
		}
	}
	if(ray.direction.p[1]>0.0){
		t=(p[0].p[1]-ray.position.p[1])/ray.direction.p[1];
		if(t>=0){
			pt=ray(t);
			if(pt.p[0]>=p[0].p[0] && pt.p[0]<=p[1].p[0] && pt.p[2]>=p[0].p[2] && pt.p[2]<=p[1].p[2]){return t;}
		}
	}
	else if(ray.direction.p[1]<0.0){
		t=(p[1].p[1]-ray.position.p[1])/ray.direction.p[1];
		if(t>=0){
			pt=ray(t);
			if(pt.p[0]>=p[0].p[0] && pt.p[0]<=p[1].p[0] && pt.p[2]>=p[0].p[2] && pt.p[2]<=p[1].p[2]){return t;}
		}
	}
	if(ray.direction.p[2]>0.0){
		t=(p[0].p[2]-ray.position.p[2])/ray.direction.p[2];
		if(t>=0){
			pt=ray(t);
			if(pt.p[0]>=p[0].p[0] && pt.p[0]<=p[1].p[0] && pt.p[1]>=p[0].p[1] && pt.p[1]<=p[1].p[1]){return t;}
		}
	}
	else if(ray.direction.p[2]<0.0){
		t=(p[1].p[2]-ray.position.p[2])/ray.direction.p[2];
		if(t>=0){
			pt=ray(t);
			if(pt.p[0]>=p[0].p[0] && pt.p[0]<=p[1].p[0] && pt.p[1]>=p[0].p[1] && pt.p[1]<=p[1].p[1]){return t;}
		}
	}
	return -1;
//	return -1;
}

/////////////////////
// Animation stuff //
/////////////////////
Matrix3D::Matrix3D(const Point3D& e){
	double cos1=cos(e.p[0]);
	double sin1=sin(e.p[0]);
	double cos2=cos(e.p[1]);
	double sin2=sin(e.p[1]);
	double cos3=cos(e.p[2]);
	double sin3=sin(e.p[2]);

	m[0][0]=cos2*cos3;
	m[1][0]=sin2*sin1*cos3-cos1*sin3;
	m[2][0]=cos1*sin2*cos3+sin1*sin3;
	m[0][1]=cos2*sin3;
	m[1][1]=sin1*sin2*sin3+cos1*cos3;
	m[2][1]=cos1*sin2*sin3-sin1*cos3;
	m[0][2]=-sin2;
	m[1][2]=cos2*sin1;
	m[2][2]=cos2*cos1;
//	(*this)=Matrix3D();
}

Matrix3D::Matrix3D(const Quaternion& q){
	m[0][0]=q.real*q.real+q.imag.p[0]*q.imag.p[0]-q.imag.p[1]*q.imag.p[1]-q.imag.p[2]*q.imag.p[2];
	m[1][1]=q.real*q.real-q.imag.p[0]*q.imag.p[0]+q.imag.p[1]*q.imag.p[1]-q.imag.p[2]*q.imag.p[2];
	m[2][2]=q.real*q.real-q.imag.p[0]*q.imag.p[0]-q.imag.p[1]*q.imag.p[1]+q.imag.p[2]*q.imag.p[2];
	m[1][0]=2*(q.imag.p[0]*q.imag.p[1]-q.real*q.imag.p[2]);
	m[0][1]=2*(q.imag.p[0]*q.imag.p[1]+q.real*q.imag.p[2]);
	m[2][0]=2*(q.imag.p[0]*q.imag.p[2]+q.real*q.imag.p[1]);
	m[0][2]=2*(q.imag.p[0]*q.imag.p[2]-q.real*q.imag.p[1]);
	m[2][1]=2*(q.imag.p[1]*q.imag.p[2]-q.real*q.imag.p[0]);
	m[1][2]=2*(q.imag.p[1]*q.imag.p[2]+q.real*q.imag.p[0]);
//	(*this)=Matrix3D();
}
Matrix3D Matrix3D::closestRotation(void) const {
	Matrix3D r1,d,r2;
	SVD(r1,d,r2);
	int s=1;
	for(int i=0;i<3;i++){
		if(d(i,i)<0){
			s*=-1;
			d(i,i)=-1;
		}
		else{d(i,i)=1;}
	}
	if(s<0){d(2,2)*=-1;}
	return r1*d*r2;
//	return (*this);
}
/* While these Exp and Log implementations are the direct implementations of the Taylor series, the Log
 * function tends to run into convergence issues so we use the other ones:*/
Matrix3D Matrix3D::Exp(const Matrix3D& m,int iter){
	Matrix3D X;
	Matrix3D A;
	for(int i=1;i<=iter;i++){
		A/=i;
		A*=m;
		X+=A;
	}
	return X;
//	return m;
}
