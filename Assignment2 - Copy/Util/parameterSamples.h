#ifndef PARAMETER_SAMPLES_INCLUDED 
#define PARAMETER_SAMPLES_INCLUDED

enum{
	LINEAR,
	CATMULL_ROM,
	UNIFORM_CUBIC_B_SPLINE
};
/** This abstract class represents a variable whose value is obtained by interpolating sample data. */
class VParameterSamples{
public:
	/** This virtual method initializes the array of data */
	virtual int set(int count)=0;
	/** This method updates the value of the in-between value, by computing the interpolation/approximation at value 0<=t<=1.
	  * The value type specifies how the interpolation/approximation is to be done.*/
	virtual void setCurrentValue(double t,int type=LINEAR)=0;
};
/** This template class stores an array of samples of a parameter. It is used for computing
  * the  in-between values using linear interpolation or spline methods.
  * In order to be used, the template class needs to support addition and right
  * multiplication by a number. */
template <class Vector>
class ParameterSamples : public VParameterSamples{
public:
	/** The sample values */
	Vector* samples;
	/** The number of samples */
	int count;
	/** The computed in-between value */
	Vector currentValue;

	ParameterSamples(void);
	~ParameterSamples(void);
	/** This method initializes the array of data*/
	int set(int count);
	/** This overloaded operator returns a reference to the i-th sample value */
	Vector& operator[] (int i);
	/** This method updates the value of the in-between value, by computing the interpolation/approximation at value 0<=t<=1.
	  * The value type specifies how the interpolation/approximation is to be done.*/
	void setCurrentValue(double t,int type=LINEAR);
};



template <class Vector>
ParameterSamples<Vector>::ParameterSamples(void){
	samples=NULL;
	count=0;
}
template <class Vector>
ParameterSamples<Vector>::~ParameterSamples(void){
	if(samples){delete[] samples;}
	samples=NULL;
	count=0;
}
template <class Vector>
int ParameterSamples<Vector>::set(int c){
	if(samples){delete[] samples;}
	samples=NULL;
	count=0;

	if(c<=0){return 1;}
	samples=new Vector[c];
	if(!samples){return 0;}
	count=c;
	return 1;
}

template <class Vector>
Vector& ParameterSamples<Vector>::operator [] (int i){return samples[i];}

#include "parameterSamples.todo.inl"

#endif //PARAMETER_SAMPLES_INCLUDED
