#include <stdio.h>
#include <string.h>
#include <Util/geometry.h>
#include <Util/cmdLineParser.h>
#include "rayGroup.h"
#include "rayKey.h"

#ifdef _WIN32
#include <windows.h>
#define strcasecmp lstrcmpi
#endif

////////////////
// RayKeyFile //
////////////////
RayKeyFile::RayKeyFile(void){
	pNames=NULL;
	keyTransforms=NULL;
	sNum=pNum=0;
}
RayKeyFile::~RayKeyFile(void){
	if(pNames){
		for(int i=0;i<pNum;i++){if(pNames[i]){delete[] pNames[i];}}
		delete[] pNames;
	}
	if(keyTransforms){delete[] keyTransforms;}
	pNames=NULL;
	keyTransforms=NULL;
}
Matrix4D* RayKeyFile::operator[] (int index){return &keyTransforms[index*pNum];}
const char* RayKeyFile::name(int idx){return pNames[idx];}
int RayKeyFile::samples(void){return sNum;}
int RayKeyFile::parameters(void){return pNum;}
int RayKeyFile::index(char* name){
	for(int i=0;i<pNum;i++){if(!strcasecmp(name,pNames[i])){return i;}}
	return -1;
}

int RayKeyFile::read(char* fileName){
	FILE* fp;
	float t;
	int i;
	char temp[100];

	if(pNames){
		for(int i=0;i<pNum;i++){if(pNames[i]){delete[] pNames[i];}}
		delete[] pNames;
	}
	if(keyTransforms){delete[] keyTransforms;}
	pNames=NULL;
	keyTransforms=NULL;

	fp=fopen(fileName,"r");
	if(!fp){return 0;}

	if(fscanf(fp," #DOFS %d ",&pNum)!=1 || pNum<=0){
		fclose(fp);
		return 0;
	}
	pNames=new char*[pNum];
	if(!pNames){
		fclose(fp);
		return 0;
	}
	for(i=0;i<pNum;i++){
		if(fscanf(fp," %s ",&temp)!=1){
			delete[] pNames;
			pNames=NULL;
			fclose(fp);
			return 0;
		}
		pNames[i]=new char[strlen(temp)+1];
		if(!pNames[i]){
			for(int j=0;j<i;j++){delete[] pNames[j];}
			delete[] pNames;
			pNames=NULL;
			fclose(fp);
			return 0;
		}
		strcpy(pNames[i],temp);
	}

	if(fscanf(fp," #DURATION %f ",&duration)!=1 || duration<=0 || fscanf(fp," #FRAMES %d ",&sNum)!=1 || sNum<=0){
		for(i=0;i<pNum;i++){delete[] pNames[i];}
		delete[] pNames;
		pNames=NULL;
		fclose(fp);
		return 0;
	}

	keyTransforms=new Matrix4D[sNum*pNum];
	if(!keyTransforms){
		for(i=0;i<pNum;i++){delete[] pNames[i];}
		delete[] pNames;
		pNames=NULL;
		fclose(fp);
		return 0;
	}

	for(i=0;i<pNum*sNum;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				if(fscanf(fp," %f",&t)!=1){
					for(int l=0;l<pNum;l++){delete[] pNames[l];}
					delete[] pNames;
					delete[] keyTransforms;
					pNames=NULL;
					keyTransforms=NULL;
					fclose(fp);
					return 0;
				}
				keyTransforms[i](j,k)=t;
			}
		}
	}
	fclose(fp);
	return 1;
}
int RayKeyFile::write(char* fileName){
	FILE* fp;
	int i;


	fp=fopen(fileName,"w");
	if(!fp){return 0;}

	fprintf(fp," #DOFS %d ",pNum);
	for(i=0;i<pNum;i++){fprintf(fp,"\t%s\n",pNames[i]);}
	fprintf(fp," #DURATION %f\n",duration);
	fprintf(fp," #FRAMES %d\n",sNum);
	for(i=0;i<pNum;i++){
		fprintf(fp,"\t");
		for(int j=0;j<sNum;j++){
			for(int k=0;k<4;k++){
				for(int l=0;l<4;l++){
					fprintf(fp," %f",keyTransforms[i*sNum+j](k,l));
				}
			}
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	return 1;
}



////////////////
// RayKeyData //
////////////////
const int RayKeyData::MATRIX						=0;
const int RayKeyData::EULER_AND_TRANSLATION			=1;
const int RayKeyData::CLOSEST_R_AND_TRANSLATION		=2;
const int RayKeyData::R_LOGARITHM_AND_TRANSLATION	=3;
const int RayKeyData::QUATERNION_AND_TRANSLATION	=4;

RayKeyData::RayKeyData(void){
	pNum=0;
	sampleData=NULL;
	type=-1;
}
RayKeyData::~RayKeyData(void){clear();}
void RayKeyData::clear(void){
	if(sampleData){
		for(int i=0;i<pNum;i++){if(sampleData[i]){delete sampleData[i];	}}
		delete[] sampleData;
	}
	sampleData=NULL;
	pNum=0;
	type=-1;
}

void RayKeyData::setCurrentValue(double t,int curveType){
	for(int i=0;i<pNum;i++){sampleData[i]->setCurrentValue(t,curveType);}
}
ParametrizedRayGroup*  RayKeyData::getParametrizedRayGroup(int i){
	ParametrizedMatrix4D *matrix;
	ParametrizedEulerAnglesAndTranslation* eulerAndTranslation;
	ParametrizedClosestRotationAndTranslation* rClosestAndTranslation;
	ParametrizedRotationLogarithmAndTranslation* rLogarithmAndTranslation;
	ParametrizedQuaternionAndTranslation* quaternionAndTranslation;
	if(i<0 || i>=pNum){return NULL;}

	switch(type){
	case MATRIX:
		matrix=new ParametrizedMatrix4D;
		if(!matrix){return NULL;}
		matrix->value=&(((ParameterSamples<Matrix4D>*)sampleData[i])->currentValue);
		return matrix;
	case EULER_AND_TRANSLATION:
		eulerAndTranslation=new ParametrizedEulerAnglesAndTranslation;
		if(!eulerAndTranslation){return NULL;}
		eulerAndTranslation->value=&(((ParameterSamples<EulerAnglesAndTranslation>*)sampleData[i])->currentValue);
		return eulerAndTranslation;
	case CLOSEST_R_AND_TRANSLATION:
		rClosestAndTranslation=new ParametrizedClosestRotationAndTranslation;
		if(!rClosestAndTranslation){return NULL;}
		rClosestAndTranslation->value=&(((ParameterSamples<RotationAndTranslation>*)sampleData[i])->currentValue);
		return rClosestAndTranslation;
	case R_LOGARITHM_AND_TRANSLATION:
		rLogarithmAndTranslation=new ParametrizedRotationLogarithmAndTranslation;
		if(!rLogarithmAndTranslation){return NULL;}
		rLogarithmAndTranslation->value=&(((ParameterSamples<LogRotationAndTranslation>*)sampleData[i])->currentValue);
		return rLogarithmAndTranslation;
	case QUATERNION_AND_TRANSLATION:
		quaternionAndTranslation=new ParametrizedQuaternionAndTranslation;
		if(!quaternionAndTranslation){return NULL;}
		quaternionAndTranslation->value=&(((ParameterSamples<QuaternionAndTranslation>*)sampleData[i])->currentValue);
		return quaternionAndTranslation;
	}
	return NULL;
}

int RayKeyData::set(RayKeyFile& keyFile,int tp){
	int i,j;
	type=tp;
	sampleData=new VParameterSamples*[keyFile.parameters()];
	if(!sampleData){return 0;}
	pNum=keyFile.parameters();
	for(i=0;i<pNum;i++){sampleData[i]=NULL;}
	for(i=0;i<pNum;i++){
		switch(type){
		case MATRIX:
			sampleData[i]=new ParameterSamples<Matrix4D>();
			break;
		case EULER_AND_TRANSLATION:
			sampleData[i]=new ParameterSamples<EulerAnglesAndTranslation>();
			break;
		case CLOSEST_R_AND_TRANSLATION:
			sampleData[i]=new ParameterSamples<RotationAndTranslation>();
			break;
		case R_LOGARITHM_AND_TRANSLATION:
			sampleData[i]=new ParameterSamples<LogRotationAndTranslation>();
			break;
		case QUATERNION_AND_TRANSLATION:
			sampleData[i]=new ParameterSamples<QuaternionAndTranslation>();
			break;
		};
		if(!sampleData[i] || !sampleData[i]->set(keyFile.samples())){
			clear();
			return 0;
		}
		for(j=0;j<keyFile.samples();j++){
			switch(type){
			case MATRIX:
				((ParameterSamples<Matrix4D>*)sampleData[i])->samples[j]=keyFile[j][i];
				break;
			case EULER_AND_TRANSLATION:
				if(j){
					((ParameterSamples<EulerAnglesAndTranslation>*)sampleData[i])->samples[j]=
						EulerAnglesAndTranslation(keyFile[j][i],((ParameterSamples<EulerAnglesAndTranslation>*)sampleData[i])->samples[j-1]);
				}
				else{((ParameterSamples<EulerAnglesAndTranslation>*)sampleData[i])->samples[j]=keyFile[j][i];}
				break;
			case CLOSEST_R_AND_TRANSLATION:
				((ParameterSamples<RotationAndTranslation>*)sampleData[i])->samples[j]=keyFile[j][i];
				break;
			case R_LOGARITHM_AND_TRANSLATION:
				if(j){
					((ParameterSamples<LogRotationAndTranslation>*)sampleData[i])->samples[j]=
						LogRotationAndTranslation(keyFile[j][i],((ParameterSamples<LogRotationAndTranslation>*)sampleData[i])->samples[j-1]);
				}
				else{((ParameterSamples<LogRotationAndTranslation>*)sampleData[i])->samples[j]=keyFile[j][i];}
				break;
			case QUATERNION_AND_TRANSLATION:
				if(j){
					((ParameterSamples<QuaternionAndTranslation>*)sampleData[i])->samples[j]=
						QuaternionAndTranslation(keyFile[j][i],((ParameterSamples<QuaternionAndTranslation>*)sampleData[i])->samples[j-1]);
				}
				else{((ParameterSamples<QuaternionAndTranslation>*)sampleData[i])->samples[j]=keyFile[j][i];}
				break;
			};
		}
	}
	return 1;
}
