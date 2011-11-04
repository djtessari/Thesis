#include "lineSegments.h"
#include <math.h>

/////////////////////////
// OrientedLineSegment //
/////////////////////////
const float OrientedLineSegment::A=1;
const float OrientedLineSegment::B=1;
const float OrientedLineSegment::P=1;

OrientedLineSegment::OrientedLineSegment(void){x1=x2=y1=y2=0;}

void OrientedLineSegment::Blend(const OrientedLineSegment& segments1,const OrientedLineSegment& segments2,const float& weight,OrientedLineSegment& outSegments){
	outSegments.x1=(int)(segments1.x1*(1.-weight)+segments2.x1*weight);
	outSegments.y1=(int)(segments1.y1*(1.-weight)+segments2.y1*weight);
	outSegments.x2=(int)(segments1.x2*(1.-weight)+segments2.x2*weight);
	outSegments.y2=(int)(segments1.y2*(1.-weight)+segments2.y2*weight);
}
int OrientedLineSegment::read(FILE* fp){
	if(fscanf(fp," %d %d %d %d ",&x1,&y1,&x2,&y2)==4){return 1;}
	else{return 0;}
}

float OrientedLineSegment::getWeight(const int& x,const int& y) const{
	return (float)pow(pow(length(),OrientedLineSegment::P)/(OrientedLineSegment::A+distance(x,y)),OrientedLineSegment::B);
}


//////////////////////////////
// OrientedLineSegmentPairs //
//////////////////////////////

OrientedLineSegmentPairs::OrientedLineSegmentPairs(void){
	count=0;
	segments1=segments2=NULL;
}
OrientedLineSegmentPairs::~OrientedLineSegmentPairs(void){setCount(0);}
int OrientedLineSegmentPairs::setCount(const int& cnt){
	if(count==cnt){return 1;}

	count=0;
	if(segments1){delete[] segments1;}
	if(segments2){delete[] segments2;}

	if(!cnt){return 1;}

	segments1=new OrientedLineSegment[cnt];
	if(!segments1){return 0;}
	segments2=new OrientedLineSegment[cnt];
	if(!segments2){
		delete[] segments1;
		return 0;
	}
	count=cnt;
	return 1;
}
int OrientedLineSegmentPairs::read(const char* fileName){
	int ret;
	FILE* fp=fopen(fileName,"r");
	if(!fp){return 0;}
	ret=read(fp);
	fclose(fp);
	return ret;
}
int OrientedLineSegmentPairs::read(FILE* fp){
	int c;

	if(!fscanf(fp," %d ",&c)){return 0;}
	if(!setCount(c)){return 0;}
	for(int i=0;i<count;i++){
		if(!segments1[i].read(fp) || !segments2[i].read(fp)){
			setCount(0);
			return 0;
		}
	}
	return 1;
}
void OrientedLineSegmentPairs::getSourcePosition(const int& targetX,const int& targetY,float& sourceX,float& sourceY) const{
	float dx,dy;
	float totalWeight=0;
	float weight;
	float totalDX=0;
	float totalDY=0;
	float x,y;

	for(int i=0;i<count;i++){
		// Compute the source position with respect to line i
		OrientedLineSegment::GetSourcePosition(segments1[i],segments2[i],targetX,targetY,x,y);
		// Compute the displacement
		dx=x-targetX;
		dy=y-targetY;
		weight=segments2[i].getWeight(targetX,targetY);
		totalDX+=dx*weight;
		totalDY+=dy*weight;
		totalWeight+=weight;
	}
	totalDX/=totalWeight;
	totalDY/=totalWeight;
	sourceX=totalDX+targetX;
	sourceY=totalDY+targetY;
}
