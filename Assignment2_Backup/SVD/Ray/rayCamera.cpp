#include "rayCamera.h"

int RayCamera::read(FILE* fp){
	if(fscanf(fp," %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg",
		&(position[0]),&(position[1]),&(position[2]),
		&(direction[0]),&(direction[1]),&(direction[2]),
		&(up[0]),&(up[1]),&(up[2]),
		&(heightAngle)) !=10 ) {return 0;}
	direction=direction.unit();
	up=up.unit();
	right=direction.crossProduct(up);
	return 1;
}
void RayCamera::write(FILE* fp){
	fprintf(fp,"#camera\n");
	fprintf(fp,"   %lg %lg %lg\n",position[0],position[1],position[2]);
	fprintf(fp,"   %lg %lg %lg\n",direction[0],direction[1],direction[2]);
	fprintf(fp,"   %lg %lg %lg\n",up[0],up[1],up[2]);
	fprintf(fp,"   %lg\n",heightAngle);
}
