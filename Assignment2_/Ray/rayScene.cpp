#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Image/bmp.h>
#include "rayScene.h"
#include "rayPointLight.h"
#include "rayDirectionalLight.h"
#include "raySpotLight.h"
#include "rayFileInstance.h"
#include "raySphere.h"
#include "rayBox.h"
#include "rayCone.h"
#include "rayCylinder.h"
#include "rayTriangle.h"
#include "rayGroup.h"

const static int BUF_SIZE=500;

int RayVertex::read(FILE* fp){
	double size;
	if(fscanf(fp," %lg %lg %lg %lg %lg %lg %lg %lg",
		&(position[0]),&(position[1]),&(position[2]),
		&(normal[0]),&(normal[1]),&(normal[2]),
		&(texCoordinate[0]),&(texCoordinate[1])) != 8){return 0;}
	size=normal.length();
	if(size==0.0){printf("No normal specified for vertex\n");}
	else{normal=normal/size;}
	return 1;
}
void RayVertex::write(FILE* fp){
	fprintf(fp,"#vertex\n");
	fprintf(fp,"   %lg %lg %lg\n",position[0],position[1],position[2]);
	fprintf(fp,"   %lg %lg %lg\n",normal[0],normal[1],normal[2]);
	fprintf(fp,"   %lg %lg\n",texCoordinate[0],texCoordinate[1]);
}

RayMaterial::RayMaterial(void){
	index=-1;
	ambient=specular=diffuse=emissive=transparent=Point3D(0,0,0);
	specularFallOff=0;
	refind=1;
	tex=NULL;
	this->foo[0]=0;
}
int RayMaterial::read(FILE* fp,int& temp){
	if(fscanf(fp," %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %d !%s!",
		&(emissive[0]),&(emissive[1]),&(emissive[2]),
		&(ambient [0]),&(ambient [1]),&(ambient [2]),
		&(diffuse [0]),&(diffuse [1]),&(diffuse [2]),
		&(specular[0]),&(specular[1]),&(specular[2]),&(specularFallOff),
		&(transparent[0]),&(transparent[1]),&(transparent[2]),
		&(refind),
		&temp,
		foo) != 19){return 0;}
	else{
		if(foo[strlen(foo)-1]=='!'){foo[strlen(foo)-1]='\0';}
		return 1;
	}
}
void RayMaterial::write(FILE* fp){
	int i;
	
	if(!tex){i=-1;}
	else{i=tex->index;}
	fprintf(fp,"#material\n");
	fprintf(fp,"   %lg %lg %lg\n",emissive[0],emissive[1],emissive[2]);
	fprintf(fp,"   %lg %lg %lg\n",ambient[0],ambient[1],ambient[2]);
	fprintf(fp,"   %lg %lg %lg\n",diffuse[0],diffuse[1],diffuse[2]);
	fprintf(fp,"   %lg %lg %lg %lg\n",specular[0],specular[2],specular[2],specularFallOff);
	fprintf(fp,"   %lg %lg %lg\n",transparent[0],transparent[1],transparent[2]);
	fprintf(fp,"   %lg\n",refind);
	fprintf(fp,"   %d\n",i);
	fprintf(fp,"   !%s!\n",foo);
}


RayTexture::RayTexture(void){
	index=0;
	filename[0]=0;
	img=NULL;
}
RayTexture::~RayTexture(void){if(img){delete img;}}

int RayTexture::read(FILE* f){
//	FILE *fp;
	
	if(fscanf(f," %s",filename) != 1){return 0;}
	img=new Image32();
	if(!img){return 0;}
	if(!img->ReadImage(filename)){
		printf("Failed to read image: %s\n",filename);
		return 0;
	}
/*
	fp=fopen(filename,"rb");
	if(!fp){
		delete img;
		img=NULL;
		return 0;
	}

	BMPReadImage(fp,*img);
	if(fclose(fp)){
		delete img;
		img=NULL;
		return 0;
	}
	*/
	return 1;
}
void RayTexture::write(FILE* fp){
	fprintf(fp,"#texture\n");
	fprintf(fp,"   %s\n",filename);
}
RayFile::~RayFile(void){if(scene){delete scene;}}
int RayFile::read(FILE* fp,int transformType){
	scene=new RayScene();
	if(!scene){return 0;}
	if(fscanf(fp," %s",filename) != 1 || !scene->read(filename,transformType)){
		delete scene;
		scene=NULL;
		return 0;
	}
	return 1;
}
void RayFile::write(FILE* fp){
	fprintf(fp,"#ray_file\n");
	fprintf(fp,"   %s\n",filename);
}


