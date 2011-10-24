#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Util/geometry.h>
#include "rayDirectionalLight.h"
#include "rayScene.h"

int RayDirectionalLight::read(FILE* fp){
	if (fscanf(fp," %lg %lg %lg %lg %lg %lg",
		&(color[0]),&(color[1]),&(color[2]),
		&(direction[0]),&(direction[1]),&(direction[2])
		) != 6){return 0;}
	direction=direction.unit();
	return 1;
}
void RayDirectionalLight::write(FILE* fp){
	fprintf(fp,"#light_dir\n");
	fprintf(fp,"  %lg %lg %lg\n",color[0],color[1],color[2]);
	fprintf(fp,"  %lg %lg %lg\n",direction[0],direction[1],direction[2]);
}
