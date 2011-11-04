#include "lineSegments.h"
#include <math.h>

////////////////////////////
// Image processing stuff //
////////////////////////////
float OrientedLineSegment::length(void) const
{
	return 0;
}
float OrientedLineSegment::distance(const int& x,const int& y) const
{
	return 0;
}
void  OrientedLineSegment::getPerpendicular(float& x,float &y) const
{
	x=y=0;
}

void  OrientedLineSegment::GetSourcePosition(const OrientedLineSegment& source,const OrientedLineSegment& destination,
											 const int& targetX,const int& targetY,
											 float& sourceX,float& sourceY)
{
	sourceX=sourceY=0;
}