RayScene::RayScene(void){
	ambient=Point3D(0.0,0.0,0.0);
	background=Point3D(1.0,1.0,1.0);
	lights=NULL;
	lightNum=0;
	materials=NULL;
	materialNum=0;
	textures=NULL;
	textureNum=0;
	rayFiles=NULL;
	keyFileNum=0;
	keyFiles=NULL;
	keyData=NULL;
	vertexNum=0;
	vertices=NULL;
	group=NULL;
	camera=NULL;
}
RayMaterial* RayScene::getMaterial(int index){
	if(index<0 || index>=materialNum){return NULL;}
	return &(materials[index]);
}
RayScene::~RayScene(void){
	int i;
	for(i=0;i<lightNum;i++){delete lights[i];}
	if(lightNum>0){delete[] lights;}
	if(materialNum>0){delete[] materials;}
	if(textureNum>0){delete[] textures;}
	if(vertexNum>0){delete[] vertices;}
	if(rayFileNum>0){delete[] rayFiles;}
	if(group){delete group;}
	if(camera){delete camera;}
	if(keyFiles){delete[] keyFiles;}
	if(keyData){delete[] keyData;}
}
int RayScene::write(char* fileName){
	FILE* fp;
	if(!fileName){write(stdout);}
	else{
		fp=fopen(fileName,"w");
		if(!fp){return 0;}
		write(fp);
		fclose(fp);
	}
	return 1;
}
int RayScene::write(FILE* fp){
	int i;
	
	if(camera){camera->write(fp);}
	if(ambient[0] || ambient[1] || ambient[2]){
		fprintf(fp,"#ambient\n");
		fprintf(fp,"   %lg %lg %lg\n",ambient[0],ambient[1],ambient[2]);
	}
	if(background[0] || background[1] || background[2]){
		fprintf(fp,"#background\n");
		fprintf(fp,"   %lg %lg %lg\n",background[0],background[1],background[2]);
	}
	if(lightNum){
		fprintf(fp,"#light_num\n");
		fprintf(fp,"   %d\n",lightNum);
		for(i=0;i<lightNum;i++){lights[i]->write(fp);}
	}
	if(textureNum){
		fprintf(fp,"#texture_num\n");
		fprintf(fp,"   %d\n",textureNum);
		for(i=0;i<textureNum;i++){textures[i].write(fp);}
	}
	if(materialNum){
		fprintf(fp,"#material_num\n");
		fprintf(fp,"   %d\n",materialNum);
		for(i=0;i<materialNum;i++){materials[i].write(fp);}
	}
	if(vertexNum){
		fprintf(fp,"#vertex_num\n");
		fprintf(fp,"   %d\n",vertexNum);
		for(i=0;i<vertexNum;i++){vertices[i].write(fp);}
	}
	if(rayFileNum){
		fprintf(fp,"#ray_file_num\n");
		fprintf(fp,"   %d\n",rayFileNum);
		for(i=0;i<rayFileNum;i++){rayFiles[i].write(fp);}
	}
	for(i=0;i<group->shapeNum();i++){group->shapes[i]->write(0,fp);}
	return 1;
}

