#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Util/geometry.h>
#include "raySpotLight.h"
#include "rayScene.h"

int RaySpotLight::read(FILE* fp){
	if (fscanf(fp," %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg", 
		&(color[0]),&(color[1]),&(color[2]),
		&(location[0]),&(location[1]),&(location[2]),
		&(direction[0]),&(direction[1]),&(direction[2]),
		&(constAtten),&(linearAtten),&(quadAtten),
		&(cutOffAngle),&(dropOffRate)) != 14){return 0;}
	direction=direction.unit();
	return 1;
}
void RaySpotLight::write(FILE* fp){
	fprintf(fp,"#light_spot\n");
	fprintf(fp,"  %lg %lg %lg\n",color[0],color[1],color[2]);
	fprintf(fp,"  %lg %lg %lg\n",location[0],location[1],location[2]);
	fprintf(fp,"  %lg %lg %lg\n",direction[0],direction[1],direction[2]);
	fprintf(fp,"  %lg %lg %lg\n",constAtten,linearAtten,quadAtten);
	fprintf(fp,"  %lg %lg\n",cutOffAngle,dropOffRate);
}
