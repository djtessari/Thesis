#ifndef LINE_SEGMENTS_INCLUDED
#define LINE_SEGMENTS_INCLUDED

#include <stdio.h>


/** This class represents an oriented line segment. */
class OrientedLineSegment{
public:

	/** The constants that define the weight of the contribution of a line segment to a particular point.*/
	static const float A,B,P;

	/** The coordinates of the end-points of the line segment.*/
	int x1,y1,x2,y2;

	OrientedLineSegment(void);

	/** This method reads in a line segment from a file. */
	int read(FILE* fp);

	/** Given a point at position (x,y), this method returns the weight of the line segment's contribution to the point.*/
	float getWeight(const int& x,const int& y) const;

	/** This static method blends between two sets line segments, using the value of blendWeight to specify the
	  * the ratio of the blend, and writes out the blended line segment into outSegment.
	  */
	static void Blend(const OrientedLineSegment& segment1,const OrientedLineSegment& segment2,const float& blendWeight,OrientedLineSegment& outSegment);

	////////////////////////
	// Unimplemented Code //
	////////////////////////
	/** This method returns the length of the line segment.*/
	float length(void) const;

	/** This method returns the (signed) distance of a point from the line segment/
	  */
	float distance(const int& x,const int& y) const;

	/** This method sets the values (x,y) to the coordinates of the unit-vector perpendicular to the direction
	  * of the line segment.
	  */
	void getPerpendicular(float& x,float& y) const;

	/** This static method sets the value of the source pixel position (sourceX,sourceY), given the destination
	  * pixel position and a pair of corresponding source and destination line segments/
	  */
	static void GetSourcePosition(const OrientedLineSegment& source,const OrientedLineSegment& destination,
		const int& destinationX,const int& destinationY,
		float& sourceX,float& sourceY);
};

/** This class represents an ordered list of corresponding line segment pairs. */
class OrientedLineSegmentPairs{
	int read(FILE* fp);
public:
	/** The number of line segment pairs.*/
	int count;
	/** An ordererd list of the corresponding line segment pairs.*/
	OrientedLineSegment *segments1,*segments2;

	OrientedLineSegmentPairs(void);
	~OrientedLineSegmentPairs(void);

	/** This method reads in the line segment pairs from a file.*/
	int read(const char* fileName);


	/** This method manages the memory allocation, allocating enough memory for the desired number of line segment pairs.*/
	int setCount(const int& count);

	/** This method sets the value of the source pixel position (sourceX,sourceY), given the destination
	  * pixel position. It computes the source position prescribed by each of the line segment pairs and
	  * sets the final source position as the weighted average.
	  */
	void getSourcePosition(const int& destinationX,const int& destinationY,float& sourceX,float& sourceY) const;

};
#endif // LINE_SEGMENTS_INCLUDED