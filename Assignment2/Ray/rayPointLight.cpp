#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Util/geometry.h>
#include "rayPointLight.h"
#include "rayScene.h"

int RayPointLight::read(FILE* fp){
	if(fscanf(fp," %lg %lg %lg %lg %lg %lg %lg %lg %lg", 
		&(color[0]),&(color[1]),&(color[2]),
		&(location[0]),&(location[1]),&(location[2]),
		&(constAtten),&(linearAtten),&(quadAtten)) != 9){return 0;}
	return 1;
}
void RayPointLight::write(FILE* fp){
	fprintf(fp,"#light_point\n");
	fprintf(fp,"  %lg %lg %lg\n",color[0],color[1],color[2]);
	fprintf(fp,"  %lg %lg %lg\n",location[0],location[1],location[2]);
	fprintf(fp,"  %lg %lg %lg\n",constAtten,linearAtten,quadAtten);
}