int RayScene::read(char* fileName,int transformType){
	FILE* fp;
	fp=fopen(fileName,"r");
	if(!fp){return 0;}
	int r=read(fp,transformType);
	fclose(fp);
	return r;
}
int RayScene::read(FILE* fp,int transformType){
	char keyword[BUF_SIZE];
	char keyFileName[BUF_SIZE];
	int cmndCtr=0;
	int backFlag=0, ambFlag=0;
	int indL=-1, indM=-1, indT=-1,indRF=-1,indV=-1,indK=-1;
	int temp;
	int inShapes=0;
	RayGroup* root;
	
	group=new StaticRayGroup();
	group->set(Matrix4D::IdentityMatrix());
	root=group;
	
	lightNum=-1;
	textureNum=-1;
	materialNum=-1;
	rayFileNum=-1;
	vertexNum=-1;
	keyFileNum=-1;
	keyFiles=NULL;
	keyData=NULL;
	lights=NULL;
	textures=NULL;
	materials=NULL;
	rayFiles=NULL;
	vertices=NULL;
	camera=NULL;
	
	
	while(fscanf(fp," #%s",keyword) == 1){
		cmndCtr++;
		
		//We try to read out the camera information. We make sure that we have
		//not begun describing the scene graph yet, and we ignore the camera if 
		//it is the second one specified.
		
		if(!strcmp(keyword,"camera")){
			if (inShapes!=0){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(camera){
				fprintf(stderr,"Parsing Line %d: Ignoring extra camera\n",cmndCtr);
			}
			else {
				camera=new RayCamera;
				if(!camera){
					ParseLineError(cmndCtr,"failed to allocate camera memory\n");
				}
				if(!camera->read(fp)){
					ParseLineError(cmndCtr,"failed to parse camera settings\n");
				}
			}
		}
		
		//Next we try to read out the environment information. Again, we make
		//sure that we have not begun describing the scene graph yet and we 
		//ignore all but the first background color and ambient color 
		//specifications.
		
		else if(!strcmp(keyword,"background")){
			if(inShapes){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(backFlag==1){
				fprintf(stderr,"Parsing Line %d: Ignoring extra background\n",cmndCtr);
			}
			else {
				backFlag=1;
				if(fscanf(fp," %lg %lg %lg",
					&(background[0]),&(background[1]),&(background[2])) != 3){
					ParseLineError(cmndCtr,"failed to parse background settings\n");
				}
			}
		}
		else if(!strcmp(keyword,"ambient")){
			if(inShapes){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(ambFlag==1){
				fprintf(stderr,"Parsing Line %d: Ignoring extra ambient\n",cmndCtr);
			}
			else {
				ambFlag=1;
				if(fscanf(fp," %lg %lg %lg",
					&(ambient[0]),&(ambient[1]),&(ambient[2])) != 3){
					ParseLineError(cmndCtr,"failed to parse ambient settings\n");
				}
			}
		}

		else if(!strcmp(keyword,"ambient")){
			if(inShapes){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(ambFlag==1){
				fprintf(stderr,"Parsing Line %d: Ignoring extra ambient\n",cmndCtr);
			}
			else {
				ambFlag=1;
				if(fscanf(fp," %lg %lg %lg",
					&(ambient[0]),&(ambient[1]),&(ambient[2])) != 3){
					ParseLineError(cmndCtr,"failed to parse ambient settings\n");
				}
			}
		}
		
		//Next we try read out the number of lights. We make sure that we have
		//not begun describing the scene graph, and we make sure that the number
		//of lights is only specified once. Once we have a "good" light number
		//we allocate memory for the lights 
		
		else if(!strcmp(keyword,"light_num")){
			if (inShapes!=0){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(lightNum>-1){
				ParseLineError(cmndCtr,"attempted to define light_num more than once\n");
			}
			else{
				if (fscanf(fp," %d", &(lightNum)) != 1){
					ParseLineError(cmndCtr,"failed to parse num_lights setting\n");
				}
				else{
					if(lightNum < 0){
						ParseLineError(cmndCtr,"you can't have negative number of lights\n");
					}
					else if(!lightNum){lights=NULL;}
					else {
						lights=new RayLight*[lightNum];
						if(!lights){
							ParseLineError(cmndCtr,"failed to allocate memory Lights\n");
						}
					}
				}
			}
		}
		
		//Next we try read out the number of textures. We make sure that we have
		//not begun describing the scene graph, and we make sure that the number
		//of textures is only specified once. Once we have a "good" texture number
		//we allocate memory for the textures.
		
		else if(!strcmp(keyword,"texture_num")){
			if(inShapes){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(textureNum>-1){
				ParseLineError(cmndCtr,"attempted to define texture_num more than once\n");
			}
			else{
				if(fscanf(fp," %d",&(textureNum)) != 1){
					ParseLineError(cmndCtr,"failed to parse num_textures setting\n");
				}
				else{
					if(textureNum < 0){
						ParseLineError(cmndCtr,"you can't have negative number of textures\n");
					}
					else if(!textureNum){textures=NULL;}
					else{
						textures=new RayTexture[textureNum];
						if(!textures){
							ParseLineError(cmndCtr,"failed to allocate memory for textures\n");
						}
					}
				}
			}
		}
		
		//Next we try read out the number of materials. We make sure that we have
		//not begun describing the scene graph, and we make sure that the number
		//of materials is only specified once. Once we have a "good" material
		//number we allocate memory for the materials.
		
		else if(!strcmp(keyword,"material_num")){
			if (inShapes){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(materialNum>-1){
				ParseLineError(cmndCtr,"attempted to define material_num more than once\n");
			}
			else{
				if(fscanf(fp," %d",&(materialNum)) != 1){
					ParseLineError(cmndCtr,"failed to parse num_materials setting\n");
				}
				else {
					if(materialNum < 0){
						ParseLineError(cmndCtr,"you can't have negative number of materials\n");
					}
					else{
						if(materialNum>0){
							materials=new RayMaterial[materialNum];
							if(!materials){
								ParseLineError(cmndCtr,"failed to allocate memory for materials\n");
							}
						}
						else{materials=NULL;}
					}
				}
			}
		}
		
		//Next we try read out the number of vertices. We make sure that we have
		//not begun describing the scene graph, and we make sure that the number
		//of vertices is only specified once. Once we have a "good" vertex
		//number we allocate memory for the vertices.
		
		else if(!strcmp(keyword,"vertex_num")){
			if (inShapes){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(vertexNum>-1){
				ParseLineError(cmndCtr,"attempted to define material_num more than once\n");
			}
			else{
				if(fscanf(fp," %d",&(vertexNum)) != 1){
					ParseLineError(cmndCtr,"failed to parse num_materials setting\n");
				}
				else {
					if(vertexNum < 0){
						ParseLineError(cmndCtr,"you can't have negative number of materials\n");
					}
					else{
						if(vertexNum>0){
							vertices=new RayVertex[vertexNum];
							if(!vertices){
								ParseLineError(cmndCtr,"failed to allocate memory for vertices\n");
							}
						}
						else{vertices=NULL;}
					}
				}
			}
		}
		
		//Next we try read out the number of ray files. We make sure that we have
		//not begun describing the scene graph, and we make sure that the number
		//of ray files is only specified once. Once we have a "good" ray file
		//number we allocate memory for the ray files.
		
		else if(!strcmp(keyword,"ray_file_num")){
			if (inShapes){ParseLineError(cmndCtr,"not a valid directive within a group\n");}
			if(rayFileNum>-1){ParseLineError(cmndCtr,"attempted to define ray_file_num more than once\n");}
			else{
				if(fscanf(fp," %d",&(rayFileNum)) != 1){ParseLineError(cmndCtr,"failed to parse ray_file_num setting\n");}
				else {
					if(rayFileNum<=0){rayFiles=NULL;}
					else{
						rayFiles=new RayFile[rayFileNum];
						if(!rayFiles){ParseLineError(cmndCtr,"failed to allocate memory for ray_files\n");}
					}
				}
			}
		}

		//Next we try read out the number of key-files. We make sure that we have
		//not begun describing the scene graph, and we make sure that the number
		//of key-files is only specified once. Once we have a "good" ray file
		//number we allocate memory for the ray files.
		
		else if(!strcmp(keyword,"key_file_num")){
			if (inShapes){ParseLineError(cmndCtr,"not a valid directive within a group\n");}
			if(keyFileNum>-1){ParseLineError(cmndCtr,"attempted to define key_file_num more than once\n");}
			else{
				if(fscanf(fp," %d",&(keyFileNum)) != 1){ParseLineError(cmndCtr,"failed to parse key_file_num setting\n");}
				else {
					if(keyFileNum<=0){
						keyFiles=NULL;
						keyData=NULL;
					}
					else{
						keyFiles=new RayKeyFile[keyFileNum];
						keyData=new RayKeyData[keyFileNum];
						if(!keyFiles || !keyData){ParseLineError(cmndCtr,"failed to allocate memory for key_files\n");}
					}
				}
			}
		}
		
		//Next we try read out the next textures. We make sure that we have
		//not begun describing the scene graph. We make sure that we are not
		//adding more textures then we promised and we make sure that all the
		//file I/O works as it should.
		
		else if(!strcmp(keyword,"texture")){
			if(inShapes){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(textureNum == -1){
				ParseLineError(cmndCtr,"attempted to define texture before texture_num\n");
			}
			indT++;
			if(indT == textureNum){
				ParseLineError(cmndCtr,"attempted to define more textures than declared\n");
			}
			if(!textures[indT].read(fp)){
				ParseLineError(cmndCtr,"failed to generate texture\n");
			}
			textures[indT].index=indT;
		}
		
		//Next we try read out the next material. We make sure that we have
		//not begun describing the scene graph. We make sure that we are not
		//adding more materials then we promised.
		
		else if(!strcmp(keyword,"material")){
			if(inShapes){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(materialNum==-1){
				ParseLineError(cmndCtr,"attempted to define materials before material_num\n");
			}
			indM++;
			if(indM == materialNum){
				ParseLineError(cmndCtr,"attempted to define more materials than declared\n");
			}
			else{
				if(!materials[indM].read(fp,temp)){
					ParseLineError(cmndCtr,"failed to parse material\n");
				}
				else{
					if(temp==-1){materials[indM].tex=NULL;}
					else{
						if(temp >= textureNum){
							ParseLineError(cmndCtr,
								"material specifies a texture out of texture_num bounds (make sure texture_num comes before material_num) \n");
						}
						materials[indM].tex=&(textures[temp]);
					}
					materials[indM].index=indM;
				}
			}
		}
		
		//Next we try read out the next vertex. We make sure that we have
		//not begun describing the scene graph. We make sure that we are not
		//adding more vertices then we promised.
		
		else if(!strcmp(keyword,"vertex")){
			if(inShapes){
				ParseLineError(cmndCtr,"not a valid directive within a group\n");
			}
			if(vertexNum==-1){
				ParseLineError(cmndCtr,"attempted to define vertices before vertex_num\n");
			}
			indV++;
			if(indV == vertexNum){
				ParseLineError(cmndCtr,"attempted to define more vertices than declared\n");
			}
			else{
				if(!vertices[indV].read(fp)){
					ParseLineError(cmndCtr,"failed to parse vertices\n");
				}
				else{vertices[indV].index=indV;}
			}
		}
		//Next we try to read out the next rayFile
		else if(!strcmp(keyword,"ray_file")){
			if(inShapes){ParseLineError(cmndCtr,"not a valid directive within a group\n");}
			if(rayFileNum==-1){ParseLineError(cmndCtr,"attempted to define ray_files before ray_file_num\n");}
			indRF++;
			if(indRF == rayFileNum){ParseLineError(cmndCtr,"attempted to define more ray_files than declared\n");}
			else{
				if(!rayFiles[indRF].read(fp,transformType)){ParseLineError(cmndCtr,"failed to parse ray_file\n");}
				rayFiles[indRF].index=indRF;
			}
		}
		
		//Next we try read out the next light. We make sure that we have
		//not begun describing the scene graph. We make sure that we are not
		//adding more materials then we promised.
		
		else if(!strcmp(keyword,"light_point") || !strcmp(keyword,"light_dir") || !strcmp(keyword,"light_spot")){
			if(inShapes){ParseLineError(cmndCtr,"not a valid directive within a group\n");}
			if(lightNum==-1){ParseLineError(cmndCtr,"attempted to define lights before light_num\n");}
			indL++;
			if(indL == lightNum){ParseLineError(cmndCtr,"attempted to define more lights than light_num\n");}
			else{
				if(!strcmp(keyword,"light_point")){lights[indL]=new RayPointLight;}
				else if(!strcmp(keyword,"light_dir")){lights[indL]=new RayDirectionalLight;}
				else if(!strcmp(keyword,"light_spot")){lights[indL]=new RaySpotLight;}
				if(!lights[indL]){ParseLineError(cmndCtr,"failed to allocate memory for light\n");}
				if(!lights[indL]->read(fp)){ParseLineError(cmndCtr,"failed to parse light\n");}
			}
		}

		//Next we try to read out the .key file. We make sure that we have not
		//begun describing the scene graph.
		else if(!strcmp(keyword,"key_file")){
			if(inShapes){ParseLineError(cmndCtr,"not a valid directive within a group\n");}
			if(keyFileNum==-1){ParseLineError(cmndCtr,"attempted to define key_files before key_file_num\n");}
			indK++;
			if(indK == keyFileNum){ParseLineError(cmndCtr,"attempted to define more key_files than key_file_num\n");}
			fscanf(fp," %s",keyFileName);
			if(!keyFiles[indK].read(keyFileName)){ParseLineError(cmndCtr,"failed to read in key_file\n");}
			if(!keyData[indK].set(keyFiles[indK],transformType)){ParseLineError(cmndCtr,"failed to set key file data\n");}
			keyData[indK].setCurrentValue(0);
		}
		
		//Next we try read out the scene graph information, obtaining the 
		//transform and either creating a new scene graph or adding a node
		//to the existing one.
		
		else if(!strcmp(keyword,"group_begin")){
			inShapes=1;
			ParseGroup(fp,cmndCtr,root);
		}
		else if(!strcmp(keyword,"joint_begin")){
			inShapes=1;
			ParseJoint(fp,cmndCtr,root);
		}
		
		//We check if we have come to the end of a scene-graph group. If we have
		//this is bad because we have not yet opened one
		
		else if(!strcmp(keyword,"group_end")){
			ParseLineError(cmndCtr,"closed more groups then began\n");
		}
		else if(!strcmp(keyword,"joint_end")){
			ParseLineError(cmndCtr,"closed more joints then began\n");
		}
		else if(ParseShape(fp,keyword,cmndCtr,root)){inShapes=1;}
		else{
			fprintf(stderr,
				"Ignoring Command %d: No valid #directive...%s \n",cmndCtr,
				keyword);
		}		
	}		
	if(indL<(lightNum-1)){ParseError("Couldn't find enough lights for light_num");}
	if(indM<(materialNum-1)){ParseError("Couldn't find enough materials for material_num");}
	if(indT<(textureNum-1)){ParseError("Couldn't find enough textures for texture_num");}
	if(indRF<(rayFileNum-1)){ParseError("Couldn't find enough ray_files for ray_file_num");}
	if(lightNum==-1){lightNum=0;}
	if(materialNum==-1){materialNum=0;}
	if(textureNum==-1){textureNum=0;}
	if(rayFileNum==-1){rayFileNum=0;}
	if(vertexNum==-1){vertexNum=0;}
	return 1;
}

void RayScene::ParseGroup(FILE* fp,int& cmndCtr,RayGroup* current){
	char keyword[BUF_SIZE];
	RayGroup *currNode,*newNode;
	currNode=current;
	newNode=new StaticRayGroup();
	if(!newNode || !((StaticRayGroup*)newNode)->read(fp)){ParseLineError(cmndCtr,"failed to allocate memory for StaticGroup\n");}
	currNode->addShape(newNode);
	currNode=newNode;
	
	while(fscanf(fp," #%s",keyword) == 1){
		cmndCtr++;
		if(!strcmp(keyword,"group_begin")){ParseGroup(fp,cmndCtr,currNode);}
		else if(!strcmp(keyword,"joint_begin")){ParseJoint(fp,cmndCtr,currNode);}
		
		/* We check if we have come to the end of a scene-graph group and we
		* do the appropriate pointer manipulation, making sure that we are not
		* leaving a group we had not begun */
		else if(!strcmp(keyword,"group_end")){return;}
		else if(!strcmp(keyword,"joint_end")){ParseLineError(cmndCtr,"joint_end within a group\n");}
		else if(ParseShape(fp,keyword,cmndCtr,currNode)){;}
		else {fprintf(stderr,"Ignoring Command %d: No valid #directive...%s \n",cmndCtr,keyword);}
	}
	ParseLineError(cmndCtr,"no group_end\n");
}
void RayScene::ParseJoint(FILE* fp,int& cmndCtr,RayGroup* current){
	char paramName[BUF_SIZE];
	char keyword[BUF_SIZE];

	ParametrizedRayGroup *newNode;
	RayGroup *currNode;
	int i,idx=-1;
	
	currNode=current;
	if(!fscanf(fp," %s ",paramName)){ParseLineError(cmndCtr,"failed to read parameter name\n");}
	for(i=0;i<keyFileNum;i++){
		idx=keyFiles[i].index(paramName);
		if(idx>=0){break;}
	}
	newNode=keyData[i].getParametrizedRayGroup(idx);
	if(!newNode){ParseLineError(cmndCtr,"failed to link joint node to parameter\n");}
	strcpy(newNode->pName,paramName);
	currNode->addShape(newNode);
	currNode=newNode;
	
	while(fscanf(fp," #%s",keyword) == 1){
		cmndCtr++;
		if(strcmp(keyword,"group_begin") == 0){ParseGroup(fp,cmndCtr,currNode);}
		else if(strcmp(keyword,"joint_begin") == 0){ParseJoint(fp,cmndCtr,currNode);}
		else if(!strcmp(keyword,"joint_end")){return;}
		else if(!strcmp(keyword,"group_end")){ParseLineError(cmndCtr,"group_end within a joint\n");}
		else if(ParseShape(fp,keyword,cmndCtr,currNode)){;}
		else {fprintf(stderr,"Ignoring Command %d: No valid #directive...%s \n",cmndCtr,keyword);}
	}
	ParseLineError(cmndCtr,"no group_end\n");
}
int RayScene::ParseShape(FILE* fp,const char* keyword,int cmndCtr,RayGroup* curr){
	int temp;
	RayGroup* current=curr;
	RayFileInstance* rayFileInstance;
	RaySphere* sphere;
	RayCone* cone;
	RayCylinder* cylinder;
	RayTriangle* triangle;
	RayBox* box;
	
	/* If we are reading in new files we want them added to the current node
	* and we want to store there information in a temporary scene object we
	* will conveniently forget to free up. */
	
	if(!strcmp(keyword,"ray_file_instance")){
		if(fscanf(fp," %d",&temp) != 1){ParseLineError(cmndCtr,"could not read ray_file index number\n");}
		if(temp<0){ParseLineError(cmndCtr,"you cannot have negative ray_file index\n");}
		if(temp>=rayFileNum){ParseLineError(cmndCtr,"shape specifies a ray_file out of ray_file_num bounds (make sure ray_file_num comes before the root group) \n");}
		rayFileInstance=new RayFileInstance(&(rayFiles[temp]));
		if(!rayFileInstance){ParseLineError(cmndCtr,"failed to allocate memory for Shape\n");}
		current->addShape(rayFileInstance);
		return 1;
	}
	/* We start reading in the shapes. We check that we are inside
	* a group and we call the appropriate instantiator */	
	
	else if(!strcmp(keyword,"shape_sphere")){
		sphere=new RaySphere();
		if(!sphere || !sphere->read(fp,&temp)){ParseLineError(cmndCtr,"failed to allocate memory for Sphere\n");}
		if(temp >= materialNum){ParseLineError(cmndCtr,"shape specifies a material out of material_num bounds (make sure material_num comes before the root group) \n");}
		else if(temp<0){ParseLineError(cmndCtr,"you cannot have a negative material index\n");}
		else{sphere->material=&(materials[temp]);}
		current->addShape(sphere);
		return 1;
	}
	
	else if(!strcmp(keyword,"shape_box")){
		box=new RayBox();
		if (!box || !box->read(fp,&temp)){ParseLineError(cmndCtr,"failed to allocate memory for Box\n");}
		if(temp >= materialNum){ParseLineError(cmndCtr,"shape specifies a material out of material_num bounds (make sure material_num comes before the root group) \n");}
		else if(temp<0){ParseLineError(cmndCtr,"you cannot have a negative material index\n");}
		else{box->material=&(materials[temp]);}
		current->addShape(box);
		return 1;
	}
    
	else if(!strcmp(keyword,"shape_cone")){
		cone=new RayCone();
		if(!cone || !cone->read(fp,&temp)){ParseLineError(cmndCtr,"failed to allocate memory for Cone\n");}
		if(temp >= materialNum){ParseLineError(cmndCtr,"shape specifies a material out of material_num bounds (make sure material_num comes before the root group) \n");}
		else if(temp<0){ParseLineError(cmndCtr,"you cannot have a negative material index\n");}
		else{cone->material=&(materials[temp]);}
		current->addShape(cone);
		return 1;
	}
	
	else if(!strcmp(keyword,"shape_cylinder")){
		cylinder=new RayCylinder();
		if (!cylinder || !cylinder->read(fp,&temp)){ParseLineError(cmndCtr,"failed to allocate memory for Cylinder\n");}
		if(temp >= materialNum){ParseLineError(cmndCtr,"shape specifies a material out of material_num bounds (make sure material_num comes before the root group) \n");}
		else if(temp<0){ParseLineError(cmndCtr,"you cannot have a negative material index\n");}
		else{cylinder->material=&(materials[temp]);}
		current->addShape(cylinder);
		return 1;
	}
	else if(!strcmp(keyword,"shape_triangle")){
		triangle=new RayTriangle();
		if(!triangle){ParseLineError(cmndCtr,"failed to allocate memory for Triangle\n");}
		if(!triangle->read(fp,&temp,vertices,vertexNum)){
			printf("Could not read triangle\n");
			return 1;
		}
		if(temp >= materialNum){ParseLineError(cmndCtr,"shape specifies a material out of material_num bounds (make sure material_num comes before the root group) \n");}
		else if(temp<0){ParseLineError(cmndCtr,"you cannot have a negative material index\n");}
		else{triangle->material=&(materials[temp]);}
		current->addShape(triangle);
		return 1;
	}
	return 0;
}		


void RayScene::setUpOpenGL(int cplx){
	int i;
	for(i=0;i<textureNum;i++){textures[i].setUpOpenGL();}
	for(i=0;i<rayFileNum;i++){rayFiles[i].scene->setUpOpenGL(cplx);}

	group->setUpOpenGL(cplx,1);
}
void RayScene::drawOpenGL(void){
	camera->drawOpenGL();

	glEnable(GL_LIGHTING);
	for(int i=0;i<lightNum;i++){lights[i]->drawOpenGL(i);}	
	
	group->drawOpenGL(-1);
}
void RayScene::setCurrentTime(double t,int curveFit){
	int i;
	for(i=0;i<keyFileNum;i++){
		double tt=t/keyFiles[i].duration;
		tt-=(int)tt;
		keyData[i].setCurrentValue(tt,curveFit);
	}
	for(i=0;i<rayFileNum;i++){rayFiles[i].scene->setCurrentTime(t,curveFit);}
}

int RayScene::RayTrace(const int& width,const int& height,const int& rLimit,const double& cLimit,Image32& img){
	int i,j;
	Ray3D ray;
	Point3D c;
	Pixel32 p;
	int rayCount=0;

	if(!img.setSize(width,height)){return 0;}
	ray.position=camera->position;
	for(i=0;i<width;i++){
		printf("           \r");
		printf("%3.1f\r",(float)i/width*100);
		for(j=0;j<height;j++){
			ray=GetRay(camera,i,height-j-1,width,height);
			c=GetColor(ray,rLimit,Point3D(cLimit,cLimit,cLimit));
			p.r=(int)(c[0]*255);
			p.g=(int)(c[1]*255);
			p.b=(int)(c[2]*255);
			img(i,j)=p;
		}
	}
	return 1;
}

void RayScene::ParseError(const char *s1){
	fprintf(stderr, "Parsing error: %s\n", s1);
	exit(EXIT_FAILURE);
}

void RayScene::ParseLineError(int i,const char *s){
	fprintf(stderr, "Parsing error of command %d: %s\n",i,s);
	exit(EXIT_FAILURE);
}

